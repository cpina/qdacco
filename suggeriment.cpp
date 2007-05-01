/*
 * This file is part of qdacco
 * qdacco: offline Dacco Catalan <-> English dictionary
 *
 * Copyright (c) 2005, 2006
 *      Carles Pina i Estany <carles@pina.cat>
 *
 * qdacco is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * any later version.
 *
 * qphotosort is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * long with Foobar; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "suggeriment.h"

Suggeriment::Suggeriment(QWidget *parent) 
{
	ui.setupUi(this);

	connect(ui.ok,SIGNAL(clicked()),this,SLOT(oks()));
	connect(ui.cancel,SIGNAL(clicked()),this,SLOT(cancels()));
}

void Suggeriment::oks() {
        userWord=ui.word->text();
        userTranslations=ui.translations->toPlainText();
        userExamples=ui.examples->toPlainText();
        userNotes=ui.usagenotes->toPlainText();

        okay = 1;
        this->close();
}


void Suggeriment::cancels() {
        okay = 0;
        this->close();
}


void Suggeriment::setWord(QString word_) {
        ui.word->setText(word_);
}

void Suggeriment::getUserWord( QString &w )
{
        w=userWord;
}


void Suggeriment::getUserTranslations( QString &w )
{
        w=userTranslations;
}


void Suggeriment::getUserExamples( QString &w )
{
        w=userExamples;
}


void Suggeriment::getUserNotes( QString &w )
{
        w=userNotes;
}


void Suggeriment::getOkay( int &o )
{
        o=okay;
}
