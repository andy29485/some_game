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
void getSelection(TileMap& hover, const TileMap& map,
                  const sf::Vector2f& start, const sf::Vector2f& size,
                  bool setTop);
void copyTiles(const TileMap& src, TileMap& dest,
          const sf::Vector2f& start_src, const sf::Vector2f& start_dest,
          const sf::Vector2f& size_src, const sf::Vector2f& size_dest,
          bool setTop);

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
    getSelection(hoverMap, toolMap, sf::Vector2f(),
                 sf::Vector2f(Tile::TILE_SIZE, Tile::TILE_SIZE), false
    );
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
    getSelection(hoverMap, toolMap, sf::Vector2f(),
                 sf::Vector2f(Tile::TILE_SIZE, Tile::TILE_SIZE), false
    );
}

int EditorEngine::mainLoop(const std::string& textureFileName,
                           const std::string& mapFileName) {
  bool mousePressed1 = false;
  bool mousePressed2 = false;
  sf::Vector2f loc1, loc2(Tile::TILE_SIZE, Tile::TILE_SIZE);
  sf::Vector2f loc3, loc4, loc1_tmp, loc3_tmp;

  while (mainWindow.isOpen() && toolboxWindow.isOpen()) {
    //TODO - Change modes: top/bottom/state
    //TODO - Change state
    //TODO - View current mode/state
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
      else if(event.type == sf::Event::KeyPressed) {
        switch(event.key.code) {
          case sf::Keyboard::S:
            this->map.save(mapFileName);
            break;
          case sf::Keyboard::L:
            this->map.load(mapFileName);
            break;
        }
      }
      else if(event.type == sf::Event::MouseButtonPressed) {
        setLoc(loc3, map, mainWindow);
        mousePressed2 = true;
      }
      else if (event.type == sf::Event::MouseButtonReleased ||
               event.type == sf::Event::MouseMoved) {
        if(mousePressed2) {
          setLoc(loc4, map, mainWindow);

          loc3_tmp = sf::Vector2f(loc3);

          if(loc3_tmp.x > loc4.x) {
            loc3_tmp.x += loc4.x;
            loc4.x      = loc3_tmp.x - loc4.x;
            loc3_tmp.x -= loc4.x;
          }
          if(loc3_tmp.y > loc4.y) {
            loc3_tmp.y += loc4.y;
            loc4.y      = loc3_tmp.y - loc4.y;
            loc3_tmp.y -= loc4.y;
          }
          loc4.x -= loc3_tmp.x - Tile::TILE_SIZE;
          loc4.y -= loc3_tmp.y - Tile::TILE_SIZE;

          hoverMap.resize(loc4.x/Tile::TILE_SIZE, loc4.y/Tile::TILE_SIZE);
          copyTiles(toolMap, hoverMap,
                    loc1_tmp, sf::Vector2f(0,0),
                    loc2, loc4, false);
        }
        if(mousePressed2 && event.type == sf::Event::MouseButtonReleased) {
          //TODO put the hover thing down
          if((int)(loc4.x - Tile::TILE_SIZE) == 0 &&
             (int)(loc4.x - loc4.y) == 0)
            copyTiles(toolMap, map,
                      loc1_tmp, loc3_tmp,
                      loc2, loc2, false);
          else
            copyTiles(hoverMap, map,
                      sf::Vector2f(0,0), loc3_tmp,
                      loc4, loc4, false);
          getSelection(hoverMap, toolMap, loc1, loc2, false);
          mousePressed2 = false;
        }
        if(!mousePressed2) {
          sf::Vector2i pos = sf::Mouse::getPosition(mainWindow);
          this->hoverMap.setPosition((int)(pos.x/Tile::TILE_SIZE),
                                     (int)(pos.y/Tile::TILE_SIZE)
          );
        }
        else {
          this->hoverMap.setPosition((int)(loc3_tmp.x/Tile::TILE_SIZE),
                                     (int)(loc3_tmp.y/Tile::TILE_SIZE)
          );
        }
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

        #ifdef DEBUG
          printf("press: %.0f, %.0f\n", loc1.x, loc1.y);
        #endif
        mousePressed1 = true;
      }
      else if (mousePressed1 &&
               (event.type == sf::Event::MouseButtonReleased ||
                event.type == sf::Event::MouseMoved)) {
        setLoc(loc2, toolMap, toolboxWindow);

        loc1_tmp = sf::Vector2f(loc1);

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

        loc2.x -= loc1_tmp.x - Tile::TILE_SIZE;
        loc2.y -= loc1_tmp.y - Tile::TILE_SIZE;

        if(!loc2.x)
          loc2.x = Tile::TILE_SIZE;
        if(!loc2.y)
          loc2.y = Tile::TILE_SIZE;

        this->selectionRectangle.setPosition(loc1_tmp);
        this->selectionRectangle.setSize(loc2);
        getSelection(hoverMap, toolMap, loc1, loc2, false);
        #ifdef DEBUG
          printf("moved: (%.0f, %.0f)  -> (%.0f, %.0f)\n", loc1_tmp.x,
                                                            loc1_tmp.y,
                                                            loc2.x,
                                                            loc2.y);
        #endif
        if(mousePressed1 && event.type == sf::Event::MouseButtonReleased) {
          mousePressed1 = false;
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
                  const sf::Vector2f& start, const sf::Vector2f& size,
                  bool setTop) {
  hover.resize(size.x/Tile::TILE_SIZE, size.y/Tile::TILE_SIZE);
  copyTiles(map, hover, start, sf::Vector2f(0,0), size, size, setTop);
}

void copyTiles(const TileMap& src, TileMap& dest,
          const sf::Vector2f& start_src, const sf::Vector2f& start_dest,
          const sf::Vector2f& size_src, const sf::Vector2f& size_dest,
          bool setTop) {
  int i;
  int j = 0;

  int src_max_y   = (int)(size_src.y/Tile::TILE_SIZE);
  int src_start_y = (int)(start_src.y/Tile::TILE_SIZE);
  int src_max_x   = (int)(size_src.x/Tile::TILE_SIZE);
  int src_start_x = (int)(start_src.x/Tile::TILE_SIZE);
  
  auto it     = dest.begin()+(int)(start_dest.y/Tile::TILE_SIZE);
  auto end_dy = it+(int)(size_dest.y/Tile::TILE_SIZE);

  for(; it!=end_dy; ++it,++j) {
    i = 0;

    auto tile   = it->begin()+(int)(start_dest.x/Tile::TILE_SIZE);
    auto end_dx = tile+(int)(size_dest.x/Tile::TILE_SIZE);

    for(; tile!=end_dx; ++tile, ++i) {
      const Tile& st = src[j%src_max_y+src_start_y][i%src_max_x+src_start_x];
      if(setTop)
        tile->setTopTile(st.getBottomTile());
      else
        tile->setBottomTile(st.getBottomTile());
    }
  }
  dest.redraw();
}

inline void setLoc(sf::Vector2f& v, const TileMap& m, const sf::Window& w) {
  sf::Vector2i pos = sf::Mouse::getPosition(w);
  #ifdef DEBUG
    printf("(%d, %d)\n", pos.x/Tile::TILE_SIZE, pos.y/Tile::TILE_SIZE);
  #endif

  v.x = (int)(pos.x/Tile::TILE_SIZE + m.getX()) * Tile::TILE_SIZE;
  v.y = (int)(pos.y/Tile::TILE_SIZE + m.getY()) * Tile::TILE_SIZE;

  if(v.x < 0)
    v.x = 0;
  else if(v.x >= m.getWidth()*Tile::TILE_SIZE)
    v.x = (m.getWidth()-1)*Tile::TILE_SIZE;
  if(v.y < 0)
    v.y = 0;
  else if(v.y >= m.getHeight()*Tile::TILE_SIZE)
    v.y = (m.getHeight()-1)*Tile::TILE_SIZE;
}

