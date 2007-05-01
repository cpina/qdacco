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

#ifndef DADESPARAULA_H
#define DADESPARAULA_H

#include <QString>
#include <QObject>
#define MAX_WORDS 50

class WordData {
public:
	WordData();
	void putDefinition(QString q);
	void putGender(QString q);
	void putTipus(QString q);
	void putCatexamp(QString q);
	void putEngexamp(QString q);
	void putExample(QString q);
	void putEngnote(QString q);
	void putCatnote(QString q);
	void putPicture(QString q);
	void putFlickr(QString q);
	void putPlural(QString q);
	void putFemplural(QString q);
	void putSynonyms(QString q);

	QString getDefinition(int i);
	QString getGender(int i);
	QString getTipus(int i);
	QString getCatexamp(int i);
	QString getEngexamp(int i);
	QString getExample(int i);
	QString getEngnote(int i);
	QString getCatnote(int i);
	QString getPicture(int i);
	QString getFlickr(int i);
	QString getPlural(int i);
	QString getFemplural(int i);
	QString getSynonyms(int i);

	int getNum();
	void incNum();
	QString getEntry(int i);

private:
	void printError(QString tag);

	int num;

	QString definition[MAX_WORDS];
	QString gender[MAX_WORDS];
	QString tipus[MAX_WORDS];
	QString catexamp[MAX_WORDS];
	QString engexamp[MAX_WORDS];
	QString example[MAX_WORDS];
	QString engnote[MAX_WORDS];
	QString catnote[MAX_WORDS];
	QString picture[MAX_WORDS];
	QString flickr[MAX_WORDS];
	QString plural[MAX_WORDS];
	QString femplural[MAX_WORDS];
	QString synonyms[MAX_WORDS];
};

#endif
