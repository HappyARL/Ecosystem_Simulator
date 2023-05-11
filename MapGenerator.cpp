//
// Created by Арлан on 02.05.2023.
//

#include "MapGenerator.h"

int MapGenerator::GetRandomNumber(int min, int max) {
  //srand(time(NULL));
   int num = min + rand() % (max - min + 1);
  return num;
}

std::pair<int, int> MapGenerator::GetRandomCoords(int min, int max) {
  int x = GetRandomNumber(min, max);
  int y = GetRandomNumber(min, max);
  while (this->perlinMap[x][y] == 1) {
    x = GetRandomNumber(++min, --max);
    y = GetRandomNumber(++min, --max);
  }
  std::cout << x << " " << y << '\n';
  std::pair<int, int> ans = std::make_pair(x, y);
  return ans;
}

std::vector<std::pair<int, int> > MapGenerator::GetCarrot() {
  return this->carrotPosition;
}

std::vector<std::vector<int> > MapGenerator::MapToAdjList(std::vector<std::vector<int>> map) {
  size_t rows = this->column_width;
  size_t cols = this->column_height;
  std::vector<std::vector<int>> graph(rows * cols);

  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      if (map[i][j] == 1) {
        int vertex = (int)(i * cols + j);
        // Check neighboring cells
        if (i > 0 && map[i - 1][j] == 1) {
          int neighbor = (int)((i - 1) * cols + j);
          graph[vertex].push_back(neighbor);
          graph[neighbor].push_back(vertex);
        }
        if (j > 0 && map[i][j - 1] == 1) {
          int neighbor = (int)(i * cols + (j - 1));
          graph[vertex].push_back(neighbor);
          graph[neighbor].push_back(vertex);
        }
        if (i < rows - 1 && map[i + 1][j] == 1) {
          int neighbor = (int)((i + 1) * cols + j);
          graph[vertex].push_back(neighbor);
          graph[neighbor].push_back(vertex);
        }
        if (j < cols - 1 && map[i][j + 1] == 1) {
          int neighbor = (int)(i * cols + (j + 1));
          graph[vertex].push_back(neighbor);
          graph[neighbor].push_back(vertex);
        }
      }
    }
  }
  return graph;
}

void MapGenerator::Init_Variables(std::vector<std::vector<int>> perlin_map, std::vector<std::pair<int, int> > carrotMap) {
  this->perlinMap = perlin_map;
  this->carrotPosition = carrotMap;
  this->KeyTime = 0.f;
  this->KeyTimeMax = 10.f;
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
      if (i == 0 || i == 50 || y == 0 || y == 50) {
        perlinMap[i][y] = 1;
      }
      std::cout << n << std::endl;
    }
  }
  return this->perlinMap;
}

MapGenerator::MapGenerator(std::vector<std::vector<int> > perlinMap, std::vector<std::pair<int, int> > carrotMap) {
  this->Init_Variables(perlinMap, carrotMap);
}

MapGenerator::~MapGenerator() {}

void MapGenerator::Update(const float& dt) {
  if (this->KeyTime < this->KeyTimeMax) {
    this->KeyTime += 5.f * dt;
  } else {
    for (int i = 0; i < 2; ++i) {
      std::pair<int, int> cur_carrot_position = GetRandomCoords(1, 50);
      this->perlinMap[cur_carrot_position.first][cur_carrot_position.second] = 2;
      this->carrotPosition.push_back(cur_carrot_position);
    }
    this->KeyTime = 0.f;
  }
}

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
