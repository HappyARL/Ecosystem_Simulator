//
// Created by Арлан on 26.04.2023.
//

#include "MainMenuState.h"

void MainMenuState::Init_Variables() {
  sf::View view(sf::Vector2f(1280, 720), sf::Vector2f(2560, 1440));
  this->main_camera = view;
}

void MainMenuState::Init_Background() {
  this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x),
                                        static_cast<float>(this->window->getSize().y)));
  if (!this->bg_texture.loadFromFile("Rescources/Images/Background/background1.png")) {
    throw "ERROR::MAINMENUSTATE::ERROR while load background!";
  }
  this->background.setTexture(&this->bg_texture);
}

void MainMenuState::Init_Fonts() {
  if (!this->font.loadFromFile("Fonts/Futura.ttc")) {
    throw("ERROR::MAINMENUSTATE::Could not load font!");
  }
}

void MainMenuState::Init_KeyBinds() {
  std::ifstream ifs("Config/mainmenustate_keybinds.ini");

  if (ifs.is_open()) {
    std::string key = "";
    std::string key2 = "";
    while (ifs >> key >> key2) {
      this->key_binds[key] = this->supported_keys->at(key2);
    }
  }
  ifs.close();
}

void MainMenuState::Init_Buttons() {
  this->buttons["GAME_STATE"] = new Button(300, 600, 500, 150, "New Game", &this->font,
                                       sf::Color(70, 70, 70, 200),
                                       sf::Color(150, 150, 150, 255),
                                       sf::Color(200, 200, 200, 200));

  this->buttons["SETTING_STATE"] = new Button(300, 800, 500, 150, "Settings", &this->font,
                                           sf::Color(70, 70, 70, 200),
                                           sf::Color(150, 150, 150, 255),
                                           sf::Color(200, 200, 200, 200));

  this->buttons["EXIT_STATE"] = new Button(300, 1100, 500, 150, "Quit", &this->font,
                                               sf::Color(70, 70, 70, 200),
                                               sf::Color(150, 150, 150, 255),
                                               sf::Color(200, 200, 200, 200));
}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supported_keys, std::stack<State*>* states)
        : State(window, supported_keys, states) {
  this->Init_Variables();
  this->Init_Background();
  this->Init_Fonts();
  this->Init_KeyBinds();
  this->Init_Buttons();
  this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
  this->background.setFillColor(sf::Color::White);
}
MainMenuState::~MainMenuState() {
  auto it = this->buttons.begin();
  for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
    delete it->second;
  }
}

void MainMenuState::UpdateInput(const float& dt) {
}

void MainMenuState::UpdateButtons() {
  // Updates all buttons
  for (auto& it : this->buttons) {
    it.second->Update(mouse_pos_view);
  }

  // New game
  if (this->buttons["GAME_STATE"]->is_pressed()) {
    this->states->push(new GameState(this->window, this->supported_keys, this->states));
  }

  // Quit the game
  if (this->buttons["EXIT_STATE"]->is_pressed()) {
    this->EndState();
  }
}

void MainMenuState::Update(const float& dt) {
  this->UpdateMousePosition();
  this->UpdateInput(dt);
  this->UpdateButtons();
}

void MainMenuState::RenderButton(sf::RenderTarget *target) {
  for (auto& it : this->buttons) {
    it.second->Render(target);
  }
}

void MainMenuState::Render(sf::RenderTarget* target) {
  if (!target) {
    target = this->window;
  }
  target->draw(this->background);
  this->RenderButton(target);
  target->setView(this->main_camera);

  // Get mouse coords
  /*
  sf::Text mouse_text;
  mouse_text.setPosition(this->mouse_pos_view);
  mouse_text.setFont(this->font);
  mouse_text.setCharacterSize(70);
  std::stringstream ss;
  ss << this->mouse_pos_view.x << " " << this->mouse_pos_view.y - 50;
  mouse_text.setString(ss.str());
  target->draw(mouse_text);
   */
}