/****************************************************************************
** Meta object code from reading C++ file 'SMIRED5_widget.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../inc/SMIRED5_widget.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SMIRED5_widget.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SMIRED5_widget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x0a,
      29,   15,   15,   15, 0x0a,
      45,   15,   15,   15, 0x0a,
      60,   15,   15,   15, 0x0a,
      84,   15,   15,   15, 0x0a,
     104,   15,   15,   15, 0x0a,
     124,   15,   15,   15, 0x0a,
     155,  148,   15,   15, 0x0a,
     178,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SMIRED5_widget[] = {
    "SMIRED5_widget\0\0sltAddFile()\0"
    "sltRemoveFile()\0sltRemoveAll()\0"
    "sltStartFragmentation()\0sltSetSubjectPath()\0"
    "sltSetImageFolder()\0sltSelectOutputFolder()\0"
    "select\0sltAbleSelection(bool)\0"
    "sltRemoveBlink()\0"
};

void SMIRED5_widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SMIRED5_widget *_t = static_cast<SMIRED5_widget *>(_o);
        switch (_id) {
        case 0: _t->sltAddFile(); break;
        case 1: _t->sltRemoveFile(); break;
        case 2: _t->sltRemoveAll(); break;
        case 3: _t->sltStartFragmentation(); break;
        case 4: _t->sltSetSubjectPath(); break;
        case 5: _t->sltSetImageFolder(); break;
        case 6: _t->sltSelectOutputFolder(); break;
        case 7: _t->sltAbleSelection((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->sltRemoveBlink(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SMIRED5_widget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SMIRED5_widget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SMIRED5_widget,
      qt_meta_data_SMIRED5_widget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SMIRED5_widget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SMIRED5_widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SMIRED5_widget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SMIRED5_widget))
        return static_cast<void*>(const_cast< SMIRED5_widget*>(this));
    if (!strcmp(_clname, "Plugin_widget"))
        return static_cast< Plugin_widget*>(const_cast< SMIRED5_widget*>(this));
    if (!strcmp(_clname, "org.test.Plugin_widget/1.0"))
        return static_cast< Plugin_widget*>(const_cast< SMIRED5_widget*>(this));
    return QWidget::qt_metacast(_clname);
}

int SMIRED5_widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
