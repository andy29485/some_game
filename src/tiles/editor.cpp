///////////////////////////////////////////////////////////////////////
// editor.cpp
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

// headers
#include "tiles/editor.hpp"

std::string help = \
           "Help\n\n" \
           "Buttons:\n" \
           "S      - save map\n" \
           "L      - load map\n" \
           "Z      - undo edit\n" \
           "R      - redo edit\n" \
           "+/=    - increase state\n" \
           "-/_    - decrease state\n" \
           "Arrows - pan map of selected window\n" \
           "Tab    - see states of tiles(temporarly)\n" \
           "/      - see help\n\n" \
           "Modes:\n" \
           "bottom - change bottom part of tiles\n" \
           "top    - change top part of tiles\n" \
           "state  - change the state of tiles\n\n" \
           "Other Actions:\n" \
           "Scroll up/down        - change mode\n" \
           "Click on toolbox      - select tile\n" \
           "Click on map          - stamp selected tiles/set state of tile\n" \
           "Click+drag on toolbox - select multiple tiles\n" \
           "Click+drag on map     - stamp selection repeatedly";

inline void setLoc(sf::Vector2f&, const TileMap&, const sf::Window&);
void getSelection(TileMap& hover, const TileMap& map,
                  const sf::Vector2f& start, const sf::Vector2f& size,
                  bool setTop);
void copyState(TileMap&, const sf::Vector2f&, const sf::Vector2f&,
               const unsigned char&);
void copyTiles(const TileMap& src, TileMap& dest,
          const sf::Vector2f& start_src, const sf::Vector2f& start_dest,
          const sf::Vector2f& size_src, const sf::Vector2f& size_dest,
          bool setTop);

EditorEngine::EditorEngine(const std::string& textureFileName,
                           sf::Font& font) :
  map(textureFileName, font),
  toolMap(textureFileName, font, true),
  hoverMap(textureFileName, font),
  textMode("bottom - 0", font),
  helpText(help, font, 17),
  mode(0),
  state(0),
  showHelp(false),
  mainWindow(sf::VideoMode(800, 600), "Editor"),
  toolboxWindow(sf::VideoMode(60, 70), "toolbox"),
  selectionRectangle(sf::Vector2f(Tile::TILE_SIZE, Tile::TILE_SIZE)) {
    this->selectionRectangle.setOutlineColor(sf::Color::Magenta);
    this->selectionRectangle.setFillColor(sf::Color::Transparent);
    this->selectionRectangle.setOutlineThickness(-4);
    this->mainWindow.setFramerateLimit(30);
    this->toolboxWindow.setFramerateLimit(30);
    this->textMode.setOrigin(this->textMode.getLocalBounds().width/2, 0);
    this->textMode.setPosition(this->mainWindow.getSize().x/2, 5);
    getSelection(hoverMap, toolMap, sf::Vector2f(),
                 sf::Vector2f(Tile::TILE_SIZE, Tile::TILE_SIZE), false
    );
}

