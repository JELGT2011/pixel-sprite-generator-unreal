
#include <math.h>
#include <iostream>
#include <string>
#include <vector>
#include "Sprite.h"
#include "Mask.h"

Sprite::Sprite()
 : Sprite(
    0,
    0,
    Mask(),
    true,
    0.3,
    0.2,
    0.3,
    0.5,
    0
  ) {};

Sprite::Sprite(
  const int width,
  const int height,
  const Mask& Mask,
  const bool colored,
  const double edgeBrightness,
  const double colorVariations,
  const double brightnessNoise,
  const double saturation,
  const int seed
) {
  this->mask = mask;
  this->width = mask.width * (mask.mirrorX ? 2 : 1);
  this->height = mask.height * (mask.mirrorY ? 2 : 1);
  this->data = std::vector<int>{};
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
};

int Sprite::GetData(const int x, const int y) {
  return this->data[y * this->width + x];
}

void Sprite::SetData(const int x, const int y, const int value) {
  this->data[y * this->width + x] = value;
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
    for (int x = 0; maskWidth; x++) {
      this->SetData(x, y, this->mask.data[y * maskWidth + x]);
    }
  }
}

void Sprite::GenerateRandomSample() {}

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

std::vector<double> Sprite::HSLToRGB(
  const double h,
  const double s,
  const double l
) {
  double f, p, q, t;
  int i = (int)floor(h * 6.0);

  f = h * 6 - i;
  p = l * (1 - s);
  q = l * (1 - f * s);
  t = l * (1 - (1 - f) * s);

  switch (i % 6) {
    case 0: return std::vector<double>{ l, t, p };
    case 1: return std::vector<double>{ q, l, p };
    case 2: return std::vector<double>{ p, l, t };
    case 3: return std::vector<double>{ p, q, l };
    case 4: return std::vector<double>{ t, p, l };
    case 5: return std::vector<double>{ l, p, q };
    default: return std::vector<double>{};
  };
}

std::vector<int> Sprite::RenderPixelData() {
  return std::vector<int>{};
}

std::string Sprite::ToString() {
  int height = this->height;
  int width = this->width;
  int val;
  std::string s = "";
    for (auto datum : this-> data) {
        std::cout << std::to_string(datum) << " ";
    }
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      val = this->GetData(x, y);
      //s += val >= 0 ? " " + std::to_string(val) : "" + std::to_string(val);
        std::cout << std::to_string(val) << " ";
    }
    s += "\n";
  }
  return s;
}