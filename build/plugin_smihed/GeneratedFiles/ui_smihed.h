/********************************************************************************
** Form generated from reading UI file 'smihed.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SMIHED_H
#define UI_SMIHED_H

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

class Ui_SMIHED_widget
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *inputs_groupBox;
    QVBoxLayout *verticalLayout_4;
    QListView *listView;
    QHBoxLayout *addRemove_horizontalLayout;
    QToolButton *addButton;
    QToolButton *removeButton;
    QToolButton *toolButton;
    QGroupBox *subject_groupBox;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *subject_horizontalLayout;
    QLineEdit *subjectCsv_pathEdit;
    QToolButton *browseSubjectButton;
    QGroupBox *image_groupBox;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *subject_horizontalLayout2;
    QLineEdit *imageFolder_pathEdit;
    QToolButton *browseImageFolderButton;
    QGroupBox *output_groupBox;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *output_horizontalLayout;
    QLineEdit *outputFolder_pathEdit;
    QToolButton *browseOutputFolderButton;
    QGroupBox *options_groupBox;
    QGridLayout *gridLayout;
    QGridLayout *options_gridLayout;
    QLabel *quality_label;
    QCheckBox *checkQuality_checkBox;
    QLineEdit *quality_lineEdit;
    QLabel *label;
    QCheckBox *use_offset;
    QCheckBox *showhistogram_checkBox;
    QLabel *label_2;
    QCheckBox *savehistogram_checkBox;
    QHBoxLayout *bottom_horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QToolButton *startButton;

    void setupUi(QWidget *SMIHED_widget)
    {
        if (SMIHED_widget->objectName().isEmpty())
            SMIHED_widget->setObjectName(QString::fromUtf8("SMIHED_widget"));
        SMIHED_widget->resize(548, 570);
        verticalLayout = new QVBoxLayout(SMIHED_widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(SMIHED_widget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_2 = new QVBoxLayout(tab);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        inputs_groupBox = new QGroupBox(tab);
        inputs_groupBox->setObjectName(QString::fromUtf8("inputs_groupBox"));
        verticalLayout_4 = new QVBoxLayout(inputs_groupBox);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        listView = new QListView(inputs_groupBox);
        listView->setObjectName(QString::fromUtf8("listView"));

        verticalLayout_4->addWidget(listView);

        addRemove_horizontalLayout = new QHBoxLayout();
        addRemove_horizontalLayout->setSpacing(8);
        addRemove_horizontalLayout->setObjectName(QString::fromUtf8("addRemove_horizontalLayout"));
        addRemove_horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        addButton = new QToolButton(inputs_groupBox);
        addButton->setObjectName(QString::fromUtf8("addButton"));
        addButton->setEnabled(true);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icons/Resources/button_blue_add.png"), QSize(), QIcon::Normal, QIcon::Off);
        addButton->setIcon(icon);
        addButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        addRemove_horizontalLayout->addWidget(addButton);

        removeButton = new QToolButton(inputs_groupBox);
        removeButton->setObjectName(QString::fromUtf8("removeButton"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Icons/Resources/button_blue_delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        removeButton->setIcon(icon1);
        removeButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        addRemove_horizontalLayout->addWidget(removeButton);

        toolButton = new QToolButton(inputs_groupBox);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Icons/Resources/button_blue_close.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton->setIcon(icon2);
        toolButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        addRemove_horizontalLayout->addWidget(toolButton);


        verticalLayout_4->addLayout(addRemove_horizontalLayout);


        verticalLayout_3->addWidget(inputs_groupBox);

        subject_groupBox = new QGroupBox(tab);
        subject_groupBox->setObjectName(QString::fromUtf8("subject_groupBox"));
        verticalLayout_5 = new QVBoxLayout(subject_groupBox);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        subject_horizontalLayout = new QHBoxLayout();
        subject_horizontalLayout->setSpacing(6);
        subject_horizontalLayout->setObjectName(QString::fromUtf8("subject_horizontalLayout"));
        subjectCsv_pathEdit = new QLineEdit(subject_groupBox);
        subjectCsv_pathEdit->setObjectName(QString::fromUtf8("subjectCsv_pathEdit"));

        subject_horizontalLayout->addWidget(subjectCsv_pathEdit);

        browseSubjectButton = new QToolButton(subject_groupBox);
        browseSubjectButton->setObjectName(QString::fromUtf8("browseSubjectButton"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Icons/Resources/folder_blue_stuffed.png"), QSize(), QIcon::Normal, QIcon::Off);
        browseSubjectButton->setIcon(icon3);
        browseSubjectButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        subject_horizontalLayout->addWidget(browseSubjectButton);


        verticalLayout_5->addLayout(subject_horizontalLayout);


        verticalLayout_3->addWidget(subject_groupBox);

        image_groupBox = new QGroupBox(tab);
        image_groupBox->setObjectName(QString::fromUtf8("image_groupBox"));
        verticalLayout_7 = new QVBoxLayout(image_groupBox);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        subject_horizontalLayout2 = new QHBoxLayout();
        subject_horizontalLayout2->setSpacing(6);
        subject_horizontalLayout2->setObjectName(QString::fromUtf8("subject_horizontalLayout2"));
        imageFolder_pathEdit = new QLineEdit(image_groupBox);
        imageFolder_pathEdit->setObjectName(QString::fromUtf8("imageFolder_pathEdit"));

        subject_horizontalLayout2->addWidget(imageFolder_pathEdit);

        browseImageFolderButton = new QToolButton(image_groupBox);
        browseImageFolderButton->setObjectName(QString::fromUtf8("browseImageFolderButton"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Icons/Resources/folder_blue.png"), QSize(), QIcon::Normal, QIcon::Off);
        browseImageFolderButton->setIcon(icon4);
        browseImageFolderButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        subject_horizontalLayout2->addWidget(browseImageFolderButton);


        verticalLayout_7->addLayout(subject_horizontalLayout2);


        verticalLayout_3->addWidget(image_groupBox);

        output_groupBox = new QGroupBox(tab);
        output_groupBox->setObjectName(QString::fromUtf8("output_groupBox"));
        verticalLayout_6 = new QVBoxLayout(output_groupBox);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        output_horizontalLayout = new QHBoxLayout();
        output_horizontalLayout->setSpacing(6);
        output_horizontalLayout->setObjectName(QString::fromUtf8("output_horizontalLayout"));
        outputFolder_pathEdit = new QLineEdit(output_groupBox);
        outputFolder_pathEdit->setObjectName(QString::fromUtf8("outputFolder_pathEdit"));

        output_horizontalLayout->addWidget(outputFolder_pathEdit);

        browseOutputFolderButton = new QToolButton(output_groupBox);
        browseOutputFolderButton->setObjectName(QString::fromUtf8("browseOutputFolderButton"));
        browseOutputFolderButton->setIcon(icon4);
        browseOutputFolderButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        output_horizontalLayout->addWidget(browseOutputFolderButton);


        verticalLayout_6->addLayout(output_horizontalLayout);


        verticalLayout_3->addWidget(output_groupBox);

        options_groupBox = new QGroupBox(tab);
        options_groupBox->setObjectName(QString::fromUtf8("options_groupBox"));
        gridLayout = new QGridLayout(options_groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        options_gridLayout = new QGridLayout();
        options_gridLayout->setSpacing(6);
        options_gridLayout->setObjectName(QString::fromUtf8("options_gridLayout"));
        quality_label = new QLabel(options_groupBox);
        quality_label->setObjectName(QString::fromUtf8("quality_label"));

        options_gridLayout->addWidget(quality_label, 0, 1, 1, 1);

        checkQuality_checkBox = new QCheckBox(options_groupBox);
        checkQuality_checkBox->setObjectName(QString::fromUtf8("checkQuality_checkBox"));
        checkQuality_checkBox->setChecked(true);

        options_gridLayout->addWidget(checkQuality_checkBox, 0, 0, 1, 1);

        quality_lineEdit = new QLineEdit(options_groupBox);
        quality_lineEdit->setObjectName(QString::fromUtf8("quality_lineEdit"));

        options_gridLayout->addWidget(quality_lineEdit, 1, 1, 1, 1);

        label = new QLabel(options_groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        options_gridLayout->addWidget(label, 1, 0, 1, 1);

        use_offset = new QCheckBox(options_groupBox);
        use_offset->setObjectName(QString::fromUtf8("use_offset"));
        use_offset->setChecked(true);

        options_gridLayout->addWidget(use_offset, 4, 0, 1, 1);

        showhistogram_checkBox = new QCheckBox(options_groupBox);
        showhistogram_checkBox->setObjectName(QString::fromUtf8("showhistogram_checkBox"));

        options_gridLayout->addWidget(showhistogram_checkBox, 2, 0, 1, 1);

        label_2 = new QLabel(options_groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        options_gridLayout->addWidget(label_2, 2, 1, 1, 1);

        savehistogram_checkBox = new QCheckBox(options_groupBox);
        savehistogram_checkBox->setObjectName(QString::fromUtf8("savehistogram_checkBox"));

        options_gridLayout->addWidget(savehistogram_checkBox, 3, 0, 1, 1);


        gridLayout->addLayout(options_gridLayout, 0, 0, 1, 1);


        verticalLayout_3->addWidget(options_groupBox);

        bottom_horizontalLayout = new QHBoxLayout();
        bottom_horizontalLayout->setSpacing(6);
        bottom_horizontalLayout->setObjectName(QString::fromUtf8("bottom_horizontalLayout"));
        bottom_horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        bottom_horizontalLayout->addItem(horizontalSpacer);

        startButton = new QToolButton(tab);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Icons/Resources/button_blue_play.png"), QSize(), QIcon::Normal, QIcon::Off);
        startButton->setIcon(icon5);
        startButton->setPopupMode(QToolButton::DelayedPopup);
        startButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        bottom_horizontalLayout->addWidget(startButton);


        verticalLayout_3->addLayout(bottom_horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout_3);

        tabWidget->addTab(tab, QString());

        verticalLayout->addWidget(tabWidget);


        retranslateUi(SMIHED_widget);
        QObject::connect(addButton, SIGNAL(clicked()), SMIHED_widget, SLOT(sltAddFile()));
        QObject::connect(removeButton, SIGNAL(clicked()), SMIHED_widget, SLOT(sltRemoveFile()));
        QObject::connect(browseSubjectButton, SIGNAL(clicked()), SMIHED_widget, SLOT(sltSetSubjectPath()));
        QObject::connect(browseOutputFolderButton, SIGNAL(clicked()), SMIHED_widget, SLOT(sltSelectOutputFolder()));
        QObject::connect(startButton, SIGNAL(clicked()), SMIHED_widget, SLOT(sltStartConversion()));
        QObject::connect(checkQuality_checkBox, SIGNAL(toggled(bool)), SMIHED_widget, SLOT(sltAbleSelection(bool)));
        QObject::connect(browseImageFolderButton, SIGNAL(clicked()), SMIHED_widget, SLOT(sltSetImageFolder()));
        QObject::connect(toolButton, SIGNAL(clicked()), SMIHED_widget, SLOT(sltRemoveAll()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SMIHED_widget);
    } // setupUi

    void retranslateUi(QWidget *SMIHED_widget)
    {
        SMIHED_widget->setWindowTitle(QApplication::translate("SMIHED_widget", "SMIHED_widget", 0, QApplication::UnicodeUTF8));
        inputs_groupBox->setTitle(QApplication::translate("SMIHED_widget", "Load files", 0, QApplication::UnicodeUTF8));
        addButton->setText(QApplication::translate("SMIHED_widget", "Add", 0, QApplication::UnicodeUTF8));
        removeButton->setText(QApplication::translate("SMIHED_widget", "Remove", 0, QApplication::UnicodeUTF8));
        toolButton->setText(QApplication::translate("SMIHED_widget", "Remove all", 0, QApplication::UnicodeUTF8));
        subject_groupBox->setTitle(QApplication::translate("SMIHED_widget", "Set path to subject.csv (optional)", 0, QApplication::UnicodeUTF8));
        browseSubjectButton->setText(QApplication::translate("SMIHED_widget", "Browse", 0, QApplication::UnicodeUTF8));
        image_groupBox->setTitle(QApplication::translate("SMIHED_widget", "Set image folder", 0, QApplication::UnicodeUTF8));
        browseImageFolderButton->setText(QApplication::translate("SMIHED_widget", "Browse", 0, QApplication::UnicodeUTF8));
        output_groupBox->setTitle(QApplication::translate("SMIHED_widget", "Select output folder", 0, QApplication::UnicodeUTF8));
        browseOutputFolderButton->setText(QApplication::translate("SMIHED_widget", "Browse", 0, QApplication::UnicodeUTF8));
        options_groupBox->setTitle(QApplication::translate("SMIHED_widget", "Options", 0, QApplication::UnicodeUTF8));
        quality_label->setText(QApplication::translate("SMIHED_widget", "(file is saved as <prefix>_quality.csv)", 0, QApplication::UnicodeUTF8));
        checkQuality_checkBox->setText(QApplication::translate("SMIHED_widget", "check quality", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SMIHED_widget", "Prefix:", 0, QApplication::UnicodeUTF8));
        use_offset->setText(QApplication::translate("SMIHED_widget", "Use offset if available", 0, QApplication::UnicodeUTF8));
        showhistogram_checkBox->setText(QApplication::translate("SMIHED_widget", "show histogram", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SMIHED_widget", "(file is saved as <prefix>_filename_[quality.csv|histogram.jpg])", 0, QApplication::UnicodeUTF8));
        savehistogram_checkBox->setText(QApplication::translate("SMIHED_widget", "save histogram", 0, QApplication::UnicodeUTF8));
        startButton->setText(QApplication::translate("SMIHED_widget", "Start conversion", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("SMIHED_widget", "File conversion", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SMIHED_widget: public Ui_SMIHED_widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SMIHED_H
