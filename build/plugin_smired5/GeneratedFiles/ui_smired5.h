/********************************************************************************
** Form generated from reading UI file 'smired5.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SMIRED5_H
#define UI_SMIRED5_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListView>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SMIRED5_widget
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *inputs_groupBox;
    QVBoxLayout *verticalLayout_3;
    QListView *listView;
    QHBoxLayout *L2b;
    QToolButton *addButton;
    QToolButton *removeButton;
    QToolButton *toolButton;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout;
    QLineEdit *subjectCsv_pathEdit;
    QToolButton *browseSubjectButton;
    QGroupBox *image_groupBox;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *L3a;
    QLineEdit *imageFolder_pathEdit;
    QToolButton *browseImageFolderButton;
    QCheckBox *convertOnlyAvaliablePictures_checkBox;
    QGroupBox *output_groupBox;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *L4a;
    QLineEdit *outputFolder_pathEdit;
    QToolButton *browseOutputFolderButton;
    QGroupBox *options_groupBox;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *quality_label1;
    QLineEdit *quality_lineEdit;
    QLabel *quality_label;
    QCheckBox *checkQuality_checkBox;
    QCheckBox *showhistogram_checkBox;
    QCheckBox *savehistogram_checkBox;
    QHBoxLayout *L5;
    QSpacerItem *horizontalSpacer;
    QToolButton *startButton;
    QToolButton *RemoveBlink;

    void setupUi(QWidget *SMIRED5_widget)
    {
        if (SMIRED5_widget->objectName().isEmpty())
            SMIRED5_widget->setObjectName(QString::fromUtf8("SMIRED5_widget"));
        SMIRED5_widget->resize(597, 592);
        verticalLayout = new QVBoxLayout(SMIRED5_widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(SMIRED5_widget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_2 = new QVBoxLayout(tab);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        inputs_groupBox = new QGroupBox(tab);
        inputs_groupBox->setObjectName(QString::fromUtf8("inputs_groupBox"));
        verticalLayout_3 = new QVBoxLayout(inputs_groupBox);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        listView = new QListView(inputs_groupBox);
        listView->setObjectName(QString::fromUtf8("listView"));

        verticalLayout_3->addWidget(listView);

        L2b = new QHBoxLayout();
        L2b->setSpacing(8);
        L2b->setObjectName(QString::fromUtf8("L2b"));
        L2b->setSizeConstraint(QLayout::SetDefaultConstraint);
        addButton = new QToolButton(inputs_groupBox);
        addButton->setObjectName(QString::fromUtf8("addButton"));
        addButton->setEnabled(true);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icons/Resources/button_blue_add.png"), QSize(), QIcon::Normal, QIcon::Off);
        addButton->setIcon(icon);
        addButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        L2b->addWidget(addButton);

        removeButton = new QToolButton(inputs_groupBox);
        removeButton->setObjectName(QString::fromUtf8("removeButton"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Icons/Resources/button_blue_delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        removeButton->setIcon(icon1);
        removeButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        L2b->addWidget(removeButton);

        toolButton = new QToolButton(inputs_groupBox);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Icons/Resources/button_blue_close.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton->setIcon(icon2);
        toolButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        L2b->addWidget(toolButton);


        verticalLayout_3->addLayout(L2b);


        verticalLayout_4->addWidget(inputs_groupBox);

        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_6 = new QVBoxLayout(groupBox);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        subjectCsv_pathEdit = new QLineEdit(groupBox);
        subjectCsv_pathEdit->setObjectName(QString::fromUtf8("subjectCsv_pathEdit"));

        horizontalLayout->addWidget(subjectCsv_pathEdit);

        browseSubjectButton = new QToolButton(groupBox);
        browseSubjectButton->setObjectName(QString::fromUtf8("browseSubjectButton"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Icons/Resources/folder_blue_stuffed.png"), QSize(), QIcon::Normal, QIcon::Off);
        browseSubjectButton->setIcon(icon3);
        browseSubjectButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        horizontalLayout->addWidget(browseSubjectButton);


        verticalLayout_6->addLayout(horizontalLayout);


        verticalLayout_4->addWidget(groupBox);

        image_groupBox = new QGroupBox(tab);
        image_groupBox->setObjectName(QString::fromUtf8("image_groupBox"));
        verticalLayout_7 = new QVBoxLayout(image_groupBox);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        L3a = new QHBoxLayout();
        L3a->setSpacing(6);
        L3a->setObjectName(QString::fromUtf8("L3a"));
        imageFolder_pathEdit = new QLineEdit(image_groupBox);
        imageFolder_pathEdit->setObjectName(QString::fromUtf8("imageFolder_pathEdit"));

        L3a->addWidget(imageFolder_pathEdit);

        browseImageFolderButton = new QToolButton(image_groupBox);
        browseImageFolderButton->setObjectName(QString::fromUtf8("browseImageFolderButton"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Icons/Resources/folder_blue.png"), QSize(), QIcon::Normal, QIcon::Off);
        browseImageFolderButton->setIcon(icon4);
        browseImageFolderButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        L3a->addWidget(browseImageFolderButton);


        verticalLayout_7->addLayout(L3a);

        convertOnlyAvaliablePictures_checkBox = new QCheckBox(image_groupBox);
        convertOnlyAvaliablePictures_checkBox->setObjectName(QString::fromUtf8("convertOnlyAvaliablePictures_checkBox"));
        convertOnlyAvaliablePictures_checkBox->setChecked(true);

        verticalLayout_7->addWidget(convertOnlyAvaliablePictures_checkBox);


        verticalLayout_4->addWidget(image_groupBox);

        output_groupBox = new QGroupBox(tab);
        output_groupBox->setObjectName(QString::fromUtf8("output_groupBox"));
        verticalLayout_9 = new QVBoxLayout(output_groupBox);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        L4a = new QHBoxLayout();
        L4a->setSpacing(6);
        L4a->setObjectName(QString::fromUtf8("L4a"));
        outputFolder_pathEdit = new QLineEdit(output_groupBox);
        outputFolder_pathEdit->setObjectName(QString::fromUtf8("outputFolder_pathEdit"));

        L4a->addWidget(outputFolder_pathEdit);

        browseOutputFolderButton = new QToolButton(output_groupBox);
        browseOutputFolderButton->setObjectName(QString::fromUtf8("browseOutputFolderButton"));
        browseOutputFolderButton->setIcon(icon4);
        browseOutputFolderButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        L4a->addWidget(browseOutputFolderButton);


        verticalLayout_9->addLayout(L4a);


        verticalLayout_4->addWidget(output_groupBox);

        options_groupBox = new QGroupBox(tab);
        options_groupBox->setObjectName(QString::fromUtf8("options_groupBox"));
        gridLayout = new QGridLayout(options_groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        quality_label1 = new QLabel(options_groupBox);
        quality_label1->setObjectName(QString::fromUtf8("quality_label1"));

        horizontalLayout_4->addWidget(quality_label1);

        quality_lineEdit = new QLineEdit(options_groupBox);
        quality_lineEdit->setObjectName(QString::fromUtf8("quality_lineEdit"));

        horizontalLayout_4->addWidget(quality_lineEdit);


        gridLayout_2->addLayout(horizontalLayout_4, 0, 1, 1, 1);

        quality_label = new QLabel(options_groupBox);
        quality_label->setObjectName(QString::fromUtf8("quality_label"));

        gridLayout_2->addWidget(quality_label, 1, 1, 1, 1);

        checkQuality_checkBox = new QCheckBox(options_groupBox);
        checkQuality_checkBox->setObjectName(QString::fromUtf8("checkQuality_checkBox"));
        checkQuality_checkBox->setChecked(true);

        gridLayout_2->addWidget(checkQuality_checkBox, 0, 0, 1, 1);

        showhistogram_checkBox = new QCheckBox(options_groupBox);
        showhistogram_checkBox->setObjectName(QString::fromUtf8("showhistogram_checkBox"));

        gridLayout_2->addWidget(showhistogram_checkBox, 1, 0, 1, 1);

        savehistogram_checkBox = new QCheckBox(options_groupBox);
        savehistogram_checkBox->setObjectName(QString::fromUtf8("savehistogram_checkBox"));

        gridLayout_2->addWidget(savehistogram_checkBox, 2, 0, 1, 1);


        gridLayout->addLayout(gridLayout_2, 0, 0, 1, 1);


        verticalLayout_4->addWidget(options_groupBox);

        L5 = new QHBoxLayout();
        L5->setSpacing(6);
        L5->setObjectName(QString::fromUtf8("L5"));
        L5->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        L5->addItem(horizontalSpacer);

        startButton = new QToolButton(tab);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Icons/Resources/button_blue_play.png"), QSize(), QIcon::Normal, QIcon::Off);
        startButton->setIcon(icon5);
        startButton->setPopupMode(QToolButton::DelayedPopup);
        startButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        L5->addWidget(startButton);

        RemoveBlink = new QToolButton(tab);
        RemoveBlink->setObjectName(QString::fromUtf8("RemoveBlink"));
        RemoveBlink->setIcon(icon5);
        RemoveBlink->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        L5->addWidget(RemoveBlink);


        verticalLayout_4->addLayout(L5);


        verticalLayout_2->addLayout(verticalLayout_4);

        tabWidget->addTab(tab, QString());

        verticalLayout->addWidget(tabWidget);


        retranslateUi(SMIRED5_widget);
        QObject::connect(addButton, SIGNAL(clicked()), SMIRED5_widget, SLOT(sltAddFile()));
        QObject::connect(removeButton, SIGNAL(clicked()), SMIRED5_widget, SLOT(sltRemoveFile()));
        QObject::connect(browseSubjectButton, SIGNAL(clicked()), SMIRED5_widget, SLOT(sltSetSubjectPath()));
        QObject::connect(browseImageFolderButton, SIGNAL(clicked()), SMIRED5_widget, SLOT(sltSetImageFolder()));
        QObject::connect(browseOutputFolderButton, SIGNAL(clicked()), SMIRED5_widget, SLOT(sltSelectOutputFolder()));
        QObject::connect(startButton, SIGNAL(clicked()), SMIRED5_widget, SLOT(sltStartFragmentation()));
        QObject::connect(checkQuality_checkBox, SIGNAL(toggled(bool)), SMIRED5_widget, SLOT(sltAbleSelection(bool)));
        QObject::connect(toolButton, SIGNAL(clicked()), SMIRED5_widget, SLOT(sltRemoveAll()));
        QObject::connect(RemoveBlink, SIGNAL(clicked()), SMIRED5_widget, SLOT(sltRemoveBlink()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SMIRED5_widget);
    } // setupUi

    void retranslateUi(QWidget *SMIRED5_widget)
    {
        SMIRED5_widget->setWindowTitle(QApplication::translate("SMIRED5_widget", "SMIRED5_widget", 0, QApplication::UnicodeUTF8));
        inputs_groupBox->setTitle(QApplication::translate("SMIRED5_widget", "Load files", 0, QApplication::UnicodeUTF8));
        addButton->setText(QApplication::translate("SMIRED5_widget", "Add", 0, QApplication::UnicodeUTF8));
        removeButton->setText(QApplication::translate("SMIRED5_widget", "Remove", 0, QApplication::UnicodeUTF8));
        toolButton->setText(QApplication::translate("SMIRED5_widget", "Remove all", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("SMIRED5_widget", "Set path to subject.csv", 0, QApplication::UnicodeUTF8));
        browseSubjectButton->setText(QApplication::translate("SMIRED5_widget", "Browse", 0, QApplication::UnicodeUTF8));
        image_groupBox->setTitle(QApplication::translate("SMIRED5_widget", "Set image folder", 0, QApplication::UnicodeUTF8));
        browseImageFolderButton->setText(QApplication::translate("SMIRED5_widget", "Browse", 0, QApplication::UnicodeUTF8));
        convertOnlyAvaliablePictures_checkBox->setText(QApplication::translate("SMIRED5_widget", "convert only files for available pictures", 0, QApplication::UnicodeUTF8));
        output_groupBox->setTitle(QApplication::translate("SMIRED5_widget", "Select output folder", 0, QApplication::UnicodeUTF8));
        browseOutputFolderButton->setText(QApplication::translate("SMIRED5_widget", "Browse", 0, QApplication::UnicodeUTF8));
        options_groupBox->setTitle(QApplication::translate("SMIRED5_widget", "Options", 0, QApplication::UnicodeUTF8));
        quality_label1->setText(QApplication::translate("SMIRED5_widget", "prefix for quality/histogram files:", 0, QApplication::UnicodeUTF8));
        quality_label->setText(QApplication::translate("SMIRED5_widget", "(file is saved as <prefix>_filename_[quality.csv|histogram.jpg])", 0, QApplication::UnicodeUTF8));
        checkQuality_checkBox->setText(QApplication::translate("SMIRED5_widget", "check quality", 0, QApplication::UnicodeUTF8));
        showhistogram_checkBox->setText(QApplication::translate("SMIRED5_widget", "show histogram", 0, QApplication::UnicodeUTF8));
        savehistogram_checkBox->setText(QApplication::translate("SMIRED5_widget", "save histogram", 0, QApplication::UnicodeUTF8));
        startButton->setText(QApplication::translate("SMIRED5_widget", "Start conversion", 0, QApplication::UnicodeUTF8));
        RemoveBlink->setText(QApplication::translate("SMIRED5_widget", "start blink remove", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("SMIRED5_widget", "File fragmentation", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SMIRED5_widget: public Ui_SMIRED5_widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SMIRED5_H
