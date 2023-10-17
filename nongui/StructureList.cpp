/*
 * This file is part of qdacco
 * qdacco: offline Dacco Catalan <-> English dictionary
 *
 * Copyright (c) 2005, 2006, 2007, 2015, 2020, 2021, 2023
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

#include <nongui/StructureList.h>
#include <QXmlStreamReader>

static QStringList exampleElements = {"example", "catexamp", "engexamp"};
static QStringList noteElements = {"catnote", "engnote"};

StructureList::StructureList()
{
    m_addEntry = nullptr;
    m_entryWanted = QString();
}

void StructureList::setEntryWanted(const QString& entryWanted) {
    m_entryWanted = entryWanted;
}

void StructureList::parseFile(QFile& xmlFile) {
    // Open the file, parse it. Search for m_word. Call m_addEntry
    xmlFile.open(QIODevice::ReadOnly);

    m_word_normalized=normalize(m_word);

    QXmlStreamReader reader(&xmlFile);

    while (!reader.isEndDocument() && !reader.hasError()) {
        if (reader.isStartElement()) {
            startElement(reader);
        }
        if (reader.isCharacters()) {
            characters(reader);
        }
        if (reader.isEndElement()) {
            endElement(reader);
        }
        reader.readNext();
    }
}

void StructureList::startElement(QXmlStreamReader& reader) {
    QString qName = reader.name().toString();  // "entry", "translations", "date", "translation", etc.

    reader.readNext();

    if (qName == "Entry") {
        QString entry = reader.text().toString();

        if (myStartsWith(entry, m_word_normalized) && m_addEntry) {
            m_addEntry(entry);
        }

        m_inSearchedWord = (entry == m_entryWanted);
    }
}

void StructureList::endElement(QXmlStreamReader& reader) {
    const QString qName = reader.name().toString();

    if (!m_inSearchedWord) {
        return;
    }

        if (m_inPlural && qName == "plural") {
            m_inPlural = false;
        }
        else if (m_inCatAcro && qName == "catacro") {
            m_inCatAcro = false;
        }
        else if (m_inEngAcro && qName == "engacro") {
            m_inEngAcro = false;
        }
        else if (m_inFems && qName == "fems") {
            m_inFems = false;
        }
        else if (m_inFemPlural && qName == "femplural") {
            m_inFemPlural = false;
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
        else if (qName == "mistakes") {
            m_wordData.setMistakes(m_mistakes);
            m_mistakes = QString();
        }
        else if (qName == "synonyms") {
            m_inSynonyms = false;
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

        if (qName=="Entry") {	// leaving word, if we were in the matched
                                // not anymore. If we weren't it doesn't matter:
                                // we are not anymore either
            m_inSearchedWord=false;
        }
}

void StructureList::characters(QXmlStreamReader &reader) {
    processEntry(reader);
}

void StructureList::processEntry(QXmlStreamReader& reader) {
//    if (wordTypesList.contains(qName)) {
//        m_type = qName;
//    }
    QString qName = reader.text().toString().trimmed();
    if (m_type == "translation") {
        m_inTranslation = true;
        m_translation = Translation();

        m_translation.gender = reader.text().toString();
        m_translation.picture = reader.attributes().value("picture").toString();

        if (m_translation.picture.isEmpty()) {
            // It uses attributes.value("picture") if available, else tries with flickr
            m_translation.picture = reader.attributes().value("flickr").toString();
        }
        else if (qName == "mistakes") {
            m_inMistakes = true;
        } else if (qName == "catacro") {
            m_inCatAcro = true;
        } else if (qName == "engacro") {
            m_inEngAcro = true;
        } else if (qName == "expressions") {
            m_inExpressions = true;
            m_expressions = Expressions();
        } else if (qName == "plural") {
            m_inPlural = true;
        } else if (qName == "fems") {
            m_inFems = true;
        } else if (qName == "femplural") {
            m_inFemPlural = true;
        } else if (qName == "synonyms") {
            m_inSynonyms = true;
        } else if (exampleElements.contains(qName)) {
            m_inExample = true;
        } else if (noteElements.contains(qName)) {
            m_inNote = true;
        }
    }
}

//bool StructureList::startDocument()
//{
//    //WordDataQueue queuelist(10);
//    //wordqueue.setAutoDelete(TRUE);   (Ull! Tret per Qt4!)
//    //after_word = 0;
//    m_word_normalized=normalize(m_word);
//    return true;
//}

//bool StructureList::startElement( const QString&, const QString&,
//                                  const QString& qName,
//                                  const QXmlAttributes& ) //attributes
//{
//    entrada = (qName=="Entry");
//    return true;
//}

//bool StructureList::endElement( const QString&, const QString&, const QString& ) //qName
//{

//    return true;
//}

//bool StructureList::characters ( const QString & ch )
//{
//    if (entrada && myStartsWith(ch,m_word_normalized)) {
//        if(m_addEntry == nullptr)
//        {
//            if (m_list.length()==0) { //We don't want extra \n at first
//                //time

//                m_list=ch;
//            }
//            else {
//                m_list=m_list+"\n"+ch;
//            }
//        }//#endif
//        else {
//            m_addEntry(ch);
//        }
//    }

//    return true;
//}

void StructureList::setWord(const QString& w)
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

QString StructureList::normalize(const QString &word) {
    QString normalized = word;

    if (m_IgnoreCase) {
        normalized=word.toLower();
    }
    if (m_IgnoreAccents) {
        normalized.replace(u'à','a');
        normalized.replace(u'è','e');
        normalized.replace(u'ì','i');
        normalized.replace(u'ò','o');
        normalized.replace(u'ù','u');

        normalized.replace(u'á','a');
        normalized.replace(u'é','e');
        normalized.replace(u'í','i');
        normalized.replace(u'ó','o');
        normalized.replace(u'ú','u');
    }

    //printf("Paraula noramlitzada: %s\n",qPrintable(word));
    return normalized;
}

int StructureList::setAddFunction(void function(QString a)) {
    m_addEntry = function;

    return 0;
}

WordData StructureList::getWordData() {
    return m_wordData;
}
