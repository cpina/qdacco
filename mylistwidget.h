#ifndef MYLISTWIDGET_H
#define MYLISTWIDGET_H


#include <QtGui>
#include "auxiliar.h"

class MyListWidget: public QListWidget
{
	Q_OBJECT

	public:
		MyListWidget(QWidget *parent=0);
		void setParent(QObject *q);


	protected:
		void keyPressEvent(QKeyEvent *pEvent);

	private:
		QObject* m_parent;

};

#endif

