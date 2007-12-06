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

void ShowUsage();
void ShowCopyright();


