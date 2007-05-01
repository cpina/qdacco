/*
 * This file is part of qdacco
 * qdacco: offline Dacco Catalan <-> English dictionary
 *
 * Copyright (c) 2005, 2006
 *      Carles Pina i Estany <carles@pina.cat>
 *
 * qdacco is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * any later version.
 *
 * qphotosort is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * long with Foobar; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef ABOUT_H
#define ABOUT_H

#include <QApplication>
#include <QDialog>
#include <QMessageBox>
#include <QSettings>
#include <QDir>
#include <QToolButton>
#include "ui_about.h"

class About : public QDialog
{
	Q_OBJECT
	public:
		About(QWidget *parent = 0);
	
	private:
		Ui::About ui;

	private slots:

	public slots:
};

#endif
