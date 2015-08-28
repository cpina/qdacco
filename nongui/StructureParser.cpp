/*
 * This file is part of qdacco
 * qdacco: offline Dacco Catalan <-> English dictionary
 *
 * Copyright (c) 2005, 2006, 2007, 2015
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

#include "StructureParser.h"

bool StructureParser::startDocument()
{
	after_word = 0;
	return true;
}

bool StructureParser::startElement( const QString&, const QString&,
					const QString& qName,
					const QXmlAttributes& attributes)
{
	catexamp=false; engexamp=false;
	entrada=false; translation=false;
	example=false; 
	engnote=false; catnote=false;
	picture=false;
	plural=false; femplural=false;
	synonyms=false;

	catexamp=(qName=="catexamp");
	engexamp=(qName=="engexamp");
	example=(qName=="example");
	engnote=(qName=="engnote");
	catnote=(qName=="catnote");
	plural=(qName=="plural");
	femplural=(qName=="femplural");
	synonyms=(qName=="synonyms");

	qgender_=attributes.value("gender");	
	qpicture_=attributes.value("picture");
	qflickr_=attributes.value("flickr");

	entrada = (qName=="Entry");

	if (qName == "translation") {
		translation = true;
	}

	if (qName == "adjectives") {qtipus_="adj";}
	if (qName == "adverbs") {qtipus_="adv";}
	if (qName == "exclamations") {qtipus_="excl";}
	if (qName == "nouns") {qtipus_="n";}
	if (qName == "prepositions") {qtipus_="prep";}
	if (qName == "pronouns") {qtipus_="pron";}
	if (qName == "verbs") {qtipus_="v";}

	return true;
}

bool StructureParser::endElement( const QString&, const QString&, const QString& qName)
{
	if (trobat && qName=="translation") {
		wd.incNum();
		Auxiliar::debug("Increments incNum");
	}	
	if (trobat && qName=="Entry") {	//ja sortim de la paraula
		trobat=false;
	}
	return true;
}

bool StructureParser::characters ( const QString & ch )
{
	bool same;
	
	same=compare(ch,paraula);
	
	if (entrada && same) {
		trobat=true;
	}
	if (entrada && !same) {
		trobat=false;
	}
	if (trobat && catexamp) {
		wd.putCatexamp(ch);
	}

	if (trobat && engexamp) {
		wd.putEngexamp(ch);
	}

	if (trobat && example) {
		wd.putExample(ch);
	}

	
	if (trobat && translation) {
		wd.putDefinition(ch);

		wd.putGender(qgender_);
		wd.putTipus(qtipus_);

		if (!qpicture_.isEmpty()) {
			wd.putPicture(qpicture_);
		}
		if (!qflickr_.isEmpty()) {
			wd.putFlickr(qflickr_);
		}
	}

	if (trobat && engnote) {
		wd.putEngnote(ch);
	}

	if (trobat && catnote) {
		wd.putCatnote(ch);
	}

	if (trobat && plural) {
		wd.putPlural(ch);
	}

	if (trobat && femplural) {
		wd.putFemplural(ch);
	}

	if (trobat && synonyms) {
		wd.putSynonyms(ch);
	}
	return true;
}

void StructureParser::setParaula(const QString &s) 
{
	paraula=s;
}

WordData StructureParser::getWordData()
{
	return wd;
}

bool StructureParser::compare(QString ch, QString word)
{
	return ch.compare(word)==0;
}
