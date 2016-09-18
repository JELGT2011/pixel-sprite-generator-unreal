
#include <vector>
#include "mask.h"

Mask::Mask() : Mask({}, 0, 0, false, false) {}

Mask::Mask(const std::vector<int>& data,
           const int width,
           const int height,
           const bool mirrorX,
           const bool mirrorY) {
  this->data = data;
  this->width = width;
  this->height = height;
  this->mirrorX = mirrorX;
  this->mirrorY = mirrorY;
}

Mask::Mask(const Mask& mask) {
  this->width = mask.width;
  this->height = mask.height;
  this->mirrorX = mask.mirrorX;
  this->mirrorY = mask.mirrorY;
}
