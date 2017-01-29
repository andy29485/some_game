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

#ifndef TILE_MAP_HPP
#define TILE_MAP_HPP

#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/Vector2.hpp>

#include "tiles/tile.hpp"

#ifdef EDITOR
  typedef std::vector< std::vector<TileBack> > TileMapBack;
#endif

class TileMap : public sf::Drawable, public sf::Vector2i {

public:
  //Constructors
  #ifdef EDITOR
    TileMap(const std::string&, const sf::Font&,
                                const bool& fromTexture = false);
    TileMap(const std::string&, const std::string&, const sf::Font&);
    TileMap(const TileMap&);
  #else
    TileMap(const std::string& texFileName, const bool& fromTexture = false);
    TileMap(const std::string& texFileName, const std::string& mapFileName);
  #endif /* EDITOR */

  //shift the position of the map, used for draw()
  bool move(const int& x, const int& y);

  //Draw map
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  //find shortest path between two locations
  std::vector<char> findPath(const sf::Vector2i&, const sf::Vector2i&);

  #ifdef EDITOR
  //[editor only] specify if tile states should be drawn when draw() is called 
  void setDrawState(const bool&);

  //[editor only] return vector iterator[const]
  inline std::vector< std::vector<Tile> >::const_iterator begin() const {
    return this->tiles.begin();
  }
  //[editor only] return vector iterator
  inline std::vector< std::vector<Tile> >::iterator begin() {
    return this->tiles.begin();
  }

  //[editor only] return vector iterator end[const]
  inline std::vector< std::vector<Tile> >::const_iterator end() const {
    return this->tiles.end();
  }
  //[editor only] return vector iterator end
  inline std::vector< std::vector<Tile> >::iterator end() {
    return this->tiles.end();
  }

  //[editor only] resize vectors
  void resize(const unsigned&, const unsigned&);

  //access vector[const
  inline const std::vector<Tile>& operator[](const std::size_t& i) const {
    return this->tiles[i];
  }
  //[editor only] access vector
  inline std::vector<Tile>& operator[](const std::size_t& i) {
    return this->tiles[i];
  }

  //[editor only] save map to file
  void save(const std::string& filename, const bool& append = false) const;

  //[editor only] restore tiles from backup 
  TileMap& operator=(const TileMapBack&);

  //[editor only] create backup of tiles 
  TileMapBack backup() const;
  #endif /* EDITOR */

  //get aspects of the map
  inline unsigned getWidth()  const { return this->tiles[0].size(); }
  inline unsigned getHeight() const { return this->tiles.size(); }
  inline unsigned getState(unsigned row, unsigned col) const
    { return this->tiles[row][col].getState(); }

  //re-renders the map
  //  unless in editor mode, in which case - make for re-rendering
  void redraw();

  #ifdef EDITOR  
  //[editor only] used to re-render the map, when in editor mode
  void _redraw();
  #endif /* EDITOR */

  //load map from file
  std::streampos load(const std::string&    filename,
                      const std::streampos& pos = 0);

private:
  //2D vector of tiles
  std::vector< std::vector<Tile> > tiles;

  //Texture containing all tiles that this map will use
  sf::Texture texTiles;

  #ifdef EDITOR
  //[editor only] font used for tiles when explicitly drawing tile state
  const sf::Font& font;

  //[editor only] True if the tile states need to be draws(numbers)
  bool            drawState;

  //[editor only] True if re-drawing is needed
  bool            needRedraw;

  //[editor only] additional render texture with state for the the editor
  sf::RenderTexture renderTextureState;
  #endif /* EDITOR */

  //RenderTexture containing image of the map, used to render map faster
  sf::RenderTexture renderTexture;
};

#endif /* TILE_MAP_HPP */

