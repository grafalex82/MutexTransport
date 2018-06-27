#include <QtCore/QTimer>
#include <QDebug>

#include "sender.h"
#include "params.h"

Sender::Sender(QMutex & t, QObject *parent)
  : QObject(parent),
	transport(t)
{
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
	timer->start(SEND_INTERVAL);

	state = IDLE;
	bitsToGo = 8;
	currentByte = 0;

	messageToSend = "Hello!";
}

void Sender::tick()
{
	switch(state)
	{
	case IDLE:
		initiateTransfer();
		break;
	case DATA:
		sendData();
		break;
	default:
		break;
	}
}

void Sender::sendTrue()
{
	transport.tryLock(3);
}

void Sender::sendFalse()
{
	transport.tryLock(3);
	transport.unlock();
}

void Sender::initiateTransfer()
{
	if(messageToSend.isEmpty())
	{
		qDebug() << "Sender: Nothing to send";
		return;
	}

	bitsToGo = 9;
	currentByte = messageToSend.at(0).toLatin1();
	messageToSend.remove(0, 1);
	qDebug() << "Sender: Will be sending " << currentByte;

	qDebug() << "Sender: Sending start bit and switching to DATA";
	state = DATA;
	sendTrue(); // actually send start bit
}

void Sender::sendDataBit()
{
	if(currentByte & 0x80)
	{
		qDebug() << "Sender: Sending true";
		sendTrue();
	}
	else
	{
		qDebug() << "Sender: Sending false";
		sendFalse();
	}

	currentByte <<= 1;
}

void Sender::finishTransfer()
{
	qDebug() << "Sender: Sent all data. Switching to IDLE";
	state = IDLE;
	sendFalse();
}

void Sender::sendData()
{
	if(--bitsToGo == 0)
		finishTransfer();
	else
		sendDataBit();
}
