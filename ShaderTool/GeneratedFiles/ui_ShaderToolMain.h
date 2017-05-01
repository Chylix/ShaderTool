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
    QWidget *gridLayoutWidget;
    QGridLayout *viewportLayout;
    D3DRenderWidget *viewport;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    CodeEditor *plainTextEdit;
    QWidget *gridLayoutWidget_3;
    QGridLayout *resourceLyout;
    CTexturePainter *resourceViewer;
    QTextBrowser *textBrowser;
    QTextEdit *textEdit;
    QPushButton *compileButton;

    void setupUi(QMainWindow *ShaderToolMain)
    {
        if (ShaderToolMain->objectName().isEmpty())
            ShaderToolMain->setObjectName(QStringLiteral("ShaderToolMain"));
        ShaderToolMain->resize(1058, 797);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ShaderToolMain->sizePolicy().hasHeightForWidth());
        ShaderToolMain->setSizePolicy(sizePolicy);
        ShaderToolMain->setWindowOpacity(1);
        ShaderToolMain->setStyleSheet(QStringLiteral(""));
        centralWidget = new QWidget(ShaderToolMain);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, -20, 531, 541));
        viewportLayout = new QGridLayout(gridLayoutWidget);
        viewportLayout->setSpacing(6);
        viewportLayout->setContentsMargins(11, 11, 11, 11);
        viewportLayout->setObjectName(QStringLiteral("viewportLayout"));
        viewportLayout->setContentsMargins(0, 0, 0, 0);
        viewport = new D3DRenderWidget(gridLayoutWidget);
        viewport->setObjectName(QStringLiteral("viewport"));
        viewport->setEnabled(true);

        viewportLayout->addWidget(viewport, 1, 0, 1, 1);

        gridLayoutWidget_2 = new QWidget(centralWidget);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(530, 0, 531, 491));
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
"border: 0;\n"
"}"));
        plainTextEdit->setTabChangesFocus(true);

        gridLayout_2->addWidget(plainTextEdit, 0, 0, 1, 1);

        gridLayoutWidget_3 = new QWidget(centralWidget);
        gridLayoutWidget_3->setObjectName(QStringLiteral("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(530, 520, 531, 281));
        resourceLyout = new QGridLayout(gridLayoutWidget_3);
        resourceLyout->setSpacing(6);
        resourceLyout->setContentsMargins(11, 11, 11, 11);
        resourceLyout->setObjectName(QStringLiteral("resourceLyout"));
        resourceLyout->setContentsMargins(0, 0, 0, 0);
        resourceViewer = new CTexturePainter(gridLayoutWidget_3);
        resourceViewer->setObjectName(QStringLiteral("resourceViewer"));
        resourceViewer->setStyleSheet(QLatin1String(".QLineEdit, .QPlainTextEdit\n"
"{\n"
"border: 0;\n"
"}"));

        resourceLyout->addWidget(resourceViewer, 0, 0, 1, 1);

        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(0, 520, 531, 281));
        textBrowser->setStyleSheet(QLatin1String(".QTextBrowser\n"
"{\n"
"background-color: rgb(76, 76, 76);\n"
"border: 0;\n"
"}"));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(530, 490, 551, 31));
        textEdit->setStyleSheet(QLatin1String(".QTextEdit\n"
"{\n"
"background-color: rgb(46, 46, 46);\n"
"border: 0;\n"
"}"));
        textEdit->setReadOnly(true);
        compileButton = new QPushButton(centralWidget);
        compileButton->setObjectName(QStringLiteral("compileButton"));
        compileButton->setGeometry(QRect(990, 490, 75, 31));
        compileButton->setStyleSheet(QLatin1String(".QPushButton\n"
"{\n"
"background-color: rgb(56, 56, 56);\n"
"text-color: rgb(255, 255, 255);\n"
"border: 0;\n"
"color:  rgb(255, 255, 255);\n"
"font-family: Consolas, serif;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgb(66, 66, 66);\n"
"}"));
        ShaderToolMain->setCentralWidget(centralWidget);

        retranslateUi(ShaderToolMain);

        QMetaObject::connectSlotsByName(ShaderToolMain);
    } // setupUi

    void retranslateUi(QMainWindow *ShaderToolMain)
    {
        ShaderToolMain->setWindowTitle(QApplication::translate("ShaderToolMain", "CShaderToolMain", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        compileButton->setWhatsThis(QApplication::translate("ShaderToolMain", "<html><head/><body><p>Compile shader</p></body></html>", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        compileButton->setText(QApplication::translate("ShaderToolMain", "Compile", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ShaderToolMain: public Ui_ShaderToolMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHADERTOOLMAIN_H
