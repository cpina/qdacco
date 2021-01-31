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

void WordData::addTranslation(const Translation& translation, const QString &type) {
    m_found = true;
    if (type == "nouns") {
        m_entry.nouns.translations.append(translation);
    } else if (type == "adverbs") {
        m_entry.adverbs.translations.append(translation);
    }
}

void WordData::addExpressions(const Expressions& expressions) {
    m_found = true;

    m_entry.expressions.append(expressions);
}

void WordData::setGender(const QString& q) {

}

void WordData::setCatExample(const QString& q) {
}

void WordData::setEnglishExample(const QString& q) {
}

void WordData::setTipus(const QString& q) {

}

void WordData::setExample(const QString& q) {
}

void WordData::setEnglishNote(const QString& q) {

}


void WordData::setCatalanNote(const QString& q) {
}

void WordData::setPicture(const QString& q) {
}


void WordData::setFlickr(const QString& q) {
}

void WordData::setPlural(const QString& q) {
}


void WordData::setFemeninePlural(const QString& q) {
}

void WordData::setSynonyms(const QString& q) {
}


//QString WordData::getDefinition(int i) {
//    return (m_definition[i]);
//}

//QString WordData::getGender(int i) {
//    return(m_gender[i]);
//}

//QString WordData::getCatexamp(int i) {
//    return (m_catexamp[i]);
//}

//QString WordData::getEngexamp(int i) {
//    return (m_engexamp[i]);
//}

//QString WordData::getTipus(int i) {
//    return (m_tipus[i]);
//}

//QString WordData::getExample(int i) {
//    return (m_example[i]);
//}

//QString WordData::getEngnote(int i) {
//        return (m_engnote[i]);
//}

//QString WordData::getCatnote(int i) {
//        return (m_catnote[i]);
//}

//QString WordData::getPicture(int i) {
//        return (m_picture[i]);
//}

//QString WordData::getFlickr(int i) {
//        return (m_flickr[i]);
//}

//QString WordData::getPlural(int i) {
//        return (m_plural[i]);
//}

//QString WordData::getFemplural(int i) {
//        return (m_femplural[i]);
//}


//QString WordData::getSynonyms(int i) {
//        return (m_synonyms[i]);
//}

////-----------eng get

bool WordData::found() {
    return m_found;
}

//void WordData::incNum() {
//	if (num<MAX_WORDS) {
//		num++;
//	}
//}

QString WordData::HTML2Text(const QString& html) {
    QString text = html;
    text=text.replace("<BR>","\n");
    text=text.replace("<U>","");
    text=text.replace("</U>","");


    text=text.replace("<I>","");
    text=text.replace("</I>","");
	
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
        urlstart=text.indexOf("<A HREF=\"");
        urlend=text.indexOf("\"",urlstart+strlen("<A HREF=\""));
		if (urlend>urlstart) {
            text=text.remove(urlstart,urlend-urlstart+2);
		}
		else {
			endloop=1;
		}
	}
    text=text.replace("</A>","");

    return text;
}

QString WordData::getHTMLEntry() {
    return m_entry.getHtml();

//    ret="<I>"+getTipus(i)+m_gender+"</I><BR>";

//    ret += getDefinition();

//    return ret;
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
