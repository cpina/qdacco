/*
 * This file is part of qdacco
 * qdacco: offline Dacco Catalan <-> English dictionary
 *
 * Copyright (c) 2005, 2006, 2007
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

Main::Main(QWidget *)  //parent
{

        ui.setupUi(this);
	ui.paraula->setParent(this);
	ui.llistat->setParent(this);
	ui.definicio->setFather(this);
	ui.report->setText(tr("Report as new entry"));
	
	ui.report->setEnabled(false);

	installEventFilter(this);


	//m_showList=0;
	m_numberFound=0;

	m_cat_eng = new QToolButton;
	m_cat_eng->setText(tr("cat->eng"));
	m_cat_eng->setCheckable(1);
	ui.toolBar->addWidget(m_cat_eng);

	m_eng_cat = new QToolButton;
	m_eng_cat->setText(tr("eng->cat"));
	m_eng_cat->setCheckable(1);
	ui.toolBar->addWidget(m_eng_cat);

	ui.toolBar->addSeparator();

	ui.definicio->setProcess(&m_browser);

	QAction *copy = ui.toolBar->addAction(QIcon(":icons/editcopy.png"),tr("Copy"));
	QAction *paste = ui.toolBar->addAction(QIcon(":icons/editpaste.png"),tr("Paste"));
	connect(copy,SIGNAL(triggered()),this,SLOT(copy_definition()));
	connect(paste,SIGNAL(triggered()),this,SLOT(paste_word()));
	
        connect(ui.Buscar,SIGNAL(clicked()),this,SLOT(buscarClicked()));
        connect(ui.editConfigureAction,SIGNAL(activated()),this,SLOT(obrir_configuracio_slot()));
        connect(ui.editSelectAction,SIGNAL(activated()),this,SLOT(select_word()));

	connect(m_cat_eng,SIGNAL(clicked()),this,SLOT(cat_engf()));
	connect(m_eng_cat,SIGNAL(clicked()),this,SLOT(eng_catf()));
	
	connect(ui.fileChangeDictionaryAction,SIGNAL(activated()),this,SLOT(switchDictionary()));
	connect(ui.paraula,SIGNAL(returnPressed()),this,SLOT(buscarEnter()));
	connect(ui.helpAboutAction,SIGNAL(activated()),this,SLOT(obrir_about()));

	connect(ui.report,SIGNAL(clicked()),this,SLOT(obrir_suggeriment()));
	connect(ui.llistat,SIGNAL(itemDoubleClicked(QListWidgetItem *)),this,SLOT(searchListWord(QListWidgetItem*)));
	connect(ui.paraula,SIGNAL(textChanged(const QString &)),this,SLOT(paraulaChanged(const QString &)));

	connect(&m_festival,SIGNAL(error(QProcess::ProcessError)),this,SLOT(FestivalError(QProcess::ProcessError)));
	connect(&m_festival,SIGNAL(finished(int,QProcess::ExitStatus)),this,SLOT(FestivalFinished(int,QProcess::ExitStatus)));
	connect(&m_browser,SIGNAL(error(QProcess::ProcessError)),this,SLOT(BrowserError(QProcess::ProcessError)));
	
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
	showError(tr("Error executing Festival. Please consult the FAQ for help with this issue"));
}

void Main::BrowserError(QProcess::ProcessError) {
	showError(tr("Error executing browser. Please consult the FAQ for help with this issue"));
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

bool Main::eventFilter(QObject *, QEvent *event) //obj
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

	return TRUE;
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
		if (item!=NULL) {
			ui.paraula->setText(item->text());
		}
	}
	buscar();
}

void Main::buscar()
{
	treballaBuscar();
	ui.paraula->selectAll();
	ui.paraula->setFocus(Qt::OtherFocusReason);
}


void Main::paraulaChanged(const QString &paraula)
{
	bool enabled=false;

	//Update the list
	//ui.report->hide();
	ui.actiu->hide();
	ui.definicio->hide();
	ui.llistat->clear();
	UpdateList();
	m_numberFound=0;

	if (ui.llistat->count()==1) {
		ui.llistat->setCurrentRow(0);
	}


	//Enable/disable the report button
	if (paraula.length()==0) {
		enabled=false;
	}
	else { //paraula.length>0
		QListWidgetItem *item;
		item = ui.llistat->item(0);
		
		enabled=true;
		ui.report->setText(tr("Report as new entry"));

		if (item!=NULL && item->text().compare(ui.paraula->text())==0) {
			enabled=false;
		}
	}
	ui.report->setEnabled(enabled);

	
	//old stuff
	/*if (ui.llistat->count()==0 && ui.paraula->text().length()!=0) {
		ui.report->setText(tr("Report as new entry"));
		//ui.report->show();
	}
	else {
		//ui.report->hide();
	}
	*/
}

