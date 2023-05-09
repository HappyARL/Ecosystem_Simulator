//
// Created by Арлан on 02.05.2023.
//

#ifndef GAME_MAPGENERATOR_H
#define GAME_MAPGENERATOR_H

#include "PerlinNoise.h"

class MapGenerator {
 protected:
  std::vector<std::vector<int> > perlinMap;
  float KeyTime;
  float KeyTimeMax;

  size_t column_width;
  size_t column_height;
  // Function
  int GetRandomNumber(int min, int max);
  std::pair<int ,int> GetRandomCoords(int min, int max);

  void Init_Variables(std::vector<std::vector<int> > perlinMap);

 public:
  std::vector<std::vector<int> > TileGenerator(size_t length, size_t width);
  MapGenerator(std::vector<std::vector<int> > perlinMap);
  virtual ~MapGenerator();
  void Update(const float& dt);
  void Render(sf::RenderTarget* target, std::map<int, sf::Sprite> sprites);
};


#endif //GAME_MAPGENERATOR_H
