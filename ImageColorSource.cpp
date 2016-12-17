#include "ImageColorSource.h"
#include <QTimer>
#include "Logger.h"

ImageColorSource::ImageColorSource(QObject* parent)
    : ColorSource(parent), cursorSize(5,5), averageEnabled(false), sweepPos(0,0), sweepSize(200, 200),
      saturationAdjustment(1.0)
{
	sweepTimer = new QTimer(this);
	connect(sweepTimer, SIGNAL(timeout()), this, SLOT(sweep()));
    
    connect(&Settings::sweep(), &Setting::valueChanged, this, &ImageColorSource::toggleSweep);
    connect(&Settings::sweepSize(), &Setting::valueChanged, this, &ImageColorSource::sweepSizeChanged);
    connect(&Settings::average(), &Setting::valueChanged, this, &ImageColorSource::setAverage);
    connect(&Settings::averageSize(), &Setting::valueChanged, this, &ImageColorSource::averageSizeChanged);
}

void ImageColorSource::setAverage(const QVariant& value)
{
    bool enabled = value.toBool();
    averageEnabled = enabled;
	
	if (!enabled)
	{
        // Reset to small cursor
		cursorSize = QSize(5,5);
	}
    else
    {
        int averageSize = Settings::averageSize().value().toInt();
        cursorSize = QSize(averageSize, averageSize);
    }
	
    updateColor();
}

void ImageColorSource::toggleAverage()
{
	setAverage(!averageEnabled);
	
	updateColor();
}

void ImageColorSource::drawCursor(QImage& image)
{
	int posx = qMax(0, cursor.x());
	int posy = qMax(0,cursor.y());
	
	int cwidth = cursorSize.width();
	int cheight = cursorSize.height();
	
	for (int x = posx - cwidth; x < posx + cwidth; x++ )
	{
		if (x > 0 && x < image.width())
		{
			image.setPixel(x,posy,qRgb(255, 255, 255));
		}
	}

	for (int y = posy - cheight; y < posy + cheight; y++)
	{
		if (y > 0 && y < image.height())
		{
			image.setPixel(posx,y,qRgb(255, 255, 255));
		}
	}
}

Color &ImageColorSource::pickColor(const QImage& image)
{	
	if (averageEnabled)
	{
		average(image);	
	}
	else
	{
		lastColor = image.pixel(cursor);
//        LOG_INFO() << image.isNull() << image.width() << image.height();
//        lastColor = image.pixel(image.width() / 2, image.height() / 2);
	}

    if (Settings::saturationAdjustment().value().toBool())
    {
        findSaturation(image);
    }

    postProcessColor();
	
	return lastColor;
}

void ImageColorSource::findSaturation(const QImage& image)
{
    int endX = image.width();
    int endY = image.height();

    float totalSaturation = 0;

    for (int x = 0; x < endX; ++x)
    {
        for (int y = 0; y < endY; ++y)
        {
            Color color = Color(image.pixel(x, y));
            totalSaturation += color.saturation();
        }
    }

    saturationAdjustment = 1.0 / (totalSaturation / ((float) (endX * endY)));

    LOG_INFO() << "Saturation Adjustment: " << saturationAdjustment;

}

void ImageColorSource::postProcessColor()
{
    lastColor = lastColor.saturate(saturationAdjustment);
}

void ImageColorSource::average(const QImage& image)
{
	unsigned int sumr = 0;
	
	unsigned int sumg = 0;
	
	unsigned int sumb = 0;
	
	int startX = cursor.x() - cursorSize.width();
	startX = qMax(startX, 0);
	
	int endX = cursor.x() + cursorSize.width();
	endX = qMin(endX, image.width());
	
	int startY = cursor.y() - cursorSize.height();
	startY = qMax(startY, 0);
	
	int endY = cursor.y() + cursorSize.height();
	endY = qMin(endY, image.height());
	
	for (int x = startX; x < endX; x++)
	{
		for (int y = startY; y < endY; y++)
		{
			QRgb rgb = image.pixel(x,y);
			
			sumr += qRed(rgb);
			
			sumg += qGreen(rgb);
			
			sumb += qBlue(rgb);
		}
	}
	float r = (float) sumr / ( (float) cursorSize.width() * cursorSize.height() * 4 ) / 255.0f;
	lastColor.Red = r;
	lastColor.Green = (float) sumg / ( (float) cursorSize.width() * cursorSize.height() * 4 ) / 255.0f;
	lastColor.Blue = (float) sumb / ( (float) cursorSize.width() * cursorSize.height() * 4 ) / 255.0f;
}

void ImageColorSource::sweep()
{
	if (sweepDirectionIsRight)
	{
		sweepPos += QPoint(1,0);
		cursor += QPoint(1,0);
	}
	else
	{
		sweepPos += QPoint(-1,0);
		cursor += QPoint(-1,0);
	}
	
	if (sweepDirectionIsRight && sweepPos.x() >= sweepSize.width())
	{
		sweepDirectionIsRight = false;
	}
	else if (!sweepDirectionIsRight && sweepPos.x() <= -sweepSize.width())
	{
		sweepDirectionIsRight = true;
	}
	
	emit doSweep(true, QPointF((sweepSize.width() + sweepPos.x()) / ( (float) sweepSize.width()*2.0f ), sweepPos.y() / (float) sweepSize.height() ));		
	
	updateColor();
}

void ImageColorSource::toggleSweep()
{
	if (sweepTimer->isActive())
	{
		sweepTimer->stop();
		sweepPos = QPoint(0,0);
	}
	else
	{
		sweepTimer->start(10);
    }
}

void ImageColorSource::averageSizeChanged(const QVariant& value)
{
    int size = value.toInt();
    this->cursorSize = QSize(size, size);
}

void ImageColorSource::sweepSizeChanged(const QVariant& value)
{
    this->sweepSize.setWidth(value.toInt());
}
