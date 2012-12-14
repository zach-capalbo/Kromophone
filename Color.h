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
