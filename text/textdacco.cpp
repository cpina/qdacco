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
	int flags, opt;
	int c;
	int debug=0;
	int exit_later=0;
	int quiet=0;
	int help=0;

	static struct option long_options[]={
		{"engcat",0,0,0},
		{"cateng",0,0,0},
		{"word",1,0,0},
		{"beginswith",1,0,0},
		{"path",1,0,0},
		{"debug",0,0,0},
		{"help",0,0,0},
		{"quiet",0,0,0},
		{0,0,0,0}
	};
	int option_index = 0;

	QString word="",dictionary,basepath="",beginswith="";

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
			dictionary="eng";
		} else if (strcmp(option_name,"cateng")==0) {
			dictionary="cat";
		} else if (strcmp(option_name,"debug")==0) {
			debug=1;
		} else if (strcmp(option_name,"quiet")==0) {
			quiet=1;
		} else if (strcmp(option_name,"help")==0) {
			help=1;
		}
	}

	Auxiliar::setDebug(debug);
	
	if (quiet==0) {
		ShowCopyright();
	}
	
	if (help==1) {
		ShowUsage();
		exit_later=1;
	}
	if (word=="" && beginswith=="" && help==0) {
		printf("--word|--beginswith WORD is mandatory\n");
		exit_later=1;
	}
	if (dictionary=="" && help==0) {
		printf("--cateng or --engcat options are needed\n");
		exit_later=1;
	}
	if (basepath=="") {
		Auxiliar::debug(QString("Using default basepath: ")+QString(DEFAULT_BASEPATH)+QString("\n"));
		basepath=DEFAULT_BASEPATH;
	}
	if (exit_later) {
		exit(1);
	}

	if (word!="") {
		QString result = SearchWord(word,dictionary,basepath);

		result=WordData::HTML2Text(result);

		printf("%s\n",qPrintable(result));
	}

	if (beginswith!="") {
		if (quiet==0) {
			printf("Word List:\n");
		}
		QString result = SearchList(beginswith,dictionary,basepath);
		printf("%s\n",qPrintable(result));
	}
	return 0;
}
//BIG TODO: factorize SearchWord and SearchList

QString SearchWord(QString word,QString dictionary,QString basepath) {
	//TODO: integrate into core? (it's used on graphic qdacoo too!)

	//dictionary: -eng, for english to catalan translations
	//            -cat, for catalan to english
	StructureParser handler;

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
		printf("I cannot open dictionary file: %s . You can change the path using --path option\n",qPrintable(path));
		exit(2);
	}
	
	QXmlInputSource source(&xmlFile);
	QXmlSimpleReader reader;

	reader.setFeature("http://trolltech.com/xml/features/report-whitespace-only-CharData",FALSE);   //if we don't use it, we get more entries because spaces...
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
		ret="Word not found";
	}

	return ret;
}

QString SearchList(QString word,QString dictionary,QString basepath) {
	//TODO: integrate into core? (it's used on graphic qdacoo too!)

	//dictionary: -eng, for english to catalan translations
	//            -cat, for catalan to english
	StructureList handler;

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
		printf("I cannot open dictionary file: %s . You can change the path using --path option\n",qPrintable(path));
		exit(2);
	}
	
	QXmlInputSource source(&xmlFile);
	QXmlSimpleReader reader;

	reader.setFeature("http://trolltech.com/xml/features/report-whitespace-only-CharData",FALSE);   //if we don't use it, we get more entries because spaces...
	reader.setContentHandler(&handler);

	//Buf, change this! why handler needs setParaula and setWord?
	handler.setParaula(word);
	handler.setWord(word);

	QString qs="";
	handler.setList(&qs);
	reader.parse(source);

	return qs;
}

void ShowUsage() {
	printf("USAGE:\n");
	printf("--word or --beginswith\n");
	printf("--cateng or --engcat\n");
	printf("--path PATH_TO_DICT [optional]\n");
	printf("--debug [optional]\n");
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

