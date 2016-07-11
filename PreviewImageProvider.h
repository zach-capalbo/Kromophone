#ifndef PREVIEWIMAGEPROVIDER_H
#define PREVIEWIMAGEPROVIDER_H

#include <QQuickImageProvider>

class PreviewImageProvider : public QQuickImageProvider
{
public:
    PreviewImageProvider();
    
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize)
    {
        size = new QSize(image.size());
        return image;
    }
    
    void setImage(const QImage& newImage) { image = newImage; }
    
private:
    QImage image;
};

#endif // PREVIEWIMAGEPROVIDER_H
