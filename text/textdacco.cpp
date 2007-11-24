#include <iostream>

#include <QFile>
#include <QXmlInputSource>

#include "../core/auxiliar.h"
#include "../core/StructureParser.h"

#include <getopt.h>

#define DEFAULT_BASEPATH "/usr/share/dacco-common/dictionaries"

QString SearchWord(QString word,QString dictionary,QString basepath);

void ShowUsage();
void ShowCopyright();

void ShowUsage() {
	//TODO: write it
	printf("USAGE:\n");
	printf("--word or --beginswith\n");
	printf("--cateng or --engcat\n");
	printf("--path PATH_TO_DICT [optional]\n");
	printf("--ddebug [optional]\n");
	printf("\n");
}


void ShowCopyright() {
	//TODO: write it
	printf("Carles Pina i Estany, 2007\n");
	printf("License: GPL v3.0\n");
	printf("\n");
}

int main(int argc, char *argv[]) {
	int flags, opt;
	int c;
	int debug;
	int exit_later=0;
	int quiet;

	static struct option long_options[]={
		{"engcat",0,0,0},
		{"cateng",0,0,0},
		{"word",1,0,0},
		{"path",1,0,0},
		{"debug",0,0,0},
		{0,0,0,0}
	};
	int option_index = 0;

	QString word="",dictionary,basepath="";

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
		} else if (strcmp(option_name,"path")==0) {
			basepath=optarg;
		} else if (strcmp(option_name,"engcat")==0) {
			dictionary="eng";
		} else if (strcmp(option_name,"cateng")==0) {
			dictionary="cat";
		} else if (strcmp(option_name,"debug")==0) {
			debug=0;
		} else if (strcmp(option_name,"quiet")==0) {
			quiet=1;
		}
	}

	Auxiliar::setDebug(debug);
	
	if (quiet==0) {
		ShowCopyright();
	}

	if (word=="") {
		printf("--word SOME_WORD is mandatory\n");
		exit_later=1;
	}

	if (dictionary=="") {
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

	QString result = SearchWord(word,dictionary,basepath);

	result=WordData::HTML2Text(result);

	printf("%s\n",qPrintable(result));

	return 0;
}

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
