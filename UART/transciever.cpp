#include <QtCore/QTimer>
#include <QDebug>

#include "transciever.h"

Transciever::Transciever(QObject *parent) : QObject(parent)
{
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
	timer->start(1000);
}

void Transciever::tick()
{
	qDebug() << "Timer shot";
}
