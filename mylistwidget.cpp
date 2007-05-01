#include <QtGui>
#include <QCoreApplication>
#include "mylistwidget.h"

MyListWidget::MyListWidget(QWidget *parent) : QListWidget(parent)
{

}

void MyListWidget::keyPressEvent(QKeyEvent *pEvent)
{
	int qkey = pEvent->key();
	int send=0;
	int type=0;
	

 	if (qkey == Qt::Key_Down) {

		type=QEvent::User+Auxiliar::KeyDown();
		send=1;
	}
	else if (qkey == Qt::Key_Up) {
		type=QEvent::User+Auxiliar::KeyUp();
		send=1;
	}
	else if (qkey == Qt::Key_PageDown) {
		type=QEvent::User+Auxiliar::KeyNextPage();
		send=1;

	}
	else if (qkey == Qt::Key_PageUp) {
		type=QEvent::User+Auxiliar::KeyPrevPage();
		send=1;
	}

	if (send) {
		QEvent qevent((QEvent::Type)type);
		QCoreApplication::sendEvent(m_parent,&qevent);
	}
	else {
		QListWidget::keyPressEvent(pEvent);
	}
}

void MyListWidget::setParent(QObject *q)
{
	m_parent=q;
}
