/*
 * This file is part of qdacco
 * qdacco: offline Dacco Catalan <-> English dictionary
 *
 * Copyright (c) 2005, 2006, 2007, 2008, 2009, 2011, 2013, 2015, 2020
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

#include "main.h"

#include "AuxiliarGUI.h"
#include "About.h"
#include "Configure.h"
#include "TextBrowser.h"
#include "TrayIcon.h"

#include "nongui/StructureList.h"

#include <QtCore/QChar>

Main::Main(QWidget *)  //parent
{
	ui.setupUi(this);
	ui.paraula->setParent(this);
	ui.llistat->setParent(this);
    ui.definicio->setParent(this);

	resize(QSize(270,300));

	installEventFilter(this);

	m_cat_eng = new QToolButton;
	m_cat_eng->setText(tr("cat → eng"));
	m_cat_eng->setCheckable(1);
	ui.toolBar->addWidget(m_cat_eng);

	m_eng_cat = new QToolButton;
	m_eng_cat->setText(tr("eng → cat"));
	m_eng_cat->setCheckable(1);
	ui.toolBar->addWidget(m_eng_cat);

	ui.toolBar->addSeparator();

    QAction *copy = ui.toolBar->addAction(QIcon(":icons/editcopy.png"),tr("Copy"));
	QAction *paste = ui.toolBar->addAction(QIcon(":icons/editpaste.png"),tr("Paste"));
	connect(copy,SIGNAL(triggered()),this,SLOT(copy_definition()));
	connect(paste,SIGNAL(triggered()),this,SLOT(paste_word()));
	
        connect(ui.Buscar,SIGNAL(clicked()),this,SLOT(buscarClicked()));
        connect(ui.editConfigureAction,SIGNAL(triggered()),this,SLOT(obrir_configuracio_slot()));
        connect(ui.editSelectAction,SIGNAL(triggered()),this,SLOT(select_word()));

	connect(m_cat_eng,SIGNAL(clicked()),this,SLOT(cat_engf()));
	connect(m_eng_cat,SIGNAL(clicked()),this,SLOT(eng_catf()));
	
	connect(ui.fileChangeDictionaryAction,SIGNAL(triggered()),this,SLOT(switchDictionary()));
	connect(ui.paraula,SIGNAL(returnPressed()),this,SLOT(buscarEnter()));
	connect(ui.helpAboutAction,SIGNAL(triggered()),this,SLOT(obrir_about()));

	connect(ui.llistat,SIGNAL(itemDoubleClicked(QListWidgetItem *)),this,SLOT(searchListWord(QListWidgetItem*)));
	connect(ui.paraula,SIGNAL(textChanged(const QString &)),this,SLOT(paraulaChanged(const QString &)));

	connect(&m_festival,SIGNAL(errorOccurred(QProcess::ProcessError)),this,SLOT(FestivalError(QProcess::ProcessError)));
	connect(&m_festival,SIGNAL(finished(int,QProcess::ExitStatus)),this,SLOT(FestivalFinished(int,QProcess::ExitStatus)));
    connect(ui.definicio,SIGNAL(browserFailed()),this,SLOT(showBrowserError()));
	
	carrega_config(1);

	ui.clipboard->hide();
}

void Main::FestivalFinished(int exitStatus,QProcess::ExitStatus) {
	if (exitStatus!=0)
	{
		QString error_message(tr("Festival executed and returned error code: ")+QString::number(exitStatus) + ". " + tr("Please consult the FAQ for help with this issue"));

		if (m_festival_reading==Auxiliar::catalan())
		{
			error_message += "<P>"+tr("You probably haven't installed the Catalan dictionary for Festival");
		}
		showError(error_message);
	}
}

void Main::FestivalError(QProcess::ProcessError)
{
	showError(tr("Error executing Festival. Please check the FAQ for help with this issue"));
}

void Main::FestivalExecuteEntry() {
	QString arguments="";

	ui.actiu->hide();
	QString selectedText=ui.paraula->selectedText();

	if (m_idioma_actiu == Auxiliar::eng2cat()) { //TODO: Auxiliar is setted up incorrectly?
		arguments="--language catalan";
		Auxiliar::debug("Festival in catalan");
		m_festival_reading=Auxiliar::catalan();
	}
	else {
		Auxiliar::debug("Festival in English");
		m_festival_reading=Auxiliar::english();
	}
	FestivalExecute(selectedText,arguments);
}

void Main::FestivalExecuteDefinition() {
	ui.actiu->hide();

	QString selectedText=ui.definicio->getText();

	int language = ui.definicio->getLanguage();
	
	QString arguments="";
	if ((language == Auxiliar::catalan()) ||
   	    (language == 3 && m_CurrentUILanguage == 0) ||
	    (language == 4 && m_idioma_actiu==Auxiliar::cat2eng()) ||
	    (language == 5 && m_idioma_actiu==Auxiliar::eng2cat()))
	{
		arguments="--language catalan";
		Auxiliar::debug("Festival in catalan");
		m_festival_reading=Auxiliar::catalan();
	}
	else {
		Auxiliar::debug("Festival in English");
		m_festival_reading=Auxiliar::english();
	}
	FestivalExecute(selectedText,arguments);
}


void Main::FestivalExecute(QString text,QString arguments) {
	QString execute;

	execute=m_FestivalPath+" --tts "+arguments;
	Auxiliar::debug("Execute: "+execute);

	m_festival.start(execute);
	m_festival.write(qPrintable(text));

	Auxiliar::debug("Write to Festival: "+text);

	m_festival.closeWriteChannel();
}

void Main::moveWordList(QEvent *event)
{
	int type = event->type();
	int move=0;
	int newposition=0;

	if (type == QEvent::User+Auxiliar::KeyDown())
	{
		if (ui.llistat->currentRow()==ui.llistat->count()-1 || ui.llistat->currentRow()==-1) {
			newposition=0;
		}
		else {
			newposition=ui.llistat->currentRow()+1;
		}
		move=1;
	}
	else if (type == QEvent::User+Auxiliar::KeyUp())
	{
		if (ui.llistat->currentRow() == 0) {
			newposition=ui.llistat->count()-1;
		}
		else {
			newposition=ui.llistat->currentRow()-1;
		}
		move=1;
	}
	else if (type == QEvent::User+Auxiliar::KeyNextPage()) {
		newposition=ui.llistat->currentRow()+10;
		if (newposition>ui.llistat->count()-1) {
			newposition=ui.llistat->count()-1;
		}
		move=1;
	}
	else if (type == QEvent::User+Auxiliar::KeyPrevPage()) {
		newposition=ui.llistat->currentRow()-10;
		if (newposition<0) {
			newposition=0;
		}
		move=1;
	}

	if (move) {
		ui.llistat->setCurrentRow(newposition);
	}
}

void Main::moveDefinicio(QEvent *event)
{
	int type = event->type();
	int step,pagestep;

	QScrollBar *bar;
	bar=ui.definicio->verticalScrollBar();
	
	step=bar->singleStep();
	pagestep=bar->pageStep();

	if (type == QEvent::User+Auxiliar::KeyDown()) {
		bar->setSliderPosition(bar->sliderPosition()+step);
	}
	else if (type == QEvent::User+Auxiliar::KeyUp()) {
		bar->setSliderPosition(bar->sliderPosition()-step);
	}
	else if (type == QEvent::User+Auxiliar::KeyNextPage()) {
		bar->setSliderPosition(bar->sliderPosition()+pagestep);
	}
	else if (type == QEvent::User+Auxiliar::KeyPrevPage()) {
		bar->setSliderPosition(bar->sliderPosition()-pagestep);
	}
}

bool Main::eventFilter(QObject *, QEvent *event) //obj
{
	int type = event->type();

	// Optimitzation: we don't want to do any other operation
	// if Event is not to move a key
	if (type!=QEvent::User+Auxiliar::KeyDown() &&
		type!=QEvent::User+Auxiliar::KeyUp() &&
		type!=QEvent::User+Auxiliar::KeyNextPage() &&
		type!=QEvent::User+Auxiliar::KeyPrevPage()) {
            return false;
	}

	if (ui.llistat->isVisible()) {
		moveWordList(event);
	} else if (ui.definicio->isVisible()) {
		moveDefinicio(event);
	}

	return true;
}

void Main::buscarClicked()
{
	buscar();
}

void Main::buscarEnter()
{
	if (ui.llistat->isVisible()) {
		QListWidgetItem *item;
		item = ui.llistat->currentItem();
        if (item!=nullptr) {
			ui.paraula->setText(item->text());
		}
	}
	buscar();
}

QString Main::getParaula()
{
	return ui.paraula->text();
}

void Main::setParaula(QString paraula)
{
	ui.paraula->setText(paraula);
}

void Main::buscar()
{
	treballaBuscar();
	ui.paraula->selectAll();
	ui.paraula->setFocus(Qt::OtherFocusReason);
}

void Main::paraulaChanged(const QString &paraula)
{
	if (m_Autocomplete==false) {
		ui.actiu->hide();
		return;
	}

	bool enabled=false;

	//Update the list
	ui.actiu->hide();
	ui.definicio->hide();
	ui.llistat->clear();
	UpdateList();

	if (ui.llistat->count()==1) {
		ui.llistat->setCurrentRow(0);
	}
	
	if (ui.llistat->count()>1 && ui.llistat->item(1)->text()==paraula) {
		ui.llistat->setCurrentRow(1);
	}
}

void lib2class(QString q) { //bridge
	((Main*)AuxiliarGUI::m)->AddEntryToGUI(q);
}

void Main::AddEntryToGUI(QString q) {
	ui.llistat->insertItem(999999999,q);
}

void Main::UpdateList() {
	StructureList handler;

	handler.setIgnoreCase(m_IgnoreCase);
	handler.setIgnoreAccents(m_IgnoreAccents);

	AuxiliarGUI::m=this;
    void (*ptrFunction)(QString)=nullptr;
	ptrFunction = lib2class;

	handler.setAddFunction(ptrFunction);
       
       	QString search = ui.paraula->text();

	handler.setWord(search);

        char letter;

        QString idioma;
	ui.llistat->show();

        //prepare the path
	if (m_idioma_actiu == Auxiliar::eng2cat() ) {
                idioma="cateng";
        }
        else {
                idioma="engcat";
        }

        if (!isValidWord(search)) {
		ui.definicio->setPlainText(""); //not valid input*
		return;
        }

    letter=removeAccents(search);
	QFile xmlFile(m_directori_usuari+"/"+idioma+"/"+letter+".dic");

	if (!xmlFile.exists()) {
		showError(tr("Cannot open dictionary file. Check configuration directory and permissions"));
	}
	else {
		Auxiliar::debug("File2: "+m_directori_usuari+"/"+idioma+"/"+letter+".dic");

        handler.parseFile(xmlFile);

        WordData d = handler.getWordData();

        ui.definicio->setPlainText("");
        m_searched=search;
        selectItem();
	}
}

int Main::getIdiomaActiu() {
	return m_idioma_actiu;
}

void Main::setIdiomaActiu(int actiu) {
	m_idioma_actiu = actiu;
	posa_idioma();
}

void Main::treballaBuscar() {
        StructureList handler;

       	QString buscar = ui.paraula->text();
        QString buscar_orig = ui.paraula->text();
        char lletra;

        QString idioma;

        //per preparar el path
        if (m_idioma_actiu== Auxiliar::eng2cat() ) {
                idioma="cateng";
        }
        else {
                idioma="engcat";
        }

        if (!isValidWord(buscar)) {
		showError(tr("You have to write a word. The word has to start with a letter."));
                ui.definicio->setPlainText(""); //not valid input
        }
        else {  //TODO: clean this crazy if-else!

        lletra=removeAccents(buscar);
		QFile xmlFile(m_directori_usuari+"/"+idioma+"/"+lletra+".dic");


		if (!xmlFile.exists()) {
			showError(tr("Cannot open dictionary file. Check configuration directory and permissions"));
		}
		else {
			Auxiliar::debug("File: "+m_directori_usuari+"/"+idioma+"/"+lletra+".dic");

//			QXmlInputSource source( &xmlFile );
//			QXmlSimpleReader reader;
//			reader.setFeature("http://trolltech.com/xml/features/report-whitespace-only-CharData",false);   //if we don't use it, we get more entries because spaces...
//			reader.setContentHandler( &handler );

//			handler.setEntryWanted(buscar_orig);

//			reader.parse(source);
            handler.setEntryWanted(buscar_orig);
            handler.parseFile(xmlFile);
            WordData d = handler.getWordData();

//            WordData d;
			ui.definicio->setPlainText("");

            if (d.found()) {
				ui.definicio->show();
				ui.llistat->hide();

                QString definicio = d.getHTMLEntry();
				ui.definicio->setHtml(definicio);
			}
            else {
				//No word found or buscar == 1: we show the list
				
				ui.definicio->setPlainText("");
				ui.definicio->hide();
				ui.llistat->show();
				//loadList(&handler);
				
				m_searched=buscar_orig;
				selectItem();
                if (!d.found()) {
					showError(tr("Exact match not found"));
				}
			}
		}
        }
}

void Main::posarApunt (int all) {
        ui.llistat->clear();
        ui.llistat->hide();
	ui.definicio->show();

        if (all) {
                ui.paraula->setText("");
        }
        ui.definicio->setPlainText("");

        ui.actiu->hide();
        ui.actiu->setText("");
        ui.paraula->selectAll();
        ui.paraula->setFocus();
}

int Main::isValidWord(QString &q) {
        //We transform the word to not-capital
        //We check that first letter is a letter
        //We delete space before word

        q=q.toLower();
        q=q.trimmed();


        Auxiliar::debug("isValidWord: _"+q+"_");

        //first=q.at(0);
        return (q.length()>0 && q.at(0).isLetter());
}

char Main::removeAccents(const QString& q) {
        QChar c = q.at(0);

        if (c==u'à' || c==u'á' || c==u'â' || c==u'ä') return 'a';
        if (c==u'è' || c==u'é' || c==u'ê' || c==u'ë') return 'e';
        if (c==u'ì'  || c==u'í' || c==u'î' || c==u'ï') return 'i';
        if (c==u'ò' || c==u'ó' || c==u'ô' || c==u'ö') return 'o';
        if (c==u'ù' || c==u'ú' || c==u'û' || c==u'ü') return 'u';

        if (q.at(0)==u'ç') return 'c';

        return (c.toLatin1());
}

void Main::selectItem()
{
	QListWidgetItem *item;

	//Si és, és a la fila 0
	
	item = ui.llistat->item(0);

    if (item!=nullptr) {
		if (item->text().compare(m_searched)==0) {
			ui.llistat->setCurrentRow(0);
		}
	}
}

void Main::obrir_configuracio_slot() {
	obrir_configuracio_worker(false);
}

void Main::obrir_configuracio()
{
	obrir_configuracio_worker(true);
}

void Main::obrir_configuracio_worker(bool first) {
        Configure *c = new Configure;
	c->carregar_config();
	c->setFirst(first);
	c->exec();

	delete c;
	
        carrega_config(0);
}


void Main::obrir_about()
{
        About *a = new About;
	a->exec();

	delete a;
}

void Main::carrega_config(int )
{
        QSettings qs("dacco","qdacco");
	QString browser;
        QString version;

	m_directori_usuari = qs.value("/dacco/directori","").toString();

	version = qs.value("/dacco/version","0").toString();

        if (version!="0.8") { //TODO: change to program constant
                //We will open the same settings file with read and then write mode
                //be careful!
                QMessageBox::information( this, "qdacco",tr("There is no configuration or old configuration. A configuration dialog will now open"));
                obrir_configuracio();
                carrega_config(1); //correct but little recursive rare call
        }
        else {
                m_idioma_actiu = qs.value("/dacco/diccionari_per_defecte",1).toInt();
		browser = qs.value("/dacco/browser","").toString();
		m_IgnoreCase = qs.value("/dacco/ignore_case","").toBool();
		m_IgnoreAccents = qs.value("/dacco/ignore_accents","").toBool();
		m_FestivalPath = qs.value("/dacco/festival","").toString();
		m_CurrentUILanguage = qs.value("/dacco/idioma_per_defecte",1).toInt();
		m_Autocomplete = qs.value("/dacco/autocomplete",1).toBool();

		ui.definicio->setFestivalEnable(m_FestivalPath!="");
		ui.paraula->setFestivalEnable(m_FestivalPath!="");

		ui.definicio->setBrowser(browser);

        Auxiliar::debug("Load config");
        Auxiliar::debug("Directory: "+m_directori_usuari);
                
		posa_idioma();
        }
}

void Main::cat_engf()
{
        m_idioma_actiu = Auxiliar::eng2cat() ;
        posa_idioma();
}


void Main::eng_catf()
{
        m_idioma_actiu= Auxiliar::cat2eng() ; 
        posa_idioma();
}


void Main::posa_idioma() {
        posarApunt(0);

        if (m_idioma_actiu== Auxiliar::eng2cat() ) {
                m_cat_eng->setChecked(true);
                m_eng_cat->setChecked(false);
        }
        else {
		m_eng_cat->setChecked(true);
                m_cat_eng->setChecked(false);
        }
}

void Main::switchDictionary() {
        if (m_idioma_actiu== Auxiliar::eng2cat() ) {
                m_idioma_actiu=Auxiliar::cat2eng();
        }
        else {
                m_idioma_actiu= Auxiliar::eng2cat() ;
        }
        posa_idioma();
        posarApunt(0);
	paraulaChanged(ui.paraula->text());
}

void Main::copy_definition() {
	QClipboard *clip = QApplication::clipboard();
	
	clip ->setText("PROVA DE PORTAPAPERS\n");

	ui.clipboard->setHtml(ui.paraula->text()+"<P>"+ui.definicio->toHtml());
	ui.clipboard->selectAll();
	ui.clipboard->copy();
}


void Main::paste_word() {
	QClipboard *clip = QApplication::clipboard();

	QString text = clip->text();

	ui.paraula->setText(text);
	treballaBuscar();
}

void Main::select_word()
{
        ui.paraula->selectAll();
        ui.paraula->setFocus();
}

void Main::searchListWord(QListWidgetItem *a)
{
	ui.paraula->setText(a->text());
	treballaBuscar();
}


void Main::showError(QString text) {
	ui.actiu->setText("<CENTER><FONT COLOR=\"red\">"+text+"</FONT></CENTER>");
	ui.actiu->show();
}

void Main::showBrowserError() {
    showError(tr("Error executing browser. Please check the FAQ for help with this issue"));
}

void Main::showMessage(QString text) {
	ui.actiu->setText("<CENTER>"+text+"</CENTER>");
	ui.actiu->show();
}

void Main::restaura() {
	setWindowState(windowState() & ~Qt::WindowMinimized | Qt::WindowActive);
	this->show();
	this->setFocus(Qt::ShortcutFocusReason);
	this->show();
}

void Main::quit() {
    // This is not the usual way to exit a Qt application!
	exit(0);
}
