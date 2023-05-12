//
// Created by Арлан on 12.05.2023.
//

#ifndef GAME_WOLF_H
#define GAME_WOLF_H

#include "Pig.h"

class Wolf : public Entity {
 private:
  bool is_male;
  bool is_adult;
  bool have_plan;

  float view_side;
  float sex_visor;
  float hunger;
  float health;
  float reproduce;
  float KeyTime;
  float KeyTimeMax;

  std::vector<Wolf *> wolf_vector_for_Wolf;
  std::vector<Pig *> pig_vector_for_Wolf;
  std::vector<std::pair<int, int> > path;

  sf::Font font;

  int newborn = 0;

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
  bool isMale();
  bool isAdult();
  bool isAlive();
  bool isHungry();
  bool isHorny();

  // Behaviour of Wolf
  void FindFood(const float x, const float y);
  void FindPartner(const float x, const float y);
  void Wandering(const float x, const float y);

  // Updates and Render
  void UpdatePigPositions(std::vector<Pig *> pig_vector);
  void UpdateWolfPositions(std::vector<Wolf *> Wolf_vector);
  int GetBabyCount();
  std::pair<float, float> GetPosition();
  void Update(const float& dt);
  void Render(sf::RenderTarget* target);
};


#endif //GAME_WOLF_H
