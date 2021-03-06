///////////////////////////////////////////////////////////////////////
// tilemap.cpp
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

#include <sys/stat.h>
#include <fstream>
#include <algorithm>

#ifdef DEBUG
  #include <stdio.h>
#endif /* DEBUG */

#include "tiles/tilemap.hpp"

inline bool fileExists(const std::string& path);

//Constructors
#ifdef EDITOR
TileMap::TileMap(const std::string& texFileName, const sf::Font& font,
                 const bool& fromTexture)
: drawState(false),
  font(font)
{
  this->texTiles.loadFromFile(texFileName);
  if(fromTexture) {
    this->resize((unsigned)(this->texTiles.getSize().x/Tile::TILE_SIZE),
                 (unsigned)(this->texTiles.getSize().y/Tile::TILE_SIZE));
    unsigned short i = ~0;
    for (auto it = this->tiles.begin(); it!=this->tiles.end(); ++it) {
      for (auto tile = it->begin(); tile != it->end(); ++tile) {
        tile->setBottomTile((unsigned short)(++i));
        tile->setTopTile(0);
      }
    }
  }
  else
    this->tiles.resize(100,
                       std::vector<Tile>(100, Tile(this->texTiles,0,0,font))
    );
  this->renderTexture.create(     Tile::TILE_SIZE*100, Tile::TILE_SIZE*100);
  this->renderTextureState.create(Tile::TILE_SIZE*100, Tile::TILE_SIZE*100);
  this->redraw();
}

TileMap::TileMap(const std::string& texFileName,
                 const std::string& mapFileName, const sf::Font& font)
: drawState(false),
  font(font)
{
  this->texTiles.loadFromFile(texFileName);
  if(fileExists(mapFileName)) {
    this->load(mapFileName);
  }
  else {
    this->tiles.resize(100,
                       std::vector<Tile>(100, Tile(this->texTiles,0,0,font))
    );
    this->renderTexture.create(     Tile::TILE_SIZE*100, Tile::TILE_SIZE*100);
    this->renderTextureState.create(Tile::TILE_SIZE*100, Tile::TILE_SIZE*100);
    this->redraw();
  }
}

TileMap::TileMap(const TileMap& map)
: tiles(map.tiles),
  texTiles(map.texTiles),
  font(map.font),
  drawState(map.drawState)
{
  this->renderTexture.create(     Tile::TILE_SIZE*this->getWidth(),
                                  Tile::TILE_SIZE*this->getHeight());
  this->renderTextureState.create(Tile::TILE_SIZE*this->getWidth(),
                                  Tile::TILE_SIZE*this->getHeight());
  this->redraw();
}
#else
TileMap::TileMap(const std::string& texFileName, const bool& fromTexture) {
  this->texTiles.loadFromFile(texFileName);
  if(fromTexture) {
    this->resize((unsigned)(this->texTiles.getSize().x/Tile::TILE_SIZE),
                 (unsigned)(this->texTiles.getSize().y/Tile::TILE_SIZE));
    unsigned short i = ~0;
    for (auto it = this->tiles.begin(); it!=this->tiles.end(); ++it) {
      for (auto tile = it->begin(); tile != it->end(); ++tile) {
        tile->setBottomTile((unsigned short)(++i));
        tile->setTopTile(0);
      }
    }
  }
  else
    this->tiles.resize(100, std::vector<Tile>(100, Tile(this->texTiles,0,0)));
  this->renderTexture.create(Tile::TILE_SIZE * 100, Tile::TILE_SIZE * 100);
  this->redraw();
}

TileMap::TileMap(const std::string& texFileName,
                 const std::string& mapFileName) {
  this->texTiles.loadFromFile(texFileName);
  if(fileExists(mapFileName)) {
    this->load(mapFileName);
  }
  else {
    this->tiles.resize(100, std::vector<Tile>(100, Tile(this->texTiles,0,0)));
    this->renderTexture.create(Tile::TILE_SIZE * 100, Tile::TILE_SIZE * 100);
    this->redraw();
  }
}
#endif /* EDITOR */

