/*
 * This file is part of qdacco
 * qdacco: offline Dacco Catalan <-> English dictionary
 *
 * Copyright (c) 2005, 2006, 2007, 2015
 *      Carles Pina i Estany <carles@pina.cat>
 *
 * qdacco is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * any later version.
 *
 * qdacco is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TEXTBROWSER_H
#define TEXTBROWSER_H

#include <QApplication>
#include <QTextBrowser>
#include <QTextEdit>
#include <QProcess>
#include <QMainWindow>
#include <QMenu>
#include <QContextMenuEvent>
#include <QHashIterator>

//qdaccolib
#include <nongui/auxiliar.h>

class TextBrowser : public QTextBrowser
{
	Q_OBJECT
	private:
		QProcess *m_browser_process;
		QString m_browser_location;
		int m_festival_enable;

		QMainWindow *m_parent;
		QPoint m_qpoint;

		int getCharPosition() {
			QTextCursor qtc;
			qtc = this->textCursor();
			return qtc.position();
		}

		void selectWord() {
			//Warn: only valid after m_qupoint has been setted up
			QTextCursor qtc;
			QString s;

			if (!this->textCursor().hasSelection()) {
				qtc = this->cursorForPosition(m_qpoint);
				qtc.select(QTextCursor::WordUnderCursor);
				this->setTextCursor(qtc);
			}
		}

	public:
        TextBrowser(QWidget *&) {}

		void setFather(QMainWindow *m) {
			m_parent=m;
		}
		void setProcess(QProcess *p_) {
			m_browser_process=p_;
		}
		void setBrowser(QString browser_) {
			m_browser_location=browser_;
		}

		void setParent(QMainWindow *m) {
			m_parent=m;
		}
		void setFestivalEnable(int f) {
			m_festival_enable=f;
		}
	
		virtual void setSource(const QUrl& url) {
            m_browser_process->setProgram(m_browser_location);
            m_browser_process->setArguments(QStringList() << url.toString());
            m_browser_process->startDetached();
            Auxiliar::debug("Executing: "+m_browser_location);
		}

		virtual void contextMenuEvent(QContextMenuEvent *e) {
			int language;
			m_qpoint=e->pos();
			
			selectWord();

			QMenu *menu = createStandardContextMenu();
			if (Auxiliar::isWindows()==false) {
				QAction *festival = menu->addAction(tr("Read"));
				
				language = getLanguage();
				festival->setEnabled(m_festival_enable && language!=0);

				connect(festival,SIGNAL(triggered()),m_parent,SLOT(FestivalExecuteDefinition()));

			}
			menu->exec(e->globalPos());
		}

		QPoint getPosition() {
			return m_qpoint;
		}

		int getLanguage() {
			int cursor_position=getCharPosition();
			//return Auxiliar::catalan(), Auxiliar::english(),
			//3: UI language
			//4: destination language
			//5: NOT destination language
			
			QString text = this->toPlainText();

			int cat = Auxiliar::catalan();
			int eng = Auxiliar::english();

			QHash<QString,int>hash;

			hash.insert(tr("Catalan example(s): "),cat);
			hash.insert(tr("English example(s): "),eng);
			hash.insert(tr("English notes: "),eng);
			hash.insert(tr("Catalan notes: "),cat);
			hash.insert(tr("Example(s): "),5);
			hash.insert(tr("Synonym(s): "),5);
			hash.insert(tr("Plural: "),4);
			hash.insert(tr("Female Plural: "),4);
		
			hash.insert(tr("Picture: "),0);
			hash.insert(tr("Flickr: "),0);

			QHashIterator<QString,int> i(hash);
			
			int position=0;
			int textLanguage=4;
			int temp;
			while (i.hasNext()) {
				i.next();
				temp=text.lastIndexOf(i.key(),cursor_position,Qt::CaseSensitive);
				if (temp!=-1 && temp > position) {
					position=temp;
					textLanguage=i.value();

					if (temp+i.key().length() > cursor_position) {
						textLanguage=3;
					}
				}
			}
			Auxiliar::debug("Language to read: "+textLanguage);
			return textLanguage;
		}

		QString getText() {
			QTextCursor tc = this->textCursor();
			return tc.selectedText();
		}

	signals:
		void browserFailed();
		void browserOpened();
};
#endif
