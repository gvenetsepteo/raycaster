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

struct Points {
  double posX, posY;  // x and y start position
  double dirX, dirY;  // initial direction vector
  double planeX,
      planeY;  // the 2d raycaster version of camera plane

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
}

struct RayDir {
  double x;
  double y;
}

struct Map {
  int def[mapWidth][mapHeight];

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
};

struct Texture {
  std::vector<Uint32> texture[8];

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
};

}  // namespace RC
#endif