
#ifndef MASK_H_
#define MASK_H_

#include <vector>

/**
 *   The Mask class defines a 2D template form which sprites can be generated.
 *
 *   @class Mask
 *   @constructor
 *   @param {data} Integer array describing which parts of the sprite should be
 *   empty, body, and border. The mask only defines a semi-ridgid stucture
 *   which might not strictly be followed based on randomly generated numbers.
 *
 *      -1 = Always border (black)
 *       0 = Empty
 *       1 = Randomly chosen Empty/Body
 *       2 = Randomly chosen Border/Body
 *
 *   @param {width} Width of the mask data array
 *   @param {height} Height of the mask data array
 *   @param {mirrorX} A boolean describing whether the mask should be mirrored on the x axis
 *   @param {mirrorY} A boolean describing whether the mask should be mirrored on the y axis
 */
class Mask {
 public:
  std::vector<int> data;
  int width;
  int height;
  bool mirrorX;
  bool mirrorY;

  Mask();

  Mask(const std::vector<int>& data,
       const int width,
       const int height,
       const bool mirrorX,
       const bool mirrorY);

  Mask(const Mask& mask);
};

#endif
