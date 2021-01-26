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

#include <QString>
#include <QObject>

class WordData {
public:
	WordData();

    void setDefinition(const QString &q);
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

	int getNum();
	void incNum();
	QString getEntry(int i);
	QString getTextEntry(int i);
	QString getHTMLEntry(int i);
    QString getHTMLEntry();

    static QString HTML2Text(const QString& t);

private:
    void printError(const QString &tag);

    QStringList definition;
    QStringList gender;
    QStringList tipus;
    QStringList catexamp;
    QStringList engexamp;
    QStringList example;
    QStringList engnote;
    QStringList catnote;
    QStringList picture;
    QStringList flickr;
    QStringList plural;
    QStringList femplural;
    QStringList synonyms;
};
/*
class WordDataConversor {
	static QString HTML2Text(QString t);

}

*/
#endif
