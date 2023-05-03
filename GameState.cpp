//
// Created by Арлан on 21.04.2023.
//

#include "GameState.h"
#include "MapGenerator.h"

void GameState::Init_KeyBinds() {
  std::ifstream ifs("Config/gamestate_keybinds.ini");

  if (ifs.is_open()) {
    std::string key = "";
    std::string key2 = "";
    while (ifs >> key >> key2) {
      this->key_binds[key] = this->supported_keys->at(key2);
    }
  }
  ifs.close();
}

void GameState::Init_Texture() {
  if (!this->textures["PLAYER_IDLE"].loadFromFile("Rescources/Images/Sprites/Player/pig_idle1.png")) {
    throw "ERROR::GAMESTATE::Error while load Player texture!";
  }
  if (!this->textures["GRASS"].loadFromFile("Rescources/Images/Texture/grass_2.png")) {
    throw "ERROR::GAMESTATE::Error while load grass texture!";
  }
  if (!this->textures["WATER"].loadFromFile("Rescources/Images/Texture/water_2.png")) {
    throw "ERROR::GAMESTATE::Error while load water texture!";
  }
}

void GameState::Init_Sprite() {
  this->sprites[0] = sf::Sprite(this->textures["GRASS"]);
  this->sprites[1] = sf::Sprite(this->textures["WATER"]);
}

void GameState::Init_Players() {
  this->player = new Player(2500, 2500, &this->textures["PLAYER_IDLE"]);
}

void GameState::Init_Map() {
  this->map_gen = new MapGenerator(map);
  this->map = map_gen->TileGenerator(50, 50);
}

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supported_keys, std::stack<State*>* states)
  : State(window, supported_keys, states) {
  this->Init_KeyBinds();
  this->Init_Texture();
  this->Init_Sprite();
  this->Init_Players();
  this->Init_Map();
}

GameState::~GameState() {
  delete this->player;
}

void GameState::UpdateInput(const float& dt) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("MOVE_LEFT")))) {
    this->player->Move(dt, -1.f, 0.f);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("MOVE_RIGHT")))) {
    this->player->Move(dt, 1.f, 0.f);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("MOVE_UP")))) {
    this->player->Move(dt, 0.f, -1.f);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("MOVE_DOWN")))) {
    this->player->Move(dt, 0.f, 1.f);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("CLOSE")))) {
    this->EndState();
  }
}

void GameState::Update(const float& dt) {
  this->UpdateMousePosition();
  this->UpdateInput(dt);
  this->player->Update(dt);
}

void GameState::Render(sf::RenderTarget* target) {
  if (!target) {
    target = this->window;
  }
  this->map_gen->Render(this->window, sprites);
  this->player->Render(this->window);
}