bool TileMap::move(const int& x, const int& y) {
  //TODO - figure out why this was here
  //if(   (-y < this->y)
  //   || (-x < this->x)
  //   || (y != 0 && this->y + y - 1 < -this->getHeight())
  //   || (x != 0 && this->x + x - 1 < -this->getWidth())
  //  ) {
  //  return false;
  //}

  this->x += x;
  this->y += y;

  return true;
}

//Draw tile
void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  sf::Sprite sprite;
  sprite.setTexture(this->renderTexture.getTexture());
  if(this->x >= 0 && this->y >= 0) {
    sprite.setPosition(this->x*Tile::TILE_SIZE,
                       this->y*Tile::TILE_SIZE
    );
  }
  else {
    sprite.setPosition(0, 0);
    sprite.setTextureRect(sf::IntRect(-this->x*Tile::TILE_SIZE,
                                      -this->y*Tile::TILE_SIZE,
                                      sprite.getLocalBounds().width,
                                      sprite.getLocalBounds().height)
    );
  }
  target.draw(sprite, states);

  #ifdef EDITOR
  if(this->drawState) {
    sf::Sprite sprite2;
    sprite2.setTexture(this->renderTextureState.getTexture());
    if(this->x >= 0 && this->y >= 0) {
      sprite2.setPosition(this->x*Tile::TILE_SIZE,
                          this->y*Tile::TILE_SIZE
      );
    }
    else {
      sprite2.setPosition(0, 0);
      sprite2.setTextureRect(sf::IntRect(-this->x*Tile::TILE_SIZE,
                                         -this->y*Tile::TILE_SIZE,
                                         sprite2.getLocalBounds().width,
                                         sprite2.getLocalBounds().height)
      );
    }
    target.draw(sprite2, states);
  }
  #endif /* EDITOR */
}

//find shortest path between two locations
std::vector<char> TileMap::findPath(const sf::Vector2i& start_loc,
                                    const sf::Vector2i& end_loc) {
  //TODO - findpath
}

#ifdef EDITOR
void TileMap::setDrawState(const bool& drawState) {
  this->drawState = drawState;
}

void TileMap::resize(const unsigned& width, const unsigned& height) {
  #ifdef DEBUG
  printf("resize: %d, %d\n", width, height);
  #endif /* DEBUG */

  if (width == 0 || height == 0) {
    return;
  }

  this->renderTextureState.create(Tile::TILE_SIZE*width,
                                  Tile::TILE_SIZE*height);
  this->renderTexture.create(Tile::TILE_SIZE*width, Tile::TILE_SIZE*height);

  this->tiles.reserve(height);
  this->tiles.resize(height);

  int j = 0;
  for (auto it = this->tiles.begin(); it!=this->tiles.end(); ++it) {
    it->reserve(width);
    it->resize(width, Tile(this->texTiles, 0, 0, this->font));

    int i = 0;
    for (auto tile = it->begin(); tile != it->end(); ++tile) {
      tile->setPosition(i, j);
      i += Tile::TILE_SIZE;
    }
    j += Tile::TILE_SIZE;
  }

  this->redraw();
}

void TileMap::save(const std::string& filename, const bool& append) const {
  unsigned int width  = this->tiles.size();
  unsigned int height = this->tiles[0].size();
  unsigned short tmps;
  unsigned char  tmpc;
  std::ofstream data;

  if(append) {
    data.open(filename.c_str(),
              std::ios::out | std::ios::binary | std::ios::app);
  }
  else {
    data.open(filename.c_str(), std::ios::out | std::ios::binary);
  }

  data.write((char*)&width,  sizeof(width));
  data.write((char*)&height, sizeof(height));

  for (auto it = this->tiles.begin(); it!=this->tiles.end(); ++it) {
    for (auto tile = it->begin(); tile!=it->end(); ++tile) {
      tmps = tile->getBottomTile();
      data.write((char*)&tmps, sizeof(tmps));
      if(tmps) {
        tmps = tile->getTopTile();
        data.write((char*)&tmps, sizeof(tmps));
        tmpc = tile->getState();
        data.write((char*)&tmpc, sizeof(tmpc));
      }
    }
  }
  data.close();
}
#endif /* EDITOR */

