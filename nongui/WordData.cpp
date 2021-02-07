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

#include <QDebug>

#include "WordData.h"

WordData::WordData() {
    m_found = false;
}

void WordData::setType(const QString& type, const QString& ipa) {
    m_currentType = type;
    m_currentIpa = ipa;
    m_found = true;
}

void WordData::setCatalanAcronym(const QString& acronym)
{
    m_entry.catalanAcronym = acronym;
}

void WordData::setEnglishAcronym(const QString& acronym)
{
    m_entry.englishAcronym = acronym;
}

void WordData::setMistakes(const QString& mistakes) {
    m_entry.mistakes = mistakes;
}

void WordData::addTranslation(const Translation& translation, const QString &type) {
    m_found = true;

    m_entry.wordTypes[type].translations.append(translation);
}

void WordData::addExpressions(const Expressions& expressions) {
    m_found = true;

    m_entry.expressions.append(expressions);
}

bool WordData::found() {
    return m_found;
}

QString WordData::getHTMLEntry() {
    return m_entry.getHtml();
}
