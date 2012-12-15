#ifndef KROMOPHONEKEYBOARDFILTER_H
#define KROMOPHONEKEYBOARDFILTER_H

#include <QObject>

class KeyboardFilter : public QObject
{
	Q_OBJECT
public:
	explicit KeyboardFilter(QObject *parent = 0);
	
signals:
	
public slots:
	
protected:
	bool eventFilter(QObject *obj, QEvent *event);
	
};

#endif // KROMOPHONEKEYBOARDFILTER_H
