/*
 * This file is part of qdacco
 * qdacco: offline Dacco Catalan <-> English dictionary
 *
 * Copyright (c) 2005, 2006, 2007, 2013, 2015, 2020, 2021, 2023
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

#include <QtCore/QQueue>
#include <QtCore/QString>
#include <QXmlStreamReader>
#include <QFile>
#include "WordData.h"

class QString;

class StructureList
{
public:
    StructureList();


//    bool startDocument();
//    bool startElement( const QString&, const QString&, const QString& ,
//                       const QXmlAttributes& attributes);
//    bool endElement( const QString&, const QString&, const QString& );
//    bool characters ( const QString & ch );

    void parseFile(QFile& xmlFile);

    void setIgnoreCase(bool capital);
    void setIgnoreAccents(bool capital);

    void setParaula(const QString &) {}
    WordData getWordData();


    void setWord(const QString& w);

    bool myStartsWith(const QString &ch, QString &word);

    QString normalize(const QString& word);

    int setAddFunction(void function(QString a));

    void setEntryWanted(const QString& entryWanted);

private:
    void startElement(QXmlStreamReader& reader);
    void endElement(QXmlStreamReader& reader);
    void characters(QXmlStreamReader& reader);

    void processEntry(QXmlStreamReader& reader);

    bool entrada;

    int m_IgnoreCase;
    int m_IgnoreAccents;

    QString m_word;
    QString m_word_normalized;

    WordData m_wordData;

    QString m_entryWanted;

    void (*m_addEntry)(QString q);


    ///////////
    bool m_isEntry;
    bool m_found;
    bool m_inTranslation;
    bool m_inExpressions;
    bool m_inExample;
    bool m_inPlural;
    bool m_inNote;
    bool m_inFems;
    bool m_inFemPlural;
    bool m_inCatAcro;
    bool m_inEngAcro;
    bool m_inMistakes;
    bool m_inSynonyms;

    Translation m_translation;
    Expressions m_expressions;

    bool m_inSearchedWord;

    QString m_type;
    QString m_mistakes;
};

#endif
