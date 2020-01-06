/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../MyQtSerial/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[55];
    char stringdata0[1148];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 14), // "serialReceived"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 32), // "on_Connect_serial_button_clicked"
QT_MOC_LITERAL(4, 60, 35), // "on_disconnect_serial_button_c..."
QT_MOC_LITERAL(5, 96, 22), // "on_send_button_clicked"
QT_MOC_LITERAL(6, 119, 26), // "on_send_CMD_button_clicked"
QT_MOC_LITERAL(7, 146, 32), // "on_fk_calculation_button_clicked"
QT_MOC_LITERAL(8, 179, 17), // "M1_moveLeft_Timer"
QT_MOC_LITERAL(9, 197, 18), // "M1_moveRight_Timer"
QT_MOC_LITERAL(10, 216, 24), // "on_M1Left_button_pressed"
QT_MOC_LITERAL(11, 241, 25), // "on_M1Left_button_released"
QT_MOC_LITERAL(12, 267, 25), // "on_M1Right_button_pressed"
QT_MOC_LITERAL(13, 293, 26), // "on_M1Right_button_released"
QT_MOC_LITERAL(14, 320, 17), // "M2_moveLeft_Timer"
QT_MOC_LITERAL(15, 338, 18), // "M2_moveRight_Timer"
QT_MOC_LITERAL(16, 357, 24), // "on_M2Left_button_pressed"
QT_MOC_LITERAL(17, 382, 25), // "on_M2Left_button_released"
QT_MOC_LITERAL(18, 408, 25), // "on_M2Right_button_pressed"
QT_MOC_LITERAL(19, 434, 26), // "on_M2Right_button_released"
QT_MOC_LITERAL(20, 461, 17), // "M3_moveLeft_Timer"
QT_MOC_LITERAL(21, 479, 18), // "M3_moveRight_Timer"
QT_MOC_LITERAL(22, 498, 24), // "on_M3Left_button_pressed"
QT_MOC_LITERAL(23, 523, 25), // "on_M3Left_button_released"
QT_MOC_LITERAL(24, 549, 25), // "on_M3Right_button_pressed"
QT_MOC_LITERAL(25, 575, 26), // "on_M3Right_button_released"
QT_MOC_LITERAL(26, 602, 17), // "M4_moveLeft_Timer"
QT_MOC_LITERAL(27, 620, 18), // "M4_moveRight_Timer"
QT_MOC_LITERAL(28, 639, 24), // "on_M4Left_button_pressed"
QT_MOC_LITERAL(29, 664, 25), // "on_M4Left_button_released"
QT_MOC_LITERAL(30, 690, 25), // "on_M4Right_button_pressed"
QT_MOC_LITERAL(31, 716, 26), // "on_M4Right_button_released"
QT_MOC_LITERAL(32, 743, 17), // "M5_moveLeft_Timer"
QT_MOC_LITERAL(33, 761, 18), // "M5_moveRight_Timer"
QT_MOC_LITERAL(34, 780, 24), // "on_M5Left_button_pressed"
QT_MOC_LITERAL(35, 805, 25), // "on_M5Left_button_released"
QT_MOC_LITERAL(36, 831, 25), // "on_M5Right_button_pressed"
QT_MOC_LITERAL(37, 857, 26), // "on_M5Right_button_released"
QT_MOC_LITERAL(38, 884, 23), // "on_M6_ON_button_clicked"
QT_MOC_LITERAL(39, 908, 24), // "on_M6_OFF_button_clicked"
QT_MOC_LITERAL(40, 933, 26), // "on_MyTestIK_button_clicked"
QT_MOC_LITERAL(41, 960, 21), // "on_Run_button_clicked"
QT_MOC_LITERAL(42, 982, 10), // "moveMotor1"
QT_MOC_LITERAL(43, 993, 2), // "Px"
QT_MOC_LITERAL(44, 996, 2), // "Py"
QT_MOC_LITERAL(45, 999, 2), // "Pz"
QT_MOC_LITERAL(46, 1002, 11), // "gripControl"
QT_MOC_LITERAL(47, 1014, 3), // "var"
QT_MOC_LITERAL(48, 1018, 7), // "moveToP"
QT_MOC_LITERAL(49, 1026, 11), // "updateFrame"
QT_MOC_LITERAL(50, 1038, 3), // "Mat"
QT_MOC_LITERAL(51, 1042, 5), // "image"
QT_MOC_LITERAL(52, 1048, 34), // "on_visionServo_open_button_cl..."
QT_MOC_LITERAL(53, 1083, 35), // "on_visionServo_close_button_c..."
QT_MOC_LITERAL(54, 1119, 28) // "on_ResetRobot_button_clicked"

    },
    "MainWindow\0serialReceived\0\0"
    "on_Connect_serial_button_clicked\0"
    "on_disconnect_serial_button_clicked\0"
    "on_send_button_clicked\0"
    "on_send_CMD_button_clicked\0"
    "on_fk_calculation_button_clicked\0"
    "M1_moveLeft_Timer\0M1_moveRight_Timer\0"
    "on_M1Left_button_pressed\0"
    "on_M1Left_button_released\0"
    "on_M1Right_button_pressed\0"
    "on_M1Right_button_released\0M2_moveLeft_Timer\0"
    "M2_moveRight_Timer\0on_M2Left_button_pressed\0"
    "on_M2Left_button_released\0"
    "on_M2Right_button_pressed\0"
    "on_M2Right_button_released\0M3_moveLeft_Timer\0"
    "M3_moveRight_Timer\0on_M3Left_button_pressed\0"
    "on_M3Left_button_released\0"
    "on_M3Right_button_pressed\0"
    "on_M3Right_button_released\0M4_moveLeft_Timer\0"
    "M4_moveRight_Timer\0on_M4Left_button_pressed\0"
    "on_M4Left_button_released\0"
    "on_M4Right_button_pressed\0"
    "on_M4Right_button_released\0M5_moveLeft_Timer\0"
    "M5_moveRight_Timer\0on_M5Left_button_pressed\0"
    "on_M5Left_button_released\0"
    "on_M5Right_button_pressed\0"
    "on_M5Right_button_released\0"
    "on_M6_ON_button_clicked\0"
    "on_M6_OFF_button_clicked\0"
    "on_MyTestIK_button_clicked\0"
    "on_Run_button_clicked\0moveMotor1\0Px\0"
    "Py\0Pz\0gripControl\0var\0moveToP\0updateFrame\0"
    "Mat\0image\0on_visionServo_open_button_clicked\0"
    "on_visionServo_close_button_clicked\0"
    "on_ResetRobot_button_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      47,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  249,    2, 0x08 /* Private */,
       3,    0,  250,    2, 0x08 /* Private */,
       4,    0,  251,    2, 0x08 /* Private */,
       5,    0,  252,    2, 0x08 /* Private */,
       6,    0,  253,    2, 0x08 /* Private */,
       7,    0,  254,    2, 0x08 /* Private */,
       8,    0,  255,    2, 0x08 /* Private */,
       9,    0,  256,    2, 0x08 /* Private */,
      10,    0,  257,    2, 0x08 /* Private */,
      11,    0,  258,    2, 0x08 /* Private */,
      12,    0,  259,    2, 0x08 /* Private */,
      13,    0,  260,    2, 0x08 /* Private */,
      14,    0,  261,    2, 0x08 /* Private */,
      15,    0,  262,    2, 0x08 /* Private */,
      16,    0,  263,    2, 0x08 /* Private */,
      17,    0,  264,    2, 0x08 /* Private */,
      18,    0,  265,    2, 0x08 /* Private */,
      19,    0,  266,    2, 0x08 /* Private */,
      20,    0,  267,    2, 0x08 /* Private */,
      21,    0,  268,    2, 0x08 /* Private */,
      22,    0,  269,    2, 0x08 /* Private */,
      23,    0,  270,    2, 0x08 /* Private */,
      24,    0,  271,    2, 0x08 /* Private */,
      25,    0,  272,    2, 0x08 /* Private */,
      26,    0,  273,    2, 0x08 /* Private */,
      27,    0,  274,    2, 0x08 /* Private */,
      28,    0,  275,    2, 0x08 /* Private */,
      29,    0,  276,    2, 0x08 /* Private */,
      30,    0,  277,    2, 0x08 /* Private */,
      31,    0,  278,    2, 0x08 /* Private */,
      32,    0,  279,    2, 0x08 /* Private */,
      33,    0,  280,    2, 0x08 /* Private */,
      34,    0,  281,    2, 0x08 /* Private */,
      35,    0,  282,    2, 0x08 /* Private */,
      36,    0,  283,    2, 0x08 /* Private */,
      37,    0,  284,    2, 0x08 /* Private */,
      38,    0,  285,    2, 0x08 /* Private */,
      39,    0,  286,    2, 0x08 /* Private */,
      40,    0,  287,    2, 0x08 /* Private */,
      41,    0,  288,    2, 0x08 /* Private */,
      42,    3,  289,    2, 0x08 /* Private */,
      46,    1,  296,    2, 0x08 /* Private */,
      48,    3,  299,    2, 0x08 /* Private */,
      49,    1,  306,    2, 0x08 /* Private */,
      52,    0,  309,    2, 0x08 /* Private */,
      53,    0,  310,    2, 0x08 /* Private */,
      54,    0,  311,    2, 0x08 /* Private */,

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
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   43,   44,   45,
    QMetaType::Void, QMetaType::Int,   47,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   43,   44,   45,
    QMetaType::Void, 0x80000000 | 50,   51,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->serialReceived(); break;
        case 1: _t->on_Connect_serial_button_clicked(); break;
        case 2: _t->on_disconnect_serial_button_clicked(); break;
        case 3: _t->on_send_button_clicked(); break;
        case 4: _t->on_send_CMD_button_clicked(); break;
        case 5: _t->on_fk_calculation_button_clicked(); break;
        case 6: _t->M1_moveLeft_Timer(); break;
        case 7: _t->M1_moveRight_Timer(); break;
        case 8: _t->on_M1Left_button_pressed(); break;
        case 9: _t->on_M1Left_button_released(); break;
        case 10: _t->on_M1Right_button_pressed(); break;
        case 11: _t->on_M1Right_button_released(); break;
        case 12: _t->M2_moveLeft_Timer(); break;
        case 13: _t->M2_moveRight_Timer(); break;
        case 14: _t->on_M2Left_button_pressed(); break;
        case 15: _t->on_M2Left_button_released(); break;
        case 16: _t->on_M2Right_button_pressed(); break;
        case 17: _t->on_M2Right_button_released(); break;
        case 18: _t->M3_moveLeft_Timer(); break;
        case 19: _t->M3_moveRight_Timer(); break;
        case 20: _t->on_M3Left_button_pressed(); break;
        case 21: _t->on_M3Left_button_released(); break;
        case 22: _t->on_M3Right_button_pressed(); break;
        case 23: _t->on_M3Right_button_released(); break;
        case 24: _t->M4_moveLeft_Timer(); break;
        case 25: _t->M4_moveRight_Timer(); break;
        case 26: _t->on_M4Left_button_pressed(); break;
        case 27: _t->on_M4Left_button_released(); break;
        case 28: _t->on_M4Right_button_pressed(); break;
        case 29: _t->on_M4Right_button_released(); break;
        case 30: _t->M5_moveLeft_Timer(); break;
        case 31: _t->M5_moveRight_Timer(); break;
        case 32: _t->on_M5Left_button_pressed(); break;
        case 33: _t->on_M5Left_button_released(); break;
        case 34: _t->on_M5Right_button_pressed(); break;
        case 35: _t->on_M5Right_button_released(); break;
        case 36: _t->on_M6_ON_button_clicked(); break;
        case 37: _t->on_M6_OFF_button_clicked(); break;
        case 38: _t->on_MyTestIK_button_clicked(); break;
        case 39: _t->on_Run_button_clicked(); break;
        case 40: _t->moveMotor1((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 41: _t->gripControl((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 42: _t->moveToP((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 43: _t->updateFrame((*reinterpret_cast< Mat(*)>(_a[1]))); break;
        case 44: _t->on_visionServo_open_button_clicked(); break;
        case 45: _t->on_visionServo_close_button_clicked(); break;
        case 46: _t->on_ResetRobot_button_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 47)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 47;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 47)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 47;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
