//
// Created by Арлан on 22.04.2023.
//

#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <map>
#include <time.h>
#include <stdlib.h>

class Entity {
 private:
  void Init_Variables();

 protected:
  sf::Texture* texture;
  sf::Sprite* sprite;
  sf::Texture* texture_dead;
  sf::Sprite* sprite_dead;
  //sf::FloatRect boundingBox = sprite->getGlobalBounds();
  float movement_speed;

 public:
  sf::View camera_view;
  Entity();
  virtual ~Entity();

  // Component function
  void CreateSprite(sf::Texture* texture);

  // Functions
  virtual void SetPosition(const float x, const float y);
  void SetCameraPosition(const float x, const float y);
  virtual void Move(const float& dt, const float dir_x, const float dir_y);
  virtual void MoveCamera(const float& dt, const float dir_x, const float dir_y);
  void Zoom(const float power_zoom);
  virtual void Update(const float& dt) = 0;
  virtual void Render(sf::RenderTarget* target = nullptr) = 0;
};

#endif //GAME_ENTITY_H
