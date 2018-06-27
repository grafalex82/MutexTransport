#ifndef TRANSCIEVER_H
#define TRANSCIEVER_H

#include <QObject>

class Transciever : public QObject
{
	Q_OBJECT
public:
	explicit Transciever(QMutex & QObject *parent = nullptr);

signals:

public slots:
	void tick();
};

#endif // TRANSCIEVER_H
