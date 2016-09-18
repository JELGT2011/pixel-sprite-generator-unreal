
#ifndef SPRITE_H_
#define SPRITE_H_

#include <vector>
#include "mask.h"

/**
 * The Sprite class makes use of a Mask instance to generate a 2D sprite on a
 * HTML canvas.
 * <p>
 * var options = {
 * colored         : true,   // boolean
 * edgeBrightness  : 0.3,    // value from 0 to 1
 * colorVariations : 0.2,    // value from 0 to 1
 * brightnessNoise : 0.3,    // value from 0 to 1
 * saturation      : 0.5     // value from 0 to 1
 * }
 *
 * @param {mask}
 * @param {options}
 * @class Sprite
 * @constructor
 */
class Sprite {
 public:
  int width;
  int height;
  Mask mask;
  std::vector<int> data;
  bool colored;
  double edgeBrightness;
  double colorVariations;
  double brightnessNoise;
  double saturation;
  int seed;

  Sprite();

  Sprite(const int width,
         const int height,
         const Mask& mask,
         const bool colored,
         const double edgeBrightness,
         const double colorVariations,
         const double brightnessNoise,
         const double saturation,
         const int seed);

  /**
   * The initData method initializes the sprite data to completely solid.
   *
   * @method InitData
   * @returns {undefined}
   */
  void InitData();

  /**
   * The getData method returns the sprite template data at location (x, y)
   * <p>
   * -1 = Always border (black)
   * 0 = Empty
   * 1 = Randomly chosen Empty/Body
   * 2 = Randomly chosen Border/Body
   *
   * @param {x}
   * @param {y}
   * @method GetData
   * @returns {undefined}
   */
  int GetData(const int x, const int y);

  /**
   * The setData method sets the sprite template data at location (x, y)
   * <p>
   * -1 = Always border (black)
   * 0 = Empty
   * 1 = Randomly chosen Empty/Body
   * 2 = Randomly chosen Border/Body
   *
   * @param {x}
   * @param {y}
   * @param {value}
   * @method SetData
   * @returns {undefined}
   */
  void SetData(const int x, const int y, const int value);

  /**
   * The mirrorX method mirrors the template data horizontally.
   *
   * @method MirrorX
   * @returns {undefined}
   */
  void MirrorX();

  /**
   * The mirrorY method mirrors the template data vertically.
   *
   * @method MirrorY
   * @returns {undefined}
   */
  void MirrorY();

  /**
   * The applyMask method copies the mask data into the template data array at
   * location (0, 0).
   * <p>
   * (note: the mask may be smaller than the template data array)
   *
   * @method ApplyMask
   * @returns {undefined}
   */
  void ApplyMask();

  /**
   * Apply a random sample to the sprite template.
   * <p>
   * If the template contains a 1 (internal body part) at location (x, y), then
   * there is a 50% chance it will be turned empty. If there is a 2, then there
   * is a 50% chance it will be turned into a body or border.
   * <p>
   * (feel free to play with this logic for interesting results)
   *
   * @method GenerateRandomSample
   * @returns {undefined}
   */
  void GenerateRandomSample();

  /**
   * This method applies edges to any template location that is positive in
   * value and is surrounded by empty (0) pixels.
   *
   * @method GenerateEdges
   * @returns {undefined}
   */
  void GenerateEdges();

  /**
   * This method converts HSL color values to RGB color values.
   *
   * @param {h}
   * @param {s}
   * @param {l}
   * @param {result}
   * @method HSLToRGB
   * @returns {result}
   */
  std::vector<double> HSLToRGB(const double h,
                               const double s,
                               const double l);

  /**
   * This method renders out the template data to a HTML canvas to finally
   * create the sprite.
   * <p>
   * (note: only template locations with the values of -1 (border) are rendered)
   *
   * @method RenderPixelData
   * @returns {undefined}
   */
   std::vector<int> RenderPixelData();

   std::string ToString();
};

inline
int Sprite::GetData(const int x, const int y) {
  return this->data[y * this->width + x];
}

inline
void Sprite::SetData(const int x, const int y, const int value) {
  this->data[y * this->width + x] = value;
}

#endif
