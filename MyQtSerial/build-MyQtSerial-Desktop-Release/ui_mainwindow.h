/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_28;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_2;
    QPushButton *Connect_serial_button;
    QPushButton *disconnect_serial_button;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEdit;
    QPushButton *send_button;
    QTextEdit *textEdit;
    QFrame *line_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_11;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_2;
    QLineEdit *lineEdit_m1;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *M1Left_button;
    QPushButton *M1Right_button;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLineEdit *lineEdit_m2;
    QHBoxLayout *horizontalLayout_14;
    QPushButton *M2Left_button;
    QPushButton *M2Right_button;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_4;
    QLineEdit *lineEdit_m3;
    QHBoxLayout *horizontalLayout_16;
    QPushButton *M3Left_button;
    QPushButton *M3Right_button;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_5;
    QLineEdit *lineEdit_m4;
    QHBoxLayout *horizontalLayout_17;
    QPushButton *M4Left_button;
    QPushButton *M4Right_button;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_7;
    QLineEdit *lineEdit_m5;
    QHBoxLayout *horizontalLayout_18;
    QPushButton *M5Left_button;
    QPushButton *M5Right_button;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_6;
    QLineEdit *lineEdit_m6;
    QHBoxLayout *horizontalLayout_15;
    QPushButton *M6_ON_button;
    QPushButton *M6_OFF_button;
    QVBoxLayout *verticalLayout_6;
    QPushButton *send_CMD_button;
    QPushButton *fk_calculation_button;
    QSpacerItem *verticalSpacer_3;
    QFrame *line_3;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_13;
    QHBoxLayout *horizontalLayout_26;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_23;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_8;
    QLineEdit *lineEdit_x;
    QHBoxLayout *horizontalLayout_12;
    QPushButton *X_Left_button;
    QPushButton *X_Right_button;
    QHBoxLayout *horizontalLayout_25;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_9;
    QLineEdit *lineEdit_y;
    QHBoxLayout *horizontalLayout_21;
    QPushButton *Y_Left_button;
    QPushButton *Y_Right_button;
    QHBoxLayout *horizontalLayout_24;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_10;
    QLineEdit *lineEdit_z;
    QHBoxLayout *horizontalLayout_22;
    QPushButton *Z_Left_button;
    QPushButton *Z_Right_button;
    QVBoxLayout *verticalLayout_5;
    QPushButton *MyTestIK_button;
    QHBoxLayout *horizontalLayout_20;
    QHBoxLayout *horizontalLayout_13;
    QLineEdit *lineEdit_ID;
    QPushButton *Run_button;
    QFrame *line;
    QTextEdit *textEdit_endPointcontrol;
    QFrame *line_4;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_14;
    QHBoxLayout *horizontalLayout_27;
    QPushButton *visionServo_open_button;
    QPushButton *visionServo_close_button;
    QSpacerItem *horizontalSpacer;
    QPushButton *ResetRobot_button;
    QLabel *image_Label;
    QSpacerItem *verticalSpacer;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1442, 719);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_28 = new QHBoxLayout(centralWidget);
        horizontalLayout_28->setSpacing(6);
        horizontalLayout_28->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_28->setObjectName(QStringLiteral("horizontalLayout_28"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEdit_2 = new QLineEdit(centralWidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        horizontalLayout->addWidget(lineEdit_2);

        Connect_serial_button = new QPushButton(centralWidget);
        Connect_serial_button->setObjectName(QStringLiteral("Connect_serial_button"));

        horizontalLayout->addWidget(Connect_serial_button);

        disconnect_serial_button = new QPushButton(centralWidget);
        disconnect_serial_button->setObjectName(QStringLiteral("disconnect_serial_button"));

        horizontalLayout->addWidget(disconnect_serial_button);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout_2->addWidget(lineEdit);

        send_button = new QPushButton(centralWidget);
        send_button->setObjectName(QStringLiteral("send_button"));

        horizontalLayout_2->addWidget(send_button);


        verticalLayout->addLayout(horizontalLayout_2);

        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        verticalLayout->addWidget(textEdit);


        horizontalLayout_28->addLayout(verticalLayout);

        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_28->addWidget(line_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QStringLiteral("label_11"));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        label_11->setFont(font);
        label_11->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_11);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_5->addWidget(label_2);

        lineEdit_m1 = new QLineEdit(centralWidget);
        lineEdit_m1->setObjectName(QStringLiteral("lineEdit_m1"));

        horizontalLayout_5->addWidget(lineEdit_m1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        M1Left_button = new QPushButton(centralWidget);
        M1Left_button->setObjectName(QStringLiteral("M1Left_button"));
        M1Left_button->setMinimumSize(QSize(35, 0));
        M1Left_button->setMaximumSize(QSize(35, 16777215));

        horizontalLayout_3->addWidget(M1Left_button);

        M1Right_button = new QPushButton(centralWidget);
        M1Right_button->setObjectName(QStringLiteral("M1Right_button"));
        M1Right_button->setMaximumSize(QSize(35, 16777215));

        horizontalLayout_3->addWidget(M1Right_button);


        horizontalLayout_5->addLayout(horizontalLayout_3);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_4->addWidget(label_3);

        lineEdit_m2 = new QLineEdit(centralWidget);
        lineEdit_m2->setObjectName(QStringLiteral("lineEdit_m2"));

        horizontalLayout_4->addWidget(lineEdit_m2);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(0);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        M2Left_button = new QPushButton(centralWidget);
        M2Left_button->setObjectName(QStringLiteral("M2Left_button"));
        M2Left_button->setMinimumSize(QSize(35, 0));
        M2Left_button->setMaximumSize(QSize(35, 16777215));

        horizontalLayout_14->addWidget(M2Left_button);

        M2Right_button = new QPushButton(centralWidget);
        M2Right_button->setObjectName(QStringLiteral("M2Right_button"));
        M2Right_button->setMaximumSize(QSize(35, 16777215));

        horizontalLayout_14->addWidget(M2Right_button);


        horizontalLayout_4->addLayout(horizontalLayout_14);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_7->addWidget(label_4);

        lineEdit_m3 = new QLineEdit(centralWidget);
        lineEdit_m3->setObjectName(QStringLiteral("lineEdit_m3"));

        horizontalLayout_7->addWidget(lineEdit_m3);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(0);
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        M3Left_button = new QPushButton(centralWidget);
        M3Left_button->setObjectName(QStringLiteral("M3Left_button"));
        M3Left_button->setMinimumSize(QSize(35, 0));
        M3Left_button->setMaximumSize(QSize(35, 16777215));

        horizontalLayout_16->addWidget(M3Left_button);

        M3Right_button = new QPushButton(centralWidget);
        M3Right_button->setObjectName(QStringLiteral("M3Right_button"));
        M3Right_button->setMaximumSize(QSize(35, 16777215));

        horizontalLayout_16->addWidget(M3Right_button);


        horizontalLayout_7->addLayout(horizontalLayout_16);


        verticalLayout_2->addLayout(horizontalLayout_7);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_6->addWidget(label_5);

        lineEdit_m4 = new QLineEdit(centralWidget);
        lineEdit_m4->setObjectName(QStringLiteral("lineEdit_m4"));

        horizontalLayout_6->addWidget(lineEdit_m4);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(0);
        horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
        M4Left_button = new QPushButton(centralWidget);
        M4Left_button->setObjectName(QStringLiteral("M4Left_button"));
        M4Left_button->setMinimumSize(QSize(35, 0));
        M4Left_button->setMaximumSize(QSize(35, 16777215));

        horizontalLayout_17->addWidget(M4Left_button);

        M4Right_button = new QPushButton(centralWidget);
        M4Right_button->setObjectName(QStringLiteral("M4Right_button"));
        M4Right_button->setMaximumSize(QSize(35, 16777215));

        horizontalLayout_17->addWidget(M4Right_button);


        horizontalLayout_6->addLayout(horizontalLayout_17);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setObjectName(QStringLiteral("horizontalLayout_19"));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_19->addWidget(label_7);

        lineEdit_m5 = new QLineEdit(centralWidget);
        lineEdit_m5->setObjectName(QStringLiteral("lineEdit_m5"));

        horizontalLayout_19->addWidget(lineEdit_m5);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(0);
        horizontalLayout_18->setObjectName(QStringLiteral("horizontalLayout_18"));
        M5Left_button = new QPushButton(centralWidget);
        M5Left_button->setObjectName(QStringLiteral("M5Left_button"));
        M5Left_button->setMinimumSize(QSize(35, 0));
        M5Left_button->setMaximumSize(QSize(35, 16777215));

        horizontalLayout_18->addWidget(M5Left_button);

        M5Right_button = new QPushButton(centralWidget);
        M5Right_button->setObjectName(QStringLiteral("M5Right_button"));
        M5Right_button->setMaximumSize(QSize(35, 16777215));

        horizontalLayout_18->addWidget(M5Right_button);


        horizontalLayout_19->addLayout(horizontalLayout_18);


        verticalLayout_2->addLayout(horizontalLayout_19);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_8->addWidget(label_6);

        lineEdit_m6 = new QLineEdit(centralWidget);
        lineEdit_m6->setObjectName(QStringLiteral("lineEdit_m6"));

        horizontalLayout_8->addWidget(lineEdit_m6);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(0);
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        M6_ON_button = new QPushButton(centralWidget);
        M6_ON_button->setObjectName(QStringLiteral("M6_ON_button"));
        M6_ON_button->setMinimumSize(QSize(35, 0));
        M6_ON_button->setMaximumSize(QSize(35, 16777215));

        horizontalLayout_15->addWidget(M6_ON_button);

        M6_OFF_button = new QPushButton(centralWidget);
        M6_OFF_button->setObjectName(QStringLiteral("M6_OFF_button"));
        M6_OFF_button->setMaximumSize(QSize(35, 16777215));

        horizontalLayout_15->addWidget(M6_OFF_button);


        horizontalLayout_8->addLayout(horizontalLayout_15);


        verticalLayout_2->addLayout(horizontalLayout_8);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        send_CMD_button = new QPushButton(centralWidget);
        send_CMD_button->setObjectName(QStringLiteral("send_CMD_button"));
        send_CMD_button->setMinimumSize(QSize(0, 80));

        verticalLayout_6->addWidget(send_CMD_button);

        fk_calculation_button = new QPushButton(centralWidget);
        fk_calculation_button->setObjectName(QStringLiteral("fk_calculation_button"));
        fk_calculation_button->setMinimumSize(QSize(0, 80));

        verticalLayout_6->addWidget(fk_calculation_button);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_3);


        verticalLayout_2->addLayout(verticalLayout_6);


        horizontalLayout_28->addLayout(verticalLayout_2);

        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);

        horizontalLayout_28->addWidget(line_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label_13 = new QLabel(centralWidget);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setFont(font);
        label_13->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(label_13);

        horizontalLayout_26 = new QHBoxLayout();
        horizontalLayout_26->setSpacing(6);
        horizontalLayout_26->setObjectName(QStringLiteral("horizontalLayout_26"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setSpacing(6);
        horizontalLayout_23->setObjectName(QStringLiteral("horizontalLayout_23"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_9->addWidget(label_8);

        lineEdit_x = new QLineEdit(centralWidget);
        lineEdit_x->setObjectName(QStringLiteral("lineEdit_x"));

        horizontalLayout_9->addWidget(lineEdit_x);


        horizontalLayout_23->addLayout(horizontalLayout_9);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(0);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        X_Left_button = new QPushButton(centralWidget);
        X_Left_button->setObjectName(QStringLiteral("X_Left_button"));
        X_Left_button->setMinimumSize(QSize(35, 0));
        X_Left_button->setMaximumSize(QSize(35, 16777215));

        horizontalLayout_12->addWidget(X_Left_button);

        X_Right_button = new QPushButton(centralWidget);
        X_Right_button->setObjectName(QStringLiteral("X_Right_button"));
        X_Right_button->setMaximumSize(QSize(35, 16777215));

        horizontalLayout_12->addWidget(X_Right_button);


        horizontalLayout_23->addLayout(horizontalLayout_12);


        verticalLayout_3->addLayout(horizontalLayout_23);

        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setSpacing(6);
        horizontalLayout_25->setObjectName(QStringLiteral("horizontalLayout_25"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_10->addWidget(label_9);

        lineEdit_y = new QLineEdit(centralWidget);
        lineEdit_y->setObjectName(QStringLiteral("lineEdit_y"));

        horizontalLayout_10->addWidget(lineEdit_y);


        horizontalLayout_25->addLayout(horizontalLayout_10);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setSpacing(0);
        horizontalLayout_21->setObjectName(QStringLiteral("horizontalLayout_21"));
        Y_Left_button = new QPushButton(centralWidget);
        Y_Left_button->setObjectName(QStringLiteral("Y_Left_button"));
        Y_Left_button->setMinimumSize(QSize(35, 0));
        Y_Left_button->setMaximumSize(QSize(35, 16777215));

        horizontalLayout_21->addWidget(Y_Left_button);

        Y_Right_button = new QPushButton(centralWidget);
        Y_Right_button->setObjectName(QStringLiteral("Y_Right_button"));
        Y_Right_button->setMaximumSize(QSize(35, 16777215));

        horizontalLayout_21->addWidget(Y_Right_button);


        horizontalLayout_25->addLayout(horizontalLayout_21);


        verticalLayout_3->addLayout(horizontalLayout_25);

        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setSpacing(6);
        horizontalLayout_24->setObjectName(QStringLiteral("horizontalLayout_24"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_11->addWidget(label_10);

        lineEdit_z = new QLineEdit(centralWidget);
        lineEdit_z->setObjectName(QStringLiteral("lineEdit_z"));

        horizontalLayout_11->addWidget(lineEdit_z);


        horizontalLayout_24->addLayout(horizontalLayout_11);

        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setSpacing(0);
        horizontalLayout_22->setObjectName(QStringLiteral("horizontalLayout_22"));
        Z_Left_button = new QPushButton(centralWidget);
        Z_Left_button->setObjectName(QStringLiteral("Z_Left_button"));
        Z_Left_button->setMinimumSize(QSize(35, 0));
        Z_Left_button->setMaximumSize(QSize(35, 16777215));

        horizontalLayout_22->addWidget(Z_Left_button);

        Z_Right_button = new QPushButton(centralWidget);
        Z_Right_button->setObjectName(QStringLiteral("Z_Right_button"));
        Z_Right_button->setMaximumSize(QSize(35, 16777215));

        horizontalLayout_22->addWidget(Z_Right_button);


        horizontalLayout_24->addLayout(horizontalLayout_22);


        verticalLayout_3->addLayout(horizontalLayout_24);


        horizontalLayout_26->addLayout(verticalLayout_3);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        MyTestIK_button = new QPushButton(centralWidget);
        MyTestIK_button->setObjectName(QStringLiteral("MyTestIK_button"));

        verticalLayout_5->addWidget(MyTestIK_button);


        horizontalLayout_26->addLayout(verticalLayout_5);


        verticalLayout_4->addLayout(horizontalLayout_26);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setObjectName(QStringLiteral("horizontalLayout_20"));

        verticalLayout_4->addLayout(horizontalLayout_20);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        lineEdit_ID = new QLineEdit(centralWidget);
        lineEdit_ID->setObjectName(QStringLiteral("lineEdit_ID"));

        horizontalLayout_13->addWidget(lineEdit_ID);

        Run_button = new QPushButton(centralWidget);
        Run_button->setObjectName(QStringLiteral("Run_button"));

        horizontalLayout_13->addWidget(Run_button);


        verticalLayout_4->addLayout(horizontalLayout_13);

        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_4->addWidget(line);

        textEdit_endPointcontrol = new QTextEdit(centralWidget);
        textEdit_endPointcontrol->setObjectName(QStringLiteral("textEdit_endPointcontrol"));

        verticalLayout_4->addWidget(textEdit_endPointcontrol);


        horizontalLayout_28->addLayout(verticalLayout_4);

        line_4 = new QFrame(centralWidget);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);

        horizontalLayout_28->addWidget(line_4);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        label_14 = new QLabel(centralWidget);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setFont(font);
        label_14->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(label_14);

        horizontalLayout_27 = new QHBoxLayout();
        horizontalLayout_27->setSpacing(6);
        horizontalLayout_27->setObjectName(QStringLiteral("horizontalLayout_27"));
        visionServo_open_button = new QPushButton(centralWidget);
        visionServo_open_button->setObjectName(QStringLiteral("visionServo_open_button"));

        horizontalLayout_27->addWidget(visionServo_open_button);

        visionServo_close_button = new QPushButton(centralWidget);
        visionServo_close_button->setObjectName(QStringLiteral("visionServo_close_button"));

        horizontalLayout_27->addWidget(visionServo_close_button);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_27->addItem(horizontalSpacer);

        ResetRobot_button = new QPushButton(centralWidget);
        ResetRobot_button->setObjectName(QStringLiteral("ResetRobot_button"));

        horizontalLayout_27->addWidget(ResetRobot_button);


        verticalLayout_7->addLayout(horizontalLayout_27);

        image_Label = new QLabel(centralWidget);
        image_Label->setObjectName(QStringLiteral("image_Label"));
        image_Label->setMinimumSize(QSize(640, 480));
        image_Label->setStyleSheet(QStringLiteral("background-color: rgb(13, 13, 13);"));

        verticalLayout_7->addWidget(image_Label);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer);


        horizontalLayout_28->addLayout(verticalLayout_7);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1442, 27));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        QWidget::setTabOrder(lineEdit_m1, lineEdit_m2);
        QWidget::setTabOrder(lineEdit_m2, lineEdit_m3);
        QWidget::setTabOrder(lineEdit_m3, lineEdit_m4);
        QWidget::setTabOrder(lineEdit_m4, lineEdit_m5);
        QWidget::setTabOrder(lineEdit_m5, lineEdit_m6);
        QWidget::setTabOrder(lineEdit_m6, lineEdit_x);
        QWidget::setTabOrder(lineEdit_x, lineEdit_y);
        QWidget::setTabOrder(lineEdit_y, lineEdit_z);
        QWidget::setTabOrder(lineEdit_z, lineEdit_ID);
        QWidget::setTabOrder(lineEdit_ID, M3Right_button);
        QWidget::setTabOrder(M3Right_button, M3Left_button);
        QWidget::setTabOrder(M3Left_button, M1Left_button);
        QWidget::setTabOrder(M1Left_button, textEdit);
        QWidget::setTabOrder(textEdit, M4Left_button);
        QWidget::setTabOrder(M4Left_button, M4Right_button);
        QWidget::setTabOrder(M4Right_button, lineEdit_2);
        QWidget::setTabOrder(lineEdit_2, M5Left_button);
        QWidget::setTabOrder(M5Left_button, M5Right_button);
        QWidget::setTabOrder(M5Right_button, disconnect_serial_button);
        QWidget::setTabOrder(disconnect_serial_button, M6_ON_button);
        QWidget::setTabOrder(M6_ON_button, M6_OFF_button);
        QWidget::setTabOrder(M6_OFF_button, send_CMD_button);
        QWidget::setTabOrder(send_CMD_button, fk_calculation_button);
        QWidget::setTabOrder(fk_calculation_button, M1Right_button);
        QWidget::setTabOrder(M1Right_button, Connect_serial_button);
        QWidget::setTabOrder(Connect_serial_button, M2Left_button);
        QWidget::setTabOrder(M2Left_button, MyTestIK_button);
        QWidget::setTabOrder(MyTestIK_button, M2Right_button);
        QWidget::setTabOrder(M2Right_button, Run_button);
        QWidget::setTabOrder(Run_button, textEdit_endPointcontrol);
        QWidget::setTabOrder(textEdit_endPointcontrol, lineEdit);
        QWidget::setTabOrder(lineEdit, send_button);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Water Grasping Software", 0));
        label->setText(QApplication::translate("MainWindow", "Port:", 0));
        lineEdit_2->setText(QApplication::translate("MainWindow", "/dev/ttyACM0", 0));
        Connect_serial_button->setText(QApplication::translate("MainWindow", "Connect", 0));
        disconnect_serial_button->setText(QApplication::translate("MainWindow", "Disconnect", 0));
        lineEdit->setText(QApplication::translate("MainWindow", "Enter a string here...", 0));
        send_button->setText(QApplication::translate("MainWindow", "Send", 0));
        label_11->setText(QApplication::translate("MainWindow", "Joint Control", 0));
        label_2->setText(QApplication::translate("MainWindow", "Motor1", 0));
        lineEdit_m1->setText(QApplication::translate("MainWindow", "0", 0));
        M1Left_button->setText(QApplication::translate("MainWindow", "<<<", 0));
        M1Right_button->setText(QApplication::translate("MainWindow", ">>>", 0));
        label_3->setText(QApplication::translate("MainWindow", "Motor2", 0));
        lineEdit_m2->setText(QApplication::translate("MainWindow", "38", 0));
        M2Left_button->setText(QApplication::translate("MainWindow", "<<<", 0));
        M2Right_button->setText(QApplication::translate("MainWindow", ">>>", 0));
        label_4->setText(QApplication::translate("MainWindow", "Motor3", 0));
        lineEdit_m3->setText(QApplication::translate("MainWindow", "-90", 0));
        M3Left_button->setText(QApplication::translate("MainWindow", "<<<", 0));
        M3Right_button->setText(QApplication::translate("MainWindow", ">>>", 0));
        label_5->setText(QApplication::translate("MainWindow", "Motor4", 0));
        lineEdit_m4->setText(QApplication::translate("MainWindow", "-90", 0));
        M4Left_button->setText(QApplication::translate("MainWindow", "<<<", 0));
        M4Right_button->setText(QApplication::translate("MainWindow", ">>>", 0));
        label_7->setText(QApplication::translate("MainWindow", "Motor5", 0));
        lineEdit_m5->setText(QApplication::translate("MainWindow", "0", 0));
        M5Left_button->setText(QApplication::translate("MainWindow", "<<<", 0));
        M5Right_button->setText(QApplication::translate("MainWindow", ">>>", 0));
        label_6->setText(QApplication::translate("MainWindow", "Motor6", 0));
        lineEdit_m6->setText(QApplication::translate("MainWindow", "1", 0));
        M6_ON_button->setText(QApplication::translate("MainWindow", "ON", 0));
        M6_OFF_button->setText(QApplication::translate("MainWindow", "OFF", 0));
        send_CMD_button->setText(QApplication::translate("MainWindow", "SendCMD", 0));
        fk_calculation_button->setText(QApplication::translate("MainWindow", "FK Calculation", 0));
        label_13->setText(QApplication::translate("MainWindow", "End Point Control", 0));
        label_8->setText(QApplication::translate("MainWindow", "X:", 0));
        lineEdit_x->setText(QApplication::translate("MainWindow", "0", 0));
        X_Left_button->setText(QApplication::translate("MainWindow", "<<<", 0));
        X_Right_button->setText(QApplication::translate("MainWindow", ">>>", 0));
        label_9->setText(QApplication::translate("MainWindow", "Y:", 0));
        lineEdit_y->setText(QApplication::translate("MainWindow", "0", 0));
        Y_Left_button->setText(QApplication::translate("MainWindow", "<<<", 0));
        Y_Right_button->setText(QApplication::translate("MainWindow", ">>>", 0));
        label_10->setText(QApplication::translate("MainWindow", "Z:", 0));
        lineEdit_z->setText(QApplication::translate("MainWindow", "515", 0));
        Z_Left_button->setText(QApplication::translate("MainWindow", "<<<", 0));
        Z_Right_button->setText(QApplication::translate("MainWindow", ">>>", 0));
        MyTestIK_button->setText(QApplication::translate("MainWindow", "Compute", 0));
        lineEdit_ID->setText(QApplication::translate("MainWindow", "0", 0));
        Run_button->setText(QApplication::translate("MainWindow", "Run", 0));
        label_14->setText(QApplication::translate("MainWindow", "Vision Servo", 0));
        visionServo_open_button->setText(QApplication::translate("MainWindow", "open", 0));
        visionServo_close_button->setText(QApplication::translate("MainWindow", "close", 0));
        ResetRobot_button->setText(QApplication::translate("MainWindow", "ResetRobot", 0));
        image_Label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
