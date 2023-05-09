//
//  Game.cpp
//  HappyFarm
//
//  Created by Арлан on 21.04.2023.
//  Copyright © 2023 Арлан. All rights reserved.
//

#include "Game.h"

// Initializer functions

void Game::Init_Variables() {
  this->window = nullptr;
  this->fullscreen = false;
  this->delta_time = 0.f;
}

void Game::Init_Window() {
  std::ifstream  ifs("Config/window.ini");
  this->video_modes = sf::VideoMode::getFullscreenModes();
  std::string title = "None";
  sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
  bool fullscreen = false;
  unsigned framerate_limit = 120;
  bool vertical_sync_enable = false;
  unsigned antialiasing_level = 0;

  if (ifs.is_open()) {
    std::getline(ifs, title);
    ifs >> window_bounds.width >> window_bounds.height;
    ifs >> fullscreen;
    ifs >> framerate_limit;
    ifs >> vertical_sync_enable;
    ifs >> antialiasing_level;
  }

  ifs.close();

  this->fullscreen = fullscreen;
  this->window_settings.antialiasingLevel = antialiasing_level;
  if (this->fullscreen) {
    this->window = new sf::RenderWindow(window_bounds, title,
                                        sf::Style::Fullscreen | sf::Style::Titlebar | sf::Style::Close,
                                        window_settings);
  } else {
    this->window = new sf::RenderWindow(window_bounds, title,
                                        sf::Style::Titlebar | sf::Style::Close,
                                        window_settings);
  }
  this->window->setFramerateLimit(framerate_limit);
  this->window->setVerticalSyncEnabled(vertical_sync_enable);
}

void Game::Init_Keys() {
  std::ifstream ifs("Config/supported_keys.ini");

  if (ifs.is_open()) {
    std::string key = "";
    int key_value = 0;
    while (ifs >> key >> key_value) {
      this->supported_keys[key] = key_value;
    }
  }
  ifs.close();
}

void Game::Init_States() {
  this->states.push(new MainMenuState(this->window, &this->supported_keys, &this->states));
}

// Constructors / Destructors

Game::Game() {
  this->Init_Window();
  this->Init_Keys();
  this->Init_States();
}

Game::~Game() {
  delete this->window;

  while (!this->states.empty()) {
    delete this->states.top();
    this->states.pop();
  }
}

// Functions

void Game::EndApplication() {
  std::cout << "Ending application" << '\n';
}

void Game::UpdateDeltaTime() {
  // Update delta_time with time it takes to update and render frame
  this->delta_time = this->delta_time_clock.restart().asSeconds();

  // Print tech info
  system("cls");
  std::cout << this->delta_time << '\n';
}

void Game::Update_SFML_Events() {
  while (this->window->pollEvent(this->sf_event)) {
    if (this->sf_event.type == sf::Event::Closed) {
      this->window->close();
    }
  }
}

void Game::Update() {
  this->Update_SFML_Events();

  if (!this->states.empty()) {
    this->states.top()->Update(this->delta_time);
    if (this->states.top()->GetQuit()) {
      this->states.top()->EndState();
      delete this->states.top();
      this->states.pop();
    }
  }
  // App lication end
  else {
    this->EndApplication();
    this->window->close();
  }
}

void Game::Render() {
  this->window->clear();

  if (!this->states.empty()) {
    this->states.top()->Render(this->window);
  }
  // Render items
  this->window->display();
}

void Game::Run() {
  while (this->window->isOpen()) {
    this->UpdateDeltaTime();
    this->Update();
    this->Render();
  }
}