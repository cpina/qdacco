#ifndef AUXILIARGUI_H
#define AUXILIARGUI_H

#include <QString>

class AuxiliarGUI {
	private:
		static QString version;
		static QString copyright_date;

        public:
        	static void *m;

		static QString getVersion();
		static QString getCopyrightDate();
};

#endif
