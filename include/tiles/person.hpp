///////////////////////////////////////////////////////////////////////
// person.hpp
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

#ifndef PERSON_HPP
#define PERSON_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
//#include <SFML/System/Vector2.hpp>

namespace sf {
  class Texture;
}

class Person : public sf::Drawable, sf::Vector2i {

public:
  static const char LEFT  = 0;
  static const char EAST  = 0;

  static const char UP    = 1;
  static const char NORTH = 1;

  static const char RIGHT = 2;
  static const char WEST  = 2;

  static const char DOWN  = 3;
  static const char SOUTH = 3;

  Person(const sf::Texture&, unsigned char state = 0);
  Person(const sf::Texture&, int, int, unsigned char state = 0);

  //Draw the person
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  //move/turn in direction,
  //  if bool is true move without turning
  virtual bool move(const unsigned char&, const bool& turn = false);

  //set the state
  void setState(const unsigned char&);

  //set the direction w/o affecting other parts of the state
  void setDirection(const unsigned char&);

  //get the state
  inline unsigned char getState() const { return this->state; }

  //get the direction w/o the other parts of the state
  inline unsigned char getDirection() const { return this->state & 3; }

private:
  //sprite that will be used to represent the person
  sf::Sprite sprite;

  //state of player (includes direction)
  unsigned char state;
};

#endif /* PERSON_HPP */

