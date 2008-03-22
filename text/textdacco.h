/*
 * qdacco: offline Dacco Catalan <-> English dictionary
 * Copyright (C) 2005, 2006, 2007, 2008 Carles Pina i estany <carles@pina.cat>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; version 2 or any
 * later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
 * USA.
 */

#include <QFile>
#include <QXmlInputSource>
#include <QSettings>
#include <QDir>

#include <qdacco/auxiliar.h>
#include <qdacco/StructureParser.h>
#include <qdacco/StructureList.h>

#include <getopt.h>
#include <cstdlib>

QString Search(QString word,QString dictionary,QString basepath,int type);
QString GetDictionaryPath();

void ExtendedBiSearch(QString search,QString basepath);
void ExtendedSearch(QString search,QString dictionary,QString basepath);
void ShowUsage();
void ShowCopyright();

void underline(QString search);

