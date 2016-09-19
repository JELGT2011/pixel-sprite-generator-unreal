
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include "sprite.h"
#include "mask.h"

double SeededDouble() {
  return rand() % 100 / 100.0;
}

bool SeededBool() {
  return rand() % 2 == 0;
}

Sprite::Sprite() : Sprite(6, 12, Mask(), true, 0.3, 0.2, 0.3, 0.5, 0) {}

Sprite::Sprite(const int width,
               const int height,
               const Mask& mask,
               const bool colored,
               const double edgeBrightness,
               const double colorVariations,
               const double brightnessNoise,
               const double saturation,
               const int seed) {
  this->mask = mask;
  this->width = mask.width * (mask.mirrorX ? 2 : 1);
  this->height = mask.height * (mask.mirrorY ? 2 : 1);
  this->data = std::vector<int>(this->width * this->height);
  this->colored = colored;
  this->edgeBrightness = edgeBrightness;
  this->colorVariations = colorVariations;
  this->brightnessNoise = brightnessNoise;
  this->saturation = saturation;
  this->seed = seed;

  this->InitData();
  this->ApplyMask();
  this->GenerateRandomSample();
  if (this->mask.mirrorX) {
    this->MirrorX();
  }
  if (this->mask.mirrorY) {
    this->MirrorY();
  }
  this->GenerateEdges();
}

void Sprite::InitData() {
  int height = this->height;
  int width = this->width;
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      this->SetData(x, y, -1);
    }
  }
}

void Sprite::MirrorX() {
  int height = this->height;
  int width = this->width;
  int mirroredWidth = (int)floor(width / 2.0);
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < mirroredWidth; x++) {
      this->SetData(width - x - 1, y, this->GetData(x, y));
    }
  }
}

void Sprite::MirrorY() {
  int height = this->height;
  int width = this->width;
  int mirroredHeight = (int)floor(height / 2.0);
  for (int y = 0; y < mirroredHeight; y++) {
    for (int x = 0; x < width; x++) {
      this->SetData(x, height - y - 1, this->GetData(x, y));
    }
  }
}

void Sprite::ApplyMask() {
  int maskHeight = this->mask.height;
  int maskWidth = this->mask.width;
  for (int y = 0; y < maskHeight; y++) {
    for (int x = 0; x < maskWidth; x++) {
      this->SetData(x, y, this->mask.data[y * maskWidth + x]);
    }
  }
}

void Sprite::GenerateRandomSample() {
  std::srand(this->seed);
  int height = this->height;
  int width = this->width;
  int val;
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      val = this->GetData(x, y);
      switch (val) {
      case 1:
        val = SeededBool();
        break;
      case 2:
        val = SeededBool() ? 1 : -1;
        break;
      default:
        val = 0;
        break;
      }
      this->SetData(x, y, val);
    }
  }
}

void Sprite::GenerateEdges() {
  int height = this->height;
  int width = this->width;
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      if (this->GetData(x, y) <= 0) {
        continue;
      }
      if (y - 1 >= 0 && this->GetData(x, y - 1) == 0) {
        this->SetData(x, y - 1, -1);
      }
      if (y + 1 < height && this->GetData(x, y + 1) == 0) {
        this->SetData(x, y + 1, -1);
      }
      if (x - 1 >= 0 && this->GetData(x - 1, y) == 0) {
        this->SetData(x - 1, y, -1);
      }
      if (x + 1 < width && this->GetData(x +1, y) == 0) {
        this->SetData(x + 1, y, -1);
      }
    }
  }
}

std::vector<double> Sprite::HSLToRGB(const double h,
                                     const double s,
                                     const double l) {
  double f, p, q, t;
  int i = (int)floor(h * 6.0);

  f = h * 6 - i;
  p = l * (1 - s);
  q = l * (1 - f * s);
  t = l * (1 - (1 - f) * s);

  switch (i % 6) {
    case 0: return { l, t, p };
    case 1: return { q, l, p };
    case 2: return { p, l, t };
    case 3: return { p, q, l };
    case 4: return { t, p, l };
    case 5: return { l, p, q };
    default: return {};
  };
}

std::vector<int> Sprite::RenderPixelData() {
  bool isVerticalGradient = SeededBool();
  double saturation = fmax(fmin(SeededDouble() * this->saturation, 1.0), 0.0);
  double hue = SeededDouble();
  std::vector<int> pixels = std::vector<int>(this->height * this->width * 4);
  int ulen, vlen;

  if (isVerticalGradient) {
    ulen = this->height;
    vlen = this->width;
  } else {
    ulen = this->width;
    vlen = this->height;
  }

  for (int u = 0; u < ulen; u++) {
    double isNewColor = fabs(((SeededDouble() * 2 - 1) +
                              (SeededDouble() * 2 - 1) +
                              (SeededDouble() * 2 - 1) / 3.0));
    if (isNewColor > (1.0 - this->colorVariations)) {
      hue = SeededDouble();
    }

    for (int v = 0; v < vlen; v++) {
      int val, index;
      if (isVerticalGradient) {
        val = this->GetData(v, u);
        index = (u * vlen + v) * 4;
      } else {
        val = this->GetData(u, v);
        index = (v * ulen + u) * 4;
      }
      std::vector<double> rgb = { 1, 1, 1 };

      if (val != 0) {
        if (this->colored) {
          double brightness = sin(((double)u / (double)ulen) * M_PI)
                            * (1 - this->brightnessNoise) + SeededDouble()
                            * this->brightnessNoise;
          rgb = this->HSLToRGB(hue, saturation, brightness);
          if (val == -1) {
            rgb[0] *= this->edgeBrightness;
            rgb[1] *= this->edgeBrightness;
            rgb[2] *= this->edgeBrightness;
          }
        } else {
          if (val == -1) {
            rgb = { 0, 0, 0 };
          }
        }
      }
      pixels[index + 0] = (int)(rgb[0] * 255);
      pixels[index + 1] = (int)(rgb[1] * 255);
      pixels[index + 2] = (int)(rgb[2] * 255);
      if (val != 0) {
        pixels[index + 3] = 255;
      } else {
        pixels[index + 3] = 0;
      }
    }
  }

  return pixels;
}

std::string Sprite::ToString() {
  int height = this->height;
  int width = this->width;
  int val;
  std::string s = "";
  std::vector<int> pixels = this->RenderPixelData();
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      val = pixels[y * this->width + x];
      s += val >= 0 ? " " + std::to_string(val) : "" + std::to_string(val);
    }
    s += "\n";
  }
  return s;
}
