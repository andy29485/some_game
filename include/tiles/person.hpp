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

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

#include "gameobject.hpp"

typedef std::vector<char> Path;

class TileMap;

class Person : public GameObject, public sf::Vector2i {

public:
  enum direction {
    LEFT,
    UP,
    RIGHT,
    DOWN,

    WEST  = LEFT,
    NORTH = UP,
    EAST  = RIGHT,
    SOUTH = DOWN
  };

  Person(const std::string&, TileMap*, const unsigned char& state = 0);
  Person(const std::string&, TileMap*, const int&, const int&,
         const unsigned char& state = 0);

  //Draw the person
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  //move/turn in direction,
  //  if bool is true move without turning
  virtual bool move(const unsigned char&, const bool& turn = false);

  //set the state
  void setState(const unsigned char&);

  //set the direction w/o affecting other parts of the state
  void setDirection(const unsigned char&);

  //update player, responsible for actual movement as well as other
  // heavy calculations
  virtual void update();

  //sequence of pregiven moves is given to the character
  void follow_path(Path);

  //get the state
  inline unsigned char getState() const { return this->state; }

  //get the direction w/o the other parts of the state
  inline unsigned char getDirection() const { return this->state & 0x3; }

protected:
  //sprite that will be used to represent the person
  sf::Sprite sprite;
  sf::Texture texture;

  /*state of player (includes direction)
   * 0 0 0 0 0 0 0 0
   *     +-+ | | +-+ --- direction [0-3] - direction that person is facing
   *      |  | + ------- in motion [true/false]
   *      |  + --------- half step [t/f] - if true, person is *currently*
   *      |                                 between two tiles
   *      + ------------ direction [0-3] - direction person is moving in
   */
  unsigned char state;

  // The map that the person resides on
  TileMap* map;
};

#endif /* PERSON_HPP */

