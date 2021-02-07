#include "TextBrowser.h"

TextBrowser::TextBrowser(QWidget* parent) :
    QTextBrowser(parent)
{}

int TextBrowser::getCharPosition() const {
    QTextCursor qtc;
    qtc = this->textCursor();
    return qtc.position();
}

void TextBrowser::selectWord() {
    //Warn: only valid after m_qupoint has been setted up
    QTextCursor qtc;
    QString s;

    if (!this->textCursor().hasSelection()) {
        qtc = this->cursorForPosition(m_qpoint);
        qtc.select(QTextCursor::WordUnderCursor);
        this->setTextCursor(qtc);
    }
}

void TextBrowser::setBrowser(const QString& browserLocation) {
    m_browser_location = browserLocation;
}

void TextBrowser::setParent(QMainWindow *mainWindow) {
    m_parent=mainWindow;
}

void TextBrowser::setFestivalEnable(int f) {
    m_festival_enable=f;
}

void TextBrowser::setSource(const QUrl& url) {
    bool success = QProcess::startDetached(m_browser_location, QStringList() << url.toString());

    Auxiliar::debug("Executing: "+m_browser_location);

    if (!success) {
        emit browserFailed();
    }
}

void TextBrowser::contextMenuEvent(QContextMenuEvent *e) {
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

QPoint TextBrowser::getPosition() const {
    return m_qpoint;
}

int TextBrowser::getLanguage() const {
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
    Auxiliar::debug(QString("Language to read: ") + textLanguage);
    return textLanguage;
}

QString TextBrowser::getText() const {
    QTextCursor tc = this->textCursor();
    return tc.selectedText();
}
