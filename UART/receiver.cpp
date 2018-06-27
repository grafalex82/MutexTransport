#include <QtCore/QTimer>
#include <QDebug>

#include "receiver.h"
#include "params.h"

Receiver::Receiver(QMutex & t, QObject *parent)
	: QObject(parent),
	  transport(t)
{
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
	timer->start(SEND_INTERVAL / RECEIVER_SUB_TICKS);

	state = IDLE;
	subTicksToWait = 0;
}

void Receiver::tick()
{
	qDebug() << "        Receiver Timer shot. State: " << state;

	if(state != IDLE && --subTicksToWait)
		return;

	switch(state)
	{
	case IDLE:
		detectStartBit();
		break;

	case DATA:
		receiveBits();
		break;
	default:
		break;

	}
}

bool Receiver::readBit()
{
	bool locked = transport.tryLock(3);
	if(locked)
		transport.unlock();

	return !locked;
}

void Receiver::detectStartBit()
{
	if(readBit())
	{
		qDebug() << "        Receiver: Detected start bit";
		state = DATA;
		subTicksToWait = RECEIVER_SUB_TICKS + 1;
		receivedByte = 0;
		bitsToReceive = 8;
	}
}

void Receiver::receiveBits()
{
	if(bitsToReceive-- == 0)
	{
		qDebug() << "        Receiver: All bits received: " << receivedByte;
		state = IDLE;
		subTicksToWait = RECEIVER_SUB_TICKS - 1;
		return;
	}

	bool bit = readBit();
	qDebug() << "        Receiver: received bit " << bit;
	receivedByte <<= 1;
	receivedByte |= bit ? 1 : 0;

	subTicksToWait = RECEIVER_SUB_TICKS;
}
