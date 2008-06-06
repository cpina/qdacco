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



#include "trayicon.h"

TrayIcon* TrayIcon::ptr_trayicon;

TrayIcon* TrayIcon::instance() {
        if (!ptr_trayicon) {
                ptr_trayicon=new TrayIcon;
        }

        return ptr_trayicon;
}

TrayIcon::TrayIcon()
{
        trayIcon = new QSystemTrayIcon(this);

        trayIcon->setIcon(QIcon(":/icons/qdacco.png"));

        trayIcon->show();

	// connect the signals-slots
	connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(leftclick(QSystemTrayIcon::ActivationReason)));

	//trayIconMenu=0;

	installEventFilter(this);
}

void TrayIcon::SetMain(QWidget *qw)
{
	main = qw;
	setMenu();
}

void TrayIcon::setMenu()
{
	/*if (trayIconMenu!=0) {
		delete trayIconMenu;
	}
	*/

        trayIconMenu = new QMenu(this);
	QAction *action;
	if (main->isVisible()) {
		action = trayIconMenu->addAction(tr("Show"));
	}
	else {
		action = trayIconMenu->addAction(tr("Hide"));
	}
	connect(action,SIGNAL(triggered()),this,SLOT(changestatus()));

        trayIconMenu->addSeparator();

	QAction *quit = trayIconMenu->addAction(QIcon(":/icons/exit"),tr("Quit"));
	connect(quit,SIGNAL(triggered()),this,SLOT(quit()));
        trayIcon->setContextMenu(trayIconMenu);

}

void TrayIcon::changestatus()
{
	leftclick(QSystemTrayIcon::Trigger);

}

void TrayIcon::leftclick(QSystemTrayIcon::ActivationReason reason)
{
	if (reason==QSystemTrayIcon::Trigger) {
		if (main->isVisible()) {
			setMenu();
			main->hide();
		}
		else {
			setMenu();
			main->show();
		}
	}
}

void TrayIcon::quit()
{
	main->close();

}

void TrayIcon::primerPla() {
	leftclick(QSystemTrayIcon::Trigger);
}

