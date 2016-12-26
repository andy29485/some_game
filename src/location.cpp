///////////////////////////////////////////////////////////////////////
// location.h
// This file is part of SomeGame
//
// Copyright (C) 2017 - GroupName
//
// SomeGame is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// SomeGame is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with SomeGame. If not, see <http://www.gnu.org/licenses/>.
///////////////////////////////////////////////////////////////////////

#include "location.h"

Location::Location() {
  this->init(0, 0, 0);
}

Location::Location(char state) {
  this->init(0, 0, state);
}

Location::Location(int x, int y) {
  this->init(x, y, 0);
}

Location::Location(int x, int y, char state){
  this->init(x, y, state);
}

//get direction without
//  other parts of state
unsigned char Location::getDirection() {
  return this->state & 3;
}
  
//get X position
unsigned int Location::getX() {
  return this->x;
}

//get Y position
unsigned int Location::getY() {
  return this->y;
}

//move/turn in direction
//  same as move(dir, false)
bool Location::move(char dir) {
  return this->move(dir, false);
}

//move/turn in direction,
//  if bool is true move without turning
//  return true if movement did not go into the negatives
bool Location::move(char dir, bool turn) {
  if(dir == this->getDirection() || turn) {
    if(dir == Location::UP) {
      return this->y && (this->y-- || true);
    }
    else if(dir == Location::DOWN) {
      return this->y++;
    }
    else if(dir == Location::LEFT) {
      return this->x && (this->x-- || true);
    }
    else if(dir == Location::RIGHT) {
      return this->x++;
    }
  }
  else {
    this->setDirection(dir);
    return true;
  }
  return false;
}

//set X position
void Location::setX(unsigned int x) {
  this->x = x;
}

//set Y position
void Location::setY(unsigned int y) {
  this->y = y;
}

//set the state
void Location::setState(unsigned char state) {
  this->state = state;
}

//set the direction w/o affecting other parts of the state
void Location::setDirection(unsigned char dir) {
  this->state = (this->state & ~3) | (dir & 3); 
}

//set the x/y position
void Location::setPosition(unsigned int x, unsigned int y) {
  this->x = x;
  this->y = y;
}

void Location::init(unsigned int x, unsigned int y, unsigned char state){
  this->x     = x;
  this->y     = y;
  this->state = state;
}
