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
                                    "phrasalverbs", "verbTense",
                                    "conjunctions", "determiners", "acronyms"
                                    // "mistakes", "catacro", "engacro", Handled differently
                                   };



static QString xmlToUserInterface(const QString& xmlWord) {
    static QHash<QString, QString> xmlInternalToUserInterface = { {"verbs", QObject::tr("v")},
                                                                  {"nouns", QObject::tr("n")},
                                                                  {"adjectives", QObject::tr("adj")},
                                                                  {"adverbs", QObject::tr("adv")},
                                                                  {"pronouns", QObject::tr("pron")},
                                                                  {"exclamations", QObject::tr("excl")},
                                                                  {"abbreviations", QObject::tr("abbrev")},
                                                                  {"prepositions", QObject::tr("prep")},
                                                                  {"phrasalverbs", QObject::tr("phrasal verb")},
                                                                  {"verbTense", QObject::tr("verb tense")},
                                                                  {"mistakes", QObject::tr("mistake")},
                                                                  {"conjunctions", QObject::tr("conj")},
                                                                  {"determiners", QObject::tr("det")},
                                                                  {"acronyms", QObject::tr("acronym")},
                                                                  {"catacro", QObject::tr("catalan acronym")},
                                                                  {"engacro", QObject::tr("english acronym")},
                                                                };

    return xmlInternalToUserInterface.value(xmlWord, xmlWord);
}

static QString formatInformation(const QString& typeOfInformation, const QString& information) {
    if (information.isEmpty()) {
        return QString();
    }
    return QString("<u>%1:</u> %2<br>").arg(typeOfInformation).arg(information);
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

    QString catalanAcronym;
    QString englishAcronym;

    QString getHtml(const QString& typeOfWord, const QString& mistakes = QString()) const {
        QString html;

        if (!typeOfWord.isEmpty())
        {
            html += QString("<i>%1</i>").arg(xmlToUserInterface(typeOfWord));
        }

        if (!gender.isEmpty()) {
            if (!html.isNull()) {
                html += " ";
            }

            html += QString("<i>(%1)</i>").arg(gender);
        }

        if (!html.isEmpty())
        {
            html += "<br>";
        }

        html += translation + "<br>";

        html += formatInformation(QObject::tr("Common mistakes"), mistakes);

        html += formatInformation(QObject::tr("Plural"), plural);

        html += formatInformation(QObject::tr("Female"), female);

        html += formatInformation(QObject::tr("Female plural"), femalePlural);

        html += formatInformation(QObject::tr("Catalan acronym"), catalanAcronym);

        html += formatInformation(QObject::tr("English acronym"), englishAcronym);


        for (const QString& example: examples) {
            html += formatInformation(QObject::tr("Example"), example);
        }

        for (const QString& note: notes)  {
            html += formatInformation(QObject::tr("Note"), note);
        }

        if (!picture.isEmpty()) {
            html += formatInformation(QObject::tr("Picture"), QString("<a href=\"%1\">%1</a>").arg(picture));
        }

        return html;
    }
};

struct Translations : public QList<Translation> {
    QString getHtml(const QString& typeOfWord, const QString& mistakes) const {
        QString html;

        QString typeOfWordHtml;

        bool first = true;
        for(const Translation& translation : *this) {
            if (!first) {
                html += "<br>";
            }
            html += typeOfWordHtml;
            html += translation.getHtml(typeOfWord, mistakes);
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

    QString getHtml(const QString& wordType, const QString& mistakes) const {
        if (translations.isEmpty()) {
            return QString();
        }
        return translations.getHtml(wordType, mistakes);
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
        html += translations.getHtml(QString(), QString()) + "<br>";

        return html;
    }
};

struct Entry
{
    QString entry;

    QHash<QString, WordType> wordTypes;

    QList<Expressions> expressions;

    QString catalanAcronym;
    QString englishAcronym;
    QString mistakes;

    QString getHtml() const {
        QString html;

        html += formatInformation(QObject::tr("Catalan acronym"), catalanAcronym);

        html += formatInformation(QObject::tr("English acronym"), englishAcronym);

        if (!html.isEmpty()) {
            html += "<br>";
        }

        for (const QString& wordType : wordTypesList) {
            if (wordTypes.contains(wordType)) {
                html += wordTypes[wordType].getHtml(wordType, mistakes);
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
    void setCatalanAcronym(const QString& acronym);
    void setEnglishAcronym(const QString& acronym);
    void setMistakes(const QString& mistakes);

    bool found();

    QString getHTMLEntry();

private:
    bool m_found;
    Entry m_entry;

    QString m_currentType;
    QString m_currentIpa;
};
#endif
