#ifndef HOOKS_HPP
#define HOOKS_HPP

#include <vector>

#include "../lib/quickcg.h"

namespace RC {

#define USE_TEXTURES 0
#define USE_COLORS 1

#define screenWidth 1280
#define screenHeight 960
#define texWidth 64
#define texHeight 64
#define mapWidth 24
#define mapHeight 24

struct Speed {
  double moveSpeed;
  double rotSpeed;
};

struct Buffer {
  Uint32 buffer[screenHeight][screenWidth];

  void drawBuffer() {
    QuickCG::drawBuffer(buffer[0]);
    for (int y = 0; y < QuickCG::h; y++)
      for (int x = 0; x < QuickCG::w; x++)
        buffer[y][x] = 0;  // clear the buffer instead of cls()
  }
};

struct Points {
  double posX, posY;      // x and y start position
  double dirX, dirY;      // initial direction vector
  double planeX, planeY;  // the 2d raycaster version of camera plane

  double time;     // time of current frame
  double oldTime;  // time of previous frame

  Points() {
    posX = 22.0;
    posY = 11.5;
    dirX = -1.0;
    dirY = 0.0;
    planeX = 0.0;
    planeY = 0.66;
    time = 0;
    oldTime = 0;
  }
};

struct Camera {
  double x;
};

struct Map {
  int def[mapWidth][mapHeight];
  int x;
  int y;

