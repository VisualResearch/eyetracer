/********************************************************************************
** Form generated from reading UI file 'idmt.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IDMT_H
#define UI_IDMT_H

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

class Ui_IDMT_widget
{
public:
    QHBoxLayout *horizontalLayout_2;
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
    QLineEdit *image_pathEdit;
    QToolButton *browseImageButton;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *heightLabel;
    QLineEdit *height_lineEdit;
    QLabel *widthLabel;
    QLineEdit *width_lineEdit;
    QGroupBox *output_groupBox;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *L4a;
    QLineEdit *outputFolder_pathEdit;
    QToolButton *browseOutputFolderButton;
    QGroupBox *options_groupBox;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_2;
    QCheckBox *checkQuality_checkBox;
    QHBoxLayout *horizontalLayout_4;
    QLabel *quality_label1;
    QLineEdit *quality_lineEdit;
    QCheckBox *showhistogram_checkBox;
    QLabel *quality_label2;
    QCheckBox *savehistogram_checkBox;
    QCheckBox *applypdetected_checkBox;
    QHBoxLayout *horizontalLayout_5;
    QLabel *pd_label1;
    QLineEdit *pd_lineEdit;
    QCheckBox *applysmooth_checkBox;
    QHBoxLayout *horizontalLayout_6;
    QLabel *window_label;
    QLineEdit *window_length_lineEdit;
    QLabel *minpd_label;
    QLineEdit *window_valid_lineEdit;
    QCheckBox *checkCombi_checkBox;
    QHBoxLayout *horizontalLayout_7;
    QLabel *combi_label1;
    QLineEdit *combi_lineEdit;
    QLabel *user_distance_label;
    QLineEdit *user_distance_lineEdit;
    QHBoxLayout *horizontalLayout_8;
    QLabel *bild_distance_label;
    QLabel *bild_distance_label1;
    QLineEdit *bild_distance_lineEdit_X;
    QLabel *bild_distance_label2;
    QLineEdit *bild_distance_lineEdit_Y;
    QLabel *bild_distance_label3;
    QHBoxLayout *L5;
    QSpacerItem *horizontalSpacer;
    QToolButton *startButton;

    void setupUi(QWidget *IDMT_widget)
    {
        if (IDMT_widget->objectName().isEmpty())
            IDMT_widget->setObjectName(QString::fromUtf8("IDMT_widget"));
        IDMT_widget->resize(640, 835);
        horizontalLayout_2 = new QHBoxLayout(IDMT_widget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        tabWidget = new QTabWidget(IDMT_widget);
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
        subjectCsv_pathEdit->setEnabled(true);

        horizontalLayout->addWidget(subjectCsv_pathEdit);

        browseSubjectButton = new QToolButton(groupBox);
        browseSubjectButton->setObjectName(QString::fromUtf8("browseSubjectButton"));
        browseSubjectButton->setEnabled(true);
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
        image_pathEdit = new QLineEdit(image_groupBox);
        image_pathEdit->setObjectName(QString::fromUtf8("image_pathEdit"));
        image_pathEdit->setEnabled(true);

        L3a->addWidget(image_pathEdit);

        browseImageButton = new QToolButton(image_groupBox);
        browseImageButton->setObjectName(QString::fromUtf8("browseImageButton"));
        browseImageButton->setEnabled(true);
        browseImageButton->setIcon(icon3);
        browseImageButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        L3a->addWidget(browseImageButton);


        verticalLayout_7->addLayout(L3a);


        verticalLayout_4->addWidget(image_groupBox);

        groupBox_2 = new QGroupBox(tab);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalLayout_3 = new QHBoxLayout(groupBox_2);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        heightLabel = new QLabel(groupBox_2);
        heightLabel->setObjectName(QString::fromUtf8("heightLabel"));

        horizontalLayout_3->addWidget(heightLabel);

        height_lineEdit = new QLineEdit(groupBox_2);
        height_lineEdit->setObjectName(QString::fromUtf8("height_lineEdit"));

        horizontalLayout_3->addWidget(height_lineEdit);

        widthLabel = new QLabel(groupBox_2);
        widthLabel->setObjectName(QString::fromUtf8("widthLabel"));

        horizontalLayout_3->addWidget(widthLabel);

        width_lineEdit = new QLineEdit(groupBox_2);
        width_lineEdit->setObjectName(QString::fromUtf8("width_lineEdit"));

        horizontalLayout_3->addWidget(width_lineEdit);


        verticalLayout_4->addWidget(groupBox_2);

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
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Icons/Resources/folder_blue.png"), QSize(), QIcon::Normal, QIcon::Off);
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
        checkQuality_checkBox = new QCheckBox(options_groupBox);
        checkQuality_checkBox->setObjectName(QString::fromUtf8("checkQuality_checkBox"));
        checkQuality_checkBox->setChecked(true);

        gridLayout_2->addWidget(checkQuality_checkBox, 0, 0, 1, 1);

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

        showhistogram_checkBox = new QCheckBox(options_groupBox);
        showhistogram_checkBox->setObjectName(QString::fromUtf8("showhistogram_checkBox"));

        gridLayout_2->addWidget(showhistogram_checkBox, 1, 0, 1, 1);

        quality_label2 = new QLabel(options_groupBox);
        quality_label2->setObjectName(QString::fromUtf8("quality_label2"));

        gridLayout_2->addWidget(quality_label2, 1, 1, 1, 1);

        savehistogram_checkBox = new QCheckBox(options_groupBox);
        savehistogram_checkBox->setObjectName(QString::fromUtf8("savehistogram_checkBox"));

        gridLayout_2->addWidget(savehistogram_checkBox, 2, 0, 1, 1);

        applypdetected_checkBox = new QCheckBox(options_groupBox);
        applypdetected_checkBox->setObjectName(QString::fromUtf8("applypdetected_checkBox"));
        applypdetected_checkBox->setChecked(true);

        gridLayout_2->addWidget(applypdetected_checkBox, 3, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        pd_label1 = new QLabel(options_groupBox);
        pd_label1->setObjectName(QString::fromUtf8("pd_label1"));

        horizontalLayout_5->addWidget(pd_label1);

        pd_lineEdit = new QLineEdit(options_groupBox);
        pd_lineEdit->setObjectName(QString::fromUtf8("pd_lineEdit"));

        horizontalLayout_5->addWidget(pd_lineEdit);


        gridLayout_2->addLayout(horizontalLayout_5, 3, 1, 1, 1);

        applysmooth_checkBox = new QCheckBox(options_groupBox);
        applysmooth_checkBox->setObjectName(QString::fromUtf8("applysmooth_checkBox"));
        applysmooth_checkBox->setChecked(true);

        gridLayout_2->addWidget(applysmooth_checkBox, 4, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        window_label = new QLabel(options_groupBox);
        window_label->setObjectName(QString::fromUtf8("window_label"));

        horizontalLayout_6->addWidget(window_label);

        window_length_lineEdit = new QLineEdit(options_groupBox);
        window_length_lineEdit->setObjectName(QString::fromUtf8("window_length_lineEdit"));

        horizontalLayout_6->addWidget(window_length_lineEdit);

        minpd_label = new QLabel(options_groupBox);
        minpd_label->setObjectName(QString::fromUtf8("minpd_label"));
        minpd_label->setEnabled(true);

        horizontalLayout_6->addWidget(minpd_label);

        window_valid_lineEdit = new QLineEdit(options_groupBox);
        window_valid_lineEdit->setObjectName(QString::fromUtf8("window_valid_lineEdit"));

        horizontalLayout_6->addWidget(window_valid_lineEdit);


        gridLayout_2->addLayout(horizontalLayout_6, 4, 1, 1, 1);

        checkCombi_checkBox = new QCheckBox(options_groupBox);
        checkCombi_checkBox->setObjectName(QString::fromUtf8("checkCombi_checkBox"));
        checkCombi_checkBox->setChecked(true);

        gridLayout_2->addWidget(checkCombi_checkBox, 5, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        combi_label1 = new QLabel(options_groupBox);
        combi_label1->setObjectName(QString::fromUtf8("combi_label1"));

        horizontalLayout_7->addWidget(combi_label1);

        combi_lineEdit = new QLineEdit(options_groupBox);
        combi_lineEdit->setObjectName(QString::fromUtf8("combi_lineEdit"));

        horizontalLayout_7->addWidget(combi_lineEdit);

        user_distance_label = new QLabel(options_groupBox);
        user_distance_label->setObjectName(QString::fromUtf8("user_distance_label"));

        horizontalLayout_7->addWidget(user_distance_label);

        user_distance_lineEdit = new QLineEdit(options_groupBox);
        user_distance_lineEdit->setObjectName(QString::fromUtf8("user_distance_lineEdit"));

        horizontalLayout_7->addWidget(user_distance_lineEdit);


        gridLayout_2->addLayout(horizontalLayout_7, 5, 1, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        bild_distance_label = new QLabel(options_groupBox);
        bild_distance_label->setObjectName(QString::fromUtf8("bild_distance_label"));

        horizontalLayout_8->addWidget(bild_distance_label);

        bild_distance_label1 = new QLabel(options_groupBox);
        bild_distance_label1->setObjectName(QString::fromUtf8("bild_distance_label1"));

        horizontalLayout_8->addWidget(bild_distance_label1);

        bild_distance_lineEdit_X = new QLineEdit(options_groupBox);
        bild_distance_lineEdit_X->setObjectName(QString::fromUtf8("bild_distance_lineEdit_X"));

        horizontalLayout_8->addWidget(bild_distance_lineEdit_X);

        bild_distance_label2 = new QLabel(options_groupBox);
        bild_distance_label2->setObjectName(QString::fromUtf8("bild_distance_label2"));

        horizontalLayout_8->addWidget(bild_distance_label2);

        bild_distance_lineEdit_Y = new QLineEdit(options_groupBox);
        bild_distance_lineEdit_Y->setObjectName(QString::fromUtf8("bild_distance_lineEdit_Y"));

        horizontalLayout_8->addWidget(bild_distance_lineEdit_Y);

        bild_distance_label3 = new QLabel(options_groupBox);
        bild_distance_label3->setObjectName(QString::fromUtf8("bild_distance_label3"));

        horizontalLayout_8->addWidget(bild_distance_label3);


        gridLayout_2->addLayout(horizontalLayout_8, 6, 1, 1, 1);


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


        verticalLayout_4->addLayout(L5);


        verticalLayout_2->addLayout(verticalLayout_4);

        tabWidget->addTab(tab, QString());

        horizontalLayout_2->addWidget(tabWidget);


        retranslateUi(IDMT_widget);
        QObject::connect(addButton, SIGNAL(clicked()), IDMT_widget, SLOT(sltAddFile()));
        QObject::connect(removeButton, SIGNAL(clicked()), IDMT_widget, SLOT(sltRemoveFile()));
        QObject::connect(browseSubjectButton, SIGNAL(clicked()), IDMT_widget, SLOT(sltSetSubjectPath()));
        QObject::connect(browseImageButton, SIGNAL(clicked()), IDMT_widget, SLOT(sltSetImagePath()));
        QObject::connect(browseOutputFolderButton, SIGNAL(clicked()), IDMT_widget, SLOT(sltSelectOutputFolder()));
        QObject::connect(startButton, SIGNAL(clicked()), IDMT_widget, SLOT(sltStartConversion()));
        QObject::connect(toolButton, SIGNAL(clicked()), IDMT_widget, SLOT(sltRemoveAll()));
        QObject::connect(checkQuality_checkBox, SIGNAL(toggled(bool)), IDMT_widget, SLOT(sltAbleQualitySelection(bool)));
        QObject::connect(applypdetected_checkBox, SIGNAL(toggled(bool)), IDMT_widget, SLOT(sltAblePdetectedSelection(bool)));
        QObject::connect(applysmooth_checkBox, SIGNAL(toggled(bool)), IDMT_widget, SLOT(sltAbleSmoothingSelection(bool)));
        QObject::connect(checkCombi_checkBox, SIGNAL(toggled(bool)), IDMT_widget, SLOT(sltAbleCombiSelection(bool)));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(IDMT_widget);
    } // setupUi

    void retranslateUi(QWidget *IDMT_widget)
    {
        IDMT_widget->setWindowTitle(QApplication::translate("IDMT_widget", "IDMT_widget", 0, QApplication::UnicodeUTF8));
        inputs_groupBox->setTitle(QApplication::translate("IDMT_widget", "Load files", 0, QApplication::UnicodeUTF8));
        addButton->setText(QApplication::translate("IDMT_widget", "Add", 0, QApplication::UnicodeUTF8));
        removeButton->setText(QApplication::translate("IDMT_widget", "Remove", 0, QApplication::UnicodeUTF8));
        toolButton->setText(QApplication::translate("IDMT_widget", "Remove all", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("IDMT_widget", "Set path to subject.csv", 0, QApplication::UnicodeUTF8));
        browseSubjectButton->setText(QApplication::translate("IDMT_widget", "Browse", 0, QApplication::UnicodeUTF8));
        image_groupBox->setTitle(QApplication::translate("IDMT_widget", "Set image path", 0, QApplication::UnicodeUTF8));
        browseImageButton->setText(QApplication::translate("IDMT_widget", "Browse", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("IDMT_widget", "Specify original picture size", 0, QApplication::UnicodeUTF8));
        heightLabel->setText(QApplication::translate("IDMT_widget", "height in mm:", 0, QApplication::UnicodeUTF8));
        widthLabel->setText(QApplication::translate("IDMT_widget", "width in mm:", 0, QApplication::UnicodeUTF8));
        output_groupBox->setTitle(QApplication::translate("IDMT_widget", "Select output folder", 0, QApplication::UnicodeUTF8));
        browseOutputFolderButton->setText(QApplication::translate("IDMT_widget", "Browse", 0, QApplication::UnicodeUTF8));
        options_groupBox->setTitle(QApplication::translate("IDMT_widget", "Options", 0, QApplication::UnicodeUTF8));
        checkQuality_checkBox->setText(QApplication::translate("IDMT_widget", "check quality", 0, QApplication::UnicodeUTF8));
        quality_label1->setText(QApplication::translate("IDMT_widget", "prefix for quality/histogram files:", 0, QApplication::UnicodeUTF8));
        showhistogram_checkBox->setText(QApplication::translate("IDMT_widget", "show histogram", 0, QApplication::UnicodeUTF8));
        quality_label2->setText(QApplication::translate("IDMT_widget", "(file is saved as <prefix>_[quality.csv|histogram.jpg])", 0, QApplication::UnicodeUTF8));
        savehistogram_checkBox->setText(QApplication::translate("IDMT_widget", "save histogram", 0, QApplication::UnicodeUTF8));
        applypdetected_checkBox->setText(QApplication::translate("IDMT_widget", "person detected", 0, QApplication::UnicodeUTF8));
        pd_label1->setText(QApplication::translate("IDMT_widget", "person detected length:", 0, QApplication::UnicodeUTF8));
        pd_lineEdit->setText(QApplication::translate("IDMT_widget", "2", 0, QApplication::UnicodeUTF8));
        applysmooth_checkBox->setText(QApplication::translate("IDMT_widget", "smooth data", 0, QApplication::UnicodeUTF8));
        window_label->setText(QApplication::translate("IDMT_widget", "window length", 0, QApplication::UnicodeUTF8));
        window_length_lineEdit->setText(QApplication::translate("IDMT_widget", "5", 0, QApplication::UnicodeUTF8));
        minpd_label->setText(QApplication::translate("IDMT_widget", "minimum \"person detected\":", 0, QApplication::UnicodeUTF8));
        window_valid_lineEdit->setText(QApplication::translate("IDMT_widget", "3", 0, QApplication::UnicodeUTF8));
        checkCombi_checkBox->setText(QApplication::translate("IDMT_widget", "combi algorithm", 0, QApplication::UnicodeUTF8));
        combi_label1->setText(QApplication::translate("IDMT_widget", "algorithm: (1..16)", 0, QApplication::UnicodeUTF8));
        user_distance_label->setText(QApplication::translate("IDMT_widget", "user distance in mm:", 0, QApplication::UnicodeUTF8));
        user_distance_lineEdit->setText(QApplication::translate("IDMT_widget", "220", 0, QApplication::UnicodeUTF8));
        bild_distance_label->setText(QApplication::translate("IDMT_widget", "Gazetracker distance in mm (", 0, QApplication::UnicodeUTF8));
        bild_distance_label1->setText(QApplication::translate("IDMT_widget", "X:", 0, QApplication::UnicodeUTF8));
        bild_distance_lineEdit_X->setText(QApplication::translate("IDMT_widget", "-310", 0, QApplication::UnicodeUTF8));
        bild_distance_label2->setText(QApplication::translate("IDMT_widget", "Y:", 0, QApplication::UnicodeUTF8));
        bild_distance_lineEdit_Y->setText(QApplication::translate("IDMT_widget", "460", 0, QApplication::UnicodeUTF8));
        bild_distance_label3->setText(QApplication::translate("IDMT_widget", ")", 0, QApplication::UnicodeUTF8));
        startButton->setText(QApplication::translate("IDMT_widget", "Start conversion", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("IDMT_widget", "File conversion", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class IDMT_widget: public Ui_IDMT_widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IDMT_H
