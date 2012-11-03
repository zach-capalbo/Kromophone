#ifndef COLOR_H
#define COLOR_H

typedef unsigned char ColorType;
#define MAX_COLOR_TYPE 255

#include <QMetaType>

struct Color
{

public:
    Color();

    Color(ColorType r, ColorType g, ColorType b) { Red = r; Green = g; Blue = b; }

    ColorType Red;
    ColorType Green;
    ColorType Blue;

};

Q_DECLARE_METATYPE(Color)

#endif // COLOR_H
