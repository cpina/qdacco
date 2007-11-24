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

#ifndef StructureList_H
#define StructureList_H

#include <QListWidget>
#include <QXmlDefaultHandler>
#include <QQueue> 
#include <QString>

#include "../core/worddata.h"

class QString;

class StructureList : public QXmlDefaultHandler
{
	public:
	bool startDocument();
	bool startElement( const QString&, const QString&, const QString& ,
			const QXmlAttributes& attributes);
	bool endElement( const QString&, const QString&, const QString& );
	bool characters ( const QString & ch );

	void setIgnoreCase(bool capital);
	void setIgnoreAccents(bool capital);

	void setParaula(const QString &) {}
	WordData getWordData() { WordData h; return h;}

	void setList(QListWidget *l);
	void setWord(QString w);

	bool myStartsWith(const QString &ch, QString &word);

	QString &normalize(QString &word);

	private:
	bool entrada;

	int m_IgnoreCase;
	int m_IgnoreAccents;

	QListWidget *m_list;
	QString m_word;
	QString m_word_normalized;
};

#endif
