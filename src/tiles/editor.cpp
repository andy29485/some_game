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

inline void setLoc(Location&, const TileMap&, const sf::Event&);

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
  toolboxWindow(sf::VideoMode(60, 70), "toolbox"),
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
  Location loc1, loc2;

  while (mainWindow.isOpen() && toolboxWindow.isOpen()) {
    sf::Event event;
    //Process mainWindow events
    while (mainWindow.pollEvent(event)) {
      // Request for closing the window
      if (event.type == sf::Event::Closed) {
        mainWindow.close();
        toolboxWindow.close();
      }
    }
 
    //Process toolboxWindow events
    while (toolboxWindow.pollEvent(event)) {
      // Request for closing the window
      if (event.type == sf::Event::Closed) {
        toolboxWindow.close();
        mainWindow.close();
      }
      if (event.type == sf::Event::MouseButtonPressed) {
        setLoc(loc1, toolMap, event);
        mousePressed = true;
      }
      if (event.type == sf::Event::MouseButtonReleased) {
        setLoc(loc2, toolMap, event);
        this->selectionRectangle.setPosition(loc1.getX()*Tile::TILE_SIZE,
                                             loc1.getY()*Tile::TILE_SIZE);
        sf::Vector2f tmpV2f((loc2.getX()-loc1.getX())*Tile::TILE_SIZE,
                            (loc2.getY()-loc1.getY())*Tile::TILE_SIZE);
        this->selectionRectangle.setSize(tmpV2f);
        mousePressed = false;
      }
      if (mousePressed && event.type == sf::Event::MouseMoved) {
        setLoc(loc2, toolMap, event);
        sf::Vector2f tmp1(loc1.getX()<loc2.getX() ?loc1.getX() :loc2.getX(),
                          loc1.getY()<loc2.getY() ?loc1.getY() :loc2.getY());

        sf::Vector2f tmp2((loc2.getX()-loc1.getX())*Tile::TILE_SIZE,
                          (loc2.getY()-loc1.getY())*Tile::TILE_SIZE);

        tmp1.x *= Tile::TILE_SIZE;
        tmp1.y *= Tile::TILE_SIZE;

        if(tmp2.x < 0)
          tmp2.x *= -1;
        if(tmp2.x < Tile::TILE_SIZE)
          tmp2.x = Tile::TILE_SIZE;

        if(tmp2.y < 0)
          tmp2.y *= -1;
        if(tmp2.y < Tile::TILE_SIZE)
          tmp2.y = Tile::TILE_SIZE;

        this->selectionRectangle.setPosition(tmp1);
        this->selectionRectangle.setSize(tmp2);
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

inline void setLoc(Location& loc, const TileMap& map, const sf::Event& event) {
  loc.setPosition((unsigned)(event.mouseButton.x/Tile::TILE_SIZE) + map.getX(),
                  (unsigned)(event.mouseButton.y/Tile::TILE_SIZE) + map.getY());
}

