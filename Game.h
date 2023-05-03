//
// Created by Арлан on 21.04.2023.
//

#ifndef GAME_GAME_H
#define GAME_GAME_H

#include "MainMenuState.h"

class Game {
 private:
  // Variables
  sf::RenderWindow *window;
  sf::Event sf_event;
  std::vector<sf::VideoMode> video_modes;
  sf::ContextSettings window_settings;
  bool fullscreen;
  sf::Clock delta_time_clock;
  float delta_time;

  std::stack<State*> states;

  std::map<std::string, int> supported_keys;


  // Initialization
  void Init_Variables();
  void Init_Window();
  void Init_Keys();
  void Init_States();

 public:
  // Constructors / Destructors
  Game();
  virtual ~Game();
  // Fucntions
  void EndApplication();
  void UpdateDeltaTime();
  void Update_SFML_Events();
  void Update();
  void Render();
  void Run();
};


#endif //GAME_GAME_H
