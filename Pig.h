//
// Created by Арлан on 04.05.2023.
//

#ifndef GAME_PIG_H
#define GAME_PIG_H

#include "Entity.h"

class Wolf;

enum Priority {
  UNDER_CHASE = 1,
  STARVING = 2,
  LONELY = 3,
  SAFE = 4
};

class Pig : public Entity {
 private:
  bool is_male;
  bool is_adult;

  float view_side;
  float sex_visor;
  float hunger;
  float health;
  float reproduce;
  float KeyTime;
  float KeyTimeMax;

  std::vector<std::pair<int, int> > carrot_vector_for_pig;
  std::vector<Pig *> pig_vector_for_pig;
  std::vector<Wolf *> wolf_vector_for_pig;
  Wolf* src_fo_danger = nullptr;
  std::vector<std::pair<int, int> > path;

  sf::Font font;

  int newborn = 0;

  void Init_Fonts();
  void Init_Variables(float x, float y, bool adult, bool sex, std::vector<std::vector<int> > map,
                      sf::Texture* texture_dead);
  void Init_Components();
  float CountDistance(const float pig_x, const float pig_y, const float carrot_x, const float carrot_y);

 public:
  std::vector<std::vector<int> > map_for_pig;

  // Constructor for Pig
  Pig(float x, float y, sf::Texture* texture_alive, sf::Texture* texture_dead, bool adult, bool sex,
      std::vector<std::vector<int> > map);
  virtual ~Pig();

  // Condition of Pig
  bool InDanger();
  bool isMale();
  bool isAdult();
  bool isAlive();
  bool isHungry();
  bool isHorny();

  // Behaviour of Pig
  void FindFood(const float x, const float y);
  void FindPartner(const float x, const float y);
  void Run(const float x, const float y);
  void Dying();
  void Wandering(const float x, const float y);

  void Movement(const float& dt);

  // Updates Get-func. and Render
  void UpdateCarrotPositions(std::vector<std::pair<int, int> > carrot_vector);
  void UpdatePigPositions(std::vector<Pig *> pig_vector);
  void UpdateWolfPositions(std::vector<Wolf *> wolf_vector);

  std::vector<std::vector<int> > UpdateGlobalMap();
  int GetBabyCount();
  std::pair<float, float> GetPosition();

  void Update(const float& dt);
  void Render(sf::RenderTarget* target);
};


#endif //GAME_PIG_H
