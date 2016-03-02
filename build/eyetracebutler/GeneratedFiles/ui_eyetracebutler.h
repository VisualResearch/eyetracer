/********************************************************************************
** Form generated from reading UI file 'eyetracebutler.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EYETRACEBUTLER_H
#define UI_EYETRACEBUTLER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Eyetracebutler_widget
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *ET_comboBox;
    QPushButton *ET_submitButton;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Eyetracebutler_widget)
    {
        if (Eyetracebutler_widget->objectName().isEmpty())
            Eyetracebutler_widget->setObjectName(QString::fromUtf8("Eyetracebutler_widget"));
        Eyetracebutler_widget->resize(660, 155);
        centralWidget = new QWidget(Eyetracebutler_widget);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        ET_comboBox = new QComboBox(groupBox);
        ET_comboBox->setObjectName(QString::fromUtf8("ET_comboBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ET_comboBox->sizePolicy().hasHeightForWidth());
        ET_comboBox->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(ET_comboBox);

        ET_submitButton = new QPushButton(groupBox);
        ET_submitButton->setObjectName(QString::fromUtf8("ET_submitButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(ET_submitButton->sizePolicy().hasHeightForWidth());
        ET_submitButton->setSizePolicy(sizePolicy1);
        ET_submitButton->setLayoutDirection(Qt::LeftToRight);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icons/Resources/button_blue_fastforward.png"), QSize(), QIcon::Normal, QIcon::Off);
        ET_submitButton->setIcon(icon);
        ET_submitButton->setAutoDefault(true);
        ET_submitButton->setDefault(true);

        horizontalLayout_2->addWidget(ET_submitButton);


        verticalLayout->addWidget(groupBox);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));

        verticalLayout->addLayout(verticalLayout_2);

        Eyetracebutler_widget->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Eyetracebutler_widget);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 660, 25));
        Eyetracebutler_widget->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Eyetracebutler_widget);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Eyetracebutler_widget->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Eyetracebutler_widget);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Eyetracebutler_widget->setStatusBar(statusBar);

        retranslateUi(Eyetracebutler_widget);
        QObject::connect(ET_submitButton, SIGNAL(clicked()), Eyetracebutler_widget, SLOT(refreshSurface()));

        QMetaObject::connectSlotsByName(Eyetracebutler_widget);
    } // setupUi

    void retranslateUi(QMainWindow *Eyetracebutler_widget)
    {
        Eyetracebutler_widget->setWindowTitle(QApplication::translate("Eyetracebutler_widget", "EyetraceButler", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("Eyetracebutler_widget", "Please select your Eyetracker", 0, QApplication::UnicodeUTF8));
        ET_submitButton->setText(QApplication::translate("Eyetracebutler_widget", "Submit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Eyetracebutler_widget: public Ui_Eyetracebutler_widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EYETRACEBUTLER_H
