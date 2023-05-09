//
// Created by Арлан on 27.04.2023.
//

#ifndef GAME_BUTTON_H
#define GAME_BUTTON_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>

enum button_states {
  BTN_IDLE = 0,
  BTN_HOVER,
  BTN_ACTIVE
};

class Button {
 private:
  short unsigned button_state;

  sf::RectangleShape shape;
  sf::Font* font;
  sf::Text text;

  float x;
  float y;

  sf::Color idle_color;
  sf::Color hover_color;
  sf::Color active_color;

 public:
  Button(float x, float y, float width, float height,
         std::string text, sf::Font* font,
         sf::Color idle_color, sf::Color hover_color, sf::Color active_color);
  ~Button();

  // Accessors
  const bool is_pressed();

  // Functions
  void Update(const sf::Vector2f& mouse_pos);
  void Render(sf::RenderTarget* target);
};


#endif //GAME_BUTTON_H
