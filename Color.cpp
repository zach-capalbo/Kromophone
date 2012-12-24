#include "Color.h"
#include <QString>


Color::Color()
{

}

Color& Color::operator=(const QRgb& qrgb)
{
	Red = qRed(qrgb) / 255.0f;
	Green = qGreen(qrgb) / 255.0f;
	Blue = qBlue(qrgb) / 255.0f;
	
	return *this;
}

float Color::hue() const
{
	float h,s,l;
	
	hsl(h,s,l);
	
	return h;
}

float Color::saturation() const
{
	return qMin(Red, qMin(Green, Blue));
}

float Color::luminosity() const
{
	float h,s,l;
	
	hsl(h,s,l);
	
	return l;
}

void Color::hsl(float& hue, float& saturation, float& luminosity) const
{
	float imax = qMax( qMax(Red, Green), Blue);
	
	float imin = qMin( qMin(Red, Green), Blue);
	
	luminosity = (imax+imin)/2.0f;
	
	saturation = 0;
	
	hue = 0;
	
	if (imax==imin) 
	{ 
		return;
	}
	else
	{
		
		saturation=(imax-imin)/imax;
		
		if (imax==Red)
		{
			hue = (Green - Blue)/(imax-imin);
		}
		else if (imax==Green)
		{
			hue = 2.0f + (Blue - Red)/(imax-imin);
		}
		else if (imax==Blue)
		{
			hue = 4.0f + (Red - Green)/(imax-imin);
		}
	}
	hue/=5.0f;
}

const QString Color::toHex() const
{
	QString out;
	
	return out.sprintf("0x%2X%2X%2X",(int) (Red*255.0),(int) (Blue*255.0),(int) (Green*255.0)).replace(" ","0");
}
