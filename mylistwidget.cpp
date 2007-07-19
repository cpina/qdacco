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

#include <QtGui>
#include <QCoreApplication>
#include "mylistwidget.h"

MyListWidget::MyListWidget(QWidget *parent) : QListWidget(parent)
{

}

void MyListWidget::keyPressEvent(QKeyEvent *pEvent)
{
	int qkey = pEvent->key();
	int send=0;
	int type=0;
	

 	if (qkey == Qt::Key_Down) {

		type=QEvent::User+Auxiliar::KeyDown();
		send=1;
	}
	else if (qkey == Qt::Key_Up) {
		type=QEvent::User+Auxiliar::KeyUp();
		send=1;
	}
	else if (qkey == Qt::Key_PageDown) {
		type=QEvent::User+Auxiliar::KeyNextPage();
		send=1;

	}
	else if (qkey == Qt::Key_PageUp) {
		type=QEvent::User+Auxiliar::KeyPrevPage();
		send=1;
	}

	if (send) {
		QEvent qevent((QEvent::Type)type);
		QCoreApplication::sendEvent(m_parent,&qevent);
	}
	else {
		QListWidget::keyPressEvent(pEvent);
	}
}

void MyListWidget::setParent(QObject *q)
{
	m_parent=q;
}
