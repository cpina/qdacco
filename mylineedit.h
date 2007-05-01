#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H


#include <QtGui>
#include "auxiliar.h"

class MyLineEdit : public QLineEdit
{
	Q_OBJECT

	public:
		MyLineEdit (QWidget *parent=0);
		void setParent(QObject *q);
		virtual void contextMenuEvent(QContextMenuEvent *e);
		void setFestivalEnable(int f);


	protected:
		void keyPressEvent(QKeyEvent *pEvent);

	private:
		QObject* m_parent;
		int m_festival_enable;

};

#endif

