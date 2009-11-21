#ifndef AUXILIARGUI_CPP
#define AUXILIARGUI_CPP

#include "AuxiliarGUI.h"

void *AuxiliarGUI::m=0;

QString AuxiliarGUI::version = "0.8.1";
QString AuxiliarGUI::copyright_date = "2005, 2006, 2007, 2008, 2009";

QString AuxiliarGUI::getVersion() {
        return version;
}

QString AuxiliarGUI::getCopyrightDate() {
        return copyright_date;
}

#endif 
