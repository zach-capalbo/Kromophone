#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <QObject>
#include <stdlib.h>
#include "Sound.h"
#include "Color.h"


/**
*/
class Transform : public QObject {

	Q_OBJECT

public:

	Transform();

private:


signals:

	void toNathan(Sound P);

public slots:

	void fromJon(Color P);

};

#endif