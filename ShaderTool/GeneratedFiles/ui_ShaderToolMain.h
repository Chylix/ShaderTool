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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
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
    QGridLayout *gridLayout;
    CTexturePainter *resourceViewer;
    QGridLayout *viewportLayout;
    D3DRenderWidget *viewport;
    QGridLayout *codelayout;
    CodeEditor *plainTextEdit;
    QGridLayout *resourceLyout;
    QHBoxLayout *shaderLayout;
    QPushButton *addShader;
    QHBoxLayout *horizontalLayout;
    QPushButton *SaveProject;
    QPushButton *OpenProject;
    QHBoxLayout *console;
    QTextEdit *textEdit;
    QPushButton *compileButton;

    void setupUi(QMainWindow *ShaderToolMain)
    {
        if (ShaderToolMain->objectName().isEmpty())
            ShaderToolMain->setObjectName(QStringLiteral("ShaderToolMain"));
        ShaderToolMain->resize(1107, 795);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ShaderToolMain->sizePolicy().hasHeightForWidth());
        ShaderToolMain->setSizePolicy(sizePolicy);
        ShaderToolMain->setWindowOpacity(1);
        ShaderToolMain->setStyleSheet(QStringLiteral(""));
        centralWidget = new QWidget(ShaderToolMain);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QLatin1String("    QFrame::layout { margin: 0px }\n"
"     \n"
"    QFrame {\n"
"    	margin-top: 0px;\n"
"    	margin-right: 0px;\n"
"    	margin-bottom: 0px;\n"
"    	margin-left: 0px;\n"
"    	spacing: 0px;\n"
"    	padding: 0px;\n"
"    }\n"
"\n"
""));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        resourceViewer = new CTexturePainter(centralWidget);
        resourceViewer->setObjectName(QStringLiteral("resourceViewer"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(resourceViewer->sizePolicy().hasHeightForWidth());
        resourceViewer->setSizePolicy(sizePolicy1);
        resourceViewer->setStyleSheet(QLatin1String(".QLineEdit, .QPlainTextEdit\n"
"{\n"
"border: 0;\n"
"}"));

        gridLayout->addWidget(resourceViewer, 5, 1, 1, 1);

        viewportLayout = new QGridLayout();
        viewportLayout->setSpacing(6);
        viewportLayout->setObjectName(QStringLiteral("viewportLayout"));
        viewport = new D3DRenderWidget(centralWidget);
        viewport->setObjectName(QStringLiteral("viewport"));
        viewport->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(60);
        sizePolicy2.setVerticalStretch(60);
        sizePolicy2.setHeightForWidth(viewport->sizePolicy().hasHeightForWidth());
        viewport->setSizePolicy(sizePolicy2);
        viewport->setMinimumSize(QSize(600, 600));

        viewportLayout->addWidget(viewport, 1, 0, 1, 1);


        gridLayout->addLayout(viewportLayout, 0, 0, 5, 1);

        codelayout = new QGridLayout();
        codelayout->setSpacing(6);
        codelayout->setObjectName(QStringLiteral("codelayout"));
        plainTextEdit = new CodeEditor(centralWidget);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        sizePolicy1.setHeightForWidth(plainTextEdit->sizePolicy().hasHeightForWidth());
        plainTextEdit->setSizePolicy(sizePolicy1);
        plainTextEdit->setMinimumSize(QSize(500, 400));
        plainTextEdit->setFocusPolicy(Qt::ClickFocus);
        plainTextEdit->setStyleSheet(QLatin1String(".QLineEdit, .QPlainTextEdit\n"
"{\n"
"background-color: rgb(76, 76, 76);\n"
"border: 0;\n"
"}"));
        plainTextEdit->setTabChangesFocus(false);
        plainTextEdit->setTabStopWidth(20);

        codelayout->addWidget(plainTextEdit, 0, 0, 1, 1);


        gridLayout->addLayout(codelayout, 2, 1, 1, 2);

        resourceLyout = new QGridLayout();
        resourceLyout->setSpacing(6);
        resourceLyout->setObjectName(QStringLiteral("resourceLyout"));

        gridLayout->addLayout(resourceLyout, 7, 1, 1, 2);

        shaderLayout = new QHBoxLayout();
        shaderLayout->setSpacing(0);
        shaderLayout->setObjectName(QStringLiteral("shaderLayout"));
        shaderLayout->setSizeConstraint(QLayout::SetNoConstraint);
        addShader = new QPushButton(centralWidget);
        addShader->setObjectName(QStringLiteral("addShader"));
        sizePolicy.setHeightForWidth(addShader->sizePolicy().hasHeightForWidth());
        addShader->setSizePolicy(sizePolicy);
        addShader->setMinimumSize(QSize(40, 40));
        addShader->setStyleSheet(QLatin1String(".QPushButton\n"
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

        shaderLayout->addWidget(addShader, 0, Qt::AlignRight);


        gridLayout->addLayout(shaderLayout, 0, 1, 1, 2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        SaveProject = new QPushButton(centralWidget);
        SaveProject->setObjectName(QStringLiteral("SaveProject"));
        sizePolicy1.setHeightForWidth(SaveProject->sizePolicy().hasHeightForWidth());
        SaveProject->setSizePolicy(sizePolicy1);
        SaveProject->setStyleSheet(QLatin1String(".QPushButton\n"
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

        horizontalLayout->addWidget(SaveProject);

        OpenProject = new QPushButton(centralWidget);
        OpenProject->setObjectName(QStringLiteral("OpenProject"));
        sizePolicy1.setHeightForWidth(OpenProject->sizePolicy().hasHeightForWidth());
        OpenProject->setSizePolicy(sizePolicy1);
        OpenProject->setStyleSheet(QLatin1String(".QPushButton\n"
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

        horizontalLayout->addWidget(OpenProject);


        gridLayout->addLayout(horizontalLayout, 5, 0, 1, 1);

        console = new QHBoxLayout();
        console->setSpacing(0);
        console->setObjectName(QStringLiteral("console"));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setEnabled(true);
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy3);
        textEdit->setMinimumSize(QSize(0, 0));
        textEdit->setMaximumSize(QSize(16777215, 40));
        textEdit->setStyleSheet(QLatin1String(".QTextEdit\n"
"{\n"
"background-color: rgb(46, 46, 46);\n"
"border: 0;\n"
"}"));
        textEdit->setReadOnly(true);

        console->addWidget(textEdit);

        compileButton = new QPushButton(centralWidget);
        compileButton->setObjectName(QStringLiteral("compileButton"));
        sizePolicy.setHeightForWidth(compileButton->sizePolicy().hasHeightForWidth());
        compileButton->setSizePolicy(sizePolicy);
        compileButton->setMinimumSize(QSize(55, 40));
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

        console->addWidget(compileButton);


        gridLayout->addLayout(console, 3, 1, 1, 1);

        ShaderToolMain->setCentralWidget(centralWidget);

        retranslateUi(ShaderToolMain);

        QMetaObject::connectSlotsByName(ShaderToolMain);
    } // setupUi

    void retranslateUi(QMainWindow *ShaderToolMain)
    {
        ShaderToolMain->setWindowTitle(QApplication::translate("ShaderToolMain", "CShaderToolMain", Q_NULLPTR));
        addShader->setText(QApplication::translate("ShaderToolMain", "+", Q_NULLPTR));
        SaveProject->setText(QApplication::translate("ShaderToolMain", "Save Project", Q_NULLPTR));
        OpenProject->setText(QApplication::translate("ShaderToolMain", "Open Project", Q_NULLPTR));
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
