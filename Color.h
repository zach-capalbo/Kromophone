/*
    This file is part of The Kromophone.
    Copyright (C) 2014 Zachary Capalbo
 
	The Kromophone is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    The Kromophone is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with The Kromophone.  If not, see <http://www.gnu.org/licenses/>.
	
*/
#ifndef COLOR_H
#define COLOR_H

typedef float ColorType;
#define MAX_COLOR_TYPE 1.0f

#include <QMetaType>
#include <QRgb>

struct Color
{

public:
    Color();

    Color(ColorType r, ColorType g, ColorType b) { Red = r; Green = g; Blue = b; }

    ColorType Red;
    ColorType Green;
    ColorType Blue;
	
	Color& operator=(const QRgb& qrgb);
	
	float hue() const;
	float saturation() const;
	float luminosity() const;
	
	void hsl(float& hue, float& saturation, float& luminosity) const;
	
	const QString toHex() const;

};

Q_DECLARE_METATYPE(Color)

#endif // COLOR_H
