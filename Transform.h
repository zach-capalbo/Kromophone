#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <QObject>


/**
*/
class Transform : public QObject {
public:

	Transform();

private:


signals:

	void toNathan(Sound P);

public slots:

	void fromJon(Color P);

}

#endif