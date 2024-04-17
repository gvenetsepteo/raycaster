#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "../inc/raycaster.hpp"
#include "../lib/quickcg.h"



int main(int /*argc*/, char* /*argv*/[]) {
  RC::Map worldMap = RC::Map();
  Uint32 buffer[screenHeight][screenWidth];
  RC::Points p = RC::Points();
  RC::Texture tex = RC::Texture();

  // start the main loop
  while (!QuickCG::done()) {
    for (int x = 0; x < QuickCG::w; x++) {
      // calculate ray position and direction
      double cameraX =
          2 * x / (double)QuickCG::w - 1;  // x-coordinate in camera space
      double rayDirX = p.dirX + p.planeX * cameraX;
      double rayDirY = p.dirY + p.planeY * cameraX;

      // which box of the map we're in
      int mapX = int(p.posX);
      int mapY = int(p.posY);

      // length of ray from current position to next x or y-side
      double sideDistX;
      double sideDistY;

      // length of ray from one x or y-side to next x or y-side
      double deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1 / rayDirX);
      double deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1 / rayDirY);
      double perpWallDist;

      // what direction to step in x or y-direction (either +1 or -1)
      int stepX;
      int stepY;

      int hit = 0;  // was there a wall hit?
      int side;     // was a NS or a EW wall hit?

      // calculate step and initial sideDist
      if (rayDirX < 0) {
        stepX = -1;
        sideDistX = (p.posX - mapX) * deltaDistX;
      } else {
        stepX = 1;
        sideDistX = (mapX + 1.0 - p.posX) * deltaDistX;
      }
      if (rayDirY < 0) {
        stepY = -1;
        sideDistY = (p.posY - mapY) * deltaDistY;
      } else {
        stepY = 1;
        sideDistY = (mapY + 1.0 - p.posY) * deltaDistY;
      }
      // perform DDA
      while (hit == 0) {
        // jump to next map square, either in x-direction, or in y-direction
        if (sideDistX < sideDistY) {
          sideDistX += deltaDistX;
          mapX += stepX;
          side = 0;
        } else {
          sideDistY += deltaDistY;
          mapY += stepY;
          side = 1;
        }
        // Check if ray has hit a wall
        if (worldMap.def[mapX][mapY] > 0) hit = 1;
      }

      // Calculate distance of perpendicular ray (Euclidean distance would give
      // fisheye effect!)
      if (side == 0)
        perpWallDist = (sideDistX - deltaDistX);
      else
        perpWallDist = (sideDistY - deltaDistY);

      // Calculate height of line to draw on screen
      int lineHeight = (int)(QuickCG::h / perpWallDist);

      int pitch = 100;

      // calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + QuickCG::h / 2 + pitch;
      if (drawStart < 0) drawStart = 0;
      int drawEnd = lineHeight / 2 + QuickCG::h / 2 + pitch;
      if (drawEnd >= QuickCG::h) drawEnd = QuickCG::h - 1;

      // texturing calculations
      int texNum = worldMap.def[mapX][mapY] -
                   1;  // 1 subtracted from it so that texture 0 can be used!

      // calculate value of wallX
      double wallX;  // where exactly the wall was hit
      if (side == 0)
        wallX = p.posY + perpWallDist * rayDirY;
      else
        wallX = p.posX + perpWallDist * rayDirX;
      wallX -= floor((wallX));

      // x coordinate on the texture
      int texX = int(wallX * double(texWidth));
      if (side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
      if (side == 1 && rayDirY < 0) texX = texWidth - texX - 1;

      // TODO: an integer-only bresenham or DDA like algorithm could make the
      // texture coordinate stepping faster How much to increase the texture
      // coordinate per screen pixel
      double step = 1.0 * texHeight / lineHeight;
      // Starting texture coordinate
      double texPos =
          (drawStart - pitch - QuickCG::h / 2 + lineHeight / 2) * step;
      for (int y = drawStart; y < drawEnd; y++) {
        // Cast the texture coordinate to integer, and mask with (texHeight - 1)
        // in case of overflow
        int texY = (int)texPos & (texHeight - 1);
        texPos += step;
        Uint32 color = tex.texture[texNum][texHeight * texY + texX];
        // make color darker for y-sides: R, G and B byte each divided through
        // two with a "shift" and an "and"
        if (side == 1) color = (color >> 1) & 8355711;
        buffer[y][x] = color;
      }
    }

    QuickCG::drawBuffer(buffer[0]);
    for (int y = 0; y < QuickCG::h; y++)
      for (int x = 0; x < QuickCG::w; x++)
        buffer[y][x] = 0;  // clear the buffer instead of cls()
    // timing for input and FPS counter
    p.oldTime = p.time;
    p.time = QuickCG::getTicks();
    double frameTime =
        (p.time - p.oldTime) /
        1000.0;  // frametime is the time this frame has taken, in seconds
    QuickCG::print(1.0 / frameTime);  // FPS counter
    QuickCG::redraw();

    // speed modifiers
    double moveSpeed =
        frameTime * 5.0;  // the constant value is in squares/second
    double rotSpeed =
        frameTime * 3.0;  // the constant value is in radians/second

    QuickCG::readKeys();
    // move forward if no wall in front of you
    if (QuickCG::keyDown(SDLK_z)) {
      if (worldMap.def[int(p.posX + p.dirX * moveSpeed)][int(p.posY)] == false)
        p.posX += p.dirX * moveSpeed;
      if (worldMap.def[int(p.posX)][int(p.posY + p.dirY * moveSpeed)] == false)
        p.posY += p.dirY * moveSpeed;
    }
    // move backwards if no wall behind you
    if (QuickCG::keyDown(SDLK_s)) {
      if (worldMap.def[int(p.posX - p.dirX * moveSpeed)][int(p.posY)] == false)
        p.posX -= p.dirX * moveSpeed;
      if (worldMap.def[int(p.posX)][int(p.posY - p.dirY * moveSpeed)] == false)
        p.posY -= p.dirY * moveSpeed;
    }
    // move to the right
    if (QuickCG::keyDown(SDLK_d)) {
      if (worldMap.def[int(p.posX + p.dirY * moveSpeed)][int(p.posY)] == false)
        p.posX += p.dirY * moveSpeed;
      if (worldMap.def[int(p.posX)][int(p.posY - p.dirX * moveSpeed)] == false)
        p.posY -= p.dirX * moveSpeed;
    }
    // move to the left
    if (QuickCG::keyDown(SDLK_q)) {
      if (worldMap.def[int(p.posX - p.dirY * moveSpeed)][int(p.posY)] == false)
        p.posX -= p.dirY * moveSpeed;
      if (worldMap.def[int(p.posX)][int(p.posY + p.dirX * moveSpeed)] == false)
        p.posY += p.dirX * moveSpeed;
    }
    // rotate to the right
    if (QuickCG::keyDown(SDLK_RIGHT)) {
      // both camera p.direction and camera plane must be rotated
      double oldDirY = p.dirX;
      p.dirX = p.dirX * cos(-rotSpeed) - p.dirY * sin(-rotSpeed);
      p.dirY = oldDirY * sin(-rotSpeed) + p.dirY * cos(-rotSpeed);
      double oldPlaneX = p.planeX;
      p.planeX = p.planeX * cos(-rotSpeed) - p.planeY * sin(-rotSpeed);
      p.planeY = oldPlaneX * sin(-rotSpeed) + p.planeY * cos(-rotSpeed);
    }
    // rotate to the left
    if (QuickCG::keyDown(SDLK_LEFT)) {
      // both camera direction and camera plane must be rotated
      double oldDirX = p.dirX;
      p.dirX = p.dirX * cos(rotSpeed) - p.dirY * sin(rotSpeed);
      p.dirY = oldDirX * sin(rotSpeed) + p.dirY * cos(rotSpeed);
      double oldPlaneX = p.planeX;
      p.planeX = p.planeX * cos(rotSpeed) - p.planeY * sin(rotSpeed);
      p.planeY = oldPlaneX * sin(rotSpeed) + p.planeY * cos(rotSpeed);
    }

    if (QuickCG::keyDown(SDLK_ESCAPE)) {
      break;
    }
  }
}
