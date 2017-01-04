///////////////////////////////////////////////////////////////////////
// tile.hpp
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

#include <SFML/Graphics/Drawable.hpp>
#include "location.hpp"

#ifndef TILE_HPP
#define TILE_HPP

class Tile : public sf::Drawable, public Location {
  //TODO
  
public:
  //Draw tile
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states);
  
  //TODO
};

#endif /* TILE_HPP */
