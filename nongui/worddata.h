/*
 * This file is part of qdacco
 * qdacco: offline Dacco Catalan <-> English dictionary
 *
 * Copyright (c) 2005, 2006, 2007, 2021
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

#ifndef DADESPARAULA_H
#define DADESPARAULA_H

#include <QVariant>

#include <QDebug>
#include <QString>
#include <QObject>

static QStringList wordTypesList = {"verbs", "nouns", "adjectives", "adverbs", "pronouns",
                                    "exclamations", "abbreviations", "prepositions",
                                    "phrasalverbs", "verbTense", "mistakes",
                                    "conjunctions", "determiners", "acronyms", "catacro", "engacro",
                                   };



static QString xmlToUserInterface(const QString& xmlWord) {
    static QHash<QString, QString> xmlInternalToUserInterface = { {"verbs", "v"},
                                                                  {"nouns", "n"},
                                                                  {"ajectives", "adj"},
                                                                  {"adverbs", "adv"},
                                                                  {"pronouns", "pron"},
                                                                  {"exclamations", "excl"},
                                                                  {"abbreviations", "abbrev"},
                                                                  {"prepositions", "prep"},
                                                                  {"phrasalverbs", "phrasal verb"},
                                                                  {"verbTense", "verb tense"},
                                                                  {"mistakes", "mistake"},
                                                                  {"conjunctions", "conj"},
                                                                  {"determiners", "det"},
                                                                  {"acronyms", "acronym"},
                                                                  {"catacro", "catalan acronym"},
                                                                  {"engacro", "english acronym"},
                                                                };

    return xmlInternalToUserInterface.value(xmlWord, xmlWord);
}

struct Translation {
    QString translation;
    QString female;
    QString femalePlural;

    QVariant collocation;   // bool
    QVariant transitive;    // bool

    QStringList examples;
    QStringList notes;
    QString plural;

    QString catagory;
    QString gender;

    QStringList synonyms;
    QString picture;
    QString flickr;

    QString getHtml(const QString& typeOfWord) const {
        QString html;

        if (!typeOfWord.isNull())
        {
            html += QString("<i>%1</i>").arg(xmlToUserInterface(typeOfWord));
        }

        if (!gender.isNull()) {
            if (!html.isNull()) {
                html += " ";
            }

            html += QString("<i>(%1)</i>").arg(gender);
        }

        if (!html.isNull())
        {
            html += "<br>";
        }

        html += translation + "<br>";

        if (!plural.isEmpty()) {
            html += QString("<u>Plural:</u> %1<br>").arg(plural);
        }

        if (!female.isEmpty()) {
            html += QString("<u>Female:</u> %1<br>").arg(female);
        }

        if (!femalePlural.isEmpty()) {
            html += QString("<u>Female plural:</u> %1</br>").arg(femalePlural);
        }

        for (const QString& example: examples) {
            html += "<u>Example:</u> " + example + "<br>";
        }

        for (const QString& note: notes)  {
            html += "<u>Note:</u> " + note + "<br>";
        }

        if (!flickr.isEmpty()) {
            html += QString("<u>Picture:</u> <a href=\"%1\">%1</a><br>").arg(flickr);
        }

        if (flickr.isEmpty() && !picture.isEmpty()) {
            html += QString("<u>Picture:</u> <a href=\"%1\">%1</a><br>").arg(picture);
        }

        return html;
    }
};

struct Translations : public QList<Translation> {
    QString getHtml(const QString& typeOfWord = QString()) const {
        QString html;

        QString typeOfWordHtml;

        bool first = true;
        for(const Translation& translation : *this) {
            if (!first) {
                html += "<br>";
            }
            html += typeOfWordHtml;
            html += translation.getHtml(typeOfWord);
            first = false;
        }

        return html;
    }
};

struct WordType
{
    QString wordType;
    Translations translations;
    QString ipa;

    QString getHtml(const QString& wordType) const {
        if (translations.isEmpty()) {
            return QString();
        }
//        QString html = QString("<i>%1</i><br>").arg(xmlToUserInterface(wordType));
        QString html = translations.getHtml(wordType);
        return html;
    }
};

struct Expressions
{
    QString expression;
    Translations translations;

    QString getHtml() const {
        QString html;

        html += "<i>expression</i><br>";
        html += "<b>" + expression + "</b>" + "<br>";
        html += translations.getHtml() + "<br>";

        return html;
    }
};

struct Entry
{
    QString entry;

    QHash<QString, WordType> wordTypes;

    QList<Expressions> expressions;

    QString catacro;
    QString engacro;
    QStringList mistakes;

    QString getHtml() const {
        QString html;

        for (const QString& wordType : wordTypesList) {
            if (wordTypes.contains(wordType)) {
                html += wordTypes[wordType].getHtml(wordType);
                html += "<br>";
            }
        }

        for (const Expressions& _expressions: expressions) {
            html += _expressions.getHtml();
        }

        return html;
    }
};


class WordData {
public:
    WordData();

    void addTranslation(const Translation& translation, const QString& type);
    void addExpressions(const Expressions& expressions);

    void setType(const QString& type, const QString& ipa);

    bool found();

    QString getHTMLEntry();

private:
    bool m_found;
    Entry m_entry;

    QString m_currentType;
    QString m_currentIpa;
};
#endif
