//
// Created by Арлан on 28.04.2023.
//

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "Entity.h"

class Player : public Entity {
 private:
  // Variables

  // Initializer functions
  void Init_Variables();
  void Init_Components();

 public:
  Player(float x, float y, sf::Texture* texture);
  std::pair<float, float> GetCoords();
  virtual ~Player();
  void Update(const float& dt);
  void Render(sf::RenderTarget* target);
  //Functions

};


#endif //GAME_PLAYER_H
