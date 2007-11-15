/*
 * qdacco: offline Dacco Catalan <-> English dictionary
 * Copyright (C) 2005, 2006, 2007 Carles Pina i estany <carles@pina.cat>
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


#include <qapplication.h>
#include <qdialog.h>
#include <qmessagebox.h>
#include <QLocale>
#include "main.h"
#include "auxiliar.h"

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	//MyDialog *window=new MyDialog;

	if (app.argc()>1 && strcmp(app.argv()[1],"-d")==0) {
                printf("Debug enabled\n");
                Auxiliar::setDebug(1);
        }
	else {
		Auxiliar::setDebug(0);
	}

        if (app.argc()>1 && strcmp(app.argv()[1],"-d")!=0) {
                printf("qdacco use:\n");
                printf("qdacco -d: to enable debug mode\n");
                printf("Just qdacco to just use qdacco\n");
                exit(1);
        }

	printf("qdacco %s Copyright (C) %s Carles Pina i Estany\n",qPrintable(Auxiliar::getVersion()),qPrintable(Auxiliar::getCopyrightDate()));
	printf("This program comes with ABSOLUTELY NO WARRANTY;\n");
	printf("This is free software, and you are welcome to redistribute it\n");
	printf("under certain conditions\n\n");
        printf("Program: GPL v3. Data: LGPL\n");

	QSettings qs("dacco","qdacco");
	int idioma = qs.value("/dacco/idioma_per_defecte",1).toInt();
	QTranslator translator;

	if (idioma==0) {
		if (translator.load(":/qdacco_ca.qm")) {
			app.installTranslator(&translator);
		}
	}
		
	if (idioma==1) {
	
	}

	if (idioma==2) {
		QLocale a;
		QString locale=a.name();

		if (locale.startsWith("ca")) {
			qs.setValue("/dacco/idioma_per_defecte",1);
		
			if (translator.load(":/qdacco_ca.qm")) {
				app.installTranslator(&translator);
			}

		}
	}

	// Debug info
	if (Auxiliar::isWindows()) {
		Auxiliar::debug("isWindows: true");	
	}
	else {
		Auxiliar::debug("isWindows: false");
	}


	if (Auxiliar::isMac()) {
		Auxiliar::debug("isMac: true");	
	}
	else {
		Auxiliar::debug("isMac: false");
	}
	// End of debug info

	qs.sync();
	
	Main *window = new Main;

	window->show();

	return app.exec();
} 
