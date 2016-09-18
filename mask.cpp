
#include <iostream>
#include <vector>
#include "Mask.h"

Mask::Mask()
 : Mask(
    std::vector<int>{},
    0,
    0,
    false,
    false
  ) {};

Mask::Mask(
  const std::vector<int>& data,
  const int width,
  const int height,
  const bool mirrorX,
  const bool mirrorY
) {
  this->data = data;
  this->width = width;
  this->height = height;
  this->mirrorX = mirrorX;
  this->mirrorY = mirrorY;
};
