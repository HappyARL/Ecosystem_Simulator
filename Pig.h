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
  bool have_plan;

  float view_side;
  float hunger;
  float health;
  float reproduce;
  float KeyTime;
  float KeyTimeMax;

  std::pair<int, int> direction;
  std::vector<std::vector<int> > graph_for_pig;
  std::vector<std::pair<int, int> > carrot_vector_for_pig;
  std::vector<std::pair<int, int> > path;

  sf::Font font;

  void Init_Fonts();
  void Init_Variables(float x, float y, bool adult, bool sex, std::vector<std::vector<int> > map,
                      std::vector<std::vector<int> > graph, sf::Texture* texture_dead);
  void Init_Components();
  float CountDistance(const float pig_x, const float pig_y, const float carrot_x, const float carrot_y);

 public:
  std::vector<std::vector<int> > map_for_pig;
  // Constructor for Pig
  Pig(float x, float y, sf::Texture* texture_alive, sf::Texture* texture_dead, bool adult, bool sex,
      std::vector<std::vector<int> > map, std::vector<std::vector<int> > graph);
  virtual ~Pig();

  // Condition of Pig
  bool InDanger(const float x, const float y);
  bool isMale();
  bool isAdult();
  bool isAlive();
  bool isHungry();
  bool isHorny();

  // Behaviour of Pig
  void FindFood(const float x, const float y);
  void FindPartner(const float x, const float y);
  void Run(const float x, const float y);
  void Wandering(const float x, const float y, bool access_to_change);

  // Updates and Render
  void UpdateCarrotPositions(std::vector<std::pair<int, int> > carrot_vector);
  std::vector<std::vector<int> > UpdateGlobalMap();
  void Update(const float& dt);
  void Render(sf::RenderTarget* target);
};


#endif //GAME_PIG_H
