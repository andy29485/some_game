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

GameEngine::GameEngine() 
: mainWindow(sf::VideoMode(800, 600), "Editor"),
  map("tiles.png", "map.map"),
  player1("player1.png", 5, 5)
{
  //TODO
}

void GameEngine::draw() {
  //TODO
}

void GameEngine::update() {
  //TODO
}

void GameEngine::processEvent(sf::Event event) {
  //TODO
}

