///////////////////////////////////////////////////////////////////////
// editor.hpp
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

#ifndef EDITOR_HPP
#define EDITOR_HPP

// headers
#include <string>
#include <vector>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>

#include "tiles/tilemap.hpp"
#include "tiles/tile.hpp"

class EditorEngine {
  
public:
  // Default Constructor
  EditorEngine(const std::string&, const sf::Font&);
  EditorEngine(const std::string&, const std::string&, const sf::Font&);

  // Main loop of the editor
  int mainLoop(const std::string&, const std::string&);
  
  // Render the graphics on to the screen
  void draw();

  void undo();

  void redo();

private:
  // Map that will be saved
  // apears in mainWindow
  TileMap map;

  // Map with toolbox
  // apears in toolboxWindow
  TileMap toolMap;

  // Map with selected tile that will hover over the actual map
  TileMap hoverMap;

  // Display to user the current mode 
  sf::Text textMode;

  // Help Text
  sf::Text helpText;

  std::vector<TileMapBack> vec_undo, vec_redo;

  //mode:
  //  0 - bottom
  //  1 - top
  //  2 - state
  unsigned char mode;
  unsigned char state;
  bool          showHelp;

  // The window where the map is
  sf::RenderWindow mainWindow;
  
  // The window where the toolbox is
  sf::RenderWindow toolboxWindow;
  
  // Rectangle appearing on the toolbox window showing the selection
  sf::RectangleShape selectionRectangle;

  // change mode string
  void updateMode();
};

#endif

