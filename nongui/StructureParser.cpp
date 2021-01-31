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
static QStringList exampleElements = {"example", "catexamp", "engexamp"};

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

        m_translation.gender = attributes.value("gender");
    }

    if (qName == "expressions") {
        m_inExpressions = true;
        m_expressions = Expressions();
    }

    if (exampleElements.contains(qName)) {
        m_inExample = true;
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
	
    if (m_entry && same) {
        m_found=true;
        m_inExpressions = false;
        m_inTranslation = false;
        m_inExample = false;
	}

    if (m_found && m_inTranslation && m_inExample) {
        m_translation.examples.append(ch);
    }
    else if (m_found && m_inTranslation) {
        m_translation.translation = ch;
    }
    else if (m_found && m_inExpressions) {
        m_expressions.expression = ch;
    }

    if (m_entry && !same) {
        m_found=false;
    }

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

    if (m_found && exampleElements.contains(qName)) {
        m_inExample = false;
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
