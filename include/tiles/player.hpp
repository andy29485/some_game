///////////////////////////////////////////////////////////////////////
// player.hpp
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

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "tiles/person.hpp"
#include <cstdint>

class Player : public Person {
public:
  //Constructors
  Player(const std::string&, unsigned char state = 0);
  Player(const std::string&, int, int, unsigned char state = 0);

  //TODO figure out what else this class should do

  inline void clearFlag (unsigned flag) { this->flags |=  (1 << flag); }
  inline void setFlag   (unsigned flag) { this->flags &= ~(1 << flag); }
  inline void toggleFlag(unsigned flag) { this->flags ^=  (1 << flag); }
  inline bool checkFlag (unsigned flag) const
    { return this->flags & (1 << flag); }

private:
  //flags that can be checked later
  uint64_t flags;
};

#endif /* PLAYER_HPP */

