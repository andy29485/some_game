///////////////////////////////////////////////////////////////////////
// textbox.hpp
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

#include <cmath>
#include <string>

#include <SFML/Graphics/ConvexShape.hpp>

#include "textbox.hpp"



sf::ConvexShape
RoundedRectangle(const float& rectWidth, const float& rectHeight,
                 const float& radius, const float& outline,
                 const sf::Color& fillCol, const sf::Color& outlineCol);


                 
                 
TextBox::TextBox(std::string string) {
  //TODO
}



sf::ConvexShape
RoundedRectangle(const float& rectWidth, const float& rectHeight,
                 const float& radius, const float& outline,
                 const sf::Color& fillCol, const sf::Color& outlineCol) {
  float x = 0, y = 0;
  int index = -1;
  const int POINTS = 10;
  sf::ConvexShape rrect = sf::ConvexShape(4*POINTS);

  rrect.setOutlineThickness(outline);
  rrect.setFillColor(fillCol);
  rrect.setOutlineColor(outlineCol);

  for(int i=0; i<POINTS; ++i)	{
    x += radius/POINTS;
    y  = std::sqrt(radius*radius-x*x);
    rrect.setPoint(++index, sf::Vector2f(x+rectWidth-radius, -y+radius));
  }

  y = 0;
  for(int i=0; i<POINTS; ++i) {
    x += radius/POINTS;
    y  = std::sqrt(radius*radius-y*y);
    rrect.setPoint(++index, sf::Vector2f(x+rectWidth-radius,
                                         y+rectHeight-radius)
    );
  }

  x = 0;
  for(int i=0; i<POINTS; i++) {
    x += radius/POINTS;
    y  = std::sqrt(radius*radius-x*x);
    rrect.setPoint(++index, sf::Vector2f(-x+radius, y+rectHeight-radius));
  }

  y = 0;
  for(int i=0; i<POINTS; i++) {
    y += radius/POINTS;
    x  = std::sqrt(radius*radius - y*y);
    rrect.setPoint(++index, sf::Vector2f(-x+radius, -y+radius));
  }
  return rrect;
}


