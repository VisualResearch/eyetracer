/****************************************************************************
** Meta object code from reading C++ file 'SMIHED_widget.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../inc/SMIHED_widget.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SMIHED_widget.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SMIHED_widget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x0a,
      28,   14,   14,   14, 0x0a,
      44,   14,   14,   14, 0x0a,
      59,   14,   14,   14, 0x0a,
      80,   14,   14,   14, 0x0a,
     100,   14,   14,   14, 0x0a,
     120,   14,   14,   14, 0x0a,
     151,  144,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SMIHED_widget[] = {
    "SMIHED_widget\0\0sltAddFile()\0sltRemoveFile()\0"
    "sltRemoveAll()\0sltStartConversion()\0"
    "sltSetSubjectPath()\0sltSetImageFolder()\0"
    "sltSelectOutputFolder()\0select\0"
    "sltAbleSelection(bool)\0"
};

void SMIHED_widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SMIHED_widget *_t = static_cast<SMIHED_widget *>(_o);
        switch (_id) {
        case 0: _t->sltAddFile(); break;
        case 1: _t->sltRemoveFile(); break;
        case 2: _t->sltRemoveAll(); break;
        case 3: _t->sltStartConversion(); break;
        case 4: _t->sltSetSubjectPath(); break;
        case 5: _t->sltSetImageFolder(); break;
        case 6: _t->sltSelectOutputFolder(); break;
        case 7: _t->sltAbleSelection((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SMIHED_widget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SMIHED_widget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SMIHED_widget,
      qt_meta_data_SMIHED_widget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SMIHED_widget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SMIHED_widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SMIHED_widget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SMIHED_widget))
        return static_cast<void*>(const_cast< SMIHED_widget*>(this));
    if (!strcmp(_clname, "Plugin_widget"))
        return static_cast< Plugin_widget*>(const_cast< SMIHED_widget*>(this));
    if (!strcmp(_clname, "org.test.Plugin_widget/1.0"))
        return static_cast< Plugin_widget*>(const_cast< SMIHED_widget*>(this));
    return QWidget::qt_metacast(_clname);
}

int SMIHED_widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
