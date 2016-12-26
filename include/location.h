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

#ifndef LOCATION_H
#define LOCATION_H

class Location {
  // x and y positions on the map
  unsigned int x, y;

  //state of player(includes direction
  unsigned char state;
  
  //constructor helper
  void init(unsigned int, unsigned int, unsigned char);
  
public:
  static const char LEFT  = 0;
  static const char EAST  = 0;

  static const char UP    = 1;
  static const char NORTH = 1;

  static const char RIGHT = 2;
  static const char WEST  = 2;

  static const char DOWN  = 3;
  static const char SOUTH = 3;

  Location();
  Location(char);
  Location(int, int);
  Location(int, int, char);

  //get direction without
  //  other parts of state
  unsigned char getDirection();
  
  //get X position
  unsigned int getX();
  
  //get Y position
  unsigned int getY();

  //move/turn in direction
  //  same as move(dir, false)
  bool move(char);
  
  //move/turn in direction,
  //  if bool is true move without turning
  bool move(char, bool);

  //set X position
  void setX(unsigned int);
  
  //set Y position
  void setY(unsigned int);

  //set the state
  void setState(unsigned char);

  //set the direction w/o affecting other parts of the state
  void setDirection(unsigned char);

  //set the x/y position
  void setPosition(unsigned int, unsigned int);

};

#endif /* LOCATION_H */
