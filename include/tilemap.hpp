///////////////////////////////////////////////////////////////////////
// tilemap.hpp
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

#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include "tile.hpp"

#ifndef TILE_MAP_HPP
#define TILE_MAP_HPP

class TileMap : public sf::Drawable {
  //2D vector of tiles
  std::vector<std::vector<Tile>> tiles;

public:
  //Draw tile
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states);
  
  //find shortest path between two locations
  std::vector<char> findPath(Location a, Location b);
  
};

#endif /* TILE_MAP_HPP */
