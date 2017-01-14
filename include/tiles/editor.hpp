///////////////////////////////////////////////////////////////////////
// editor.hpp
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

#ifndef EDITOR_HPP
#define EDITOR_HPP

// headers
#include <string>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "tiles/tilemap.hpp"
#include "tiles/tile.hpp"

class EditorEngine {
private:
  // Map that will be saved
  // apears in mainWindow
  TileMap map;
  
  // Map with toolbox
  // apears in toolboxWindow
  TileMap toolMap;
  
  // Map with selected tile that will hover over the actual map
  TileMap hoverMap;
  
  // char that controlls if the 
  // program will "listen" to input
  //  0 - no
  //  1 - main
  //  2 - tool
  char listen;
  
  // The window where the map is
  sf::RenderWindow mainWindow;
  
  // The window where the toolbox is
  sf::RenderWindow toolboxWindow;
  
  //Rectangle appearing on the toolbox window showing the selection
  sf::RectangleShape selectionRectangle;
  
public:
  // Default Constructor
  EditorEngine(const std::string&);
  EditorEngine(const std::string&, const std::string&);

  // Main loop of the editor
  int mainLoop(const std::string&, const std::string&);
  
  // Render the graphics on to the screen
  void draw();
};

#endif

