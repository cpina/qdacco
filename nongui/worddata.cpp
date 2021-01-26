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
	num=0;
}

void WordData::setDefinition(const QString& q) {
	if (num<MAX_WORDS) {
		definition[num]=q;
	}
	else {
		printError("definition");
	}
}

void WordData::setGender(const QString& q) {
	if (num<MAX_WORDS) {
		gender[num]=q;
	}
	else {
		printError("gender");
	}

}

void WordData::setCatExample(const QString& q) {
	if (num<MAX_WORDS) {
		catexamp[num]=q;
	}
	else {
		printError("catexamp");
	}
}

void WordData::setEnglishExample(const QString& q) {
	if (num<MAX_WORDS) {
		engexamp[num]=q;
	}
	else {
		printError("engexamp");
	}
}

void WordData::setTipus(const QString& q) {
	if (num<MAX_WORDS) {
		tipus[num]=q;
	}
	else {
		printError("type");
	}

}

void WordData::setExample(const QString& q) {
	if (num<MAX_WORDS) {
		example[num]+=q+"<BR>";
	}
	else {
		printError("example");
	}
}

void WordData::setEnglishNote(const QString& q) {
	if (num<MAX_WORDS) {
		engnote[num]+=q;
	}
	else {
		printError("engnote");
	}
}


void WordData::setCatalanNote(const QString& q) {
	if (num<MAX_WORDS) {
		catnote[num]+=q;
	}
	else {
		printError("catnote");
	}
}

void WordData::setPicture(const QString& q) {
	if (num<MAX_WORDS) {
		picture[num]+="<A HREF=\""+q+"\">"+q+"</A>";
	}
	else {
		printError("picture");
	}
}


void WordData::setFlickr(const QString& q) {
	if (num<MAX_WORDS) {
		flickr[num]+="<A HREF=\""+q+"\">"+q+"</A>";
	}
	else {
		printError("flickr");
	}
}

void WordData::setPlural(const QString& q) {
	if (num<MAX_WORDS) {
		plural[num]+=q;
	}
	else {
		printError("plural");
	}
}


void WordData::setFemeninePlural(const QString& q) {
	if (num<MAX_WORDS) {
		femplural[num]+=q;
	}
	else {
		printError("femplural");
	}
}

void WordData::setSynonyms(const QString& q) {
	if (num<MAX_WORDS) {
		synonyms[num]+=q;
	}
	else {
		printError("synonyms");
	}
}



//---------------end put

QString WordData::getDefinition(int i) {
	return (definition[i]);
}

QString WordData::getGender(int i) {
	return(gender[i]);
}

QString WordData::getCatexamp(int i) {
	return (catexamp[i]);
}

QString WordData::getEngexamp(int i) {
	return (engexamp[i]);
}

QString WordData::getTipus(int i) {
	return (tipus[i]);
}

QString WordData::getExample(int i) {
	return (example[i]);
}

QString WordData::getEngnote(int i) {
        return (engnote[i]);
}

QString WordData::getCatnote(int i) {
        return (catnote[i]);
}

QString WordData::getPicture(int i) {
        return (picture[i]);
}

QString WordData::getFlickr(int i) {
        return (flickr[i]);
}

QString WordData::getPlural(int i) {
        return (plural[i]);
}

QString WordData::getFemplural(int i) {
        return (femplural[i]);
}


QString WordData::getSynonyms(int i) {
        return (synonyms[i]);
}

//-----------eng get

int WordData::getNum() {
	return num;
}

void WordData::incNum() {
	if (num<MAX_WORDS) {
		num++;
	}
}

QString WordData::HTML2Text(QString t) {
	t=t.replace("<BR>","\n");
	t=t.replace("<U>","");
	t=t.replace("</U>","");


	t=t.replace("<I>","");
	t=t.replace("</I>","");
	
	//printf("paraula: %s\n",qPrintable(t));

	int urlstart,urlend;
	int endloop=0;

	// TODO: don't write what we don't want

	// Tricky way to remove <A HREF=" from Flickr and Pictures fields
	// Right now, this TAGS are setted up during putFlickr and putPicture
	// (called from StructureParser) so StructureParser should know if we
	// will want text or HTML. Or we should format when getting the data
	// (better way). By the moment I do the tricky system to remove what
	// should not be here
	//
	while (endloop==0) {
		urlstart=t.indexOf("<A HREF=\"");
		urlend=t.indexOf("\"",urlstart+strlen("<A HREF=\""));
		if (urlend>urlstart) {
			t=t.remove(urlstart,urlend-urlstart+2);
		}
		else {
			endloop=1;
		}
	}
	t=t.replace("</A>","");

	return t;
}

QString WordData::getEntry(int i) {
	return getHTMLEntry(i);
}

QString WordData::getTextEntry(int i) {
	QString p=getHTMLEntry(i);

	//Note: usually to treat with HTML without specialized library
	//is "crap". But since I added only this tag's, I can remove myself :-)
	
	p=p.replace("<BR>","\n");
	p=p.replace("<U>","");
	p=p.replace("</U>","");


	p=p.replace("<I>","");
	p=p.replace("</I>","");

	return p;
}

QString WordData::getHTMLEntry(int i) {
	QString ret;
	QString gender;
	int picture=false;

	if (!(getGender(i)).isNull()) {
		gender=" ("+getGender(i)+")";
	}
	ret="<I>"+getTipus(i)+gender+"</I><BR>";
	ret+=getDefinition(i);

	//Warning/TODO: this constants strings are also used in textbrowser.h
	if (!(getPlural(i)).isNull()) {
		ret+="<BR><U>"+QObject::tr("Plural: ")+"</U>"+getPlural(i);
	}

	if (!(getFemplural(i)).isNull()) {
		ret+="<BR><U>"+QObject::tr("Female plural: ")+"</U>"+getFemplural(i);
	}

	if (!(getSynonyms(i)).isNull()) {
		ret+="<BR><U>"+QObject::tr("Synonym(s): " )+"</U>"+getSynonyms(i);
	}

	if (!(getCatexamp(i)).isNull()) {
		ret+="<BR><U>"+QObject::tr("Catalan example(s): ")+"</U>"+getCatexamp(i);
	}

	if (!(getEngexamp(i)).isNull()) {
		ret+="<BR><U>"+QObject::tr("English example(s): ")+"</U>"+getEngexamp(i);
	}

	if (!(getExample(i)).isNull()) {
		ret+="<BR><U>"+QObject::tr("Example(s): ")+"</U>"+getExample(i);
	}
	
	if (!(getEngnote(i)).isNull()) {
		ret+="<BR><U>"+QObject::tr("English notes: ")+"</U>"+getEngnote(i);
	}

	if (!(getCatnote(i)).isNull()) {
		ret+="<BR><U>"+QObject::tr("Catalan notes: ")+"</U>"+getCatnote(i);
	}

	if (!(getPicture(i)).isNull()) {
		ret+="<BR>";
		ret+="<BR><U>"+QObject::tr("Picture: ")+"</U> "+getPicture(i);
		picture=true;
	}

	if (!(getFlickr(i)).isNull()) {
		if (picture==false) {
			ret+="<BR>";
		}
		ret+="<BR><U>"+QObject::tr("Flickr: ")+"</U> "+getFlickr(i);
	}

	return ret;
}

void WordData::printError(const QString& tag) {
	qDebug() << "ERROR: not saving" << tag << "because there is more than 50";
}
