/********************************************************************************
** Form generated from reading UI file 'ShaderToolMain.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHADERTOOLMAIN_H
#define UI_SHADERTOOLMAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include "codeeditor.h"
#include "ctexturepainter.h"
#include "d3drenderwidget.h"

QT_BEGIN_NAMESPACE

class Ui_ShaderToolMain
{
public:
    QWidget *centralWidget;
    QPushButton *compileButton;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    D3DRenderWidget *widget;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    CodeEditor *plainTextEdit;
    QTextEdit *textEdit;
    QWidget *gridLayoutWidget_3;
    QGridLayout *gridLayout_3;
    CTexturePainter *widget_2;
    QTextBrowser *textBrowser;

    void setupUi(QMainWindow *ShaderToolMain)
    {
        if (ShaderToolMain->objectName().isEmpty())
            ShaderToolMain->setObjectName(QStringLiteral("ShaderToolMain"));
        ShaderToolMain->resize(1059, 797);
        centralWidget = new QWidget(ShaderToolMain);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        compileButton = new QPushButton(centralWidget);
        compileButton->setObjectName(QStringLiteral("compileButton"));
        compileButton->setGeometry(QRect(980, 520, 81, 31));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, -20, 531, 541));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        widget = new D3DRenderWidget(gridLayoutWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setEnabled(true);

        gridLayout->addWidget(widget, 1, 0, 1, 1);

        gridLayoutWidget_2 = new QWidget(centralWidget);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(530, 0, 531, 521));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        plainTextEdit = new CodeEditor(gridLayoutWidget_2);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setStyleSheet(QLatin1String(".QLineEdit, .QPlainTextEdit\n"
"{\n"
"background-color: rgb(76, 76, 76);\n"
"}"));
        plainTextEdit->setTabChangesFocus(true);

        gridLayout_2->addWidget(plainTextEdit, 0, 0, 1, 1);

        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(530, 520, 551, 31));
        textEdit->setStyleSheet(QLatin1String(".QTextEdit\n"
"{\n"
"background-color: rgb(76, 76, 76);\n"
"}"));
        textEdit->setReadOnly(true);
        gridLayoutWidget_3 = new QWidget(centralWidget);
        gridLayoutWidget_3->setObjectName(QStringLiteral("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(530, 550, 531, 251));
        gridLayout_3 = new QGridLayout(gridLayoutWidget_3);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        widget_2 = new CTexturePainter(gridLayoutWidget_3);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setStyleSheet(QLatin1String(".QLineEdit, .QPlainTextEdit\n"
"{\n"
"background-color: rgb(76, 76, 76);\n"
"}"));

        gridLayout_3->addWidget(widget_2, 0, 0, 1, 1);

        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(0, 520, 531, 281));
        textBrowser->setStyleSheet(QLatin1String(".QTextBrowser\n"
"{\n"
"background-color: rgb(76, 76, 76);\n"
"}"));
        ShaderToolMain->setCentralWidget(centralWidget);
        textEdit->raise();
        compileButton->raise();
        gridLayoutWidget->raise();
        gridLayoutWidget_2->raise();
        gridLayoutWidget_3->raise();
        textBrowser->raise();

        retranslateUi(ShaderToolMain);

        QMetaObject::connectSlotsByName(ShaderToolMain);
    } // setupUi

    void retranslateUi(QMainWindow *ShaderToolMain)
    {
        ShaderToolMain->setWindowTitle(QApplication::translate("ShaderToolMain", "CShaderToolMain", Q_NULLPTR));
        compileButton->setText(QApplication::translate("ShaderToolMain", "Compile", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ShaderToolMain: public Ui_ShaderToolMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHADERTOOLMAIN_H
