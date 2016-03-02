/****************************************************************************
** Meta object code from reading C++ file 'Eyetracebutler_widget.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../inc/Eyetracebutler_widget.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Eyetracebutler_widget.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Eyetracebutler_widget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      23,   22,   22,   22, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Eyetracebutler_widget[] = {
    "Eyetracebutler_widget\0\0refreshSurface()\0"
};

void Eyetracebutler_widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Eyetracebutler_widget *_t = static_cast<Eyetracebutler_widget *>(_o);
        switch (_id) {
        case 0: _t->refreshSurface(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData Eyetracebutler_widget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Eyetracebutler_widget::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Eyetracebutler_widget,
      qt_meta_data_Eyetracebutler_widget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Eyetracebutler_widget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Eyetracebutler_widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Eyetracebutler_widget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Eyetracebutler_widget))
        return static_cast<void*>(const_cast< Eyetracebutler_widget*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Eyetracebutler_widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
