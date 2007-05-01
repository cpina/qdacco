/****************************************************************************
** Meta object code from reading C++ file 'mydialog.h'
**
** Created: dj set 28 19:49:44 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "old/mydialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mydialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_MyDialog[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x08,
      19,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MyDialog[] = {
    "MyDialog\0\0msgbox()\0pushButtonClicked()\0"
};

const QMetaObject MyDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_MyDialog,
      qt_meta_data_MyDialog, 0 }
};

const QMetaObject *MyDialog::metaObject() const
{
    return &staticMetaObject;
}

void *MyDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyDialog))
	return static_cast<void*>(const_cast<MyDialog*>(this));
    if (!strcmp(_clname, "Ui::Dialog"))
	return static_cast<Ui::Dialog*>(const_cast<MyDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int MyDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: msgbox(); break;
        case 1: pushButtonClicked(); break;
        }
        _id -= 2;
    }
    return _id;
}
