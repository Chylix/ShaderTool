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
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include <codeeditor.h>
#include <ctexturepainter.h>
#include <d3drenderwidget.h>

QT_BEGIN_NAMESPACE

class Ui_ShaderToolMain
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QSplitter *splitter_8;
    QSplitter *splitter;
    QWidget *gridLayoutWidget;
    QGridLayout *ViewportLayout;
    D3DRenderWidget *Viewport;
    QSplitter *splitter_6;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *SceneLayout;
    QPushButton *AddSceneButton;
    QSplitter *splitter_5;
    QPushButton *SaveProjectButton;
    QPushButton *LoadProjectButton;
    QSplitter *splitter_4;
    QSplitter *splitter_3;
    QSplitter *splitter_2;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *ShaderLayout;
    QPushButton *AddShaderButton;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_3;
    CCodeEditorE *CodeEditor;
    QSplitter *splitter_7;
    QTextEdit *Console;
    QPushButton *CompileButton;
    CTexturePainter *ResourceViewport;

    void setupUi(QMainWindow *ShaderToolMain)
    {
        if (ShaderToolMain->objectName().isEmpty())
            ShaderToolMain->setObjectName(QStringLiteral("ShaderToolMain"));
        ShaderToolMain->resize(1376, 754);
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
        splitter_8 = new QSplitter(centralWidget);
        splitter_8->setObjectName(QStringLiteral("splitter_8"));
        splitter_8->setStyleSheet(QLatin1String("QSplitter::handle {\n"
"    background: rgb(56, 56, 56);\n"
"}"));
        splitter_8->setOrientation(Qt::Horizontal);
        splitter_8->setHandleWidth(1);
        splitter = new QSplitter(splitter_8);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Vertical);
        gridLayoutWidget = new QWidget(splitter);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        ViewportLayout = new QGridLayout(gridLayoutWidget);
        ViewportLayout->setSpacing(6);
        ViewportLayout->setContentsMargins(11, 11, 11, 11);
        ViewportLayout->setObjectName(QStringLiteral("ViewportLayout"));
        ViewportLayout->setContentsMargins(0, 0, 0, 0);
        Viewport = new D3DRenderWidget(gridLayoutWidget);
        Viewport->setObjectName(QStringLiteral("Viewport"));

        ViewportLayout->addWidget(Viewport, 0, 0, 1, 1);

        splitter->addWidget(gridLayoutWidget);
        splitter_6 = new QSplitter(splitter);
        splitter_6->setObjectName(QStringLiteral("splitter_6"));
        splitter_6->setStyleSheet(QLatin1String("QSplitter::handle {\n"
"    background: rgb(56, 56, 56);\n"
"}"));
        splitter_6->setOrientation(Qt::Vertical);
        horizontalLayoutWidget_2 = new QWidget(splitter_6);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        SceneLayout = new QHBoxLayout(horizontalLayoutWidget_2);
        SceneLayout->setSpacing(6);
        SceneLayout->setContentsMargins(11, 11, 11, 11);
        SceneLayout->setObjectName(QStringLiteral("SceneLayout"));
        SceneLayout->setSizeConstraint(QLayout::SetMaximumSize);
        SceneLayout->setContentsMargins(0, 0, 0, 0);
        AddSceneButton = new QPushButton(horizontalLayoutWidget_2);
        AddSceneButton->setObjectName(QStringLiteral("AddSceneButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(AddSceneButton->sizePolicy().hasHeightForWidth());
        AddSceneButton->setSizePolicy(sizePolicy1);
        AddSceneButton->setMaximumSize(QSize(3020000, 30));
        AddSceneButton->setStyleSheet(QLatin1String("			.QPushButton\n"
"			{\n"
"			background-color: rgb(56, 56, 56);\n"
"			text-color: rgb(255, 255, 255);\n"
"			border: 0;\n"
"			color:  rgb(255, 255, 255);\n"
"			font-family: Courier, serif;\n"
"			}\n"
"			QPushButton:hover {\n"
"			   background-color: rgb(66, 66, 66);\n"
"		}"));

        SceneLayout->addWidget(AddSceneButton);

        splitter_6->addWidget(horizontalLayoutWidget_2);
        splitter_5 = new QSplitter(splitter_6);
        splitter_5->setObjectName(QStringLiteral("splitter_5"));
        splitter_5->setEnabled(true);
        splitter_5->setStyleSheet(QLatin1String("QSplitter::handle {\n"
"    background: rgb(56, 56, 56);\n"
"}"));
        splitter_5->setOrientation(Qt::Horizontal);
        SaveProjectButton = new QPushButton(splitter_5);
        SaveProjectButton->setObjectName(QStringLiteral("SaveProjectButton"));
        sizePolicy1.setHeightForWidth(SaveProjectButton->sizePolicy().hasHeightForWidth());
        SaveProjectButton->setSizePolicy(sizePolicy1);
        SaveProjectButton->setMaximumSize(QSize(16777215, 50));
        SaveProjectButton->setBaseSize(QSize(0, 0));
        SaveProjectButton->setStyleSheet(QLatin1String("			.QPushButton\n"
"			{\n"
"			background-color: rgb(56, 56, 56);\n"
"			text-color: rgb(255, 255, 255);\n"
"			border: 0;\n"
"			color:  rgb(255, 255, 255);\n"
"			font-family: Courier, serif;\n"
"			}\n"
"			QPushButton:hover {\n"
"			   background-color: rgb(66, 66, 66);\n"
"		}"));
        splitter_5->addWidget(SaveProjectButton);
        LoadProjectButton = new QPushButton(splitter_5);
        LoadProjectButton->setObjectName(QStringLiteral("LoadProjectButton"));
        sizePolicy1.setHeightForWidth(LoadProjectButton->sizePolicy().hasHeightForWidth());
        LoadProjectButton->setSizePolicy(sizePolicy1);
        LoadProjectButton->setMinimumSize(QSize(0, 0));
        LoadProjectButton->setMaximumSize(QSize(16777215, 50));
        LoadProjectButton->setStyleSheet(QLatin1String("			.QPushButton\n"
"			{\n"
"			background-color: rgb(56, 56, 56);\n"
"			text-color: rgb(255, 255, 255);\n"
"			border: 0;\n"
"			color:  rgb(255, 255, 255);\n"
"			font-family: Courier, serif;\n"
"			}\n"
"			QPushButton:hover {\n"
"			   background-color: rgb(66, 66, 66);\n"
"		}"));
        splitter_5->addWidget(LoadProjectButton);
        splitter_6->addWidget(splitter_5);
        splitter->addWidget(splitter_6);
        splitter_8->addWidget(splitter);
        splitter_4 = new QSplitter(splitter_8);
        splitter_4->setObjectName(QStringLiteral("splitter_4"));
        splitter_4->setStyleSheet(QLatin1String("QSplitter::handle {\n"
"    background: rgb(56, 56, 56);\n"
"}"));
        splitter_4->setOrientation(Qt::Vertical);
        splitter_3 = new QSplitter(splitter_4);
        splitter_3->setObjectName(QStringLiteral("splitter_3"));
        splitter_3->setEnabled(true);
        splitter_3->setStyleSheet(QLatin1String("QSplitter::handle {\n"
"    background: rgb(56, 56, 56);\n"
"}"));
        splitter_3->setLineWidth(1);
        splitter_3->setOrientation(Qt::Vertical);
        splitter_2 = new QSplitter(splitter_3);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(splitter_2->sizePolicy().hasHeightForWidth());
        splitter_2->setSizePolicy(sizePolicy2);
        splitter_2->setStyleSheet(QLatin1String("QSplitter::handle {\n"
"    background: rgb(56, 56, 56);\n"
"}"));
        splitter_2->setLineWidth(0);
        splitter_2->setOrientation(Qt::Vertical);
        splitter_2->setHandleWidth(0);
        horizontalLayoutWidget = new QWidget(splitter_2);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        ShaderLayout = new QHBoxLayout(horizontalLayoutWidget);
        ShaderLayout->setSpacing(0);
        ShaderLayout->setContentsMargins(11, 11, 11, 11);
        ShaderLayout->setObjectName(QStringLiteral("ShaderLayout"));
        ShaderLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        ShaderLayout->setContentsMargins(0, 0, 0, 0);
        AddShaderButton = new QPushButton(horizontalLayoutWidget);
        AddShaderButton->setObjectName(QStringLiteral("AddShaderButton"));
        AddShaderButton->setEnabled(true);
        QSizePolicy sizePolicy3(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(AddShaderButton->sizePolicy().hasHeightForWidth());
        AddShaderButton->setSizePolicy(sizePolicy3);
        AddShaderButton->setMinimumSize(QSize(0, 0));
        AddShaderButton->setMaximumSize(QSize(30, 30));
        AddShaderButton->setStyleSheet(QLatin1String("			.QPushButton\n"
"			{\n"
"			background-color: rgb(56, 56, 56);\n"
"			text-color: rgb(255, 255, 255);\n"
"			border: 0;\n"
"			color:  rgb(255, 255, 255);\n"
"			font-family: Courier, serif;\n"
"			}\n"
"			QPushButton:hover {\n"
"			   background-color: rgb(66, 66, 66);\n"
"		}"));

        ShaderLayout->addWidget(AddShaderButton);

        splitter_2->addWidget(horizontalLayoutWidget);
        gridLayoutWidget_2 = new QWidget(splitter_2);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayout_3 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_3->setSpacing(0);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        CodeEditor = new CCodeEditorE(gridLayoutWidget_2);
        CodeEditor->setObjectName(QStringLiteral("CodeEditor"));
        CodeEditor->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_3->addWidget(CodeEditor, 0, 0, 1, 1);

        splitter_2->addWidget(gridLayoutWidget_2);
        splitter_3->addWidget(splitter_2);
        splitter_7 = new QSplitter(splitter_3);
        splitter_7->setObjectName(QStringLiteral("splitter_7"));
        splitter_7->setStyleSheet(QLatin1String("QSplitter::handle {\n"
"    background: rgb(66, 66, 66);\n"
"}"));
        splitter_7->setOrientation(Qt::Horizontal);
        Console = new QTextEdit(splitter_7);
        Console->setObjectName(QStringLiteral("Console"));
        sizePolicy.setHeightForWidth(Console->sizePolicy().hasHeightForWidth());
        Console->setSizePolicy(sizePolicy);
        Console->setMaximumSize(QSize(15845456, 50));
        Console->setStyleSheet(QLatin1String(".QTextEdit\n"
"{\n"
"background-color: rgb(66, 66, 66);\n"
"text-color: rgb(255, 255, 255);\n"
"border: 0;\n"
"color:  rgb(255, 255, 255);\n"
"font-family: Courier, serif;\n"
"}\n"
""));
        splitter_7->addWidget(Console);
        CompileButton = new QPushButton(splitter_7);
        CompileButton->setObjectName(QStringLiteral("CompileButton"));
        sizePolicy.setHeightForWidth(CompileButton->sizePolicy().hasHeightForWidth());
        CompileButton->setSizePolicy(sizePolicy);
        CompileButton->setMinimumSize(QSize(0, 0));
        CompileButton->setMaximumSize(QSize(70, 50));
        CompileButton->setStyleSheet(QLatin1String("			.QPushButton\n"
"			{\n"
"			background-color: rgb(66, 66, 66);\n"
"			text-color: rgb(255, 255, 255);\n"
"			border: 0;\n"
"			color:  rgb(255, 255, 255);\n"
"			font-family: Courier, serif;\n"
"			}\n"
"			QPushButton:hover {\n"
"			   background-color: rgb(76, 76, 76);\n"
"		}"));
        splitter_7->addWidget(CompileButton);
        splitter_3->addWidget(splitter_7);
        splitter_4->addWidget(splitter_3);
        ResourceViewport = new CTexturePainter(splitter_4);
        ResourceViewport->setObjectName(QStringLiteral("ResourceViewport"));
        splitter_4->addWidget(ResourceViewport);
        splitter_8->addWidget(splitter_4);

        gridLayout->addWidget(splitter_8, 0, 0, 1, 1);

        ShaderToolMain->setCentralWidget(centralWidget);

        retranslateUi(ShaderToolMain);

        QMetaObject::connectSlotsByName(ShaderToolMain);
    } // setupUi

    void retranslateUi(QMainWindow *ShaderToolMain)
    {
        ShaderToolMain->setWindowTitle(QApplication::translate("ShaderToolMain", "CShaderToolMain", Q_NULLPTR));
        AddSceneButton->setText(QApplication::translate("ShaderToolMain", "+", Q_NULLPTR));
        SaveProjectButton->setText(QApplication::translate("ShaderToolMain", "Save Project", Q_NULLPTR));
        LoadProjectButton->setText(QApplication::translate("ShaderToolMain", "Open Project", Q_NULLPTR));
        AddShaderButton->setText(QApplication::translate("ShaderToolMain", "+", Q_NULLPTR));
        CompileButton->setText(QApplication::translate("ShaderToolMain", "Compile", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ShaderToolMain: public Ui_ShaderToolMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHADERTOOLMAIN_H