void Main::UpdateList() {
        StructureList handler;
	handler.setIgnoreCase(m_IgnoreCase);
	handler.setIgnoreAccents(m_IgnoreAccents);
	handler.setList(ui.llistat);
       
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

	letter=lletra_buscar(search);
	QFile xmlFile(m_directori_usuari+"/"+idioma+"/"+letter+".dic");


	if (!xmlFile.exists()) {
		showError(tr("Cannot open dictionary file. Check configuration directory and permissions"));
	}
	else {
		Auxiliar::debug("Fitxer2: "+m_directori_usuari+"/"+idioma+"/"+letter+".dic");

		QXmlInputSource source( &xmlFile );
		QXmlSimpleReader reader;
		reader.setFeature("http://trolltech.com/xml/features/report-whitespace-only-CharData",FALSE);   //if we don't use it, we get more entries because spaces...
		reader.setContentHandler(&handler);

		handler.setParaula(search);

		reader.parse(source);

		WordData d = handler.getWordData();

		ui.definicio->setPlainText("");

		ui.definicio->setPlainText("");
		m_searched=search;
		selectItem();
	}
}


void Main::treballaBuscar() {
        StructureParser handler;

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

		lletra=lletra_buscar(buscar);
		QFile xmlFile(m_directori_usuari+"/"+idioma+"/"+lletra+".dic");


		if (!xmlFile.exists()) {
			showError(tr("Cannot open dictionary file. Check configuration directory and permissions"));
		}
		else {
			Auxiliar::debug("Fitxer: "+m_directori_usuari+"/"+idioma+"/"+lletra+".dic");

			QXmlInputSource source( &xmlFile );
			QXmlSimpleReader reader;
			reader.setFeature("http://trolltech.com/xml/features/report-whitespace-only-CharData",FALSE);   //if we don't use it, we get more entries because spaces...
			reader.setContentHandler( &handler );

			handler.setParaula(buscar_orig);

			reader.parse(source);

			WordData d = handler.getWordData();

			ui.definicio->setPlainText("");

		        if (d.getNum()!=0) {
				ui.definicio->show();
				ui.llistat->hide();
				
				for (int i=0;i<d.getNum();i++) {
					ui.definicio->setHtml(ui.definicio->toHtml()+d.getEntry(i)+"<P>");
				}
			}
			
			else if (d.getNum()==0) {
				//No word found or buscar == 1: we show the list
				
				ui.definicio->setPlainText("");
				ui.definicio->hide();
				ui.llistat->show();
				//loadList(&handler);
				
				m_searched=buscar_orig;
				selectItem();
				if (d.getNum()==0) {
					showError(tr("Exact match not found"));
					ui.report->setText(tr("Report as new entry"));
					//ui.report->show();
				}
			}
			if (d.getNum()>0) {
				ui.report->setText(tr("Send comment(s)"));
				ui.report->setEnabled(true);
				//ui.report->show();
			}
			m_numberFound=d.getNum();
		}
        }
}

void Main::posarApunt (int all) {
	m_numberFound=0;
        ui.llistat->clear();
        ui.llistat->hide();
	ui.definicio->show();

        if (all) {
                ui.paraula->setText("");
        }
        ui.definicio->setPlainText("");

        ui.actiu->hide();
        ui.actiu->setText("");
        //ui.report->hide();
        ui.paraula->selectAll();
        ui.paraula->setFocus();
}

int Main::isValidWord(QString &q) {
        QChar first;
        //We transform the word to not-capital
        //We check that first letter is a letter
        //We delete space before word

        q=q.toLower();
        q=q.trimmed();


        Auxiliar::debug("isValidWord: _"+q+"_");
        first=q.at(0);
        return (first.isLetter() && q.length()>0);
}

