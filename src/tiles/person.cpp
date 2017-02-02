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

#ifdef DEBUG
  #include <stdio.h>
#endif /* DEBUG */

#include <SFML/Graphics/RenderTarget.hpp>

#include "tiles/person.hpp"
#include "tiles/tile.hpp"
#include "tiles/tilemap.hpp"

void _move(unsigned char&, sf::Sprite&, int);


const unsigned char Person::LEFT  = 0;
const unsigned char Person::WEST  = 0;

const unsigned char Person::UP    = 1;
const unsigned char Person::NORTH = 1;

const unsigned char Person::RIGHT = 2;
const unsigned char Person::EAST  = 2;

const unsigned char Person::DOWN  = 3;
const unsigned char Person::SOUTH = 3;

Person::Person(const std::string& filename, TileMap* map,
               const unsigned char& state)
: sf::Vector2i(),
  state(state)
{
  this->map = map;
  texture.loadFromFile(filename);
  sprite.setTexture(texture);
  sprite.setTextureRect( sf::IntRect(
    0,
    Tile::TILE_SIZE * (state & 0x3),
    Tile::TILE_SIZE,
    Tile::TILE_SIZE
  ));
}

Person::Person(const std::string& filename, TileMap* map,
               const int& x, const int& y, const unsigned char& state)
: sf::Vector2i(x, y),
  state(state)
{
  this->map = map;
  texture.loadFromFile(filename);
  sprite.setTexture(texture);
  sprite.setPosition(x * Tile::TILE_SIZE, y * Tile::TILE_SIZE);
  sprite.setTextureRect( sf::IntRect(
    0,
    Tile::TILE_SIZE * (state & 0x3),
    Tile::TILE_SIZE,
    Tile::TILE_SIZE
  ));
}

void Person::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(this->sprite);
}

//move/turn in direction,
//  if bool is true move without turning
//  return true if movement did not go into the negatives
bool Person::move(const unsigned char& dir,const bool& turn) {
  //face direction of movement
  if(dir != this->getDirection() && !turn) {
    this->setDirection(dir);
    return true;
  }

  //currently in motion, cannot move yet
  if(this->state & 0x4) { return false; }

  int x, y;

  switch(dir & 0x3) {
    case Person::UP:
      x = 0;
      y = -1;
      break;

    case Person::DOWN:
      x = 0;
      y = 1;
      break;

    case Person::LEFT:
      x = -1;
      y = 0;
      break;

    case Person::RIGHT:
      x = 1;
      y = 0;
  }

  if(this->y + y < 0 || this->y + y >= this->map->getHeight()) { return false; }
  if(this->x + x < 0 || this->x + x >= this->map->getWidth())  { return false; }

  #ifdef DEBUG
  printf("next map state: %d\n", 
         (*this->map)[this->y + y][this->x + x].getState()
  );
  #endif /* DEBUG */

  if(!(*this->map)[this->y + y][this->x + x].getState()) { return false; }

  this->state &=     ~0x30; //clear old direction flag
  this->state |= dir << 4;  //set direction of current movement
  this->state |=      0xC;  //set current half-step and movement flags

  //increment location of player (but not the sprite location)
  this->x += x;
  this->y += y;
  return true;
}

//update player, responsible for actual movement as well as other
// heavy calculations
void Person::update() {
  //move player over one half step
  _move(this->state, this->sprite, (this->x + this->y)%2);
  #ifdef DEBUG
  printf("player updating\n");
  #endif /* DEBUG */
}

void follow_path(Path path) {
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
    #ifdef DEBUG
    printf("player text rect: (%d, %d - %dx%d)\n", 
      0,
      Tile::TILE_SIZE * (state & 0x3),
      Tile::TILE_SIZE,
      Tile::TILE_SIZE
    );
    #endif /* DEBUG */

    //TODO - this may not be needed as it is taken care of when stepping
    //       fully onto the tile

    sprite.setTextureRect( sf::IntRect(
      0,                                //Not in the middle of a step
      Tile::TILE_SIZE * (state & 0x3),  //direction facing
      Tile::TILE_SIZE,
      Tile::TILE_SIZE
    ));
    return;
  }

  switch((state >> 4) & 0x3) {
    case Person::UP:
      sprite.move(0, -(int)Tile::TILE_SIZE/2);
      break;

    case Person::DOWN:
      sprite.move(0, (int)Tile::TILE_SIZE/2);
      break;

    case Person::LEFT:
      sprite.move(-(int)Tile::TILE_SIZE/2, 0);
      break;

    case Person::RIGHT:
      sprite.move((int)Tile::TILE_SIZE/2, 0);
  }
  
  unsigned char half_step = state & 0x8;

  #ifdef DEBUG
  printf("player moved: (%.0f, %.0f) - %x\n", 
    sprite.getPosition().x, 
    sprite.getPosition().y,
    state & 0xC
  );
  printf("player text rect: (%d, %d - %dx%d)\n",
    Tile::TILE_SIZE * (half_step ? 1 : 0) * (1 + left_side),
    Tile::TILE_SIZE * (state & 0x3),
    Tile::TILE_SIZE,
    Tile::TILE_SIZE
  );
  #endif /* DEBUG */

  /*set what the player looks like,
   * fisrt arg    - determines if in halfstep - on left or right foot - (0 both)
   * second       - direction facing
   * third/fourth - constant b/c players do not get fatter nor do they duplicate
   */
  sprite.setTextureRect( sf::IntRect(
    Tile::TILE_SIZE * (half_step ? 1 : 0) * (1 + left_side),
    Tile::TILE_SIZE * (state & 0x3),
    Tile::TILE_SIZE,
    Tile::TILE_SIZE
  ));

  //clear movement/half step flags
  state &= ~0xC;
  state |= half_step >> 1; // but if player *was* in half step, keep moving
}

