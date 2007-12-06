#include <QFile>
#include <QXmlInputSource>

#include "../core/auxiliar.h"
#include "../core/StructureParser.h"
#include "../core/StructureList.h"

#include <getopt.h>

#define DEFAULT_BASEPATH "/usr/share/dacco-common/dictionaries"

QString Search(QString word,QString dictionary,QString basepath,int type);

void ShowUsage();
void ShowCopyright();
