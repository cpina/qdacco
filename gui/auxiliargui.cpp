#ifndef AUXILIARGUI_CPP
#define AUXILIARGUI_CPP

#include "auxiliargui.h"
#include <cstdlib>
#include <cstdio>

void *AuxiliarGUI::m=0;

QString AuxiliarGUI::version = "0.8.0";
QString AuxiliarGUI::copyright_date = "2005, 2006, 2007, 2008";

QString AuxiliarGUI::getVersion() {
        return version;
}

QString AuxiliarGUI::getCopyrightDate() {
        return copyright_date;
}

#endif 
