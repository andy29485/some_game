///////////////////////////////////////////////////////////////////////
// tilemap.hpp
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

#include <vector>
#include <string>
#include <fstream>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

#include "tiles/tile.hpp"
#include "tiles/location.hpp"

#ifndef TILE_MAP_HPP
#define TILE_MAP_HPP

#ifdef EDITOR
  typedef std::vector< std::vector<TileBack> > TileMapBack;
#endif

class TileMap : public sf::Drawable, public Location {
  //2D vector of tiles
  std::vector< std::vector<Tile> > tiles;

  //Texture containing all tiles that this map will use
  sf::Texture texTiles;

  #ifdef EDITOR
    sf::Font& font;
    bool      drawState;
  #endif

  //RenderTexture containing image of the map, used to render map faster
  sf::RenderTexture renderTexture;
  #ifdef EDITOR
    //additional render texture with state for the the editor
    sf::RenderTexture renderTextureState;
  #endif

public:
  //Constructors
  #ifdef EDITOR
    TileMap(const std::string&, sf::Font&, const bool& fromTexture = false);
    TileMap(const std::string&, const std::string&, sf::Font&);
    TileMap(const TileMap&);
  #else
    TileMap(const std::string& texFileName, const bool& fromTexture = false);
    TileMap(const std::string& texFileName, const std::string& mapFileName);
  #endif

  bool move(int x, int y);

  //Draw tile
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  //find shortest path between two locations
  std::vector<char> findPath(Location a, Location b);

  #ifdef EDITOR
    void setDrawState(const bool&);

    //return vector iterator[const]
    inline std::vector< std::vector<Tile> >::const_iterator begin() const {
      return this->tiles.begin();
    }
    //return vector iterator
    inline std::vector< std::vector<Tile> >::iterator begin() {
      return this->tiles.begin();
    }

    //return vector iterator end[const]
    inline std::vector< std::vector<Tile> >::const_iterator end() const {
      return this->tiles.end();
    }
    //return vector iterator end
    inline std::vector< std::vector<Tile> >::iterator end() {
      return this->tiles.end();
    }

    //get size of map
    inline unsigned getWidth()  const { return this->tiles[0].size(); }
    inline unsigned getHeight() const { return this->tiles.size(); }

    //resize vectors
    void resize(unsigned int, unsigned int);

    //access vector[const
    inline const std::vector<Tile>& operator[](std::size_t i) const {
      return this->tiles[i];
    }
    //access vector
    inline std::vector<Tile>& operator[](std::size_t i) {
      return this->tiles[i];
    }

    //save map to file
    void save(const std::string& filename, bool append = false) const;

    TileMap& operator=(const TileMapBack&);

    TileMapBack backup() const;
  #endif

  void redraw();

  //load map from file
  std::streampos load(const std::string&    filename,
                      const std::streampos& pos = 0);
};

#endif /* TILE_MAP_HPP */
