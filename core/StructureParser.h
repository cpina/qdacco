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

#ifndef STRUCTUREPARSER_H
#define STRUCTUREPARSER_H

#include <stdio.h>
#include <qstring.h>

#include <QXmlDefaultHandler>
#include <QQueue> 

#include "worddata.h"
#include "auxiliar.h"

class QString;

class StructureParser : public QXmlDefaultHandler
{
	public:
	bool startDocument();
	bool startElement( const QString&, const QString&, const QString& ,
			const QXmlAttributes& attributes);
	bool endElement( const QString&, const QString&, const QString& );
	bool characters ( const QString & ch );
	void setParaula(const QString &s);
	void setPdebug(int i);
	WordData getWordData();
	int ensenyarLlistat();
	QQueue<QString> getWordQueue();
	bool esBuida();
	QString seguent();
	void setCapital(bool capital);

	private:
	bool compare(QString ch, QString word);

	bool entrada,translation,catexamp,engexamp,tipus,example;
	bool engnote,catnote,picture,plural,femplural;
	bool synonyms;

	bool trobat;
	QString paraula,definicio,qcatexamp,qengexamp;
	QString qtipus,qgender,qgender_,qtipus_,qpicture_,qflickr_;
	WordData wd;

	int after_word;
};

#endif
