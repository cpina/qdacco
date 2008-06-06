/*
 * This file is part of qdacco
 * qdacco: offline Dacco Catalan <-> English dictionary
 *
 * Copyright (c) 2005, 2006, 2007, 2008
 *      Carles Pina i Estany <carles@pina.cat>
 *
 * qdacco is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * any later version.
 *
 * qdacco is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "oneinstance.h"

bool oneInstance::isAnotherInstance() {
	bool ret=FALSE;

	// Return true if there is another instance
	
	QDBusConnection bus = QDBusConnection::sessionBus();
	QStringList serviceNames = bus.interface()->registeredServiceNames();

	//qDebug() << serviceNames;

	// Ok, I could do return (serviceNames.indexOf("qdacco.org")!=-1)
	if (serviceNames.indexOf("qdacco.org")==-1) {
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


void oneInstance::sendQuit() {
	// Send to the other instance a restore message
	QDBusConnection bus = QDBusConnection::sessionBus();
	QDBusMessage msg = QDBusMessage::createMethodCall("qdacco.org","/serveis","","quit");
	QDBusMessage reply = bus.call(msg);
}

void oneInstance::restore() {
	Main* window = Main::instance();
	window->restaura();
}

void oneInstance::quit() {
	Main* window = Main::instance();
	delete window;
	window = Main::instance();
	window->show();

	//window->quit();
	//window->show();
}


void oneInstance::registerInstance() {
	QDBusConnection bus = QDBusConnection::sessionBus();
	bus.interface()->registerService("qdacco.org");
	bus.registerObject("/serveis",this,QDBusConnection::ExportAllSlots);
}
