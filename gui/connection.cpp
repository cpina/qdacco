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


#ifndef HTTPCONNECTION_CPP
#define HTTPCONNECTION_CPP

#include "connection.h"

/*Original idea to program it from:
http://cvs.sourceforge.net/viewcvs.py/kmess/kmess/kmess/network/extra/httpsoapconnection.cpp?rev=1.1&view=auto
 */

HTTPConnection::HTTPConnection(QMainWindow *m) {
	m_http = new QHttp(Auxiliar::getHost(), 80);
	
	connect(m_http,SIGNAL(requestFinished(int,bool)),
			m,SLOT(ReportChangeState(int,bool)));
}

int HTTPConnection::sendNewWord(const QString &paraula, const QString &user,
				const QString &email, int idioma_actiu) {
	QString idioma;
	QString *content;

	if (idioma_actiu==1) {
		idioma="català";
	}
	else {
		idioma="english";
	}

	content=new QString("name="+user+"&version="+AuxiliarGUI::getVersion()+"&word="+paraula+"&email="+email+"&language="+idioma+"&type=new");
	
	send_post(*content);

	return 0;
}

int HTTPConnection::sendSuggestion(const QString &paraula,const QString &translation, const QString &examples, const QString &notes, const QString &user, const QString &email, int idioma_actiu) {
	QString idioma;
	QString *content;
	
        if (idioma_actiu==1) {
                idioma="català";
        }
        else {
                idioma="english";
        }

	content=new QString("name="+user+"&version="+AuxiliarGUI::getVersion()+"&word="+paraula+"&email="+email+"&language="+idioma+"&translation="+translation+"&examples="+examples+"&notes="+notes+"&type=suggestion");
	
	send_post(*content);
	
	return 0;
}

int HTTPConnection::send_post(const QString &q) {
	QByteArray content; 
	content = q.toUtf8();
	Auxiliar::debug("POST: "+q);

	QHttpRequestHeader header("POST", Auxiliar::getURL());

	header.setContentType("application/x-www-form-urlencoded");
	header.setContentLength(content.length());
	header.setValue("Host",Auxiliar::getHost());

	m_http->request(header,content);

	return 0;
}

QString* HTTPConnection::getStateError() {
	QString *ret;
	
	if (m_http->error() == QHttp::NoError) {
		ret=new QString("");
	}
	else {
		ret=new QString(m_http->errorString());
	}
	return ret;
}
#endif
