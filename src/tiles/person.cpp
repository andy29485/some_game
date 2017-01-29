///////////////////////////////////////////////////////////////////////
// person.cpp
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

#include <SFML/Graphics/RenderTarget.hpp>

#include "tiles/person.hpp"

Person::Person(const sf::Texture& texture, unsigned char state)
: sprite(texture),
  sf::Vector2i(),
  state(state)
{}

Person::Person(const sf::Texture& texture, int x, int y, unsigned char state)
: sprite(texture),
  sf::Vector2i(x, y),
  state(state)
{}

void Person::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(this->sprite);
}

//move/turn in direction,
//  if bool is true move without turning
//  return true if movement did not go into the negatives
bool Person::move(char dir, bool turn) {
  if(dir == this->getDirection() || turn) {
    if(dir == Person::UP) {
      return this->y && (--this->y || true);
    }
    else if(dir == Person::DOWN) {
      return ++this->y;
    }
    else if(dir == Person::LEFT) {
      return this->x && (--this->x || true);
    }
    else if(dir == Person::RIGHT) {
      return ++this->x;
    }
  }
  else {
    this->setDirection(dir);
    return true;
  }
  return false;
}

//set the state
void Person::setState(unsigned char state) {
  this->state = state;
}

//set the direction w/o affecting other parts of the state
void Person::setDirection(unsigned char dir) {
  this->state = (this->state & ~3) | (dir & 3); 
}

