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

sf::Shape&
RoundedRectangle(const float& x, const float& y,
                 const float& rectWidth, const float& rectHeight,
                 const float& radius, const float& outline,
                 const sf::Color& fillCol, const sf::Color& outlineCol);


TextBox::TextBox(std::string string) {
  //TODO
}



sf::Shape&
RoundedRectangle(const float& x, const float& y,
                 const float& rectWidth, const float& rectHeight,
                 const float& radius, const float& outline,
                 const sf::Color& fillCol, const sf::Color& outlineCol) {
  sf::Shape rrect = sf::Shape();
  float x = 0, y = 0;
  const int POINTS = 10;

  rrect.SetOutlineWidth(outline);

  for(int i=0; i<POINTS; ++i)	{
    x += radius/POINTS;
    y  = sqrt(radius*radius-X*X);
    rrect.AddPoint(x+rectWidth-radius,-y+radius, fillCol, outlineCol);
  }

  y = 0;
  for(int i=0; i<POINTS; ++i) {
    x += radius/POINTS;
    y  = sqrt(radius*radius-Y*Y);
    rrect.AddPoint(x+rectWidth-radius, y+rectHeight-radius, fillCol, outlineCol);
  }

  x = 0;
  for(int i=0; i<POINTS; i++) {
    x += radius/POINTS;
    y  = sqrt(radius*radius-X*X);
    rrect.AddPoint(-x+radius, y+rectHeight-radius, fillCol, outlineCol);
  }

  y = 0;
  for(int i=0; i<POINTS; i++) {
    y += radius/POINTS;
    x  = sqrt(radius*radius - y*y);
    rrect.AddPoint(-x+radius, -y+radius, fillCol, outlineCol);
  }
  return rrect;
}


