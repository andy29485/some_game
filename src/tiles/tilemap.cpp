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
#include <vector>
#include <algorithm>

#ifdef DEBUG
  #include <stdio.h>
#endif

#include "tiles/tilemap.hpp"

inline bool fileExists(const std::string& path);

//Constructors
#ifdef EDITOR
  TileMap::TileMap(const std::string& texFileName, sf::Font& font,
                   const bool& fromTexture) :
  drawState(false),
  font(font) {
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
                   const std::string& mapFileName, sf::Font& font) :
  drawState(false),
  font(font) {
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

  TileMap::TileMap(const TileMap& map) :
  tiles(map.tiles),
  texTiles(map.texTiles),
  font(map.font),
  drawState(map.drawState) {
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
#endif

bool TileMap::move(int x, int y) {
  if(   (y != 0 && this->getY() < -y)
     || (x != 0 && this->getX() < -x)
     || (y != 0 && this->getY() + y > tiles.size())
     || (x != 0 && this->getX() + x > tiles[0].size())
    ) {
    return false;
  }

  this->addX(x);
  this->addY(y);

  return true;
}

//Draw tile
void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  sf::Sprite sprite;

  #ifdef EDITOR
    if(this->drawState)
      sprite.setTexture(this->renderTextureState.getTexture());
    else
      sprite.setTexture(this->renderTexture.getTexture());
  #else
    sprite.setTexture(this->renderTexture.getTexture());
  #endif

  sprite.setPosition(this->getX()*Tile::TILE_SIZE,
                     this->getY()*Tile::TILE_SIZE
  );

  target.draw(sprite, states);
}

//find shortest path between two locations
std::vector<char> TileMap::findPath(Location a, Location b) {
  //TODO - findpath
}

#ifdef EDITOR
  void TileMap::setDrawState(const bool& drawState) {
    this->drawState = drawState;
  }

  void TileMap::resize(unsigned int width, unsigned int height) {
    #ifdef DEBUG
      printf("resize: %d, %d\n", width, height);
    #endif
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

  void TileMap::save(const std::string& filename, bool append) const {
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
#endif

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
  #endif

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
  this->renderTexture.clear();
  #ifdef EDITOR
    this->renderTextureState.clear();
  #endif

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
      #endif
      this->renderTexture.draw(*tile);

      w += Tile::TILE_SIZE;
    }
    h += Tile::TILE_SIZE;
  }
  this->renderTexture.display();
  #ifdef EDITOR
    this->renderTextureState.display();
  #endif
}

TileMap& TileMap::operator=(const TileMap& map) {
  this->texTiles  = map.texTiles;
  this->font      = map.font;
  this->drawState = map.drawState;

  this->resize(map.getWidth(), map.getHeight());

  auto it_m = map.begin();
  auto it_t = this->begin();
  for (; it_m!=map.end(); ++it_m, ++it_t) {
    auto tile_m = it_m->begin();
    auto tile_t = it_t->begin();
    for (; tile_m != it_m->end(); ++tile_m, ++tile_t) {
      *tile_t = *tile_m;
    }
  }
  
  this->redraw();
}

inline bool fileExists(const std::string& path) {
  struct stat fileStat; 
  return (stat (path.c_str(), &fileStat) == 0);
}

