///////////////////////////////////////////////////////////////////////
// main.cpp
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

#include <string>
#include <SFML/Graphics/Font.hpp>

#ifdef _WIN32
  #include <Windows.h>
#endif /* _WIN32 */

#ifdef EDITOR
  #include "tiles/editor.hpp"
#endif

int main(const int argc, char const** argv) {
  #if defined (_WIN32) && !defined (DEBUG)
    FreeConsole();
  #endif

  #ifdef EDITOR
    sf::Font font;
    if (!font.loadFromFile("LiberationSans.ttf"))
        return EXIT_FAILURE;
    std::string map, tiles;
    if(argc == 2) {
      map   = "map.map";
      tiles = argv[1];
    }
    else if(argc == 3) {
      map   = argv[2];
      tiles = argv[1];
    }
    else {
      map   = "map.map";
      tiles = "tiles.png";
    }
    EditorEngine ee(tiles, map, font);
    return ee.mainLoop(tiles, map);
  #else
    //TODO Regular game stuff
  #endif

  return 0;
}
