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
#include <string>
#include <fstream>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include "tiles/tile.hpp"
#include "tiles/location.hpp"

#ifndef TILE_MAP_HPP
#define TILE_MAP_HPP

class TileMap : public sf::Drawable, public Location {
  //2D vector of tiles
  std::vector<std::vector<Tile>> tiles;

  //Texture containing all tiles that this map will use
  sf::Texture texTiles;

  //RenderTexture containing image of the map, used to render map faster
  sf::RenderTexture renderTexture;

public:
  //Constructors
  //TODO - do we need more?
  TileMap(const std::string& texFileName, const std::string& mapFileName);

  bool move(int x, int y);

  //Draw tile
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  //find shortest path between two locations
  std::vector<char> findPath(Location a, Location b);

  //save map to file
  void save(const std::string& filename, bool append = false);

  //load map from file
  std::streampos load(const std::string& filename, std::streampos pos = 0);
};

#endif /* TILE_MAP_HPP */
