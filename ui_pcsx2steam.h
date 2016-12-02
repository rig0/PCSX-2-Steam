/********************************************************************************
** Form generated from reading UI file 'pcsx2steam.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PCSX2STEAM_H
#define UI_PCSX2STEAM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PCSX2Steam
{
public:
    QWidget *centralWidget;
    QGraphicsView *logoDisplay;
    QLineEdit *nameInput;
    QLineEdit *iconInput;
    QLabel *nameLabel;
    QLabel *iconLabel;
    QLabel *dirLabel;
    QLineEdit *dirInput;
    QPushButton *dirBrowseBtn;
    QPushButton *createButton;
    QLabel *dirLabel_2;
    QPushButton *iconPicBtn;
    QPushButton *resetButton;

    void setupUi(QMainWindow *PCSX2Steam)
    {
        if (PCSX2Steam->objectName().isEmpty())
            PCSX2Steam->setObjectName(QStringLiteral("PCSX2Steam"));
        PCSX2Steam->resize(500, 320);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PCSX2Steam->sizePolicy().hasHeightForWidth());
        PCSX2Steam->setSizePolicy(sizePolicy);
        PCSX2Steam->setMinimumSize(QSize(500, 320));
        PCSX2Steam->setMaximumSize(QSize(500, 320));
        PCSX2Steam->setStyleSheet(QLatin1String("background-color: rgb(51, 51, 51);\n"
"border-style: 0px; \n"
"/*background-image: url(\":/res/imgs/bg.png\");*/\n"
"\n"
""));
        centralWidget = new QWidget(PCSX2Steam);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        logoDisplay = new QGraphicsView(centralWidget);
        logoDisplay->setObjectName(QStringLiteral("logoDisplay"));
        logoDisplay->setGeometry(QRect(90, 20, 318, 61));
        sizePolicy.setHeightForWidth(logoDisplay->sizePolicy().hasHeightForWidth());
        logoDisplay->setSizePolicy(sizePolicy);
        logoDisplay->setStyleSheet(QLatin1String("QGraphicsView#logoDisplay\n"
"{\n"
"	background-image: url(\":/res/imgs/logo.png\");\n"
"	/*border-style: 0px; */ \n"
"}\n"
""));
        logoDisplay->setLineWidth(0);
        nameInput = new QLineEdit(centralWidget);
        nameInput->setObjectName(QStringLiteral("nameInput"));
        nameInput->setGeometry(QRect(140, 100, 205, 30));
        QFont font;
        font.setFamily(QStringLiteral("Calibri"));
        font.setPointSize(12);
        nameInput->setFont(font);
        nameInput->setStyleSheet(QStringLiteral("background-color: #ccc;"));
        iconInput = new QLineEdit(centralWidget);
        iconInput->setObjectName(QStringLiteral("iconInput"));
        iconInput->setGeometry(QRect(140, 150, 205, 30));
        iconInput->setFont(font);
        iconInput->setStyleSheet(QStringLiteral("background-color: #ccc;"));
        nameLabel = new QLabel(centralWidget);
        nameLabel->setObjectName(QStringLiteral("nameLabel"));
        nameLabel->setGeometry(QRect(60, 103, 71, 21));
        QFont font1;
        font1.setFamily(QStringLiteral("Calibri"));
        font1.setPointSize(18);
        font1.setBold(true);
        font1.setWeight(75);
        nameLabel->setFont(font1);
        nameLabel->setStyleSheet(QStringLiteral("color: #45b9e2;"));
        iconLabel = new QLabel(centralWidget);
        iconLabel->setObjectName(QStringLiteral("iconLabel"));
        iconLabel->setGeometry(QRect(70, 153, 51, 22));
        iconLabel->setFont(font1);
        iconLabel->setStyleSheet(QStringLiteral("color: #45b9e2;"));
        dirLabel = new QLabel(centralWidget);
        dirLabel->setObjectName(QStringLiteral("dirLabel"));
        dirLabel->setGeometry(QRect(70, 203, 51, 22));
        dirLabel->setFont(font1);
        dirLabel->setStyleSheet(QStringLiteral("color: #45b9e2;"));
        dirInput = new QLineEdit(centralWidget);
        dirInput->setObjectName(QStringLiteral("dirInput"));
        dirInput->setGeometry(QRect(140, 200, 205, 30));
        dirInput->setFont(font);
        dirInput->setStyleSheet(QStringLiteral("background-color: #ccc;"));
        dirBrowseBtn = new QPushButton(centralWidget);
        dirBrowseBtn->setObjectName(QStringLiteral("dirBrowseBtn"));
        dirBrowseBtn->setGeometry(QRect(365, 200, 80, 30));
        dirBrowseBtn->setFont(font);
        dirBrowseBtn->setStyleSheet(QLatin1String("QPushButton#dirBrowseBtn\n"
"{\n"
"   background-color: #cccccc;\n"
"}\n"
"QPushButton:hover#dirBrowseBtn\n"
"{\n"
"  background-color: #f1f1f1;\n"
"}\n"
"QPushButton:pressed#dirBrowseBtn\n"
"{\n"
"   background-color: #45b9e2;\n"
"}"));
        createButton = new QPushButton(centralWidget);
        createButton->setObjectName(QStringLiteral("createButton"));
        createButton->setGeometry(QRect(250, 250, 80, 30));
        createButton->setFont(font);
        createButton->setStyleSheet(QLatin1String("QPushButton#createButton\n"
"{\n"
"   background-color: #cccccc;\n"
"}\n"
"QPushButton:hover#createButton\n"
"{\n"
"  background-color: #f1f1f1;\n"
"}\n"
"QPushButton:pressed#createButton\n"
"{\n"
"   background-color: #45b9e2;\n"
"}"));
        dirLabel_2 = new QLabel(centralWidget);
        dirLabel_2->setObjectName(QStringLiteral("dirLabel_2"));
        dirLabel_2->setGeometry(QRect(120, 290, 271, 22));
        QFont font2;
        font2.setFamily(QStringLiteral("Calibri"));
        font2.setPointSize(8);
        font2.setBold(false);
        font2.setWeight(50);
        dirLabel_2->setFont(font2);
        dirLabel_2->setStyleSheet(QStringLiteral("color: #171717;"));
        iconPicBtn = new QPushButton(centralWidget);
        iconPicBtn->setObjectName(QStringLiteral("iconPicBtn"));
        iconPicBtn->setGeometry(QRect(365, 100, 80, 80));
        iconPicBtn->setFont(font);
        iconPicBtn->setStyleSheet(QLatin1String("QPushButton#iconPicBtn\n"
"{\n"
"    background-image: url(\":/res/imgs/blankico.png\");\n"
"    background-color: #cccccc;\n"
"}\n"
"QPushButton:hover#iconPicBtn\n"
"{\n"
"  background-color: #f1f1f1;\n"
"  background-image: url(\":/res/imgs/blankico2.png\");\n"
"}\n"
"QPushButton:pressed#iconPicBtn\n"
"{\n"
"   background-color: #45b9e2;\n"
"   background-image: url(\":/res/imgs/blankico3.png\");\n"
"}\n"
""));
        resetButton = new QPushButton(centralWidget);
        resetButton->setObjectName(QStringLiteral("resetButton"));
        resetButton->setGeometry(QRect(160, 250, 80, 30));
        resetButton->setFont(font);
        resetButton->setStyleSheet(QLatin1String("QPushButton#resetButton\n"
"{\n"
"   background-color: #cccccc;\n"
"}\n"
"QPushButton:hover#resetButton\n"
"{\n"
"  background-color: #f1f1f1;\n"
"}\n"
"QPushButton:pressed#resetButton\n"
"{\n"
"   background-color: #45b9e2;\n"
"}"));
        PCSX2Steam->setCentralWidget(centralWidget);

        retranslateUi(PCSX2Steam);

        QMetaObject::connectSlotsByName(PCSX2Steam);
    } // setupUi

    void retranslateUi(QMainWindow *PCSX2Steam)
    {
        PCSX2Steam->setWindowTitle(QApplication::translate("PCSX2Steam", "PCSX 2 Steam", 0));
        nameLabel->setText(QApplication::translate("PCSX2Steam", "NAME", 0));
        iconLabel->setText(QApplication::translate("PCSX2Steam", "ICON", 0));
        dirLabel->setText(QApplication::translate("PCSX2Steam", "PATH", 0));
        dirBrowseBtn->setText(QApplication::translate("PCSX2Steam", "BROWSE", 0));
        createButton->setText(QApplication::translate("PCSX2Steam", "CREATE", 0));
        dirLabel_2->setText(QApplication::translate("PCSX2Steam", "D E S I G N E D   A N D   D E V E L O P E D   B Y   R A M B O R I G S", 0));
        iconPicBtn->setText(QString());
        resetButton->setText(QApplication::translate("PCSX2Steam", "RESET", 0));
    } // retranslateUi

};

namespace Ui {
    class PCSX2Steam: public Ui_PCSX2Steam {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PCSX2STEAM_H
