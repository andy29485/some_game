///////////////////////////////////////////////////////////////////////
// location.cpp
// This file is part of SomeGame
//
// Copyright (C) 2017 - GroupName
//
// SomeGame is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
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

#include "tiles/location.hpp"

Location::Location() : x(0), y(0) {}

Location::Location(int x, int y) : x(x), y(y) {}
  
//set X position
void Location::setX(unsigned int x) {
  this->x = x;
}

//set Y position
void Location::setY(unsigned int y) {
  this->y = y;
}

//add to X position
void Location::addX(unsigned int x) {
  this->x += x;
}

//add to Y position
void Location::addY(unsigned int y) {
  this->y += y;
}

//set the x/y position
void Location::setPosition(unsigned int x, unsigned int y) {
  this->x = x;
  this->y = y;
}
