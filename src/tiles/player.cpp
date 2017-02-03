///////////////////////////////////////////////////////////////////////
// player.cpp
// This file is part of Return of the Horsemen: A Tale of Calamity in a Perfect
// World
//
// Copyright (C) 2017 - Revelations Gaming
//
// Return of the Horsemen: A Tale of Calamity in a Perfect World is free
// software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// Return of the Horsemen: A Tale of Calamity in a Perfect World is distributed
// in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Return of the Horsemen: A Tale of Calamity in a Perfect World. If
// not, see <http://www.gnu.org/licenses/>.
///////////////////////////////////////////////////////////////////////

#include "tiles/player.hpp"
#include <SFML/Window/Event.hpp>


Player::Player(const std::string& filename, TileMap* map,
               const unsigned char& state)
: Person(filename, map, state)
{}

Player::Player(const std::string& filename, TileMap* map,
               const int& x, const int& y, const unsigned char& state)
: Person(filename, map, x, y, state)
{}

void
Player::update() {
  if(this->action & 0x4)
    this->move((unsigned char)this->action & 0x3);
  Person::update();
}

void
Player::processEvent(sf::Event event) {
  switch(event.type) {
    case (sf::Event::KeyPressed):
      switch (event.key.code) {
        case sf::Keyboard::Up:
          this->action = 0x4 | Person::UP;
          break;
        case sf::Keyboard::Down:
          this->action = 0x4 | Person::DOWN;
          break;
        case sf::Keyboard::Right:
          this->action = 0x4 | Person::RIGHT;
          break;
        case sf::Keyboard::Left:
          this->action = 0x4 | Person::LEFT;
          break;
      }
      break;
    case (sf::Event::KeyReleased):
      switch (event.key.code) {
        case sf::Keyboard::Up:
        case sf::Keyboard::Down:
        case sf::Keyboard::Right:
        case sf::Keyboard::Left:
          //TODO - maybe check if action is not the same as button released?
          this->action = 0;
          break;
      }
      break;
  }
}

