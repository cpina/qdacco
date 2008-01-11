#include <QFile>
#include <QXmlInputSource>
#include <QSettings>
#include <QDir>

#include "../core/auxiliar.h"
#include "../core/StructureParser.h"
#include "../core/StructureList.h"

#include <getopt.h>

QString Search(QString word,QString dictionary,QString basepath,int type);
QString GetDictionaryPath();

void ExtendedBiSearch(QString search,QString basepath);
void ExtendedSearch(QString search,QString dictionary,QString basepath);
void ShowUsage();
void ShowCopyright();

void underline(QString search);

