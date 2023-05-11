//
// Created by Арлан on 21.04.2023.
//

#include "GameState.h"
#include "MapGenerator.h"

int GameState::GetRandomNumber(int min, int max) {
  //srand(time(NULL));
  int num = min + rand() % (max - min + 1);
  return num;
}

std::pair<float, float> GameState::GetRandomCoords(int min, int max) {
  int x = GetRandomNumber(min, max);
  int y = GetRandomNumber(min, max);
  while (map[x][y] == 1) {
    x = GetRandomNumber(++min, --max);
    y = GetRandomNumber(++min, --max);
  }
  std::cout << x << " " << y << '\n';
  std::pair<float, float> ans = std::make_pair(x * 100, y * 100);
  return ans;
}

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

void GameState::Init_Fonts() {
  if (!this->font.loadFromFile("Fonts/Futura.ttc")) {
    throw("ERROR::MAINMENUSTATE::Could not load font!");
  }
}

void GameState::Init_Texture() {
  if (!this->textures["PLAYER_IDLE"].loadFromFile("Rescources/Images/Sprites/Player/white_dot.png")) {
    throw "ERROR::GAMESTATE::Error while load Player texture!";
  }
  if (!this->textures["PIG_ALIVE"].loadFromFile("Rescources/Images/Animals/pig.png")) {
    throw "ERROR::GAMESTATE::Error while load PigAlive texture!";
  }
  if (!this->textures["PIG_DEAD"].loadFromFile("Rescources/Images/Animals/pig_dead.png")) {
    throw "ERROR::GAMESTATE::Error while load PigDead texture!";
  }
  if (!this->textures["GRASS"].loadFromFile("Rescources/Images/Texture/grass_2.png")) {
    throw "ERROR::GAMESTATE::Error while load grass texture!";
  }
  if (!this->textures["WATER"].loadFromFile("Rescources/Images/Texture/water_2.png")) {
    throw "ERROR::GAMESTATE::Error while load water texture!";
  }
  if (!this->textures["CARROT"].loadFromFile("Rescources/Images/Texture/carrot.png")) {
    throw "ERROR::GAMESTATE::Error while load carrot texture!";
  }
}

void GameState::Init_PauseMenu() {
  this->pause_menu = new PauseMenuState(this->player->camera_view, this->font);

}

void GameState::Init_Sprite() {
  this->sprites[0] = sf::Sprite(this->textures["GRASS"]);
  this->sprites[1] = sf::Sprite(this->textures["WATER"]);
  this->sprites[2] = sf::Sprite(this->textures["CARROT"]);
}

void GameState::Init_Players() {
  this->player = new Player(2500, 2500, &this->textures["PLAYER_IDLE"]);
}

void GameState::Init_Animals() {
  for (size_t i = 0; i < this->pig_amount; ++i) {
    std::pair<float, float> map_pos = GetRandomCoords(1, 49);
    int sex_num = GetRandomNumber(0, 1);
    bool sex = sex_num == 1; // true = male and false = female
    this->pig_vector.push_back(new Pig(map_pos.first, map_pos.second, &this->textures["PIG_ALIVE"],
                                       &this->textures["PIG_DEAD"], true, sex, this->map, this->graph));
  }
}

void GameState::Init_Map() {
  this->map_gen = new MapGenerator(map, carrot_vector);
  this->map = map_gen->TileGenerator(51, 51);
  this->graph = map_gen->MapToAdjList(map);
}

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supported_keys, std::stack<State*>* states)
  : State(window, supported_keys, states) {
  this->Init_KeyBinds();
  this->Init_Fonts();
  this->Init_Texture();
  this->Init_Sprite();
  this->Init_Map();
  this->Init_Players();
  this->Init_PauseMenu();
  this->Init_Animals();
}

GameState::~GameState() {
  delete this->player;
  delete this->pause_menu;
  for (size_t i = 0; i < this->pig_amount; ++i) {
    delete this->pig_vector[i];
  }
}

void GameState::UpdateInput(const float& dt) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("PAUSE"))) && this->GetKeyTime()) {
    if (!this->pause) {
      this->PauseState();
    } else {
      this->unPauseState();
    }
  }
}

void GameState::UpdatePlayerInput(const float& dt) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("MOVE_LEFT")))) {
    this->player->Move(dt, -3.f, 0.f);
    this->player->MoveCamera(dt, -3.f, 0.f);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("MOVE_RIGHT")))) {
    this->player->Move(dt, 3.f, 0.f);
    this->player->MoveCamera(dt, 3.f, 0.f);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("MOVE_UP")))) {
    this->player->Move(dt, 0.f, -3.f);
    this->player->MoveCamera(dt, 0.f, -3.f);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("MOVE_DOWN")))) {
    this->player->Move(dt, 0.f, 3.f);
    this->player->MoveCamera(dt, 0.f, 3.f);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("CLOSE")))) {
    this->EndState();
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("ZOOM_IN")))) {
    this->player->Zoom(.97f);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("ZOOM_OUT")))) {
    this->player->Zoom(1.03f);
  }
}

void GameState::Update(const float& dt) {
  this->UpdateMousePosition();
  this->UpdateKeyTime(dt);
  this->UpdateInput(dt);

  this->UpdatePlayerInput(dt);
  this->player->Update(dt);

  if (!pause) {
    this->map_gen->Update(dt);
    this->carrot_vector = map_gen->GetCarrot();
    size_t curr_amount = 0;
    for (size_t i = 0; i < this->pig_amount; ++i) {
      this->pig_vector[i]->UpdateCarrotPositions(this->carrot_vector);
      this->pig_vector[i]->Update(dt);
      if (this->pig_vector[i]->isAlive()) {
        ++curr_amount;
      }
      this->map = this->pig_vector[i]->UpdateGlobalMap();
    }
    this->pig_amount = curr_amount;
  } else {
    this->pause_menu->Update(this->mouse_pos_view);
  }
}

void GameState::Render(sf::RenderTarget* target) {
  if (!target) {
    target = this->window;
  }

  target->clear(sf::Color(18,140,235, 255));
  this->map_gen->Render(this->window, sprites);
  this->player->Render(this->window);

  sf::Text info_text;
  info_text.setPosition(this->player->GetCoords().first - 3500,
                        this->player->GetCoords().second - 1900);

  info_text.setFont(this->font);
  info_text.setCharacterSize(100);
  std::stringstream ss;
  if (this->pig_amount <= 0) {
    ss << "They are in a better place ..." << '\n';
  } else {
    ss << "Pig count: " << this->pig_amount << '\n';
  }
  ss << "Carrot count: " << this->carrot_vector.size() << '\n';
  info_text.setString(ss.str());
  target->draw(info_text);


  for (size_t i = 0; i < this->pig_amount; ++i) {
    this->pig_vector[i]->Render(this->window);
  }

  if (this->pause) {
    this->pause_menu->Render(target, this->player->GetCoords().first, this->player->GetCoords().second);
  }

/*
  if (pause_update_pig) {
    sf::Text info_text;
    info_text.setPosition(this->player->GetCoords().first - 600,
                          this->player->GetCoords().second);
    info_text.setFont(this->font);
    info_text.setCharacterSize(400);
    std::stringstream ss;
    ss << "-PAUSE-"<< '\n';
    info_text.setString(ss.str());
    target->draw(info_text);
  }
*/
}
