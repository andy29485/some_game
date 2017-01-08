///////////////////////////////////////////////////////////////////////
// location.hpp
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

#ifndef LOCATION_HPP
#define LOCATION_HPP

class Location {
protected:
  // x and y positions on the map
  unsigned int x, y;
  
public:
  Location();
  Location(int, int);

  //get X position
  inline unsigned int getX() const { return this->x; }
  
  //get Y position
  inline unsigned int getY() const { return this->y; }

  //set X position
  void setX(unsigned int);
  
  //set Y position
  void setY(unsigned int);
  
  //add to X position
  void addX(unsigned int);

  //add to Y position
  void addY(unsigned int);

  void setPosition(unsigned int, unsigned int);
};

#endif /* LOCATION_H */
