/*
 * This file is part of qdacco
 * qdacco: offline Dacco Catalan <-> English dictionary
 *
 * Copyright (c) 2005, 2006, 2007, 2015
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


#ifndef LINEEDIT_H
#define LINEEDIT_H

#include <QtGui>

//qdaccolib
#include <nongui/Auxiliar.h>

//Adds to QLineEdit capability to scroll list word box
//Adds to QLineEdit capability to read words

#include <QtWidgets/QLineEdit>

class LineEdit : public QLineEdit
{
	Q_OBJECT

	public:
		LineEdit (QWidget *parent=0);
		void setParent(QObject *q);
		virtual void contextMenuEvent(QContextMenuEvent *e);
		void setFestivalEnable(int f);

	protected:
		void keyPressEvent(QKeyEvent *pEvent);

	private:
		QObject* m_parent;
		int m_festival_enable;
		QPoint m_qpoint;

		void selectWord();
		int getPrevSpace(int pos);
		int getNextSpace(int pos);

};

#endif

