/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *topHorizontalLayout;
    QLabel *inputLabel;
    QLineEdit *inputLineEdit;
    QPushButton *inputPushButton;
    QGroupBox *filterTypeGroupBox;
    QRadioButton *medianBlurRadioButton;
    QRadioButton *gaussianBlurRradioButton;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *bottomHorizontalLayout;
    QLabel *outputLabel;
    QLineEdit *outputLineEdit;
    QPushButton *outputPushButton;
    QCheckBox *displayImageCheckBox;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(530, 288);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 521, 61));
        topHorizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        topHorizontalLayout->setSpacing(6);
        topHorizontalLayout->setContentsMargins(11, 11, 11, 11);
        topHorizontalLayout->setObjectName(QStringLiteral("topHorizontalLayout"));
        topHorizontalLayout->setContentsMargins(0, 0, 0, 0);
        inputLabel = new QLabel(horizontalLayoutWidget);
        inputLabel->setObjectName(QStringLiteral("inputLabel"));

        topHorizontalLayout->addWidget(inputLabel);

        inputLineEdit = new QLineEdit(horizontalLayoutWidget);
        inputLineEdit->setObjectName(QStringLiteral("inputLineEdit"));

        topHorizontalLayout->addWidget(inputLineEdit);

        inputPushButton = new QPushButton(horizontalLayoutWidget);
        inputPushButton->setObjectName(QStringLiteral("inputPushButton"));

        topHorizontalLayout->addWidget(inputPushButton);

        filterTypeGroupBox = new QGroupBox(centralWidget);
        filterTypeGroupBox->setObjectName(QStringLiteral("filterTypeGroupBox"));
        filterTypeGroupBox->setGeometry(QRect(0, 70, 521, 80));
        medianBlurRadioButton = new QRadioButton(filterTypeGroupBox);
        medianBlurRadioButton->setObjectName(QStringLiteral("medianBlurRadioButton"));
        medianBlurRadioButton->setGeometry(QRect(50, 40, 89, 16));
        gaussianBlurRradioButton = new QRadioButton(filterTypeGroupBox);
        gaussianBlurRradioButton->setObjectName(QStringLiteral("gaussianBlurRradioButton"));
        gaussianBlurRradioButton->setGeometry(QRect(280, 40, 111, 16));
        horizontalLayoutWidget_2 = new QWidget(centralWidget);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(0, 160, 521, 61));
        bottomHorizontalLayout = new QHBoxLayout(horizontalLayoutWidget_2);
        bottomHorizontalLayout->setSpacing(6);
        bottomHorizontalLayout->setContentsMargins(11, 11, 11, 11);
        bottomHorizontalLayout->setObjectName(QStringLiteral("bottomHorizontalLayout"));
        bottomHorizontalLayout->setContentsMargins(0, 0, 0, 0);
        outputLabel = new QLabel(horizontalLayoutWidget_2);
        outputLabel->setObjectName(QStringLiteral("outputLabel"));

        bottomHorizontalLayout->addWidget(outputLabel);

        outputLineEdit = new QLineEdit(horizontalLayoutWidget_2);
        outputLineEdit->setObjectName(QStringLiteral("outputLineEdit"));

        bottomHorizontalLayout->addWidget(outputLineEdit);

        outputPushButton = new QPushButton(horizontalLayoutWidget_2);
        outputPushButton->setObjectName(QStringLiteral("outputPushButton"));

        bottomHorizontalLayout->addWidget(outputPushButton);

        displayImageCheckBox = new QCheckBox(centralWidget);
        displayImageCheckBox->setObjectName(QStringLiteral("displayImageCheckBox"));
        displayImageCheckBox->setGeometry(QRect(10, 240, 191, 16));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        inputLabel->setText(QApplication::translate("MainWindow", "Input Image:", Q_NULLPTR));
        inputPushButton->setText(QApplication::translate("MainWindow", "Brower", Q_NULLPTR));
        filterTypeGroupBox->setTitle(QApplication::translate("MainWindow", "Filter Type", Q_NULLPTR));
        medianBlurRadioButton->setText(QApplication::translate("MainWindow", "Median Blur", Q_NULLPTR));
        gaussianBlurRradioButton->setText(QApplication::translate("MainWindow", "Gaussion Blur", Q_NULLPTR));
        outputLabel->setText(QApplication::translate("MainWindow", "Output Image:", Q_NULLPTR));
        outputPushButton->setText(QApplication::translate("MainWindow", "Brower", Q_NULLPTR));
        displayImageCheckBox->setText(QApplication::translate("MainWindow", "Display image after saving", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
