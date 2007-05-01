/*
 * This file is part of qdacco
 * qdacco: offline Dacco Catalan <-> English dictionary
 *
 * Copyright (c) 2005, 2006, 2007
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

#ifndef AUXILIAR_H
#define AUXILIAR_H

#include <qstring.h>


class Auxiliar
{
	private:
		static QString version;
		static int debugLevel;
		static QString host;
		static QString url;
		static QString dictionaries_directory;
		static QString copyright_date;
	
	public:
		static QString getVersion();
		static QString getNetVersion();
		static QString getHost();
		static QString getURL();
		static QString getDictionariesDirectory();
		static QString getCopyrightDate();

		static int catalan();
		static int english();

		
		static void setDebug(int i);
		static int getDebug();
		static void debug(QString s);

		static int eng2cat();
		static int cat2eng();

		static int KeyDown();
		static int KeyUp();
		static int KeyNextPage();
		static int KeyPrevPage();

		static bool isWindows();
		static bool isMac();
		static bool isUnix();
};
#endif
