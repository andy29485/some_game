///////////////////////////////////////////////////////////////////////
// editor.cpp
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

// headers
#include "tiles/editor.hpp"

inline void setLoc(sf::Vector2f&, const TileMap&, const sf::Window&);
void getSelection(TileMap&, const TileMap&,
                  const sf::Vector2f&, const sf::Vector2f&);

EditorEngine::EditorEngine(const std::string& textureFileName) :
  map(textureFileName),
  toolMap(textureFileName, true),
  hoverMap(textureFileName),
  mainWindow(sf::VideoMode(800, 600), "Editor"),
  toolboxWindow(sf::VideoMode(60, 70), "toolbox"),
  selectionRectangle(sf::Vector2f(Tile::TILE_SIZE, Tile::TILE_SIZE)),
  listen(2) {
    this->selectionRectangle.setOutlineColor(sf::Color::Magenta);
    this->selectionRectangle.setFillColor(sf::Color::Transparent);
    this->selectionRectangle.setOutlineThickness(-4);
    this->mainWindow.setFramerateLimit(30);
    this->toolboxWindow.setFramerateLimit(30);
}

EditorEngine::EditorEngine(const std::string& textureFileName,
                           const std::string& mapFileName) :
map(textureFileName, mapFileName),
  toolMap(textureFileName, true),
  hoverMap(textureFileName),
  mainWindow(sf::VideoMode(800, 600), "Editor"),
  toolboxWindow(sf::VideoMode(120, 140), "toolbox"),
  selectionRectangle(sf::Vector2f(Tile::TILE_SIZE, Tile::TILE_SIZE)),
  listen(2) {
    this->selectionRectangle.setOutlineColor(sf::Color::Magenta);
    this->selectionRectangle.setFillColor(sf::Color::Transparent);
    this->selectionRectangle.setOutlineThickness(-4);
    this->mainWindow.setFramerateLimit(30);
    this->toolboxWindow.setFramerateLimit(30);
}

