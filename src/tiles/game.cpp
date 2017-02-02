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

#define _GLIBCXX_USE_NANOSLEEP 1

#include <thread>
#include <chrono>
#ifdef DEBUG
  #include <stdio.h>
#endif /* DEBUG */

#include <SFML/Window/Event.hpp>

#include "tiles/game.hpp"
#include "tiles/person.hpp"

void update_game(GameEngine*);

GameEngine::GameEngine() 
: mainWindow(sf::VideoMode(800, 600),
             "Return of the Horsemen: A Tale of Calamity in a Perfect World"
  ),
  map("tiles.png", "map.map"),
  player1("player1.png", &map, 5, 5)
{
  mainWindow.setVerticalSyncEnabled(true);
  mainWindow.setMouseCursorVisible(true);
  mainWindow.setFramerateLimit(20);
}

int GameEngine::mainLoop() {
  sf::Event event;
  std::thread updater(update_game, this);

  while(this->mainWindow.isOpen()) {
    while(mainWindow.pollEvent(event)) {
      this->processEvent(event);
    }

    this->draw();
  }

  updater.join();

}

void GameEngine::draw() {
  this->mainWindow.clear();

  this->mainWindow.draw(this->map);
  this->mainWindow.draw(this->player1);

  this->mainWindow.display();
}

void GameEngine::update() {
  this->player1.update();

  //TODO - other things
}

void GameEngine::processEvent(sf::Event event) {
  switch(event.type) {
    case sf::Event::Closed:
      this->mainWindow.close();
      break;
  }
  this->player1.processEvent(event);
}

void update_game(GameEngine* game) {
  #ifdef DEBUG
  printf("updater started\n");
  #endif /* DEBUG */

  while(game->running()) {
    game->update();

    std::this_thread::sleep_for(std::chrono::milliseconds(130));
  }
}

