/*
 * This file is part of qdacco
 * qdacco: offline Dacco Catalan <-> English dictionary
 *
 * Copyright (c) 2005, 2006, 2007, 2009, 2011, 2015, 2021
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

#ifndef MAIN_H
#define MAIN_H


#include <QtWidgets/QScrollBar>

#include <QApplication>
#include <QDialog>
#include <QMessageBox>
#include <QToolButton>
#include <QMainWindow>
#include <QClipboard>
#include "ui_main.h"

class HTTPConnection;

// TODO: prepare a different objects for, at least, networking and festival

class Main : public QMainWindow, Ui::Main
{
	Q_OBJECT
	public:
		Main(QWidget *parent = 0);

		int UpdateList(QString &q);
        void AddEntryToGUI(QString);

		void restaura();
		void quit();
		
		/////
		QString getParaula();
		void setParaula(QString paraula);
		int getIdiomaActiu();
		void setIdiomaActiu(int actiu);
		
		void buscar();
	
	private:
		HTTPConnection *m_http;
		QProcess m_festival;

		Ui::Main ui;

		int m_idioma_actiu;
		int m_festival_reading;

		QString m_directori_usuari;
		QString m_searched;

		QToolButton *m_cat_eng;
		QToolButton *m_eng_cat;

		//TODO: prepare a config structure
		bool m_IgnoreCase;
		bool m_IgnoreAccents;
		bool m_CurrentUILanguage;
		bool m_Autocomplete;
		QString m_FestivalPath;

		void treballaBuscar();
		void posarApunt();
		int isValidWord(QString &q);
		void posarApunt(int all);
        char removeAccents(const QString &q);
		void selectItem();
		void carrega_config(int all);
		void obrir_configuracio();
		void obrir_configuracio_worker(bool first);
		

		
		void posa_idioma();

		void showError(QString text);
		void showMessage(QString text);
		
		void FestivalExecute(QString text,QString arguments);

		void moveWordList(QEvent *event);
		void moveDefinicio(QEvent *event);


    private Q_SLOTS:
		void buscarEnter();
		void buscarClicked();
		void paraulaChanged(const QString &text);
		
		void obrir_configuracio_slot();
		
		void obrir_about();
		
		void cat_engf();
		void eng_catf();

		void switchDictionary();

		void copy_definition();
		void paste_word();
		void select_word();

		void searchListWord(QListWidgetItem *a);
		void UpdateList();

        void showBrowserError();

    public Q_SLOTS:
		void FestivalExecuteEntry();
		void FestivalExecuteDefinition();
		void FestivalError(QProcess::ProcessError e);
		void FestivalFinished(int statusEvent,QProcess::ExitStatus e);
		

	protected:
		bool eventFilter(QObject *obj, QEvent *event);
};


#endif
