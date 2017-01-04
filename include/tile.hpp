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
#include <SFML/Graphics/Texture.hpp>
#include "location.hpp"

#ifndef TILE_HPP
#define TILE_HPP

class Tile : public sf::Drawable {
  //Tiles should be made from bottom up,
  //  top texture will generarly have some transparancy to it.
  //  E.G. bottom will be grass, top will also have a bridge on it
  //       - thus we get a bridge on grass, but that exact same bridge can
  //         also appear on dirt 
  //TODO this is needed for map-edditing, but will server no purpose in-game,
  //     (delete these variables later)
  #ifdef EDITOR
    unsigned short nTextureBottom;
    unsigned short nTextureTop;
  #endif
  //TODO Tile textures should probably be rectangles
  sf::Texture texBottom;
  sf::Texture texTop;
  
  //type of tile that this is:
  //  0   - can walk on
  //  1   - cannot walk on
  //  10+ - triggers some map even on step
  unsigned char state;

  
public:
  //Constructors
  Tile(unsigned short, unsigned char);
  Tile(unsigned short, unsigned short, unsigned char);
  
  //Draw tile
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states);
  
  #ifdef EDITOR
    void setBottomTile(unsigned short, sf::Image&);
    void setTopTile(unsigned short, sf::Image&);
    unsigned char setState();

    unsigned short getBottomTile();
    unsigned short getTopTile();
  #endif
  unsigned char getState();
};

#endif /* TILE_HPP */
