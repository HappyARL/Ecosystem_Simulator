//
// Created by Арлан on 04.05.2023.
//

#ifndef GAME_PIG_H
#define GAME_PIG_H

#include "Entity.h"

class Pig : public Entity {
 private:
  bool is_male;
  bool is_adult;

  float hunger;
  float health;
  float reproduce;
  float KeyTime;
  float KeyTimeMax;


  std::pair<int, int> direction;
  std::vector<std::vector<int> > map_for_pig;

  sf::Font font;

  void Init_Fonts();
  void Init_Variables(float x, float y, bool adult, bool sex, std::vector<std::vector<int> > map, sf::Texture* texture_dead);
  void Init_Components();

 public:
  Pig(float x, float y, sf::Texture* texture_alive, sf::Texture* texture_dead, bool adult, bool sex, std::vector<std::vector<int> > map);
  void FindFood(const float x, const float y);
  void FindPartner(const float x, const float y);
  bool InDanger(const float x, const float y);
  bool isMale();
  bool isAdult();
  bool isAlive();
  bool isHungry();
  bool isHorny();
  void Run(const float x, const float y);
  std::pair<float, float> GetDirection();
  void Wandering(const float x, const float y, bool access_to_change);
  virtual ~Pig();
  void Update(const float& dt);
  void Render(sf::RenderTarget* target);
};


#endif //GAME_PIG_H
