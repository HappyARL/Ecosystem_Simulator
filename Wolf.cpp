//
// Created by Арлан on 04.05.2023.
//

#include "Wolf.h"
#include "aStarAlgoritm.h"
#include <utility>
#include <float.h>

void Wolf::Init_Fonts() {
  if (!this->font.loadFromFile("Fonts/Futura.ttc")) {
    throw("ERROR::MAINMENUSTATE::Could not load font!");
  }
}

void Wolf::Init_Variables(float x, float y, bool adult, bool sex, std::vector<std::vector<int> > map,
                         sf::Texture* texture_dead) {
  this->view_side = 1000.0;
  this->sex_visor = 1500.f;
  this->is_male = sex;
  this->is_adult = adult;
  this->have_plan = false;
  this->hunger = 100.0;
  this->health = 100.0;
  this->reproduce = 100.0;
  this->map_for_Wolf = std::move(map);
  this->texture_dead = texture_dead;
  this->sprite_dead = new sf::Sprite(*this->texture_dead);
  this->KeyTime = 0.f;
  this->KeyTimeMax = 10.f;
}

void Wolf::Init_Components() {

}

float Wolf::CountDistance(const float Wolf_x, const float Wolf_y, const float carrot_x, const float carrot_y) {
  float distance = sqrt((carrot_x - Wolf_x)*(carrot_x - Wolf_x) + (carrot_y - Wolf_y)*(carrot_y - Wolf_y));
  return distance * 100;
}

// Constructor for Wolf

Wolf::Wolf(float x, float y, sf::Texture* texture_alive, sf::Texture* texture_dead, bool adult, bool sex,
         std::vector<std::vector<int> > map) {
  this->Init_Fonts();
  this->Init_Variables(x, y, adult, sex, map, texture_dead);
  this->Init_Components();
  this->CreateSprite(texture_alive);
  this->SetPosition(x, y);
}

Wolf::~Wolf() {

}

// Condition of Wolf

bool Wolf::isMale() {
  return this->is_male;
}

bool Wolf::isAdult() {
  return this->is_adult;
}

bool Wolf::isAlive() {
  return (this->health > 0);
}

bool Wolf::isHungry() {
  return (this->hunger < 60.0);
}

bool Wolf::isHorny() {
  return (this->reproduce < 50.0);
}

int GetRandomNumberWolf(int min, int max) {
  //srand(time(NULL));
  int num = min + rand() % (max - min + 1);
  return num;
}

// Behaviour of Wolf

void Wolf::FindFood(const float x, const float y) {
  float shortest_distance = FLT_MAX;
  Pig* closest_pig = nullptr;
  for (auto& curr_pig : this->pig_vector_for_Wolf) {
    float curr_distance = CountDistance(x, y,
                                        curr_pig->GetPosition().first,
                                        curr_pig->GetPosition().second);
    if (shortest_distance > curr_distance) {
      shortest_distance = curr_distance;
      closest_pig = curr_pig;
    }
  }
  if (shortest_distance <= this->view_side) {
    aStarAlgoritm star(this->map_for_Wolf);
    if (shortest_distance <= 100) {
      this->hunger += 45;
      closest_pig->Dying();
    } else {
      if (closest_pig) {
        this->path = star.got_to_position((int)x, (int)y,
                                          (int)closest_pig->GetPosition().first,
                                          (int)closest_pig->GetPosition().second);
        this->have_plan = true;
      }
    }
  }
}

void Wolf::FindPartner(const float x, const float y) {
  float shortest_distance = FLT_MAX;
  Wolf* closest_partner = nullptr;
  for (auto& curr_Wolf : this->wolf_vector_for_Wolf) {
    if (curr_Wolf->isAlive() &&
        this->isMale() != curr_Wolf->isMale() && curr_Wolf->isAdult()) {
      float curr_distance = CountDistance(x, y,
                                          curr_Wolf->sprite->getPosition().x / 100,
                                          curr_Wolf->sprite->getPosition().y) / 100;
      if (shortest_distance > curr_distance) {
        shortest_distance = curr_distance;
        closest_partner = curr_Wolf;
      }
    }
  }
  if (shortest_distance <= this->sex_visor) {
    aStarAlgoritm star(this->map_for_Wolf);
    if (this->GetPosition() == closest_partner->GetPosition()) {
      float curr_reproduce = this->reproduce;
      this->reproduce += 100.f - curr_reproduce;
      this->newborn += GetRandomNumberWolf(1, 3);
    } else {
      if (closest_partner) {
        this->path = star.got_to_position((int) x, (int) y,
                                          (int)closest_partner->sprite->getPosition().x / 100,
                                          (int)closest_partner->sprite->getPosition().y / 100);
        this->have_plan = true;
      }
    }
  }
}

