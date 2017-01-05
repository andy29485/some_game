///////////////////////////////////////////////////////////////////////
// tilemap.cpp
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

#include "tiles/tilemap.hpp"

//Constructors
TileMap::TileMap(const std::string& texFileName,
                 const std::string& mapFileName) {
  this->texTiles.loadFromFile(texFileName);
  this->load(mapFileName);
}

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
  int startI, startJ, endI, endJ;

  startI = this->getX() * Tile::TILE_SIZE;
  startJ = this->getY() * Tile::TILE_SIZE;
  endI   = std::min((int)this->tiles.size() * Tile::TILE_SIZE,
                    startI + ((int)target.getSize().x / Tile::TILE_SIZE + 1) *
                    Tile::TILE_SIZE
  );
  endJ   = std::min((int)this->tiles[0].size() * Tile::TILE_SIZE,
                  startJ + ((int)target.getSize().y / Tile::TILE_SIZE + 1) *
                  Tile::TILE_SIZE
  );

  target.draw(sf::Sprite(renderTexture.getTexture(),
                         sf::IntRect(startI, startJ, endI, endJ)
              ),
              states
  );
}

//find shortest path between two locations
std::vector<char> TileMap::findPath(Location a, Location b) {
  //TODO - findpath
}

void TileMap::save(const std::string& filename, bool append) {
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
    for (auto tile = (*it).begin(); tile!=(*it).end(); ++tile) {
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

std::streampos TileMap::load(const std::string& filename, std::streampos pos) {
  std::ifstream data(filename.c_str(), std::ios::in | std::ios::binary);
  data.seekg(pos);

  unsigned int w, h;
  unsigned short tmps;
  unsigned char  tmpc;

  data.read((char*)&w, sizeof(w));
  data.read((char*)&h, sizeof(h));

  this->tiles.resize(h, std::vector<Tile>(w, Tile(this->texTiles, 0, 0)));
  this->renderTexture.create(Tile::TILE_SIZE * w, Tile::TILE_SIZE * h);
  this->renderTexture.clear();

  h = 0;
  for (auto it = this->tiles.begin(); it!=this->tiles.end(); ++it) {
    w = 0;
    for (auto tile = (*it).begin(); tile != (*it).end(); ++tile) {
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

      tile->setPosition(w, h);
      renderTexture.draw(*tile);

      w += Tile::TILE_SIZE;
    }
    h += Tile::TILE_SIZE;
  }

  renderTexture.display();
  std::streampos new_pos = data.tellg();
  data.close();

  return new_pos;
}
  