EditorEngine::EditorEngine(const std::string& textureFileName,
                           const std::string& mapFileName,
                           sf::Font& font) :
  map(textureFileName, mapFileName, font),
  toolMap(textureFileName, font, true),
  hoverMap(textureFileName, font),
  textMode("bottom - 0", font),
  helpText(help, font, 17),
  mode(0),
  state(0),
  showHelp(false),
  mainWindow(sf::VideoMode(800, 600), "Editor"),
  toolboxWindow(sf::VideoMode(120, 140), "toolbox"),
  selectionRectangle(sf::Vector2f(Tile::TILE_SIZE, Tile::TILE_SIZE)) {
    this->selectionRectangle.setOutlineColor(sf::Color::Magenta);
    this->selectionRectangle.setFillColor(sf::Color::Transparent);
    this->selectionRectangle.setOutlineThickness(-4);
    this->mainWindow.setFramerateLimit(30);
    this->toolboxWindow.setFramerateLimit(30);
    this->textMode.setOrigin(this->textMode.getLocalBounds().width/2, 0);
    this->textMode.setPosition(this->mainWindow.getSize().x/2, 5);
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
        this->textMode.setPosition(this->mainWindow.getSize().x/2, 5);
      }
      else if(event.type == sf::Event::KeyPressed) {
        switch(event.key.code) {
          case sf::Keyboard::S:
            this->map.save(mapFileName);
            break;
          case sf::Keyboard::L:
            this->map.load(mapFileName);
            break;
          case sf::Keyboard::Slash:
            this->showHelp = true;
            break;
          case sf::Keyboard::Equal:
          case sf::Keyboard::Add:
            ++this->state;
            this->updateMode();
            break;
          case sf::Keyboard::Dash:
          case sf::Keyboard::Subtract:
            --this->state;
            this->updateMode();
            break;
          case sf::Keyboard::Z:
          case sf::Keyboard::U:
            this->undo();
            break;
          case sf::Keyboard::R:
            this->redo();
            break;
          case sf::Keyboard::Tab:
            this->map.setDrawState(true);
            break;
          case (sf::Keyboard::Up):
            this->map.addY(1);
            break;
          case (sf::Keyboard::Down):
            this->map.addY(-1);
            break;
          case (sf::Keyboard::Right):
            this->map.addX(-1);
            break;
          case (sf::Keyboard::Left):
            this->map.addX(1);
            break;
        }
      }
      else if(event.type == sf::Event::KeyReleased) {
        switch(event.key.code) {
          case sf::Keyboard::Tab:
            this->map.setDrawState(this->mode == 2);
            break;
          case sf::Keyboard::Slash:
            this->showHelp = false;
            break;
        }
      }
      else if(event.type == sf::Event::MouseWheelMoved) {
        if(event.mouseWheel.y < 0) {
          this->mode += 2;
        }
        else if(event.mouseWheel.y > 0) {
          ++this->mode;
        }
        this->mode %= 3;
        if(this->mode == 0)
          this->textMode.setString("bottom - "+std::to_string(this->state));
        else if(this->mode == 1)
          this->textMode.setString("top - "+std::to_string(this->state));
        else
          this->textMode.setString("state - "+std::to_string(this->state));
        this->map.setDrawState(this->mode == 2);
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
          if(this->mode == 2) {
            copyState(map, loc3_tmp, loc4, this->state);
          }
          else {
            this->vec_undo.push_back(this->map.backup());
            if((int)(loc4.x - Tile::TILE_SIZE) == 0 &&
               (int)(loc4.x - loc4.y) == 0)
              copyTiles(toolMap, map,
                        loc1_tmp, loc3_tmp,
                        loc2, loc2, this->mode == 1);
            else
              copyTiles(hoverMap, map,
                        sf::Vector2f(0,0), loc3_tmp,
                        loc4, loc4, this->mode == 1);
          }
          getSelection(hoverMap, toolMap, loc1_tmp, loc2, false);
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
      else if (event.type == sf::Event::KeyPressed) {
        switch(event.key.code) {
          case (sf::Keyboard::Up):
            this->map.addY(1);
            break;
          case (sf::Keyboard::Down):
            this->map.addY(-1);
            break;
          case (sf::Keyboard::Right):
            this->map.addX(-1);
            break;
          case (sf::Keyboard::Left):
            this->map.addX(1);
            break;
        }
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
        getSelection(hoverMap, toolMap, loc1_tmp, loc2, false);
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

    this->draw();
  }

  if(mainWindow.isOpen())
    mainWindow.close();

  if(toolboxWindow.isOpen())
    toolboxWindow.close();

  return 0;
}
  
void EditorEngine::draw() {
  this->mainWindow.clear();
  this->toolboxWindow.clear();

  this->toolMap._redraw();
  this->hoverMap._redraw();
  this->map._redraw();

  this->toolboxWindow.draw(this->toolMap);
  this->toolboxWindow.draw(this->selectionRectangle);
  if(showHelp) {
    this->mainWindow.draw(this->helpText);  
  }
  else {
    this->mainWindow.draw(this->map);
    this->mainWindow.draw(this->hoverMap);
    this->mainWindow.draw(this->textMode);
  }

  this->mainWindow.display();
  this->toolboxWindow.display();
}

void EditorEngine::updateMode() {
  if(this->mode == 0)
    this->textMode.setString("bottom - "+std::to_string(this->state));
  else if(this->mode == 1)
    this->textMode.setString("top - "+std::to_string(this->state));
  else
    this->textMode.setString("state - "+std::to_string(this->state));
  this->textMode.setOrigin(this->textMode.getLocalBounds().width/2, 0);
}

void EditorEngine::undo() {
  if(this->vec_undo.size() == 0)
    return;
  TileMapBack& m = this->vec_undo.back();
  this->vec_redo.push_back(map.backup());
  this->map = m;
  this->vec_undo.pop_back();
}

void EditorEngine::redo() {
  if(this->vec_redo.size() == 0)
    return;
  TileMapBack& m = this->vec_redo.back();
  this->vec_undo.push_back(map.backup());
  this->map = m;
  this->vec_redo.pop_back();
}

void getSelection(TileMap& hover, const TileMap& map,
                  const sf::Vector2f& start, const sf::Vector2f& size,
                  bool setTop) {
  hover.resize(size.x/Tile::TILE_SIZE, size.y/Tile::TILE_SIZE);
  copyTiles(map, hover, start, sf::Vector2f(0,0), size, size, setTop);
}

void copyState(TileMap& dest,
          const sf::Vector2f& start, const sf::Vector2f& size,
          const unsigned char& state) {
  auto it     = dest.begin()+(int)(start.y/Tile::TILE_SIZE);
  auto end_dy = it+(int)(size.y/Tile::TILE_SIZE);

  for(; it!=end_dy; ++it) {
    auto tile   = it->begin()+(int)(start.x/Tile::TILE_SIZE);
    auto end_dx = tile+(int)(size.x/Tile::TILE_SIZE);

    for(; tile!=end_dx; ++tile) {
      tile->setState(state);
    }
  }
  dest.redraw();
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

