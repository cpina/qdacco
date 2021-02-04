/*
 * This file is part of qdacco
 * qdacco: offline Dacco Catalan <-> English dictionary
 *
 * Copyright (c) 2005, 2006, 2007, 2015, 2021
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

#include "worddata.h"

WordData::WordData() {
}

void WordData::setType(const QString& type, const QString& ipa) {
    m_currentType = type;
    m_currentIpa = ipa;
    m_found = false;
}

void WordData::setCatalanAcronym(const QString& acronym)
{
    m_entry.catalanAcronym = acronym;
}

void WordData::setEnglishAcronym(const QString& acronym)
{
    m_entry.englishAcronym = acronym;
}

void WordData::addTranslation(const Translation& translation, const QString &type) {
    m_found = true;

    m_entry.wordTypes[type].translations.append(translation);
}

void WordData::addExpressions(const Expressions& expressions) {
    m_found = true;

    m_entry.expressions.append(expressions);
}

bool WordData::found() {
    return m_found;
}

QString WordData::getHTMLEntry() {
    return m_entry.getHtml();
}

//QString WordData::getHTMLEntry(int i) {
//	QString ret;
//	QString gender;
//	int picture=false;

//	if (!(getGender(i)).isNull()) {
//		gender=" ("+getGender(i)+")";
//	}
//	ret="<I>"+getTipus(i)+gender+"</I><BR>";
//	ret+=getDefinition(i);

//	//Warning/TODO: this constants strings are also used in textbrowser.h
//	if (!(getPlural(i)).isNull()) {
//		ret+="<BR><U>"+QObject::tr("Plural: ")+"</U>"+getPlural(i);
//	}

//	if (!(getFemplural(i)).isNull()) {
//		ret+="<BR><U>"+QObject::tr("Female plural: ")+"</U>"+getFemplural(i);
//	}

//	if (!(getSynonyms(i)).isNull()) {
//		ret+="<BR><U>"+QObject::tr("Synonym(s): " )+"</U>"+getSynonyms(i);
//	}

//	if (!(getCatexamp(i)).isNull()) {
//		ret+="<BR><U>"+QObject::tr("Catalan example(s): ")+"</U>"+getCatexamp(i);
//	}

//	if (!(getEngexamp(i)).isNull()) {
//		ret+="<BR><U>"+QObject::tr("English example(s): ")+"</U>"+getEngexamp(i);
//	}

//	if (!(getExample(i)).isNull()) {
//		ret+="<BR><U>"+QObject::tr("Example(s): ")+"</U>"+getExample(i);
//	}

//	if (!(getEngnote(i)).isNull()) {
//		ret+="<BR><U>"+QObject::tr("English notes: ")+"</U>"+getEngnote(i);
//	}

//	if (!(getCatnote(i)).isNull()) {
//		ret+="<BR><U>"+QObject::tr("Catalan notes: ")+"</U>"+getCatnote(i);
//	}

//	if (!(getPicture(i)).isNull()) {
//		ret+="<BR>";
//		ret+="<BR><U>"+QObject::tr("Picture: ")+"</U> "+getPicture(i);
//		picture=true;
//	}

//	if (!(getFlickr(i)).isNull()) {
//		if (picture==false) {
//			ret+="<BR>";
//		}
//		ret+="<BR><U>"+QObject::tr("Flickr: ")+"</U> "+getFlickr(i);
//	}

//	return ret;
//}
