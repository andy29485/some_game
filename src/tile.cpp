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

#include "tile.hpp"

inline sf::IntRect rect(unsigned, const sf::Texture&, unsigned);

Tile::Tile(const sf::Texture& tex, unsigned short bottom, unsigned char state) :
#ifdef EDITOR
  nTextureBottom(bottom),
  nTextureTop(0),
#endif
spriteBottom(tex, rect(bottom, tex, Tile::TILE_SIZE)),
spriteTop(),
state(state) {
  this->texTiles = &tex;
}

Tile::Tile(const sf::Texture& tex, unsigned short bottom, unsigned short top,
           unsigned char state) :
#ifdef EDITOR
  nTextureBottom(bottom),
  nTextureTop(top),
#endif
spriteBottom(tex, rect(bottom, tex, Tile::TILE_SIZE)),
spriteTop(   tex, rect(top,    tex, Tile::TILE_SIZE)),
state(state) {
  this->texTiles = &tex;
}
  
//Draw tile
void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(this->spriteBottom, states);
  if(this->spriteTop.getTextureRect().width != 0)
    target.draw(this->spriteTop,  states);
}

void Tile::setState(unsigned char state) {
  this->state = state;
}

#ifdef EDITOR
  void Tile::setBottomTile(unsigned short nTileNum) {
    this->nTextureBottom = nTileNum;
    this->spriteBottom.setTextureRect(rect(nTileNum,
                                           *this->texTiles, Tile::TILE_SIZE)
      );
  }

  void Tile::setTopTile(unsigned short nTileNum) {
    this->nTextureTop = nTileNum;
    if(nTileNum) {
      this->spriteTop.setTextureRect(rect(nTileNum,
                                          *this->texTiles, Tile::TILE_SIZE)
      );
    }
    else {
      this->spriteTop.setTextureRect(sf::IntRect());
    }
  }

  unsigned short Tile::getBottomTile() {
    return this->nTextureBottom;
  }

  unsigned short Tile::getTopTile() {
    return this->nTextureTop;
  }
#endif

unsigned char Tile::getState() {
  return this->state;
}

inline sf::IntRect rect(unsigned num, const sf::Texture& tex, unsigned size) {
  return sf::IntRect(num/tex.getSize().x*size*size,
                    (num%(tex.getSize().x/size))*size,
                     size,
                     size);
}

