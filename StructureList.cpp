/*
 * This file is part of qdacco
 * qdacco: offline Dacco Catalan <-> English dictionary
 *
 * Copyright (c) 2005, 2006, 2007
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

#include "StructureList.h"

#include <stdio.h>
#include <qstring.h>  

//TODO: Disable order when starting to insert, enable back again after it. New elemnts are in order, coming from dictionary!

bool StructureList::startDocument()
{
	//WordDataQueue queuelist(10);
	//wordqueue.setAutoDelete(TRUE);   (Ull! Tret per Qt4!)
	//after_word = 0;
	m_word_normalized=normalize(m_word);
	return TRUE;
}

bool StructureList::startElement( const QString&, const QString&,
					const QString& qName,
					const QXmlAttributes& ) //attributes
{
	entrada = (qName=="Entry");
	return TRUE;
}

bool StructureList::endElement( const QString&, const QString&, const QString& ) //qName
{
	
	return TRUE;
}

bool StructureList::characters ( const QString & ch )
{
	if (entrada && myStartsWith(ch,m_word_normalized)) {	
		m_list->insertItem(999999999,ch);
	}
	
	return TRUE;
}

void StructureList::setList(QListWidget *l)
{
	m_list=l;
}

void StructureList::setWord(QString w)
{
	m_word=w;
	//m_long=w->length();
}

void StructureList::setIgnoreCase(bool ignore)
{
        m_IgnoreCase=ignore;
}


void StructureList::setIgnoreAccents(bool ignore)
{
        m_IgnoreAccents=ignore;
}

//TODO: same method in StructureParser.cpp
bool StructureList::myStartsWith(const QString &ch, QString &word)
{
	QString dict(ch);
	dict=normalize(dict);

        return dict.startsWith(word);
}

QString &StructureList::normalize(QString &word) {
	if (m_IgnoreCase) {
		word=word.toLower();	
	}
	if (m_IgnoreAccents) {
		word.replace('à','a');
		word.replace('è','e');
		word.replace('ì','i');
		word.replace('ò','o');
		word.replace('ù','u');
		
		word.replace('á','a');
		word.replace('é','e');
		word.replace('í','i');
		word.replace('ó','o');
		word.replace('ú','u');
	}
	
	//printf("Paraula noramlitzada: %s\n",qPrintable(word));
	return word;
}
