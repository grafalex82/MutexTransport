#ifndef SENDER_H
#define SENDER_H

#include <QObject>
#include <QMutex>


class Sender : public QObject
{
	Q_OBJECT

	QMutex & transport;
	QString messageToSend;
	char currentByte;

	enum
	{
		IDLE,
		DATA,
	} state;
	qint8 bitsToGo;

public:
	explicit Sender(QMutex & t, QObject *parent = nullptr);

protected:
	void sendTrue();
	void sendFalse();
	void initiateTransfer();
	void sendData();
	void finishTransfer();
	void sendDataBit();

signals:

protected slots:
	void tick();


};

#endif // SENDER_H
