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

#ifndef SUGGERIMENT_H
#define SUGGERIMENT_H

#include <QApplication>
#include <QDialog>
#include <QMessageBox>
#include <QSettings>
#include <QDir>
#include <QToolButton>
#include "ui_suggeriment.h"

class Suggeriment : public QDialog
{
	Q_OBJECT
	public:
		Suggeriment(QWidget *parent = 0);

		void getUserWord (QString &w);
		void getUserTranslations (QString &w);
		void getUserExamples (QString &w);
		void getUserNotes (QString &w);
		void getOkay (int &o);

		void setWord(QString word_);
	
	private:
		Ui::Suggeriment ui;
		QString userWord,userTranslations,userExamples,userNotes;
		int okay;

	private slots:
		void oks();
		void cancels();

	public slots:
};
#endif
