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

#include "StructureParser.h"
#include <QDebug>

static QStringList typeOfWords = {"nouns", "adjectives", "adverbs"};

bool StructureParser::startDocument()
{
    m_after_word = 0;
    m_inTranslation = false;
    m_inExpressions = false;

	return true;
}

bool StructureParser::startElement(const QString& nameSpaceUri, const QString& localName,
                    const QString& qName,
                    const QXmlAttributes& attributes)
{
    Q_UNUSED(nameSpaceUri);
    Q_UNUSED(localName);

    if (typeOfWords.contains(qName)) {
        m_type = qName;
    }

    if (qName == "translation") {
        m_inTranslation = true;
        m_translation = Translation();
    }

    if (qName == "expressions") {
        m_inExpressions = true;
        m_expressions = Expressions();
    }

    m_entry = (qName == "Entry");

    if (qName == "Entry") {
        m_entry = true;
    }

    return true;
//    m_entry = (qName == "Entry");
//    m_catexamp = (qName=="catexamp");
//    m_engexamp =(qName=="engexamp");
//    m_example = (qName=="example");
//    m_engnote = (qName=="engnote");
//    m_catnote = (qName=="catnote");
//    m_plural = (qName=="plural");
//    m_femplural = (qName=="femplural");
//    m_synonyms = (qName=="synonyms");

//    m_catexamp=false; m_engexamp=false;
//    m_entry=false; m_translation=false;
//    m_example=false;
//    m_engnote=false; m_catnote=false;
//    m_picture=false;
//    m_plural=false; m_femplural=false;
//    m_synonyms=false;

//    m_catexamp=(qName=="catexamp");
//    m_engexamp=(qName=="engexamp");
//    m_example=(qName=="example");
//    m_engnote=(qName=="engnote");
//    m_catnote=(qName=="catnote");
//    m_plural=(qName=="plural");
//    m_femplural=(qName=="femplural");
//    m_synonyms=(qName=="synonyms");

//    m_qgender_=attributes.value("gender");
//    m_qpicture_=attributes.value("picture");
//    m_qflickr_=attributes.value("flickr");

//    if (qName == "translation") {
//        m_translation = true;
//	}

//    if (qName == "adjectives") {m_qtipus_="adj";}
//    if (qName == "adverbs") {m_qtipus_="adv";}
//    if (qName == "exclamations") {m_qtipus_="excl";}
//    if (qName == "nouns") {m_qtipus_="n";}
//    if (qName == "prepositions") {m_qtipus_="prep";}
//    if (qName == "pronouns") {m_qtipus_="pron";}
//    if (qName == "verbs") {m_qtipus_="v";}

//	return true;
}

bool StructureParser::characters(const QString& chrs)
{
    QString ch = chrs.trimmed();

    bool same = compare(ch,m_paraula);
	
    if (m_entry && same) {
        m_found=true;
        m_inExpressions = false;
        m_inTranslation = false;
	}

    if (m_found && m_inTranslation) {
        m_translation.translation = ch;
    }
    else if (m_found && m_inExpressions) {
        m_expressions.expression = ch;
    }

    if (m_entry && !same) {
        m_found=false;
	}

    qDebug() << ch;


//    if (m_found && m_catexamp) {
//        m_wordData.setCatExample(ch);
//	}

//    if (m_found && m_engexamp) {
//        m_wordData.setEnglishExample(ch);
//	}

//    if (m_found && m_example) {
//        m_wordData.setExample(ch);
//	}

	
//    if (m_found && m_translation) {
//        m_wordData.setTranslation(ch);

//        m_wordData.setGender(m_qgender_);
//        m_wordData.setTipus(m_qtipus_);

//        if (!m_qpicture_.isEmpty()) {
//            m_wordData.setPicture(m_qpicture_);
//		}
//        if (!m_qflickr_.isEmpty()) {
//            m_wordData.setFlickr(m_qflickr_);
//		}
//	}

//    if (m_found && m_engnote) {
//        m_wordData.setEnglishNote(ch);
//	}

//    if (m_found && m_catnote) {
//        m_wordData.setCatalanNote(ch);
//	}

//    if (m_found && m_plural) {
//        m_wordData.setPlural(ch);
//	}

//    if (m_found && m_femplural) {
//        m_wordData.setFemeninePlural(ch);
//	}

//    if (m_found && m_synonyms) {
//        m_wordData.setSynonyms(ch);
//	}
	return true;
}

bool StructureParser::endElement(const QString& nameSpaceUri, const QString& localName, const QString& qName)
{
    Q_UNUSED(nameSpaceUri);
    Q_UNUSED(localName);

    if (m_found && m_inExpressions && qName == "translation") {
        m_expressions.translations.append(m_translation);
        m_translation = Translation();
        m_inTranslation = false;
    }
    else if (m_found && qName == "translation") {
        m_wordData.addTranslation(m_translation, m_type);
        m_translation = Translation();
        m_inTranslation = false;
    }

    if (m_found && qName == "expressions") {
        m_wordData.addExpressions(m_expressions);
        m_expressions = Expressions();
        m_inExpressions = false;
    }

    if (m_found && typeOfWords.contains(qName)) {
        m_type = QString();
    }

    if (m_found && qName=="Entry") {	//ja sortim de la paraula
        m_found=false;
    }

    return true;
}

void StructureParser::setParaula(const QString &s) 
{
    m_paraula=s;
}

WordData StructureParser::getWordData()
{
    return m_wordData;
}

bool StructureParser::compare(QString ch, QString word)
{
	return ch.compare(word)==0;
}
