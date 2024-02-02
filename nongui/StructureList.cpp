/*
 * This file is part of qdacco
 * qdacco: offline Dacco Catalan <-> English dictionary
 *
 * Copyright (c) 2005, 2006, 2007, 2015, 2020, 2021, 2023-2024
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
    QString qName = reader.name().toString();
    m_isEntry = (qName == "Entry");

    if (m_addEntry) {
        // Nothing else to do: the entry will be added in the processEntry()
        // Not interested in other features for the listing
        return;
    }

    if (wordTypesList.contains(qName)) {
        m_type = qName;
    }

    if (qName == "translation") {
        m_inTranslation = true;
        m_translation = Translation();

        m_translation.gender = reader.attributes().value("gender").toString();

        m_translation.picture = reader.attributes().value("picture").toString();

        if (m_translation.picture.isEmpty()) {
            // It uses attributes.value("picture") if available, else tries with flickr
            m_translation.picture = reader.attributes().value("flickr").toString();
        }

    } else if (qName == "mistakes") {
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
    } else if (qName == "otherlocal") {
        m_inOtherLocal = true;
    } else if (exampleElements.contains(qName)) {
        m_inExample = true;
    } else if (noteElements.contains(qName)) {
        m_inNote = true;
    }
}

void StructureList::endElement(QXmlStreamReader& reader) {
    if (!m_inSearchedWord) {
        return;
    }

    QString qName = reader.name().toString();

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
    } else if (qName == "otherlocal") {
        m_inOtherLocal = false;
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

    if (qName=="Entry") {       // leaving word, if we were in the matched
        // not anymore. If we weren't it doesn't matter:
        // we are not anymore either
        m_inSearchedWord=false;
    }
}

void StructureList::characters(QXmlStreamReader &reader) {
    processEntry(reader);
}

void StructureList::processEntry(QXmlStreamReader& reader) {
    QString ch = reader.text().toString().trimmed();

    if (m_isEntry) {
        QString entry = ch;
        if (m_addEntry && myStartsWith(entry, m_word_normalized)) {
            m_addEntry(entry);
            return;
        }
    }

    if (m_isEntry && !m_inSearchedWord) {
        if (ch == m_entryWanted) {
            m_inSearchedWord = true;
            m_inExpressions = false;
            m_inTranslation = false;
            m_inExample = false;
            m_inPlural = false;
            m_inOtherLocal = false;
            m_inNote = false;
            m_inFems = false;
            m_inFemPlural = false;
            m_inCatAcro = false;
            m_inEngAcro = false;
            m_inMistakes = false;
            m_inSynonyms = false;

            m_type = QString();
        }
        else {
            m_inSearchedWord = false;
        }
    }

    if (!m_inSearchedWord) {
        return;
    }

    if (m_inTranslation && m_inPlural) {
        m_translation.plural = ch;
    }
    if (m_inTranslation && m_inOtherLocal) {
        // This is added but not used in the UI
        // (it also needs to read the "local="us" and then show it as British local)
        m_translation.otherLocal = ch;
    }
    else if (m_inTranslation && m_inSynonyms) {
        m_translation.synonyms = ch;
    }
    else if (m_inTranslation && m_inCatAcro) {
        m_translation.catalanAcronym = ch;
    }
    else if (m_inTranslation && m_inEngAcro) {
        m_translation.englishAcronym = ch;
    }
    else if (m_inCatAcro) {
        m_wordData.setCatalanAcronym(ch);
    }
    else if (m_inEngAcro) {
        m_wordData.setEnglishAcronym(ch);
    }
    else if (m_inTranslation && m_inExample) {
        m_translation.examples.append(ch);
    }
    else if (m_inTranslation && m_inNote) {
        m_translation.notes.append(ch);
    }
    else if (m_inFems) {
        m_translation.female += ch.trimmed();
    }
    else if (m_inFemPlural) {
        m_translation.femalePlural += ch.trimmed();
    }
    else if (m_inTranslation) {
        /* There are entries where the "translation" is between different parts. For example:
         *
         *   <Entry frequency="17500000">neighbor<nouns><translations><translation gender="mf" local="us">veí<otherlocal>neighbour</otherlocal>
         *
         *                      </translation></translations></nouns>
         *
         * </Entry>
         * Since there are empty spaces after </otherlocal> and before </translation>,
         * the m_translation.translation = ch; was removing the previous text added in the translation.
         * Now it's adding it trimmed so "veí" stays, and if there was some other meaningul text it would
         * be added.
         */
        m_translation.translation += ch.trimmed();
    }
    else if (m_inExpressions) {
        m_expressions.expression += ch.trimmed();
    }
    else if (m_inMistakes) {
        m_mistakes = ch;
    }
}


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

void StructureList::setParaula(const QString& searchFor) {
    m_entryWanted = searchFor;
}
