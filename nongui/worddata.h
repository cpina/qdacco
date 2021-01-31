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

static QStringList wordTypesList = {"verbs", "nouns", "adjectives", "adverbs", "pronouns"};

struct Translation {
    QString translation;

    QVariant collocation;   // bool
    QVariant transitive;    // bool

    QStringList examples;
    QStringList notes;

    QString catagory;
    QString gender;
    QStringList engnotes;
    QStringList catnotes;
    QStringList synonyms;
    QString picture;
    QString flickr;

    QString getHtml() const {
        QString html;

        if (!gender.isNull()) {
            html += QString(" <i>(%1)</i><br>").arg(gender);
        }

        html += translation + "<br>";

        for (const QString& example: examples) {
            html += "<u>Exemple:</u> " + example + "<br>";
        }

        return html;
    }
};

struct Translations : public QList<Translation> {
    QString getHtml(const QString& typeOfWord = QString()) const {
        QString html;

        QString typeOfWordHtml;

        if (!typeOfWord.isNull()) {
            typeOfWordHtml = QString("<i>%1</i>").arg(typeOfWord);
        }

        bool first = true;
        for(const Translation& translation : *this) {
            if (!first) {
                html += "<br>";
            }
            html += typeOfWordHtml;
            html += translation.getHtml();
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
        QString html = QString("<i>%1</i><br>").arg(wordType);
        html += translations.getHtml();
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

    void addTranslation(const Translation &translation, const QString& type);
    void addExpressions(const Expressions& expressions);

    void setGender(const QString& q);
    void setTipus(const QString &q);
    void setCatExample(const QString &q);
    void setEnglishExample(const QString& q);
    void setExample(const QString& q);
    void setEnglishNote(const QString& q);
    void setCatalanNote(const QString& q);
    void setPicture(const QString& q);
    void setFlickr(const QString& q);
    void setPlural(const QString& q);
    void setFemeninePlural(const QString& q);
    void setSynonyms(const QString& q);

    void setType(const QString& type, const QString& ipa);

    bool found();

	QString getDefinition(int i);
	QString getGender(int i);
	QString getTipus(int i);
	QString getCatexamp(int i);
	QString getEngexamp(int i);
	QString getExample(int i);
	QString getEngnote(int i);
	QString getCatnote(int i);
	QString getPicture(int i);
	QString getFlickr(int i);
	QString getPlural(int i);
	QString getFemplural(int i);
	QString getSynonyms(int i);

    QString getTextEntry();
    QString getHTMLEntry();

    static QString HTML2Text(const QString& t);

private:
    bool m_found;
    Entry m_entry;

    QString m_currentType;
    QString m_currentIpa;
};
#endif
