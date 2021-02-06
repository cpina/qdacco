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
#include <nongui/Auxiliar.h>

class TextBrowser : public QTextBrowser
{
    Q_OBJECT

public:
    TextBrowser(QWidget* parent = nullptr);

    void setProcess(QProcess* process);

    void setBrowser(const QString& browser);

    void setParent(QMainWindow* mainWindow);

    void setFestivalEnable(int f);

    virtual void setSource(const QUrl& url);

    virtual void contextMenuEvent(QContextMenuEvent *e);

    QPoint getPosition() const;

    int getLanguage() const;

    QString getText() const;

Q_SIGNALS:
    void browserFailed();
    void browserOpened();

private:
    int getCharPosition() const;
    void selectWord();

    QProcess *m_browser_process;
    QString m_browser_location;
    int m_festival_enable;

    QMainWindow *m_parent;
    QPoint m_qpoint;
};
#endif
