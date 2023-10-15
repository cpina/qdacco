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

//TODO: Disable order when starting to insert, enable back again after it. New elemnts are in order, coming from dictionary!
StructureList::StructureList()
{
    m_addEntry = nullptr;
    m_list="";
}


bool StructureList::startDocument()
{
    //WordDataQueue queuelist(10);
    //wordqueue.setAutoDelete(TRUE);   (Ull! Tret per Qt4!)
    //after_word = 0;
    m_word_normalized=normalize(m_word);
    return true;
}

bool StructureList::startElement( const QString&, const QString&,
                                  const QString& qName,
                                  const QXmlAttributes& ) //attributes
{
    entrada = (qName=="Entry");
    return true;
}

bool StructureList::endElement( const QString&, const QString&, const QString& ) //qName
{

    return true;
}

bool StructureList::characters ( const QString & ch )
{
    if (entrada && myStartsWith(ch,m_word_normalized)) {
        if(m_addEntry == nullptr)
        {
            if (m_list.length()==0) { //We don't want extra \n at first
                //time

                m_list=ch;
            }
            else {
                m_list=m_list+"\n"+ch;
            }
        }//#endif
        else {
            m_addEntry(ch);
        }
    }

    return true;
}

void StructureList::setWord(QString w)
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

QString &StructureList::normalize(QString &word) {
    if (m_IgnoreCase) {
        word=word.toLower();
    }
    if (m_IgnoreAccents) {
        word.replace(u'à','a');
        word.replace(u'è','e');
        word.replace(u'ì','i');
        word.replace(u'ò','o');
        word.replace(u'ù','u');

        word.replace(u'á','a');
        word.replace(u'é','e');
        word.replace(u'í','i');
        word.replace(u'ó','o');
        word.replace(u'ú','u');
    }

    //printf("Paraula noramlitzada: %s\n",qPrintable(word));
    return word;
}

int StructureList::setAddFunction(void function(QString a)) {
    m_addEntry = function;

    return 0;
}

QString StructureList::getListWords() {
    return m_list;
}
