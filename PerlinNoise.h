//
// Created by Арлан on 02.05.2023.
//

#ifndef GAME_PERLINNOISE_H
#define GAME_PERLINNOISE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <random>

class PerlinNoise {
 public:
  // Constructor
  PerlinNoise();
  PerlinNoise(double _persistence, double _frequency, double _amplitude, int _octaves, int _random_seed);
  ~PerlinNoise() = default;
  // Get Height
  [[nodiscard]] double GetHeight(double x, double y) const;

 private:
  double Total(double i, double j) const;
  double GetValue(double x, double y) const;
  double Interpolate(double x, double y, double a) const;
  double Noise(int x, int y) const;

  double persistence, frequency, amplitude;
  int octaves, random_seed;
};


#endif //GAME_PERLINNOISE_H