char Main::lletra_buscar(QString q) {
        QChar a;

        if (q.at(0)=='à' || q.at(0)=='á' || q.at(0)=='â' || q.at(0)=='ä') return 'a';
        if (q.at(0)=='è' || q.at(0)=='é' || q.at(0)=='ê' || q.at(0)=='ë') return 'e';
        if (q.at(0)=='ì'  || q.at(0)=='í' || q.at(0)=='î' || q.at(0)=='ï') return 'i';
        if (q.at(0)=='ò' || q.at(0)=='ó' || q.at(0)=='ô' || q.at(0)=='ö') return 'o';
        if (q.at(0)=='ù' || q.at(0)=='ú' || q.at(0)=='û' || q.at(0)=='ü') return 'u';

        if (q.at(0)=='ç') return 'c';

        a=q.at(0);

        return (a.toAscii());
}

void Main::selectItem()
{
	QListWidgetItem *item;

	//Si és, és a la fila 0
	
	item = ui.llistat->item(0);

	if (item!=NULL) {
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

void Main::carrega_config(int all)
{
        QSettings qs("dacco","qdacco");
	QString browser;
        int xsize,ysize,xpos,ypos;
        QString version;

	m_directori_usuari = qs.value("/dacco/directori","").toString();

	version = qs.value("/dacco/version","0").toString();

        if (version!="0.6") {
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

		ui.definicio->setFestivalEnable(m_FestivalPath!="");
		ui.paraula->setFestivalEnable(m_FestivalPath!="");

		ui.definicio->setBrowser(browser);

                Auxiliar::debug("Load config");
                Auxiliar::debug("Directory: "+m_directori_usuari);
                
		posa_idioma();

                if (all==1) {
                        xpos = qs.value("/dacco/xpos",0).toInt();
                        ypos = qs.value("/dacco/ypos",0).toInt();
                        xsize = qs.value("/dacco/xsize",234).toInt();
                        ysize = qs.value("/dacco/ysize",355).toInt();

                        resize(QSize(xsize,ysize));
                }
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
                m_cat_eng->setChecked(TRUE);
                m_eng_cat->setChecked(FALSE);
        }
        else {
		m_eng_cat->setChecked(TRUE);
                m_cat_eng->setChecked(FALSE);
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

void Main::obrir_suggeriment()
{
	QSettings qs("dacco","qdacco");

	QString name,email;
	QString userWord,userTranslations,userExamples,userNotes;
	int okay;

	name = qs.value("/dacco/name","").toString();
	email = qs.value("/dacco/email","").toString();

	m_http = new HTTPConnection(this);

	if (m_numberFound==0) {
		m_http->sendNewWord(m_searched,name,email,m_idioma_actiu);
		showMessage(tr("Sending..."));
		//ui.report->hide();
	}
	else {
        	Suggeriment *s = new Suggeriment;
		s->setWord(ui.paraula->text());
		s->exec();

		s->getOkay(okay);

		if (okay==1) {
                        s->getUserWord(userWord);
                        s->getUserTranslations(userTranslations);
                        s->getUserExamples(userExamples);
                        s->getUserNotes(userNotes);

                        if (userTranslations.length()==0 &&
                                userExamples.length()==0 &&
                                userNotes.length()==0) {
				showError(tr("You must type something"));
                        }
                        else {
                                m_http->sendSuggestion(userWord,userTranslations,userExamples,userNotes,name,email,m_idioma_actiu);

				showMessage(tr("Sending..."));
                                //ui.report->hide();
				ui.paraula->setFocus(Qt::OtherFocusReason);
                        }
                }
                else {
			showMessage(tr("Action cancelled"));
			ui.paraula->setFocus(Qt::OtherFocusReason);
                }
	}
}

void Main::ReportChangeState(int,bool)
{
        if ((*m_http->getStateError()).compare("")==0) {
		showMessage(tr("Correctly sent!"));
        }
        else {
		showError(tr("Problem sending: ")+*m_http->getStateError());
        }

        delete m_http;
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


void Main::showMessage(QString text) {
	ui.actiu->setText("<CENTER>"+text+"</CENTER>");
	ui.actiu->show();
}
