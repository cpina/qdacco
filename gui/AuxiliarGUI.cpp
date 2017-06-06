#ifndef AUXILIARGUI_CPP
#define AUXILIARGUI_CPP

#include "AuxiliarGUI.h"

#include "CMakeOptions.h"

void *AuxiliarGUI::m=0;

QString AuxiliarGUI::version = QDACCO_VERSION;
QString AuxiliarGUI::copyright_date = "2005, 2006, 2007, 2008, 2009, 2011, 2013, 2015, 2017";

QString AuxiliarGUI::getVersion() {
        return version;
}

QString AuxiliarGUI::getCopyrightDate() {
        return copyright_date;
}

#endif 
