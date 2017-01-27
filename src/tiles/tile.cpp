///////////////////////////////////////////////////////////////////////
// tile.hpp
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

#include <SFML/Graphics/RenderTarget.hpp>
#include "tiles/tile.hpp"
#ifdef EDITOR
  #include <string>
  #include <SFML/Graphics/Rect.hpp>
#endif

inline sf::IntRect rect(const unsigned&, const sf::Texture&);

#ifdef EDITOR
  Tile::Tile(const sf::Texture& tex, unsigned short bottom,
             unsigned char state, const sf::Font& font) :
  nTextureBottom(bottom),
  nTextureTop(0),
  textState(std::to_string((int)state), font, 14),
  drawState(false),
  spriteBottom(tex, rect(bottom, tex)),
  spriteTop(   tex, sf::IntRect()),
  state(state) {
    this->texTiles = &tex;
  }

  Tile::Tile(const sf::Texture& tex, unsigned short bottom, unsigned short top,
             unsigned char state, const sf::Font& font) :
  nTextureBottom(bottom),
  nTextureTop(top),
  textState(std::to_string((int)state), font, 14),
  drawState(false),
  spriteBottom(tex, rect(bottom, tex)),
  spriteTop(   tex, rect(top,    tex)),
  state(state) {
    this->texTiles = &tex;
  }
#else
  Tile::Tile(const sf::Texture& tex, unsigned short bottom, unsigned char 
state) :
  spriteBottom(tex, rect(bottom, tex)),
  spriteTop(   tex, sf::IntRect()),
  state(state) {
    this->texTiles = &tex;
  }

  Tile::Tile(const sf::Texture& tex, unsigned short bottom, unsigned short top,
             unsigned char state) :
  spriteBottom(tex, rect(bottom, tex)),
  spriteTop(   tex, rect(top,    tex)),
  state(state) {
    this->texTiles = &tex;
  }
#endif
  
//Draw tile
void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(this->spriteBottom, states);

  auto& rect = this->spriteTop.getTextureRect();
  if(rect.width != 0 && rect.height != 0)
    target.draw(this->spriteTop,  states);

  #ifdef EDITOR
    if(this->drawState)
      target.draw(this->textState, states);
  #endif
}

void Tile::setState(unsigned char state) {
  this->state = state;
  #ifdef EDITOR
    this->textState.setString(std::to_string((int)state));
    sf::FloatRect bounds = this->textState.getLocalBounds();
    this->textState.setOrigin(bounds.width/2, bounds.height/2);
  #endif
}


void Tile::setPosition(unsigned int x, unsigned int y) {
  this->spriteBottom.setPosition(x, y);
  this->spriteTop.setPosition(x, y);
  #ifdef EDITOR
    this->textState.setPosition(x + Tile::TILE_SIZE/2, y + Tile::TILE_SIZE/2);
  #endif
}


void Tile::setBottomTile(unsigned short nTileNum) {
  #ifdef EDITOR
    this->nTextureBottom = nTileNum;
  #endif
  this->spriteBottom.setTextureRect(rect(nTileNum, *this->texTiles));
}

void Tile::setTopTile(unsigned short nTileNum) {
  #ifdef EDITOR
    this->nTextureTop = nTileNum;
  #endif
  if(nTileNum) {
    this->spriteTop.setTextureRect(rect(nTileNum, *this->texTiles));
  }
  else {
    this->spriteTop.setTextureRect(sf::IntRect());
  }
}

#ifdef EDITOR
  Tile& Tile::operator=(const TileBack& backup_tile) {
    this->setBottomTile(std::get<0>(backup_tile));
    this->setTopTile(std::get<1>(backup_tile));
    this->setState(std::get<2>(backup_tile));

    return *this;
  }

  TileBack Tile::backup() const {
    return std::make_tuple(this->nTextureBottom, this->nTextureTop, this->state);
  }

  void Tile::setDrawState(const bool& drawState) {
    this->drawState = drawState;
  }
#endif

inline sf::IntRect rect(const unsigned& num, const sf::Texture& tex) {
  return sf::IntRect((num%(tex.getSize().x/Tile::TILE_SIZE))*Tile::TILE_SIZE,
                    (num*Tile::TILE_SIZE)/tex.getSize().x*Tile::TILE_SIZE,
                     Tile::TILE_SIZE,
                     Tile::TILE_SIZE);
}