void Wolf::Wandering(const float x, const float y) {
  int gen_x = GetRandomNumberWolf(-5, 5);
  int gen_y = GetRandomNumberWolf(-5, 5);
  while ((int)x + gen_x < 0 || (int)x + gen_x >= 50 ||
         (int)y + gen_y < 0 || (int)y + gen_y >= 50 ||
         this->map_for_Wolf[(int)x + gen_x][(int)y + gen_y] != 0) {
    gen_x = GetRandomNumberWolf(-5, 5);
    gen_y = GetRandomNumberWolf(-5, 5);
  }
  aStarAlgoritm star(this->map_for_Wolf);
  this->path = star.got_to_position((int)x, (int)y,
                                    (int)x + gen_x, (int)y + gen_y);
  this->have_plan = true;
}

void Wolf::UpdatePigPositions(std::vector<Pig *> pig_vector) {
  this->pig_vector_for_Wolf = pig_vector;
}

void Wolf::UpdateWolfPositions(std::vector<Wolf *> Wolf_vector) {
  this->wolf_vector_for_Wolf = Wolf_vector;
}

int Wolf::GetBabyCount() {
  return this->newborn;
}

std::pair<float, float> Wolf::GetPosition() {
  return std::make_pair(this->sprite->getPosition().x,
                        this->sprite->getPosition().x);
}

void Wolf::Update(const float& dt) {
  // Is Wolf alive
  if (isAlive()) {
    // Conditions that depend on time / timer
    if (this->KeyTime < this->KeyTimeMax) {
      this->KeyTime += 30.f * dt;
    } else {
      // Check hunger bar
      if (this->hunger > 0) {
        this->hunger -= 15.f;
      } else {
        this->health -= 20.f;
      }

      // Check reproduce urge bar
      if (this->isAdult()) {
        if (this->reproduce > 0) {
          this->reproduce -= 0.f;
        } else {
          this->health -= 10.f;
        }
      }

      // restart timer
      this->KeyTime = 0.f;
    }

    // Check does Wolf have route to smt
    if (this->have_plan) {
      if (!this->path.empty()) {
        std::pair<int, int> where_to_go = this->path.back();
        this->path.pop_back();
        this->sprite->setPosition((float) where_to_go.first * 100,
                                  (float) where_to_go.second * 100);
      } else {
        this->have_plan = false;
      }
    } else {
      if (isHungry()) {
        this->FindFood(this->sprite->getPosition().x / 100,
                       this->sprite->getPosition().y / 100);
      }
      if (isHorny()) {
        this->FindPartner(this->sprite->getPosition().x / 100,
                          this->sprite->getPosition().y / 100);
      }
      this->Wandering(this->sprite->getPosition().x / 100,
                      this->sprite->getPosition().y / 100);
    }
  }
}

void Wolf::Render(sf::RenderTarget* target) {
  if (this->sprite) {
    sf::Text info_text;
    info_text.setPosition(this->sprite->getPosition().x - 120,
                          this->sprite->getPosition().y + 60);
    info_text.setFont(this->font);
    info_text.setCharacterSize(20);
    std::stringstream ss;
    ss << "sex: " << (this->is_male ? "Male" : "Female") << '\n';
    ss << "health: " << this->health << '\n';
    ss << "hunger: " << this->hunger << '\n';
    ss << "reproduce urge: " << this->reproduce << '\n';
    ss << "age: " << (this->isAdult() ? "MATURE" : "BABY") << '\n';
    if (!this->isAlive()) {
      ss << "~DEAD~" << '\n';
    }
    info_text.setString(ss.str());
    if (!this->isAlive()) {
      this->sprite_dead->setPosition(info_text.getPosition().x + 120,
                                     info_text.getPosition().y - 60);
      target->draw(*this->sprite_dead);
    } else {
      target->draw(*this->sprite);
    }
    target->draw(info_text);
  }
}
