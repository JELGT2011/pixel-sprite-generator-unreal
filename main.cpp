
#include <iostream>
#include <vector>
#include "mask.h"
#include "sprite.h"

int main(int argc, const char* argv[]) {

  // const int SPRITE_SCALE = 2;
  const int SPRITE_COUNT = 50;

  std::vector<int> data = {
      0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 1, 1,
      0, 0, 0, 0, 1,-1,
      0, 0, 0, 1, 1,-1,
      0, 0, 0, 1, 1,-1,
      0, 0, 1, 1, 1,-1,
      0, 1, 1, 1, 2, 2,
      0, 1, 1, 1, 2, 2,
      0, 1, 1, 1, 2, 2,
      0, 1, 1, 1, 1,-1,
      0, 0, 0, 1, 1, 1,
      0, 0, 0, 0, 0, 0
  };

  Mask mask = Mask(data, 6, 12, true, false);
  std::vector<Sprite> sprites = {};

  for (int i = 0; i < SPRITE_COUNT; i++) {
    Sprite sprite = Sprite(6, 12, mask, true, 0.3, 0.2, 0.3, 0.5, 0);
    sprites.insert(sprites.begin(), sprite);
    std::cout << sprite.ToString() << std::endl;
  }

  return 0;
}
