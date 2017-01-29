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

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#ifdef EDITOR
  #include <SFML/Graphics/Text.hpp>
  #include <SFML/Graphics/Font.hpp>

  #include <tuple>
  typedef std::tuple<unsigned short, unsigned short, unsigned char> TileBack;
#endif /* EDITOR */

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
  sf::Text       textState;
  bool           drawState;
  #endif /* EDITOR */

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
  #ifdef EDITOR
    Tile(const sf::Texture&, unsigned short, unsigned char, const sf::Font&);
    Tile(const sf::Texture&, unsigned short, unsigned short, unsigned char,
         const sf::Font&
    );
  #else
    Tile(const sf::Texture&, unsigned short, unsigned char);
    Tile(const sf::Texture&, unsigned short, unsigned short, unsigned char);
  #endif  /* EDITOR */
  
  //Draw tile
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
  
  void setBottomTile(unsigned short);
  void setTopTile(unsigned short);
  void setState(unsigned char);
  void setPosition(unsigned int, unsigned int);

  #ifdef EDITOR
  void setDrawState(const bool&);

  Tile& operator=(const TileBack&);
  TileBack backup() const;

  inline unsigned short getBottomTile() const { return this->nTextureBottom;}
  inline unsigned short getTopTile()    const { return this->nTextureTop; }
  #endif /* EDITOR */
  inline unsigned char  getState()      const { return this->state; }
};

#endif /* TILE_HPP */
