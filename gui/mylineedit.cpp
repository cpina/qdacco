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
#include "mylineedit.h"

MyLineEdit::MyLineEdit(QWidget *parent) : QLineEdit(parent)
{

}

void MyLineEdit::setFestivalEnable(int f) 
{
	m_festival_enable=f;
}

void MyLineEdit::keyPressEvent(QKeyEvent *pEvent)
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
	
	QLineEdit::keyPressEvent(pEvent);
}

void MyLineEdit::setParent(QObject *q)
{
	m_parent=q;
}

void MyLineEdit::contextMenuEvent(QContextMenuEvent *e)
{
	selectWord();
	QMenu *menu = createStandardContextMenu();
	QAction *festival = menu->addAction(tr("Read"));
	festival->setEnabled(m_festival_enable && this->text().length()>0);
	connect(festival,SIGNAL(triggered()),m_parent,SLOT(FestivalExecuteEntry()));
	menu->exec(e->globalPos());
	
	//moure-ho
}

void MyLineEdit::selectWord() {
	QTextCursor qtc;
	QString s;

	if (this->hasSelectedText()==FALSE) {
		//Selecciona paraula on hi ha el cursor
		int position=this->cursorPosition();
		int begin,end;

		begin=getPrevSpace(position);
		end=getNextSpace(position);
		this->setSelection(begin,end);

	}
}

int MyLineEdit::getPrevSpace(int pos) {
	while (pos>0 && this->text()[pos]!=' ') {
		pos--;
	}
	return pos;
}

int MyLineEdit::getNextSpace(int pos) {
	while (pos<this->text().length() && this->text()[pos]!=' ') {
		pos++;
	}
	return pos;
}
