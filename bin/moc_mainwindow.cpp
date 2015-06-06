/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_RenderArea_t {
    QByteArrayData data[1];
    char stringdata[11];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RenderArea_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RenderArea_t qt_meta_stringdata_RenderArea = {
    {
QT_MOC_LITERAL(0, 0, 10)
    },
    "RenderArea"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RenderArea[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void RenderArea::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject RenderArea::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_RenderArea.data,
      qt_meta_data_RenderArea,  qt_static_metacall, 0, 0}
};


const QMetaObject *RenderArea::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RenderArea::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RenderArea.stringdata))
        return static_cast<void*>(const_cast< RenderArea*>(this));
    return QWidget::qt_metacast(_clname);
}

int RenderArea::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[31];
    char stringdata[579];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 21),
QT_MOC_LITERAL(2, 33, 0),
QT_MOC_LITERAL(3, 34, 21),
QT_MOC_LITERAL(4, 56, 21),
QT_MOC_LITERAL(5, 78, 21),
QT_MOC_LITERAL(6, 100, 19),
QT_MOC_LITERAL(7, 120, 22),
QT_MOC_LITERAL(8, 143, 22),
QT_MOC_LITERAL(9, 166, 23),
QT_MOC_LITERAL(10, 190, 25),
QT_MOC_LITERAL(11, 216, 22),
QT_MOC_LITERAL(12, 239, 22),
QT_MOC_LITERAL(13, 262, 23),
QT_MOC_LITERAL(14, 286, 25),
QT_MOC_LITERAL(15, 312, 13),
QT_MOC_LITERAL(16, 326, 14),
QT_MOC_LITERAL(17, 341, 14),
QT_MOC_LITERAL(18, 356, 13),
QT_MOC_LITERAL(19, 370, 14),
QT_MOC_LITERAL(20, 385, 14),
QT_MOC_LITERAL(21, 400, 15),
QT_MOC_LITERAL(22, 416, 15),
QT_MOC_LITERAL(23, 432, 20),
QT_MOC_LITERAL(24, 453, 21),
QT_MOC_LITERAL(25, 475, 15),
QT_MOC_LITERAL(26, 491, 15),
QT_MOC_LITERAL(27, 507, 15),
QT_MOC_LITERAL(28, 523, 16),
QT_MOC_LITERAL(29, 540, 16),
QT_MOC_LITERAL(30, 557, 21)
    },
    "MainWindow\0on_image1Open_clicked\0\0"
    "on_image1Save_clicked\0on_Image2Open_clicked\0"
    "on_Image2Save_clicked\0on_calcPSNR_clicked\0"
    "on_image1Black_clicked\0on_image1White_clicked\0"
    "on_image1GrayWA_clicked\0"
    "on_image1GrayCCIR_clicked\0"
    "on_image2Black_clicked\0on_image2White_clicked\0"
    "on_image2GrayWA_clicked\0"
    "on_image2GrayCCIR_clicked\0on_Y1_clicked\0"
    "on_Cb1_clicked\0on_Cr1_clicked\0"
    "on_Y2_clicked\0on_Cb2_clicked\0"
    "on_Cr2_clicked\0on_RGB1_clicked\0"
    "on_RGB2_clicked\0on_transform_clicked\0"
    "on_transform2_clicked\0on_dsCb_clicked\0"
    "on_dsCr_clicked\0on_dctY_clicked\0"
    "on_dctCb_clicked\0on_dctCr_clicked\0"
    "on_pushButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      29,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  159,    2, 0x08 /* Private */,
       3,    0,  160,    2, 0x08 /* Private */,
       4,    0,  161,    2, 0x08 /* Private */,
       5,    0,  162,    2, 0x08 /* Private */,
       6,    0,  163,    2, 0x08 /* Private */,
       7,    0,  164,    2, 0x08 /* Private */,
       8,    0,  165,    2, 0x08 /* Private */,
       9,    0,  166,    2, 0x08 /* Private */,
      10,    0,  167,    2, 0x08 /* Private */,
      11,    0,  168,    2, 0x08 /* Private */,
      12,    0,  169,    2, 0x08 /* Private */,
      13,    0,  170,    2, 0x08 /* Private */,
      14,    0,  171,    2, 0x08 /* Private */,
      15,    0,  172,    2, 0x08 /* Private */,
      16,    0,  173,    2, 0x08 /* Private */,
      17,    0,  174,    2, 0x08 /* Private */,
      18,    0,  175,    2, 0x08 /* Private */,
      19,    0,  176,    2, 0x08 /* Private */,
      20,    0,  177,    2, 0x08 /* Private */,
      21,    0,  178,    2, 0x08 /* Private */,
      22,    0,  179,    2, 0x08 /* Private */,
      23,    0,  180,    2, 0x08 /* Private */,
      24,    0,  181,    2, 0x08 /* Private */,
      25,    0,  182,    2, 0x08 /* Private */,
      26,    0,  183,    2, 0x08 /* Private */,
      27,    0,  184,    2, 0x08 /* Private */,
      28,    0,  185,    2, 0x08 /* Private */,
      29,    0,  186,    2, 0x08 /* Private */,
      30,    0,  187,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->on_image1Open_clicked(); break;
        case 1: _t->on_image1Save_clicked(); break;
        case 2: _t->on_Image2Open_clicked(); break;
        case 3: _t->on_Image2Save_clicked(); break;
        case 4: _t->on_calcPSNR_clicked(); break;
        case 5: _t->on_image1Black_clicked(); break;
        case 6: _t->on_image1White_clicked(); break;
        case 7: _t->on_image1GrayWA_clicked(); break;
        case 8: _t->on_image1GrayCCIR_clicked(); break;
        case 9: _t->on_image2Black_clicked(); break;
        case 10: _t->on_image2White_clicked(); break;
        case 11: _t->on_image2GrayWA_clicked(); break;
        case 12: _t->on_image2GrayCCIR_clicked(); break;
        case 13: _t->on_Y1_clicked(); break;
        case 14: _t->on_Cb1_clicked(); break;
        case 15: _t->on_Cr1_clicked(); break;
        case 16: _t->on_Y2_clicked(); break;
        case 17: _t->on_Cb2_clicked(); break;
        case 18: _t->on_Cr2_clicked(); break;
        case 19: _t->on_RGB1_clicked(); break;
        case 20: _t->on_RGB2_clicked(); break;
        case 21: _t->on_transform_clicked(); break;
        case 22: _t->on_transform2_clicked(); break;
        case 23: _t->on_dsCb_clicked(); break;
        case 24: _t->on_dsCr_clicked(); break;
        case 25: _t->on_dctY_clicked(); break;
        case 26: _t->on_dctCb_clicked(); break;
        case 27: _t->on_dctCr_clicked(); break;
        case 28: _t->on_pushButton_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 29)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 29;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 29)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 29;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
