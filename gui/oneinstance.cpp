#include "oneinstance.h"

bool oneInstance::isAnotherInstance() {
	bool ret=FALSE;

	// Return true if there is another instance
	
	QDBusConnection bus = QDBusConnection::sessionBus();
	QStringList serviceNames = bus.interface()->registeredServiceNames();


	// Ok, I could do return (serviceNames.indexOf("qdacco.org")!=-1)
	if (serviceNames.indexOf("qdacco.org")==-1) {
		printf("Servei NO engegat\n");
		ret=FALSE;
	}
	else {
		ret=TRUE;
	}
	return ret;
	
}

void oneInstance::sendRestore() {
	// Send to the other instance a restore message
	QDBusConnection bus = QDBusConnection::sessionBus();
	QDBusMessage msg = QDBusMessage::createMethodCall("qdacco.org","/serveis","","restore");
	QDBusMessage reply = bus.call(msg);
}

void oneInstance::restore() {
	printf("REBUT RESTORE\n");
	Main* window = Main::instance();
	window->restaura();
}

void oneInstance::registerInstance() {
	QDBusConnection bus = QDBusConnection::sessionBus();
	bus.interface()->registerService("qdacco.org");
	bus.registerObject("/serveis",this,QDBusConnection::ExportAllSlots);
}