  int init[mapWidth][mapHeight] = {
      {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7, 7, 7, 7, 7, 7, 7, 7},
      {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7},
      {4, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
      {4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
      {4, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7},
      {4, 0, 4, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 0, 7, 7, 7, 7, 7},
      {4, 0, 5, 0, 0, 0, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 7, 0, 0, 0, 7, 7, 7, 1},
      {4, 0, 6, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 0, 0, 0, 8},
      {4, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 1},
      {4, 0, 8, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 0, 0, 0, 8},
      {4, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 7, 7, 7, 1},
      {4, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 0, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 1},
      {6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
      {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
      {6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
      {4, 4, 4, 4, 4, 4, 0, 4, 4, 4, 6, 0, 6, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3},
      {4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2},
      {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 2, 0, 0, 5, 0, 0, 2, 0, 0, 0, 2},
      {4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2},
      {4, 0, 6, 0, 6, 0, 0, 0, 0, 4, 6, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 2},
      {4, 0, 0, 5, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2},
      {4, 0, 6, 0, 6, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 5, 0, 0, 2, 0, 0, 0, 2},
      {4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2},
      {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3}};

  Map() {
    for (int i = 0; i < mapWidth; ++i) {
      for (int j = 0; j < mapHeight; ++j) {
        def[i][j] = init[i][j];
      }
    }
  }

  // which box of the map we're in
  void calculateMapBox(Points &p) {
    x = int(p.posX);
    y = int(p.posY);
  }
};

struct Ray {
  double rayDirX;
  double rayDirY;
  double sideDistX;
  double sideDistY;
  double deltaDistX;
  double deltaDistY;

  // what direction to step in x or y-direction (either +1 or -1)
  int stepX;
  int stepY;

  void calcRayPos(Camera &c, Points &p, int x) {
    // calculate ray position and direction
    c.x = 2 * x / (double)QuickCG::w - 1;  // x-coordinate in c space
    rayDirX = p.dirX + p.planeX * c.x;
    rayDirY = p.dirY + p.planeY * c.x;
    // length of ray from one x or y-side to next x or y-side
    deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1 / rayDirX);
    deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1 / rayDirY);
  }

  void calculateStep(Points &p, Map &map) {
    // calculate step and initial sideDist
    if (rayDirX < 0) {
      stepX = -1;
      sideDistX = (p.posX - map.x) * deltaDistX;
    } else {
      stepX = 1;
      sideDistX = (map.x + 1.0 - p.posX) * deltaDistX;
    }
    if (rayDirY < 0) {
      stepY = -1;
      sideDistY = (p.posY - map.y) * deltaDistY;
    } else {
      stepY = 1;
      sideDistY = (map.y + 1.0 - p.posY) * deltaDistY;
    }
  }
};

struct DDA {
  int hit;
  int side;
  double perpWallDist;

  DDA() { hit = 0; }

  void performDDA(Ray &r, Map &map) {
    hit = 0;
    while (hit == 0) {
      // jump to next map square, either in x-direction, or in y-direction
      if (r.sideDistX < r.sideDistY) {
        r.sideDistX += r.deltaDistX;
        map.x += r.stepX;
        side = 0;
      } else {
        r.sideDistY += r.deltaDistY;
        map.y += r.stepY;
        side = 1;
      }
      // Check if ray has hit a wall
      if (map.def[map.x][map.y] > 0) hit = 1;
    }

    // Calculate distance of perpendicular ray (Euclidean distance would give
    // fisheye effect!)
    if (side == 0)
      perpWallDist = (r.sideDistX - r.deltaDistX);
    else
      perpWallDist = (r.sideDistY - r.deltaDistY);
  }
};

struct Wall {
  int lineHeight;
  int pitch;
  int drawStart;
  int drawEnd;
  double wallX;  // where exactly the wall was hit

  Wall() {}

  void calculateWallX(Points &p, DDA &d, Ray &r) {
    // calculate value of wallX
    if (d.side == 0)
      wallX = p.posY + d.perpWallDist * r.rayDirY;
    else
      wallX = p.posX + d.perpWallDist * r.rayDirX;
    wallX -= floor((wallX));
  }

  void calculateWallDraws(DDA &d) {
    lineHeight = (int)(QuickCG::h / d.perpWallDist);
    pitch = 100;
    // calculate lowest and highest pixel to fill in current stripe
    drawStart = -lineHeight / 2 + QuickCG::h / 2 + pitch;
    if (drawStart < 0) drawStart = 0;
    drawEnd = lineHeight / 2 + QuickCG::h / 2 + pitch;
    if (drawEnd >= QuickCG::h) drawEnd = QuickCG::h - 1;
  }
};

struct Texture {
  std::vector<Uint32> texture[8];
  int texNum;
  int tX;
  int tY;
  double step;
  double tPos;

  Texture() {
    for (int i = 0; i < 8; i++) texture[i].resize(texWidth * texHeight);
    QuickCG::screen(screenWidth, screenHeight, 0, "Raycaster");

    int mode = USE_TEXTURES;
    if (mode) {
      for (int x = 0; x < texWidth; x++)
        for (int y = 0; y < texHeight; y++) {
          int xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
          // int xcolor = x * 256 / texWidth;
          int ycolor = y * 256 / texHeight;
          int xycolor = y * 128 / texHeight + x * 128 / texWidth;
          texture[0][texWidth * y + x] =
              65536 * 254 *
              (x != y &&
               x != texWidth - y);  // flat red texture with black cross
          texture[1][texWidth * y + x] =
              xycolor + 256 * xycolor + 65536 * xycolor;  // sloped greyscale
          texture[2][texWidth * y + x] =
              256 * xycolor + 65536 * xycolor;  // sloped yellow gradient
          texture[3][texWidth * y + x] =
              xorcolor + 256 * xorcolor + 65536 * xorcolor;  // xor greyscale
          texture[4][texWidth * y + x] = 256 * xorcolor;     // xor green
          texture[5][texWidth * y + x] =
              65536 * 192 * (x % 16 && y % 16);           // red bricks
          texture[6][texWidth * y + x] = 65536 * ycolor;  // red gradient
          texture[7][texWidth * y + x] =
              128 + 256 * 128 + 65536 * 128;  // flat grey texture
        }
    } else {
      // generate some textures
      unsigned long tw, th;
      QuickCG::loadImage(texture[0], tw, th, "textures/eagle.png");
      QuickCG::loadImage(texture[1], tw, th, "textures/redbrick.png");
      QuickCG::loadImage(texture[2], tw, th, "textures/purplestone.png");
      QuickCG::loadImage(texture[3], tw, th, "textures/greystone.png");
      QuickCG::loadImage(texture[4], tw, th, "textures/bluestone.png");
      QuickCG::loadImage(texture[5], tw, th, "textures/mossy.png");
      QuickCG::loadImage(texture[6], tw, th, "textures/wood.png");
      QuickCG::loadImage(texture[7], tw, th, "textures/colorstone.png");
    }
  }

  void calcTexture(Wall &w, Ray &r, DDA &d, Buffer &b, int index, Map &map) {
    // texturing calculations
    texNum = map.def[map.x][map.y] - 1;
    // 1 subtracted from it so that texture 0 can be used!

    // x coordinate on the texture
    tX = int(w.wallX * double(texWidth));
    if (d.side == 0 && r.rayDirX > 0) tX = texWidth - tX - 1;
    if (d.side == 1 && r.rayDirY < 0) tX = texWidth - tX - 1;

    // coordinate per screen pixel
    step = 1.0 * texHeight / w.lineHeight;
    // Starting texture coordinate
    tPos = (w.drawStart - w.pitch - QuickCG::h / 2 + w.lineHeight / 2) * step;
    for (int y = w.drawStart; y < w.drawEnd; y++) {
      // Cast the texture coordinate to integer, and mask with (texHeight - 1)
      // in case of overflow
      tY = (int)tPos & (texHeight - 1);
      tPos += step;
      Uint32 color = texture[texNum][texHeight * tY + tX];
      // make color darker for y-sides: R, G and B byte each divided through
      // two with a "shift" and an "and"
      if (d.side == 1) color = (color >> 1) & 8355711;
      b.buffer[y][index] = color;
    }
  }

};

struct Hooks {
  int hooks(Map &map, Points &p, Speed &s) {
    if (QuickCG::keyDown(SDLK_z)) {
      if (map.def[int(p.posX + p.dirX * s.moveSpeed)][int(p.posY)] == false)
        p.posX += p.dirX * s.moveSpeed;
      if (map.def[int(p.posX)][int(p.posY + p.dirY * s.moveSpeed)] == false)
        p.posY += p.dirY * s.moveSpeed;
    }
    // move backwards if no wall behind you
    if (QuickCG::keyDown(SDLK_s)) {
      if (map.def[int(p.posX - p.dirX * s.moveSpeed)][int(p.posY)] == false)
        p.posX -= p.dirX * s.moveSpeed;
      if (map.def[int(p.posX)][int(p.posY - p.dirY * s.moveSpeed)] == false)
        p.posY -= p.dirY * s.moveSpeed;
    }
    // move to the right
    if (QuickCG::keyDown(SDLK_d)) {
      if (map.def[int(p.posX + p.dirY * s.moveSpeed)][int(p.posY)] == false)
        p.posX += p.dirY * s.moveSpeed;
      if (map.def[int(p.posX)][int(p.posY - p.dirX * s.moveSpeed)] == false)
        p.posY -= p.dirX * s.moveSpeed;
    }
    // move to the left
    if (QuickCG::keyDown(SDLK_q)) {
      if (map.def[int(p.posX - p.dirY * s.moveSpeed)][int(p.posY)] == false)
        p.posX -= p.dirY * s.moveSpeed;
      if (map.def[int(p.posX)][int(p.posY + p.dirX * s.moveSpeed)] == false)
        p.posY += p.dirX * s.moveSpeed;
    }
    // rotate to the right
    if (QuickCG::keyDown(SDLK_RIGHT)) {
      // both camera p.direction and camera plane must be rotated
      double oldDirY = p.dirX;
      p.dirX = p.dirX * cos(-s.rotSpeed) - p.dirY * sin(-s.rotSpeed);
      p.dirY = oldDirY * sin(-s.rotSpeed) + p.dirY * cos(-s.rotSpeed);
      double oldPlaneX = p.planeX;
      p.planeX = p.planeX * cos(-s.rotSpeed) - p.planeY * sin(-s.rotSpeed);
      p.planeY = oldPlaneX * sin(-s.rotSpeed) + p.planeY * cos(-s.rotSpeed);
    }
    // rotate to the left
    if (QuickCG::keyDown(SDLK_LEFT)) {
      // both camera direction and camera plane must be rotated
      double oldDirX = p.dirX;
      p.dirX = p.dirX * cos(s.rotSpeed) - p.dirY * sin(s.rotSpeed);
      p.dirY = oldDirX * sin(s.rotSpeed) + p.dirY * cos(s.rotSpeed);
      double oldPlaneX = p.planeX;
      p.planeX = p.planeX * cos(s.rotSpeed) - p.planeY * sin(s.rotSpeed);
      p.planeY = oldPlaneX * sin(s.rotSpeed) + p.planeY * cos(s.rotSpeed);
    }

    if (QuickCG::keyDown(SDLK_ESCAPE)) {
      return 1;
    } else {
      return 0;
    }
  }
};

struct Frame {
  long count = 0;
  double frameTime = 0;

  void frames(Points &p) {
    count++;
    p.oldTime = p.time;
    p.time = QuickCG::getTicks();
    if (count % 50 == 0) {
      frameTime =
          (p.time - p.oldTime) /
          1000.0;  // frametime is the time this frame has taken, in seconds
    }
    QuickCG::print(int(1.0 / frameTime));  // FPS counter
    QuickCG::redraw();
  }

  void speedModifier(Speed &s) {
    s.moveSpeed = frameTime * 5.0;  // the constant value is in squares/second
    s.rotSpeed = frameTime * 3.0;   // the constant value is in radians/second
  }
};

}  // namespace RC
#endif