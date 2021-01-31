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

static QStringList exampleElements = {"example", "catexamp", "engexamp"};
static QStringList noteElements = {"catnote", "engnote"};

bool StructureParser::startDocument()
{
    m_after_word = 0;

	return true;
}

bool StructureParser::startElement(const QString& nameSpaceUri, const QString& localName,
                    const QString& qName,
                    const QXmlAttributes& attributes)
{
    Q_UNUSED(nameSpaceUri);
    Q_UNUSED(localName);

    if (wordTypesList.contains(qName)) {
        m_type = qName;
    }

    if (qName == "translation") {
        m_inTranslation = true;
        m_translation = Translation();

        m_translation.gender = attributes.value("gender");
    }

    if (qName == "expressions") {
        m_inExpressions = true;
        m_expressions = Expressions();
    }

    if (qName == "plural") {
        m_inPlural = true;
    }

    if (qName == "fems") {
        m_inFems = true;
    }

    if (exampleElements.contains(qName)) {
        m_inExample = true;
    }

    if (noteElements.contains(qName)) {
        m_inNote = true;
    }

    m_entry = (qName == "Entry");

    if (qName == "Entry") {
        m_entry = true;
    }

    return true;
//    if (qName == "adjectives") {m_qtipus_="adj";}
//    if (qName == "adverbs") {m_qtipus_="adv";}
//    if (qName == "exclamations") {m_qtipus_="excl";}
//    if (qName == "nouns") {m_qtipus_="n";}
//    if (qName == "prepositions") {m_qtipus_="prep";}
//    if (qName == "pronouns") {m_qtipus_="pron";}
//    if (qName == "verbs") {m_qtipus_="v";}
}

bool StructureParser::characters(const QString& chrs)
{
    QString ch = chrs.trimmed();

    bool same = compare(ch,m_paraula);
	
    if (m_entry) {
        if (same) {
            m_found = true;
            m_inExpressions = false;
            m_inTranslation = false;
            m_inExample = false;
            m_inPlural = false;
            m_inNote = false;
            m_inFems = false;

            m_type = QString();
        }
        else {
            m_found=false;
        }
    }

    if (m_entry && same) {
        m_found = true;
        m_inExpressions = false;
        m_inTranslation = false;
        m_inExample = false;
        m_inPlural = false;
        m_inNote = false;
        m_inFems = false;

        m_type = QString();
	}

    if (m_found) {
        if (m_inTranslation && m_inPlural) {
            m_translation.plural = ch;
        }
        else if (m_inTranslation && m_inExample) {
            m_translation.examples.append(ch);
        }
        else if (m_inTranslation && m_inNote) {
            m_translation.notes.append(ch);
        }
        else if (m_inFems) {
            m_translation.fems = ch;
        }
        else if (m_inTranslation) {
            m_translation.translation = ch;
        }
        else if (m_inExpressions) {
            m_expressions.expression = ch;
        }
    }

	return true;
}

bool StructureParser::endElement(const QString& nameSpaceUri, const QString& localName, const QString& qName)
{
    Q_UNUSED(nameSpaceUri);
    Q_UNUSED(localName);

    if (!m_found) {
        return true;
    }

    if (m_inPlural && qName == "plural") {
        m_inPlural = false;
    }
    else if (m_inFems && qName == "fems") {
        m_inFems = false;
    }
    else if (m_inExpressions && qName == "translation") {
        m_expressions.translations.append(m_translation);
        m_translation = Translation();
        m_inTranslation = false;
    }
    else if (qName == "translation") {
        m_wordData.addTranslation(m_translation, m_type);
        m_translation = Translation();
        m_inTranslation = false;
    }

    if (exampleElements.contains(qName)) {
        m_inExample = false;
    }

    if (noteElements.contains(qName)) {
        m_inNote = false;
    }

    if (qName == "expressions") {
        m_wordData.addExpressions(m_expressions);
        m_expressions = Expressions();
        m_inExpressions = false;
    }

    if (wordTypesList.contains(qName)) {
        m_type = QString();
    }

    if (qName=="Entry") {	//ja sortim de la paraula
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
