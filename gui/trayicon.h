/*
 * This file is part of qdacco
 * qdacco: offline Dacco Catalan <-> English dictionary
 *
 * Copyright (c) 2005, 2006, 2007
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

#ifndef TRAYICON_H
#define TRAYICON_H

#include <QMenu>
#include <QSystemTrayIcon>
#include <QPushButton>

#include "oneinstance.h"

class oneInstance;

class TrayIcon : public QWidget
{
	Q_OBJECT

	public:
		TrayIcon();
		void primerPla();
	
		void SetOneInstance(oneInstance *o);


	private:
		void setMenu();

		QSystemTrayIcon *trayIcon;
		QMenu *trayIconMenu;

		oneInstance *myoneinstance;

	private slots:
		void leftclick(QSystemTrayIcon::ActivationReason reason);
		void changestatus();
		void quit();
};

#endif
