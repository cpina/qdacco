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

#ifndef HTTPCONNECTION_H
#define HTTPCONNECTION_H

#include <QApplication>
#include <QDialog>
#include <QMessageBox>
#include <QtNetwork>
#include <QMainWindow>
#include "auxiliar.h"
//#include "main.h"

/*Original idea to program it from:
 * http://cvs.sourceforge.net/viewcvs.py/kmess/kmess/kmess/network/extra/httpsoapconnection.h?rev=1.1&view=auto
 */

class HTTPConnection : public QObject {
	Q_OBJECT

	public:
		HTTPConnection (QMainWindow *window);
		//virtual ~Connection();
		
		int sendNewWord(const QString &paraula, const QString &user,const QString &email, int idioma_actiu);

		int sendSuggestion(const QString &paraula,const QString &translation, const QString &examples, const QString &notes, const QString &user, const QString &email, int idioma_actiu);

		int send_post(const QString &q);

		QString* getStateError();

	private:
		QHttp *m_http;
	
	signals:
		void requestFailed();
		void requestFinished();
};
#endif
