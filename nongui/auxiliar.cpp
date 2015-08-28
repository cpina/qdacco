/*
 * This file is part of qdacco
 * qdacco: offline Dacco Catalan <-> English dictionary
 *
 * Copyright (c) 2005, 2006, 2007, 2008, 2009, 2011, 2015
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

#include <QDebug>

#include "auxiliar.h"

//Variables to adjust
int Auxiliar::debugLevel=1;
QString Auxiliar::version = "0.7.0";
QString Auxiliar::host = "www.catalandictionary.org";
QString Auxiliar::url = "/qdaccoReport.php";
QString Auxiliar::dictionaries_directory = "/usr/share/dacco-common/dictionaries";
QString Auxiliar::copyright_date = "2005, 2006, 2007, 2008, 2009, 2011";

QString Auxiliar::getDictionariesDirectory() {
	return dictionaries_directory;
}

QString Auxiliar::getVersion() {
	return version;
}


QString Auxiliar::getNetVersion() {
	QString ret;
	if (isWindows()) {
		ret=version+"W";
	}
	else {
		ret=version+"U";
	}
	return ret;
}

QString Auxiliar::getHost() {
	return host;
}

QString Auxiliar::getURL() {
	return url;
}

QString Auxiliar::getCopyrightDate() {
	return copyright_date;
}

void Auxiliar::setDebug(int i) {
	debugLevel=i;
}

int Auxiliar::getDebug() {
	return debugLevel;
}

void Auxiliar::debug(QString s) {
	if (debugLevel) {
		qDebug() << "Debug: " << s;
	}
}

int Auxiliar::KeyDown() {
	return 0;
}

int Auxiliar::KeyUp() {
	return 1;
}

int Auxiliar::KeyNextPage() {
	return 2;
}

int Auxiliar::KeyPrevPage() {
	return 3;
}

int Auxiliar::eng2cat() {
	return 1;
}
int Auxiliar::cat2eng() {
	return 2;
}

int Auxiliar::catalan() {
	return 1;
}

int Auxiliar::english() {
	return 2;
}

bool Auxiliar::isWindows() {
	//is it not possible to know in run time?? ¿?
	#if defined(Q_OS_WIN32)
	return true;
	#else
	return false;
	#endif
}

bool Auxiliar::isMac() {
	//is it not possible to know in run time?? ¿?
	#if defined(Q_OS_MAC)
	return true;
	#else
	return false;
	#endif
}

bool Auxiliar::isUnix() {
	//bad aproximation :-D
	return (!Auxiliar::isWindows() && !Auxiliar::isMac());
}

char Auxiliar::lletra_buscar(QString q) {
        QChar a;

        if (q.at(0)=='à' || q.at(0)=='á' || q.at(0)=='â' || q.at(0)=='ä') return 'a';
        if (q.at(0)=='è' || q.at(0)=='é' || q.at(0)=='ê' || q.at(0)=='ë') return 'e';
        if (q.at(0)=='ì' || q.at(0)=='í' || q.at(0)=='î' || q.at(0)=='ï') return 'i';
        if (q.at(0)=='ò' || q.at(0)=='ó' || q.at(0)=='ô' || q.at(0)=='ö') return 'o';
        if (q.at(0)=='ù' || q.at(0)=='ú' || q.at(0)=='û' || q.at(0)=='ü') return 'u';

        if (q.at(0)=='ç') return 'c';

        a=q.at(0).toLower();

        return (a.toLatin1());
}
