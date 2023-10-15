/*
 * This file is part of qdacco
 * qdacco: offline Dacco Catalan <-> English dictionary
 *
 * Copyright (c) 2005, 2006, 2007, 2008, 2011
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

#include <QtWidgets/QPushButton>

#include "Configure.h"

Configure::Configure(QWidget *)  //parent
{
	ui.setupUi(this);
	connect(ui.okCancel,SIGNAL(accepted()),this,SLOT(okf()));
	connect(ui.okCancel,SIGNAL(rejected()),this,SLOT(cancelf()));
	
	connect(ui.busca_fitxer,SIGNAL(clicked()),this,SLOT(busca_fitxerf()));
	connect(ui.busca_browser,SIGNAL(clicked()),this,SLOT(busca_browserf()));
	connect(ui.busca_festival,SIGNAL(clicked()),this,SLOT(busca_festivalf()));
	
	connect(ui.ajuda,SIGNAL(clicked()),this,SLOT(ajuda_busca()));
	connect(ui.ajuda_browser,SIGNAL(clicked()),this,SLOT(ajuda_browser()));

	connect(ui.ajuda_festival,SIGNAL(clicked()),this,SLOT(ajuda_festival()));
	
	connect(ui.ajuda_singleinstance,SIGNAL(clicked()),this,SLOT(ajuda_singleinstance()));

	if (Auxiliar::isWindows() || Auxiliar::isMac()) {
		ui.busca_browser->hide();
		ui.ajuda_browser->hide();
		ui.browser->hide();
		ui.lbrowser->hide();

		ui.busca_festival->hide();
		ui.ajuda_festival->hide();
		ui.festival->hide();
		ui.lfestival->hide();
	}
}

void Configure::ajuda_busca() {
    QMessageBox::information(this,tr("Information"),tr("Path of the \"dictionaries\" directory in DACCO. It contains \"cateng\" and \"engcat\" directories"));
}


void Configure::ajuda_browser() {
    QMessageBox::information(this,tr("Information"),tr("Path or executable name of the browser to be used for opening links in entries"));
}

void Configure::ajuda_festival() {
    QMessageBox::information(this,tr("Information"),tr("Path or executable name to \"festival\" speech synthesis system. Install it via your package manager or from the Festival webpage: <A HREF=\"http://www.cstr.ed.ac.uk/projects/festival/\">http://www.cstr.ed.ac.uk/projects/festival/</A>"));
}

void Configure::ajuda_singleinstance() {
    QMessageBox::information(this,tr("Information"),tr("If enabled launching a new qdacco will restore the existing one and be displayed as a trayicon"));
}


void Configure::busca_fitxerf() {
	QString workingDirectory;

	QFileDialog *dlg = new QFileDialog(this);
	dlg->setFileMode(QFileDialog::Directory);
	dlg->setDirectory(ui.directori->text());

	if (dlg->exec() == QDialog::Accepted) {
		QStringList result;
		result=dlg->selectedFiles();
		ui.directori->setText(result.at(0));
	}
	delete dlg;
}


void Configure::busca_browserf() {
	QString workingDirectory;

	QFileDialog *dlg = new QFileDialog(this);
	dlg->setFileMode(QFileDialog::ExistingFile);

	if (dlg->exec() == QDialog::Accepted) {
		QStringList result;
		result=dlg->selectedFiles();
		ui.browser->setText(result.at(0));
	}
	delete dlg;
}


//TODO: refactor busca_browserf and busca_festivalf
void Configure::busca_festivalf() {
	QString workingDirectory;

	QFileDialog *dlg = new QFileDialog(this);
	dlg->setFileMode(QFileDialog::ExistingFile);

	if (dlg->exec() == QDialog::Accepted) {
		QStringList result;
		result=dlg->selectedFiles();
		ui.festival->setText(result.at(0));
	}
	delete dlg;
}

void Configure::carregar_config() {
    	QSettings qs("dacco","qdacco");
	QString dictionaries;

	//Get dictionaries file
	dictionaries=qs.value("/dacco/directori", "" ).toString();

	dictionaries=search_directory(dictionaries,Auxiliar::getDictionariesDirectory(),QDir::currentPath()+"/dictionaries/");

	ui.directori->setText(dictionaries);

        ui.traduccio_defecte->setCurrentIndex(qs.value("/dacco/diccionari_per_defecte",1).toInt()-1);

        ui.idioma_defecte->setCurrentIndex(qs.value("/dacco/idioma_per_defecte",1).toInt());

        m_language=ui.idioma_defecte->currentIndex();

	ui.browser->setText(qs.value("/dacco/browser","").toString());
	ui.festival->setText(qs.value("/dacco/festival","").toString());

	if (Auxiliar::isUnix() && ui.browser->text()=="") {
		QFile file("/etc/alternatives/x-www-browser");
		if (file.exists()) {
			ui.browser->setText("/etc/alternatives/x-www-browser");	
		}
	}

	if (Auxiliar::isUnix() && ui.festival->text()=="") {
		if (checkExecutable("festival")) {
			ui.festival->setText("festival");
		}
	}
	
	if (Auxiliar::isWindows()) {
		ui.browser->setText("cmd /c start ");
	}

	if (Auxiliar::isMac()) {
		ui.browser->setText("open ");
	}

	ui.ignorar_majuscules->setChecked(!qs.value("/dacco/ignore_case","1").toBool());
	ui.ignorar_accents->setChecked(qs.value("/dacco/ignore_accents","1").toBool());
	ui.autocompletar->setChecked(qs.value("/dacco/autocomplete","1").toBool());
	ui.singleinstance->setChecked(qs.value("/dacco/singleinstance","1").toBool());
}


void Configure::okf()
{
    QSettings settings("dacco","qdacco");

    settings.setValue("/dacco/directori", ui.directori->text());
    settings.setValue("/dacco/diccionari_per_defecte",ui.traduccio_defecte->currentIndex()+1);
    settings.setValue("/dacco/idioma_per_defecte",ui.idioma_defecte->currentIndex());
    settings.setValue("/dacco/version","0.8"); //TODO: change to program constant

    if (m_language!=ui.idioma_defecte->currentIndex()) {
                    QMessageBox::information(this, "qdacco",
    "To change the default language, you will have to restart qdacco");
    }

    settings.setValue("/dacco/browser",ui.browser->text());
    settings.setValue("/dacco/festival",ui.festival->text());
    settings.setValue("/dacco/ignore_case",!ui.ignorar_majuscules->isChecked());
    settings.setValue("/dacco/ignore_accents",ui.ignorar_accents->isChecked());
    settings.setValue("/dacco/autocomplete",ui.autocompletar->isChecked());
    
    settings.setValue("/dacco/singleinstance",ui.singleinstance->isChecked());

    this->close();
}

void Configure::cancelf()
{
        QSettings settings("dacco","qdacco");
        
	settings.setValue("/dacco/configurat",1);

        this->close();
}

QString Configure::search_directory(QString current,QString d1,QString d2)
{
	//2 directories is enough, else I will do in a list/array/...
        if (current=="") {
                QDir dir(d1);
		if (dir.exists()) {
                        current=Auxiliar::getDictionariesDirectory();
                }
        }

	if (current=="") {
		QDir dir2(d2);
		if (dir2.exists()) {
			current=d2;
		}
	}
	return current;
}

bool Configure::checkExecutable(QString executable) {
	QString path = getenv("PATH");
	QStringList paths = path.split(":");

	foreach(QString p,paths) {
		if (QFile::exists(p+"/"+executable)) {
			return true;
		}
	}
	return false;
}

void Configure::setFirst(bool first) {
	ui.okCancel->button(QDialogButtonBox::Cancel)->setEnabled(first==false);
}
