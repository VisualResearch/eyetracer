/****************************************************************************
** Meta object code from reading C++ file 'IDMT_widget.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../inc/IDMT_widget.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'IDMT_widget.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_IDMT_widget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      26,   12,   12,   12, 0x0a,
      42,   12,   12,   12, 0x0a,
      57,   12,   12,   12, 0x0a,
      78,   12,   12,   12, 0x0a,
      98,   12,   12,   12, 0x0a,
     116,   12,   12,   12, 0x0a,
     140,   12,   12,   12, 0x0a,
     170,   12,   12,   12, 0x0a,
     202,   12,   12,   12, 0x0a,
     234,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_IDMT_widget[] = {
    "IDMT_widget\0\0sltAddFile()\0sltRemoveFile()\0"
    "sltRemoveAll()\0sltStartConversion()\0"
    "sltSetSubjectPath()\0sltSetImagePath()\0"
    "sltSelectOutputFolder()\0"
    "sltAbleQualitySelection(bool)\0"
    "sltAblePdetectedSelection(bool)\0"
    "sltAbleSmoothingSelection(bool)\0"
    "sltAbleCombiSelection(bool)\0"
};

void IDMT_widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        IDMT_widget *_t = static_cast<IDMT_widget *>(_o);
        switch (_id) {
        case 0: _t->sltAddFile(); break;
        case 1: _t->sltRemoveFile(); break;
        case 2: _t->sltRemoveAll(); break;
        case 3: _t->sltStartConversion(); break;
        case 4: _t->sltSetSubjectPath(); break;
        case 5: _t->sltSetImagePath(); break;
        case 6: _t->sltSelectOutputFolder(); break;
        case 7: _t->sltAbleQualitySelection((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->sltAblePdetectedSelection((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->sltAbleSmoothingSelection((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->sltAbleCombiSelection((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData IDMT_widget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject IDMT_widget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_IDMT_widget,
      qt_meta_data_IDMT_widget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &IDMT_widget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *IDMT_widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *IDMT_widget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_IDMT_widget))
        return static_cast<void*>(const_cast< IDMT_widget*>(this));
    if (!strcmp(_clname, "Plugin_widget"))
        return static_cast< Plugin_widget*>(const_cast< IDMT_widget*>(this));
    if (!strcmp(_clname, "org.test.Plugin_widget/1.0"))
        return static_cast< Plugin_widget*>(const_cast< IDMT_widget*>(this));
    return QWidget::qt_metacast(_clname);
}

int IDMT_widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
