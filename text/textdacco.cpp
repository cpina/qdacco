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


#include "textdacco.h"

int main(int argc, char *argv[]) {
	//int flags, opt;
	int c;
	int debug=0;
	int exit_later=0;
	int silent=0;
	int help=0;


	static struct option long_options[]={
		{"engcat",1,0,0},
		{"cateng",1,0,0},
		{"word",1,0,0},
		{"beginswith",1,0,0},
		{"path",1,0,0},
		{"debug",0,0,0},
		{"help",0,0,0},
		{"silent",0,0,0},
		{0,0,0,0}
	};
	int option_index = 0;

	QString word="",dictionary,basepath="",beginswith="",search="";

	if (argc==1) {
		ShowCopyright();
		ShowUsage();
		exit(1);
	}

	for(;;) {
		c=getopt_long(argc,argv,"",long_options,&option_index);
		if (c == -1) {
			break;
		}

		const char *option_name = long_options[option_index].name;

		if (strcmp(option_name,"word")==0) {
			word=optarg;
		} else if (strcmp(option_name,"beginswith")==0) {
			beginswith=optarg;
		} else if (strcmp(option_name,"path")==0) {
			basepath=optarg;
		} else if (strcmp(option_name,"engcat")==0) {
			search=optarg;
			dictionary="eng";
		} else if (strcmp(option_name,"cateng")==0) {
			search=optarg;
			dictionary="cat";
		} else if (strcmp(option_name,"debug")==0) {
			debug=1;
		} else if (strcmp(option_name,"silent")==0) {
			silent=1;
		} else if (strcmp(option_name,"help")==0) {
			help=1;
		}
	}

	Auxiliar::setDebug(debug);
	
	if (silent==0) {
		ShowCopyright();
	}
	
	if (help==1) {
		ShowUsage();
		exit_later=1;
	}
	
	if (basepath=="") {
		basepath=GetDictionaryPath();
		Auxiliar::debug(QString("Using dictionary path: ")+basepath+QString("\n"));
	}
	
	if (exit_later) {
		exit(1);
	}


	if (argc==2) {
		search=QString(argv[1]);
		ExtendedBiSearch(search,basepath);
	}

	else if (search!="" && word=="" && dictionary!="") {
		ExtendedSearch(search,dictionary,basepath);
	}

	else if (search!="" && word=="" && dictionary=="") {
		ExtendedBiSearch(search,basepath);
	}
	else if (word!="") {
		QString result = Search(word,dictionary,basepath,1);

		result=WordData::HTML2Text(result);
		if (result!="") {
			printf("%s\n",qPrintable(result));
		}
		else {
			printf("Word not found\n");
		}
	}
	else if (beginswith!="") {
		if (silent==0) {
			printf("Word List:\n");
		}
		QString result = Search(beginswith,dictionary,basepath,2);
		printf("%s\n",qPrintable(result));
	}
	return 0;
}

void ExtendedBiSearch(QString search,QString basepath) {
	printf("CAT -> ENG\n");
	printf("==========\n");
	ExtendedSearch(search,"cat",basepath);

	printf("\n");
	printf("ENG -> CAT\n");
	printf("==========\n");
	ExtendedSearch(search,"eng",basepath);
}

void ExtendedSearch(QString search, QString dictionary,QString basepath) {
	QString result = Search(search,dictionary,basepath,1);
	result=WordData::HTML2Text(result);
	if (result!="") {
		printf("%s\n",qPrintable(search));
		underline(search);
		printf("%s\n",qPrintable(result));
	}
	else {
		result = Search(search,dictionary,basepath,2);
		if (result!="") {
			printf("%s\n",qPrintable(result));
	}
		else {
			printf("No words starts with \"%s\"\n",qPrintable(search));
		}
	}
}

void underline(QString search) {
	QString under="";
	for (int i=0;i<search.length();i++) {
		under=under+"=";
	}
	printf("%s\n",qPrintable(under));
}

//type==1: SearchWord
//type==2: SearchList
QString Search(QString word,QString dictionary,QString basepath,int type) {
	//TODO: integrate into core? (it's used similar methods in GUI!)
	
	//dictionary: -eng, for english to catalan translations
	//            -cat, for catalan to english

	QString path="";
	QString ret="";

	if (dictionary=="eng") {
		path=basepath+"/engcat/";
	}
	else if (dictionary=="cat") {
		path=basepath+"/cateng/";
	}

	char lletra=Auxiliar::lletra_buscar(word);
	path=path+lletra+".dic";

	QFile xmlFile(path);
	if (!xmlFile.exists()) {
		printf("Error opening dictionary file: %s .\nYou can change the path using --path option or in config file\n",qPrintable(path));
		exit(2);
	}
	
	QXmlInputSource source(&xmlFile);
	QXmlSimpleReader reader;

	reader.setFeature("http://trolltech.com/xml/features/report-whitespace-only-CharData",FALSE);   //if we don't use it, we get more entries because spaces...
	
	
	//Buf, change this! why handler needs setParaula and setWord?
	//List and Word?
	//handler.setWord(word);

	if (type==1) {
		//TODO: factorize with StructureList?
		StructureParser handler;
		reader.setContentHandler(&handler);
		handler.setParaula(word);

		reader.parse(source);

		WordData d = handler.getWordData();

		if (d.getNum()>0) {
			for (int i=0;i<d.getNum();i++) {
				ret=ret+d.getTextEntry(i);
				if (i+1<d.getNum()) {
					ret=ret+"\n------\n";
				}
			}
		}

		else if (d.getNum()==0) {
			ret="";
		}

	} else if (type==2) {
		//StructureList handler;
		enum Client pclient = TEXT;
		StructureList handler;

		reader.setContentHandler(&handler);
		handler.setParaula(word);
		handler.setWord(word);

		QString qs="";
		
		reader.parse(source);

		ret = handler.getListWords();

		//ret = qs;
	}
	return ret;
}

void ShowUsage() {
	printf("USAGE:\n");
	printf("--word or --beginswith\n");
	printf("--cateng or --engcat\n");
	printf("--path PATH_TO_DICT\n");
	printf("--debug optional\n");
	printf("--silent]\n");
	printf("--help\n");
}


void ShowCopyright() {
	printf("textdacco Copyright (C) 2007 Carles Pina i Estany\n");
	printf("This program comes with ABSOLUTELY NO WARRANTY\n");
	printf("This is free software, and you are welcome to redistribute it\n");
	printf("under certain conditions; type `show c' for details.\n");
	printf("License: GPL v3.0\n");

	printf("\n");
}


QString GetDictionaryPath() {
	//TODO: could we use Configure::search_directory from GUI?
	
	//If PATH in config file exists: returns it
	//else: returns default Dictionary path
	
	QSettings qs("dacco","qdacco");
	QString path,ret="";

	path=qs.value("/dacco/directori", "" ).toString();

	QDir dir(path);
	
	if (dir.exists() && path.length()>0) {
		ret=path;
	}
	else {
		QDir dir(Auxiliar::getDictionariesDirectory());

		if (dir.exists()) {
			ret=Auxiliar::getDictionariesDirectory();
		}
	}

	return ret;
}
