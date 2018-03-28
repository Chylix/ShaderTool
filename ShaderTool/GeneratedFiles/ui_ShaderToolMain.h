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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include <audiowidget.h>
#include <codeeditor.h>
#include <ctexturepainter.h>
#include <d3drenderwidget.h>
#include <scenewidget.h>
#include <timelinewidget.h>

QT_BEGIN_NAMESPACE

class Ui_ShaderToolMain
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QSplitter *splitter_10;
    QSplitter *splitter_9;
    QWidget *verticalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *LoadProjectButton;
    QPushButton *SaveProjectButton;
    QSplitter *splitter_8;
    QWidget *gridLayoutWidget;
    QGridLayout *ViewportLayout;
    D3DRenderWidget *Viewport;
    QSplitter *splitter_6;
    QSplitter *splitter_5;
    QWidget *gridLayoutWidget_3;
    QGridLayout *TimelineActions;
    QLineEdit *Time;
    QPushButton *AddScene;
    QPushButton *Pause;
    QPushButton *Play;
    QPushButton *Stop;
    QSplitter *splitter;
    CTimelineWidget *Timeline;
    CSceneWidget *SceneWidget;
    CAudioWidget *AudioWidget;
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
        ShaderToolMain->resize(1376, 1169);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ShaderToolMain->sizePolicy().hasHeightForWidth());
        ShaderToolMain->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QStringLiteral("../x64/Debug/icon1.ico"), QSize(), QIcon::Normal, QIcon::Off);
        ShaderToolMain->setWindowIcon(icon);
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
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        splitter_10 = new QSplitter(centralWidget);
        splitter_10->setObjectName(QStringLiteral("splitter_10"));
        splitter_10->setStyleSheet(QLatin1String("QSplitter::handle {\n"
"    background: rgb(40, 40, 40);\n"
"}"));
        splitter_10->setLineWidth(1);
        splitter_10->setOrientation(Qt::Horizontal);
        splitter_10->setHandleWidth(5);
        splitter_9 = new QSplitter(splitter_10);
        splitter_9->setObjectName(QStringLiteral("splitter_9"));
        splitter_9->setStyleSheet(QLatin1String("QSplitter::handle {\n"
"    background: rgb(40, 40, 40);\n"
"}"));
        splitter_9->setOrientation(Qt::Vertical);
        splitter_9->setHandleWidth(1);
        verticalLayoutWidget = new QWidget(splitter_9);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        horizontalLayout = new QHBoxLayout(verticalLayoutWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        LoadProjectButton = new QPushButton(verticalLayoutWidget);
        LoadProjectButton->setObjectName(QStringLiteral("LoadProjectButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(LoadProjectButton->sizePolicy().hasHeightForWidth());
        LoadProjectButton->setSizePolicy(sizePolicy1);
        LoadProjectButton->setMinimumSize(QSize(0, 0));
        LoadProjectButton->setMaximumSize(QSize(16777215, 30));
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

        horizontalLayout->addWidget(LoadProjectButton);

        SaveProjectButton = new QPushButton(verticalLayoutWidget);
        SaveProjectButton->setObjectName(QStringLiteral("SaveProjectButton"));
        sizePolicy1.setHeightForWidth(SaveProjectButton->sizePolicy().hasHeightForWidth());
        SaveProjectButton->setSizePolicy(sizePolicy1);
        SaveProjectButton->setMaximumSize(QSize(16777215, 30));
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

        horizontalLayout->addWidget(SaveProjectButton);

        splitter_9->addWidget(verticalLayoutWidget);
        splitter_8 = new QSplitter(splitter_9);
        splitter_8->setObjectName(QStringLiteral("splitter_8"));
        splitter_8->setStyleSheet(QLatin1String("QSplitter::handle {\n"
"    background: rgb(40, 40, 40);\n"
"}"));
        splitter_8->setOrientation(Qt::Vertical);
        splitter_8->setHandleWidth(1);
        gridLayoutWidget = new QWidget(splitter_8);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        ViewportLayout = new QGridLayout(gridLayoutWidget);
        ViewportLayout->setSpacing(6);
        ViewportLayout->setContentsMargins(11, 11, 11, 11);
        ViewportLayout->setObjectName(QStringLiteral("ViewportLayout"));
        ViewportLayout->setContentsMargins(0, 0, 0, 0);
        Viewport = new D3DRenderWidget(gridLayoutWidget);
        Viewport->setObjectName(QStringLiteral("Viewport"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(Viewport->sizePolicy().hasHeightForWidth());
        Viewport->setSizePolicy(sizePolicy2);
        Viewport->setMinimumSize(QSize(200, 50));

        ViewportLayout->addWidget(Viewport, 0, 0, 1, 1);

        splitter_8->addWidget(gridLayoutWidget);
        splitter_6 = new QSplitter(splitter_8);
        splitter_6->setObjectName(QStringLiteral("splitter_6"));
        splitter_6->setStyleSheet(QLatin1String("QSplitter::handle {\n"
"    background: rgb(40, 40, 40);\n"
"}"));
        splitter_6->setOrientation(Qt::Vertical);
        splitter_6->setHandleWidth(1);
        splitter_5 = new QSplitter(splitter_6);
        splitter_5->setObjectName(QStringLiteral("splitter_5"));
        splitter_5->setStyleSheet(QLatin1String("QSplitter::handle {\n"
"    background: rgb(40, 40, 40);\n"
"}"));
        splitter_5->setOrientation(Qt::Vertical);
        splitter_5->setHandleWidth(1);
        gridLayoutWidget_3 = new QWidget(splitter_5);
        gridLayoutWidget_3->setObjectName(QStringLiteral("gridLayoutWidget_3"));
        TimelineActions = new QGridLayout(gridLayoutWidget_3);
        TimelineActions->setSpacing(0);
        TimelineActions->setContentsMargins(11, 11, 11, 11);
        TimelineActions->setObjectName(QStringLiteral("TimelineActions"));
        TimelineActions->setSizeConstraint(QLayout::SetMaximumSize);
        TimelineActions->setContentsMargins(0, 0, 0, 0);
        Time = new QLineEdit(gridLayoutWidget_3);
        Time->setObjectName(QStringLiteral("Time"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(Time->sizePolicy().hasHeightForWidth());
        Time->setSizePolicy(sizePolicy3);
        Time->setMaximumSize(QSize(16777215, 30));
        Time->setStyleSheet(QLatin1String("			.QLineEdit\n"
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

        TimelineActions->addWidget(Time, 0, 4, 1, 1);

        AddScene = new QPushButton(gridLayoutWidget_3);
        AddScene->setObjectName(QStringLiteral("AddScene"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(AddScene->sizePolicy().hasHeightForWidth());
        AddScene->setSizePolicy(sizePolicy4);
        AddScene->setMaximumSize(QSize(16777215, 30));
        AddScene->setStyleSheet(QLatin1String("			.QPushButton\n"
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

        TimelineActions->addWidget(AddScene, 0, 0, 1, 1);

        Pause = new QPushButton(gridLayoutWidget_3);
        Pause->setObjectName(QStringLiteral("Pause"));
        sizePolicy4.setHeightForWidth(Pause->sizePolicy().hasHeightForWidth());
        Pause->setSizePolicy(sizePolicy4);
        Pause->setMaximumSize(QSize(16777215, 30));
        Pause->setStyleSheet(QLatin1String("			.QPushButton\n"
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

        TimelineActions->addWidget(Pause, 0, 2, 1, 1);

        Play = new QPushButton(gridLayoutWidget_3);
        Play->setObjectName(QStringLiteral("Play"));
        sizePolicy4.setHeightForWidth(Play->sizePolicy().hasHeightForWidth());
        Play->setSizePolicy(sizePolicy4);
        Play->setMaximumSize(QSize(16777215, 30));
        Play->setStyleSheet(QLatin1String("			.QPushButton\n"
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

        TimelineActions->addWidget(Play, 0, 1, 1, 1);

        Stop = new QPushButton(gridLayoutWidget_3);
        Stop->setObjectName(QStringLiteral("Stop"));
        sizePolicy4.setHeightForWidth(Stop->sizePolicy().hasHeightForWidth());
        Stop->setSizePolicy(sizePolicy4);
        Stop->setMaximumSize(QSize(16777215, 30));
        Stop->setStyleSheet(QLatin1String("			.QPushButton\n"
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

        TimelineActions->addWidget(Stop, 0, 3, 1, 1);

        splitter_5->addWidget(gridLayoutWidget_3);
        splitter = new QSplitter(splitter_5);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setStyleSheet(QLatin1String("QSplitter::handle {\n"
"    background: rgb(40, 40, 40);\n"
"}"));
        splitter->setOrientation(Qt::Vertical);
        splitter->setHandleWidth(1);
        Timeline = new CTimelineWidget(splitter);
        Timeline->setObjectName(QStringLiteral("Timeline"));
        Timeline->setMinimumSize(QSize(0, 100));
        Timeline->setAutoFillBackground(true);
        splitter->addWidget(Timeline);
        SceneWidget = new CSceneWidget(splitter);
        SceneWidget->setObjectName(QStringLiteral("SceneWidget"));
        SceneWidget->setMinimumSize(QSize(200, 40));
        splitter->addWidget(SceneWidget);
        splitter_5->addWidget(splitter);
        splitter_6->addWidget(splitter_5);
        AudioWidget = new CAudioWidget(splitter_6);
        AudioWidget->setObjectName(QStringLiteral("AudioWidget"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(AudioWidget->sizePolicy().hasHeightForWidth());
        AudioWidget->setSizePolicy(sizePolicy5);
        AudioWidget->setMinimumSize(QSize(0, 20));
        splitter_6->addWidget(AudioWidget);
        splitter_8->addWidget(splitter_6);
        splitter_9->addWidget(splitter_8);
        splitter_10->addWidget(splitter_9);
        splitter_4 = new QSplitter(splitter_10);
        splitter_4->setObjectName(QStringLiteral("splitter_4"));
        splitter_4->setStyleSheet(QLatin1String("QSplitter::handle {\n"
"    background: rgb(50, 50, 50);\n"
"}"));
        splitter_4->setOrientation(Qt::Vertical);
        splitter_4->setHandleWidth(1);
        splitter_3 = new QSplitter(splitter_4);
        splitter_3->setObjectName(QStringLiteral("splitter_3"));
        splitter_3->setEnabled(true);
        splitter_3->setStyleSheet(QLatin1String("QSplitter::handle {\n"
"    background: rgb(50, 50, 50);\n"
"}"));
        splitter_3->setLineWidth(1);
        splitter_3->setOrientation(Qt::Vertical);
        splitter_3->setHandleWidth(1);
        splitter_2 = new QSplitter(splitter_3);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setEnabled(true);
        sizePolicy4.setHeightForWidth(splitter_2->sizePolicy().hasHeightForWidth());
        splitter_2->setSizePolicy(sizePolicy4);
        splitter_2->setStyleSheet(QLatin1String("QSplitter::handle {\n"
"    background: rgb(50, 50, 50);\n"
"}"));
        splitter_2->setLineWidth(0);
        splitter_2->setOrientation(Qt::Vertical);
        splitter_2->setHandleWidth(1);
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
        sizePolicy2.setHeightForWidth(AddShaderButton->sizePolicy().hasHeightForWidth());
        AddShaderButton->setSizePolicy(sizePolicy2);
        AddShaderButton->setMinimumSize(QSize(30, 30));
        AddShaderButton->setMaximumSize(QSize(30, 5235235));
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
"    background: rgb(50, 50, 50);\n"
"}"));
        splitter_7->setOrientation(Qt::Horizontal);
        splitter_7->setHandleWidth(1);
        Console = new QTextEdit(splitter_7);
        Console->setObjectName(QStringLiteral("Console"));
        sizePolicy.setHeightForWidth(Console->sizePolicy().hasHeightForWidth());
        Console->setSizePolicy(sizePolicy);
        Console->setMaximumSize(QSize(15845456, 70));
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
        CompileButton->setMinimumSize(QSize(70, 50));
        CompileButton->setMaximumSize(QSize(70, 100));
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
        splitter_10->addWidget(splitter_4);

        gridLayout->addWidget(splitter_10, 0, 0, 1, 1);

        ShaderToolMain->setCentralWidget(centralWidget);

        retranslateUi(ShaderToolMain);

        QMetaObject::connectSlotsByName(ShaderToolMain);
    } // setupUi

    void retranslateUi(QMainWindow *ShaderToolMain)
    {
        ShaderToolMain->setWindowTitle(QApplication::translate("ShaderToolMain", "CShaderToolMain", Q_NULLPTR));
        LoadProjectButton->setText(QApplication::translate("ShaderToolMain", "Open Project", Q_NULLPTR));
        SaveProjectButton->setText(QApplication::translate("ShaderToolMain", "Save Project", Q_NULLPTR));
        Time->setText(QApplication::translate("ShaderToolMain", "00:00:00", Q_NULLPTR));
        AddScene->setText(QApplication::translate("ShaderToolMain", "Add New Scene", Q_NULLPTR));
        Pause->setText(QApplication::translate("ShaderToolMain", "Pause", Q_NULLPTR));
        Play->setText(QApplication::translate("ShaderToolMain", "Play", Q_NULLPTR));
        Stop->setText(QApplication::translate("ShaderToolMain", "Stop", Q_NULLPTR));
        AddShaderButton->setText(QApplication::translate("ShaderToolMain", "+", Q_NULLPTR));
        CompileButton->setText(QApplication::translate("ShaderToolMain", "Compile", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ShaderToolMain: public Ui_ShaderToolMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHADERTOOLMAIN_H
