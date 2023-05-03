//
// Created by Арлан on 02.05.2023.
//

#include "MapGenerator.h"

void MapGenerator::Init_Variables(std::vector<std::vector<int>> perlinMap) {
  this->perlinMap = perlinMap;
}

std::vector<std::vector<int> > MapGenerator::TileGenerator(size_t length, size_t width) {
  for (size_t i = 0; i <= length; ++i) {
    std::vector<int> tmp;
    tmp.resize(width);
    this->perlinMap.push_back(tmp);
  }
  // Seed with a real random value, if available
  std::random_device r;

  // Choose a random mean between 1 and 256
  std::default_random_engine e1(r());
  std::uniform_int_distribution<int> uniform_dist(1, 256);
  int seed = uniform_dist(e1);

  PerlinNoise perlNoise(1,.10,1,3,seed);

  column_width = length;
  column_height = width;

  for (size_t i = 0;i < length; ++i) {
    for (size_t y = 0;y < width; ++y) {
      double perlinReturn;

      perlinReturn = perlNoise.GetHeight(i, y);

      double n = perlinReturn;
      if (n > (-1.70) && n < (-0.1)) {
        perlinMap[i][y] = 1;
      }
      if (n > (-0.10) && n < (0.25)) {
        perlinMap[i][y] = 0;
      }
      std::cout << n << std::endl;
    }
  }
  return this->perlinMap;
}

MapGenerator::MapGenerator(std::vector<std::vector<int> > perlinMap) {
  this->Init_Variables(perlinMap);
}

MapGenerator::~MapGenerator() {}

void MapGenerator::Render(sf::RenderTarget *target, std::map<int, sf::Sprite> sprites) {
  for (int x = 0; x < column_width; ++x) {
    for (int y = 0; y < column_height; ++y) {
      int tileId = perlinMap[x][y];

      // Get the width and height of the image
      int width = 100;
      int height = 100;

      // Adjust the offset by using the width
      sprites[tileId].setPosition((float)(x * width), (float)(y * height));

      // Draw the tile
      target->draw(sprites[tileId]);
    }
  }
}
