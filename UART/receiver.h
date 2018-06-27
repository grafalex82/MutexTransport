#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>
#include <QMutex>

class Receiver : public QObject
{
	Q_OBJECT

	QMutex & transport;

	unsigned int subTicksToWait;

	enum
	{
		IDLE,
		DATA
	} state;

	unsigned int bitsToReceive;
	char receivedByte;

protected:
	void detectStartBit();
	void receiveBits();

public:
	explicit Receiver(QMutex & transport, QObject *parent = nullptr);

protected:
	bool readBit();

signals:

protected slots:
	void tick();
};

#endif // RECEIVER_H
