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
#include "tiles/tile.hpp"
#include "tiles/tilemap.hpp"

void _move(unsigned char&, sf::Sprite&, int);

Person::Person(const std::string& filename, unsigned char state)
: sf::Vector2i(),
  state(state)
{
  sf::Texture texture;
  texture.loadFromFile(filename);
  sprite.setTexture(texture);
}

Person::Person(const std::string& filename, int x, int y, unsigned char state)
: sf::Vector2i(x, y),
  state(state)
{
  sf::Texture texture;
  texture.loadFromFile(filename);
  sprite.setTexture(texture);
}

void Person::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(this->sprite);
}

//move/turn in direction,
//  if bool is true move without turning
//  return true if movement did not go into the negatives
bool Person::move(const unsigned char& dir, const TileMap& map, 
                  const bool& turn) {
  //face direction of movement
  if(dir != this->getDirection() && !turn) {
    this->setDirection(dir);
    return true;
  }

  //currently in motion, cannot move yet
  if(this->state & 0x4) { return false; }

  int x, y;

  switch(dir & 0x3) {
    case UP:
      x = 0;
      y = -1;
      break;

    case DOWN:
      x = 0;
      y = 1;
      break;

    case LEFT:
      x = -1;
      y = 0;
      break;

    case RIGHT:
      x = 1;
      y = 0;
  }

  this->state &=      ~0x30;
  this->state |= dir & 0x30;

  if(this->y + y < 0 || this->y + y >= map.getHeight()) { return false; }
  if(this->x + x < 0 || this->x + x >= map.getWidth())  { return false; }

  if(!map[this->y + y][this->x + x].getState()) { return false; }

  this->x += x;
  this->y += y;
  return true;
}

//update player, responsible for actual movement as well as other
// heavy calculations
void Person::update() {
  //move player over one half step
  _move(this->state, this->sprite, (this->x + this->y)%2);
}

void follow_path(TileMap map, Path path) {
  //TODO
}

//set the state
void Person::setState(const unsigned char& state) {
  this->state = state;
}

//set the direction w/o affecting other parts of the state
void Person::setDirection(const unsigned char& dir) {
  this->state = (this->state & ~0x3) | (dir & 0x3); 
}

void _move(unsigned char& state, sf::Sprite& sprite, int left_side) {
  //not in motion, nothing to be done 
  if(!(state & 0x4)) {
    return;
  }

  switch((state >> 4) & 0x3) {
    case Person::UP:
      sprite.move(0, -Tile::TILE_SIZE/2);
      break;

    case Person::DOWN:
      sprite.move(0, Tile::TILE_SIZE/2);
      break;

    case Person::LEFT:
      sprite.move(-Tile::TILE_SIZE/2, 0);
      break;

    case Person::RIGHT:
      sprite.move(Tile::TILE_SIZE/2, 0);
  }
  
  unsigned char half_step = state & 0x8;

  sprite.setTextureRect( sf::IntRect(
    Tile::TILE_SIZE * (half_step ? 1 : 0) * (1 + left_side),
    Tile::TILE_SIZE * (state & 0x3),
    Tile::TILE_SIZE,
    Tile::TILE_SIZE
  ));

  state &= ~0xC;
  state |= half_step << 1;
}

