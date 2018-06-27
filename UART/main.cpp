#include <QCoreApplication>
#include <QMutex>

#include "receiver.h"
#include "sender.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	QMutex transport;
	Receiver receiver(transport);
	Sender sender(transport);

	return a.exec();
}
