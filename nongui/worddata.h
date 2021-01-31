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

#include <QString>
#include <QObject>

struct Translation {
    QString translation;

    QVariant collocation;   // bool
    QVariant transitive;    // bool

    QString catagory;
    QString gender;
    QStringList catexamps;
    QStringList engexamps;
    QStringList engnotes;
    QStringList catnotes;
    QStringList synonyms;
    QString picture;
    QString flickr;

    QString getHtml() const {
        return translation;
    }
};

struct Translations : public QList<Translation> {
    QString getHtml() const {
        QString html;

        for(const Translation& translation : *this) {
            html += translation.getHtml() + "<br>";
        }

        return html;
    }
};

struct Verbs
{
    QString conj;
    QList<Translation> translations;
    QString ipa;
};

struct Nouns
{
    QList<Translation> translations;
    QString ipa;

    QString returnHtml() {

    }
};

struct Adjectives
{
    QList<Translation> translations;
    QString ipa;
};

struct Determiners
{
    QList<Translation> translations;
    QString ipa;
};

struct Acronyms
{
    QList<Translation> translations;
    QString ipa;
};

struct Prepositions
{
    QList<Translation> translations;
    QString ipa;
};

struct Conjunctions
{
    QList<Translation> translations;
    QString ipa;
};

struct Pronouns
{
    QList<Translation> translations;
    QString ipa;
};

struct Exclamations
{
    QList<Translation> translations;
    QString ipa;
};

struct Expressions
{
    QString expression;
    QList<Translation> translations;
};

struct Adverbs
{
    Translations translations;
    QString ipa;

    QString getHtml() const {
        QString html = "<i>adv</i><br>";
        return html + translations.getHtml();
    }
};

struct Abbreviations
{
    QList<Translation> translations;
    QString ipa;
};

struct PhrasalVerbs
{
    QList<Translation> translations;
    QString ipa;
};

struct VerbeTense
{
    QList<Translation> translations;
    QString ipa;
};


struct Entry
{
    QString entry;

    Nouns nouns;
    Verbs verbs;
    Adjectives adjectives;
    Acronyms acronyms;
    Prepositions prepositions;
    Conjunctions conjunctions;
    Pronouns pronouns;
    Exclamations exclamations;
    Expressions expressions;
    Adverbs adverbs;
    Abbreviations abbreviations;
    PhrasalVerbs phrasalVerbs;
    VerbeTense verbeTense;

    QString catacro;
    QString engacro;
    QStringList mistakes;

    QString getHtml() const {
        return adverbs.getHtml();
    }
};


class WordData {
public:
	WordData();

    void addTranslation(const Translation &translation, const QString& type);
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
