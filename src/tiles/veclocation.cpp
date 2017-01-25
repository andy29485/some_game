///////////////////////////////////////////////////////////////////////
// veclocation.cpp
// This file is part of Return of the Horsemen: A Tale of Calamity in a Perfect
// World
//
// Copyright (C) 2017 - GroupName
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

#include "tiles/veclocation.hpp"

VecLocation::VecLocation() 
  : state(0), Location() {}

VecLocation::VecLocation(unsigned char state) 
  : state(state), Location() {}

VecLocation::VecLocation(unsigned int x, unsigned int y)
  : state(0), Location(x, y) {}

VecLocation::VecLocation(unsigned int x, unsigned int y, unsigned char state)
  : state(state), Location(x, y) {}

//move/turn in direction
//  same as move(dir, false)
bool VecLocation::move(char dir) {
  return this->move(dir, false);
}

//move/turn in direction,
//  if bool is true move without turning
//  return true if movement did not go into the negatives
bool VecLocation::move(char dir, bool turn) {
  if(dir == this->getDirection() || turn) {
    if(dir == VecLocation::UP) {
      return this->y && (this->y-- || true);
    }
    else if(dir == VecLocation::DOWN) {
      return this->y++;
    }
    else if(dir == VecLocation::LEFT) {
      return this->x && (this->x-- || true);
    }
    else if(dir == VecLocation::RIGHT) {
      return this->x++;
    }
  }
  else {
    this->setDirection(dir);
    return true;
  }
  return false;
}

//set the state
void VecLocation::setState(unsigned char state) {
  this->state = state;
}

//set the direction w/o affecting other parts of the state
void VecLocation::setDirection(unsigned char dir) {
  this->state = (this->state & ~3) | (dir & 3); 
}

