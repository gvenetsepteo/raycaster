#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "../inc/raycaster.hpp"
#include "../lib/quickcg.h"



int main(int /*argc*/, char* /*argv*/[]) {
  RC::Map map = RC::Map();
  // Uint32 buffer[screenHeight][screenWidth];
  RC::Points pts = RC::Points();
  RC::Texture tex = RC::Texture();
  RC::Camera cam = RC::Camera();
  RC::Ray ray = RC::Ray();
  RC::Hooks hooks = RC::Hooks();
  RC::Speed spd = RC::Speed();
  RC::Frame frame = RC::Frame();
  RC::Wall wall = RC::Wall();
  RC::DDA dda = RC::DDA();
  RC::Buffer buff = RC::Buffer();

  // start the main loop
  while (!QuickCG::done()) {
    for (int x = 0; x < QuickCG::w; x++) {
      ray.calcRayPos(cam,pts, x);
      map.calculateMapBox(pts);
      ray.calculateStep(pts, map);

      dda.performDDA(ray, map);

      wall.calculateWallDraws(dda);
      wall.calculateWallX(pts,dda,ray);

      tex.calcTexture(wall, ray, dda, buff, x, map);
    }
    buff.drawBuffer();

    frame.frames(pts);
    frame.speedModifier(spd);

    if (hooks.hooks(map, pts, spd)) {
      break;
    }
  }
}
