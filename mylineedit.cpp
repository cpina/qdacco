#include <QtGui>
#include <QCoreApplication>
#include "mylineedit.h"

MyLineEdit::MyLineEdit(QWidget *parent) : QLineEdit(parent)
{

}

void MyLineEdit::setFestivalEnable(int f) 
{
	m_festival_enable=f;
}

void MyLineEdit::keyPressEvent(QKeyEvent *pEvent)
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
	
	QLineEdit::keyPressEvent(pEvent);
}

void MyLineEdit::setParent(QObject *q)
{
	m_parent=q;
}

void MyLineEdit::contextMenuEvent(QContextMenuEvent *e)
{
	QMenu *menu = createStandardContextMenu();
	QAction *festival = menu->addAction(tr("Read"));
	festival->setEnabled(m_festival_enable && this->text().length()>0);
	connect(festival,SIGNAL(triggered()),m_parent,SLOT(FestivalExecuteEntry()));
	menu->exec(e->globalPos());
}