int EditorEngine::mainLoop() {
  bool mousePressed = false;
  sf::Vector2f loc1, loc2;

  while (mainWindow.isOpen() && toolboxWindow.isOpen()) {
    sf::Event event;
    //Process mainWindow events
    while (mainWindow.pollEvent(event)) {
      // Request for closing the window
      if (event.type == sf::Event::Closed) {
        mainWindow.close();
        toolboxWindow.close();
      }
      else if (event.type == sf::Event::Resized) {
        mainWindow.setView(sf::View(sf::FloatRect(0.f, 0.f,
                                                  mainWindow.getSize().x,
                                                  mainWindow.getSize().y)));
      }
      else if (event.type == sf::Event::MouseMoved) {
        sf::Vector2i pos = sf::Mouse::getPosition(mainWindow);
        hoverMap.setPosition((unsigned)(pos.x/Tile::TILE_SIZE),
                             (unsigned)(pos.y/Tile::TILE_SIZE));
      }
    }
 
    //Process toolboxWindow events
    while (toolboxWindow.pollEvent(event)) {
      // Request for closing the window
      if (event.type == sf::Event::Closed) {
        toolboxWindow.close();
        mainWindow.close();
      }
      else if (event.type == sf::Event::Resized) {
        toolboxWindow.setView(sf::View(sf::FloatRect(0.f, 0.f,
                                                  toolboxWindow.getSize().x,
                                                  toolboxWindow.getSize().y)));
      }
      else if (event.type == sf::Event::MouseButtonPressed) {
        setLoc(loc1, toolMap, toolboxWindow);

        if(loc1.x < 0)
          loc1.x = 0;
        else if(loc1.x >= toolMap.getWidth()*Tile::TILE_SIZE)
          loc1.x = (toolMap.getWidth()-1)*Tile::TILE_SIZE;
        if(loc1.y < 0)
          loc1.y = 0;
        else if(loc1.y >= toolMap.getHeight()*Tile::TILE_SIZE)
          loc1.y = (toolMap.getHeight()-1)*Tile::TILE_SIZE;

        #ifdef DEBUG
          printf("press: %.0f, %.0f\n", loc1.x, loc1.y);
        #endif
        mousePressed = true;
      }
      else if (mousePressed &&
               (event.type == sf::Event::MouseButtonReleased ||
                event.type == sf::Event::MouseMoved)) {
        setLoc(loc2, toolMap, toolboxWindow);

        if(loc2.x < 0)
          loc2.x = 0;
        else if(loc2.x >= toolMap.getWidth()*Tile::TILE_SIZE)
          loc2.x = (toolMap.getWidth()-1)*Tile::TILE_SIZE;
        if(loc2.y < 0)
          loc2.y = 0;
        else if(loc2.y >= toolMap.getHeight()*Tile::TILE_SIZE)
          loc2.y = (toolMap.getHeight()-1)*Tile::TILE_SIZE;

        sf::Vector2f loc1_tmp(loc1);

        if(loc1_tmp.x > loc2.x) {
          loc1_tmp.x += loc2.x;
          loc2.x      = loc1_tmp.x - loc2.x;
          loc1_tmp.x -= loc2.x;
        }
        if(loc1_tmp.y > loc2.y) {
          loc1_tmp.y += loc2.y;
          loc2.y      = loc1_tmp.y - loc2.y;
          loc1_tmp.y -= loc2.y;
        }

        loc2.x -= loc1.x - Tile::TILE_SIZE;
        loc2.y -= loc1.y - Tile::TILE_SIZE;

        if(!loc2.x)
          loc2.x = Tile::TILE_SIZE;
        if(!loc2.y)
          loc2.y = Tile::TILE_SIZE;

        this->selectionRectangle.setPosition(loc1_tmp);
        this->selectionRectangle.setSize(loc2);
        #ifdef DEBUG
          getSelection(hoverMap, toolMap, loc1, loc2);
          printf("moved: (%.0f, %.0f)  -> (%.0f, %.0f)\n", loc1_tmp.x,
                                                            loc1_tmp.y,
                                                            loc2.x,
                                                            loc2.y);
        #endif
        if(event.type == sf::Event::MouseButtonReleased) {
          mousePressed = false;
          #ifdef DEBUG
            printf("released\n");
          #endif
        }
      }
    }

    this->mainWindow.clear();
    this->toolboxWindow.clear();

    this->draw();

    this->mainWindow.display();
    this->toolboxWindow.display();
  }

  if(mainWindow.isOpen())
    mainWindow.close();

  if(toolboxWindow.isOpen())
    toolboxWindow.close();

  return 0;
}
  
void EditorEngine::draw() {
  this->toolboxWindow.draw(this->toolMap);
  this->toolboxWindow.draw(this->selectionRectangle);
  this->mainWindow.draw(this->map);
  this->mainWindow.draw(this->hoverMap);
}

void getSelection(TileMap& hover, const TileMap& map,
                  const sf::Vector2f& start, const sf::Vector2f& size) {
  int i, j = 0;
  hover.resize(size.x/Tile::TILE_SIZE, size.y/Tile::TILE_SIZE);
  for(auto it=hover.begin(); it!=hover.end(); ++it, ++j) {
    i = 0;
    for(auto tile=it->begin(); tile!=it->end(); ++tile, ++i) {
      tile->setBottomTile(map[j][i].getBottomTile());
      //TODO?
    }
  }
}

inline void setLoc(sf::Vector2f& v, const TileMap& m, const sf::Window& w) {
  sf::Vector2i pos = sf::Mouse::getPosition(w);
  #ifdef DEBUG
    printf("(%d, %d)\n", pos.x/Tile::TILE_SIZE, pos.y/Tile::TILE_SIZE);
  #endif

  v.x = (int)(pos.x/Tile::TILE_SIZE + m.getX()) * Tile::TILE_SIZE;
  v.y = (int)(pos.y/Tile::TILE_SIZE + m.getY()) * Tile::TILE_SIZE;
}

