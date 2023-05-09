//
// Created by Арлан on 05.05.2023.
//

#ifndef GAME_PAUSEMENUSTATE_H
#define GAME_PAUSEMENUSTATE_H

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

#include "Button.h"

class PauseMenuState {
 private:
  sf::Font& fonts;
  sf::Text menu_text;
  sf::View camera;

 public:
  PauseMenuState(sf::View camera_view, sf::Font& font);
  virtual ~PauseMenuState();

  // Functions
  void Update(const sf::Vector2f& mousePos);
  void Render(sf::RenderTarget* target, float x, float y);

};


#endif //GAME_PAUSEMENUSTATE_H
