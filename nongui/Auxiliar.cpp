/*
 * This file is part of qdacco
 * qdacco: offline Dacco Catalan <-> English dictionary
 *
 * Copyright (c) 2005, 2006, 2007, 2008, 2009, 2011, 2015, 2021, 2023
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

#include "Auxiliar.h"

//Variables to adjust
int Auxiliar::debugLevel=1;
QString Auxiliar::version = "0.7.0";
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
    QChar c = q.at(0);

    if (c==u'à' || c==u'á' || c==u'â' || c==u'ä') return 'a';
    if (c==u'è' || c==u'é' || c==u'ê' || c==u'ë') return 'e';
    if (c==u'ì' || c==u'í' || c==u'î' || c==u'ï') return 'i';
    if (c==u'ò' || c==u'ó' || c==u'ô' || c==u'ö') return 'o';
    if (c==u'ù' || c==u'ú' || c==u'û' || c==u'ü') return 'u';

    if (c==u'ç') return 'c';

    c = c.toLower();

    return (c.toLatin1());
}
