/*
 * This file is part of qdacco
 * qdacco: offline Dacco Catalan <-> English dictionary
 *
 * Copyright (c) 2005, 2006, 2007, 2008, 2009
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


#include "OneInstance.h"

OneInstance::OneInstance() :
	m_dbusAvailable(false)
{
	ptr_main = new Main;
	ptr_main->show();
}

bool OneInstance::isAnotherInstance() {
	// Return true if there is another instance
	bool ret=false;

	if (!QDBusConnection::systemBus().isConnected())
	{
		qDebug() << "QDbus not available";
		return false;
	}
	
	QDBusConnection bus = QDBusConnection::sessionBus();
	
	if (bus.lastError().type() != QDBusError::NoError)
	{
		m_dbusAvailable = false;
		return false;
	}
	m_dbusAvailable = true;

	QStringList serviceNames = bus.interface()->registeredServiceNames();

	if (serviceNames.indexOf("qdacco.org")==-1) {
		ret=false;
	}
	else {
		ret=true;
	}
	return ret;
	
}

void OneInstance::sendRestore() {
	if (m_dbusAvailable == false)
	{
		return;
	}
	// Send to the other instance a restore message
	QDBusConnection bus = QDBusConnection::sessionBus();
	QDBusMessage msg = QDBusMessage::createMethodCall("qdacco.org","/serveis","","restore");
	QDBusMessage reply = bus.call(msg);
}


void OneInstance::restore() {
	if (m_dbusAvailable == false)
	{
		return;
	}
	// Received by DBUS
	// Needed to destroy and create the Window again and not only
	// give the focus because some Window Managers prevents
	// focus stealing

	
	int idioma = ptr_main->getIdiomaActiu();
	QString paraula = ptr_main->getParaula();

	delete ptr_main;
	ptr_main = new Main;

	ptr_main->setIdiomaActiu(idioma);

	if (paraula.length()>0) {
		ptr_main->setParaula(paraula);
		ptr_main->buscar();
	}
	ptr_main->show();
}

void OneInstance::registerInstance() {
	if (m_dbusAvailable == false)
	{
		return;
	}
	QDBusConnection bus = QDBusConnection::sessionBus();
	bus.interface()->registerService("qdacco.org");
	bus.registerObject("/serveis",this,QDBusConnection::ExportAllSlots);
}

bool OneInstance::isVisible() {
	if (m_dbusAvailable == false)
	{
		return true;
	}
	return ptr_main->isVisible();
}

void OneInstance::close() {
	if (m_dbusAvailable == false)
	{
		return;
	}
	ptr_main->close();
}

void OneInstance::hide() {
	if (m_dbusAvailable == false)
	{
		return;
	}
	ptr_main->hide();
}

void OneInstance::show() {
	if (m_dbusAvailable == false)
	{
		return;
	}
	ptr_main->show();
}
