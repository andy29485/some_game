///////////////////////////////////////////////////////////////////////
// veclocation.hpp
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

#ifndef VEC_LOCATION_HPP
#define VEC_LOCATION_HPP

#include "location.hpp"

class VecLocation : public Location {
  //state of player (includes direction)
  unsigned char state;
  
public:
  static const char LEFT  = 0;
  static const char EAST  = 0;

  static const char UP    = 1;
  static const char NORTH = 1;

  static const char RIGHT = 2;
  static const char WEST  = 2;

  static const char DOWN  = 3;
  static const char SOUTH = 3;

  VecLocation();
  VecLocation(unsigned char);
  VecLocation(unsigned int, unsigned int);
  VecLocation(unsigned int, unsigned int, unsigned char);

  //move/turn in direction
  //  same as move(dir, false)
  bool move(char);
  
  //move/turn in direction,
  //  if bool is true move without turning
  bool move(char, bool);

  //set the state
  void setState(unsigned char);

  //set the state
  unsigned char getState();

  //set the direction w/o affecting other parts of the state
  void setDirection(unsigned char);

  //set the direction w/o affecting other parts of the state
  unsigned char getDirection();
};

#endif /* VEC_LOCATION_HPP */

