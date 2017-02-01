///////////////////////////////////////////////////////////////////////
// game.hpp
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

#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include "tilemap.hpp"
#include "player.hpp"

namespace sf {
  class Event;
}

class GameEngine {

public:
  //constructors
  GameEngine();

  //run game
  int mainLoop();

  //update contents of the window
  void draw();

  //update objects and their properies
  void update();

  //process window events
  void processEvent(sf::Event);

  //return if game is still going
  inline bool running() const { return this->mainWindow.isOpen(); }

private:
  // The window where the game will be played out
  sf::RenderWindow mainWindow;

  //game map
  TileMap map;

  //player 1
  Player player1;
};

#endif /* GAME_ENGINE_HPP */