std::streampos TileMap::load(const std::string& filename,
                             const std::streampos& pos) {
  std::ifstream data(filename.c_str(), std::ios::in | std::ios::binary);
  data.seekg(pos);

  unsigned int w, h;
  unsigned short tmps;
  unsigned char  tmpc;

  data.read((char*)&w, sizeof(w));
  data.read((char*)&h, sizeof(h));

  #ifdef EDITOR
  this->tiles.resize(h, std::vector<Tile>(w, Tile(this->texTiles, 
                                                  0, 0, this->font))
  );
  this->renderTextureState.create(Tile::TILE_SIZE * w, Tile::TILE_SIZE * h);
  #else
  this->tiles.resize(h, std::vector<Tile>(w, Tile(this->texTiles, 0, 0)));
  #endif /* EDITOR */

  this->renderTexture.create(Tile::TILE_SIZE * w, Tile::TILE_SIZE * h);

  for (auto it = this->tiles.begin(); it!=this->tiles.end(); ++it) {
    for (auto tile = it->begin(); tile != it->end(); ++tile) {
      data.read((char*)&tmps, sizeof(tmps));
      if(tmps) {
        tile->setBottomTile(tmps);

        data.read((char*)&tmps, sizeof(tmps));
        tile->setTopTile(tmps);

        data.read((char*)&tmpc, sizeof(tmpc));
        tile->setState(tmpc);
      }
      else {
        tile->setBottomTile(0);
        tile->setTopTile(0);
        tile->setState(0);
      }
    }
  }
  std::streampos new_pos = data.tellg();
  data.close();

  this->redraw();

  return new_pos;
}

void TileMap::redraw() {
#ifdef EDITOR
  this->needRedraw = true;
}

void TileMap::_redraw() {
  if(!this->needRedraw)
    return;

  this->needRedraw = false;
  this->renderTextureState.clear(sf::Color::Transparent);
#endif /* EDITOR */
  this->renderTexture.clear();

  unsigned int w, h;

  h = 0;
  for (auto it = this->tiles.begin(); it!=this->tiles.end(); ++it) {
    w = 0;
    for (auto tile = it->begin(); tile != it->end(); ++tile) {
      tile->setPosition(w, h);

      #ifdef EDITOR
      tile->setDrawState(true);
      this->renderTextureState.draw(*tile);

      tile->setDrawState(false);
      #endif /* EDITOR */
      this->renderTexture.draw(*tile);

      w += Tile::TILE_SIZE;
    }
    h += Tile::TILE_SIZE;
  }
  this->renderTexture.display();

  #ifdef EDITOR
  this->renderTextureState.display();
  #endif /* EDITOR */
}

#ifdef EDITOR
TileMap& TileMap::operator=(const TileMapBack& backup_map) {
  this->resize(backup_map[0].size(), backup_map.size());

  auto it_m = backup_map.begin();
  auto it_t = this->begin();
  for (; it_m!=backup_map.end(); ++it_m, ++it_t) {
    auto tile_m = it_m->begin();
    auto tile_t = it_t->begin();
    for (; tile_m != it_m->end(); ++tile_m, ++tile_t) {
      *tile_t = *tile_m;
    }
  }
  
  this->redraw();

  return *this;
}

TileMapBack TileMap::backup() const {
  TileMapBack backup_map(this->getHeight(),
                 std::vector<TileBack>(this->getWidth(), TileBack(0,0,0))
  );

  auto it_m = backup_map.begin();
  auto it_t = this->begin();
  for (; it_m!=backup_map.end(); ++it_m, ++it_t) {
    auto tile_m = it_m->begin();
    auto tile_t = it_t->begin();
    for (; tile_m != it_m->end(); ++tile_m, ++tile_t) {
      *tile_m = tile_t->backup();
    }
  }

  return backup_map;
}
#endif /* EDITOR */

inline bool fileExists(const std::string& path) {
  struct stat fileStat; 
  return (stat (path.c_str(), &fileStat) == 0);
}

