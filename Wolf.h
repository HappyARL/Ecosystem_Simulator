//
// Created by Арлан on 12.05.2023.
//

#ifndef GAME_WOLF_H
#define GAME_WOLF_H

#include "Entity.h"

class Pig;

class Wolf : public Entity {
 private:
  bool have_plan;

  float view_side;
  float hunger;
  float health;
  float KeyTime;
  float KeyTimeMax;

  std::vector<Pig *> pig_vector_for_Wolf;
  std::vector<std::pair<int, int> > path_walking;

  sf::Font font;

  void Init_Fonts();
  void Init_Variables(float x, float y, bool adult, bool sex, std::vector<std::vector<int> > map,
                      sf::Texture* texture_dead);
  void Init_Components();
  float CountDistance(const float Wolf_x, const float Wolf_y, const float carrot_x, const float carrot_y);

 public:
  std::vector<std::vector<int> > map_for_Wolf;
  // Constructor for Wolf
  Wolf(float x, float y, sf::Texture* texture_alive, sf::Texture* texture_dead, bool adult, bool sex,
      std::vector<std::vector<int> > map);
  ~Wolf();

  // Condition of Wolf
  bool isAlive();
  bool isHungry();

  // Behaviour of Wolf
  void FindFood(const float x, const float y);
  void Wandering(const float x, const float y);

  // Updates and Render
  void UpdatePigPositions(const std::vector<Pig*>& pig_vector);
  std::pair<float, float> GetPosition();
  void Update(const float& dt);
  void Render(sf::RenderTarget* target);
};


#endif //GAME_WOLF_H
