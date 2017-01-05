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
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
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
  #ifdef EDITOR
    unsigned short nTextureBottom;
    unsigned short nTextureTop;
  #endif
  sf::Sprite spriteBottom;
  sf::Sprite spriteTop;

  //Pointer to image with tiles
  const sf::Texture* texTiles;

  //type of tile that this is:
  //  0   - can walk on
  //  1   - cannot walk on
  //  10+ - triggers some map even on step
  unsigned char state;

  
public:
  static const unsigned int TILE_SIZE = 30;

  //Constructors
  Tile(const sf::Texture&, unsigned short, unsigned char);
  Tile(const sf::Texture&, unsigned short, unsigned short, unsigned char);
  
  //Draw tile
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
  
  void setState(unsigned char);
  #ifdef EDITOR
    void setBottomTile(unsigned short);
    void setTopTile(unsigned short);

    unsigned short getBottomTile();
    unsigned short getTopTile();
  #endif
  unsigned char getState();
};

#endif /* TILE_HPP */
