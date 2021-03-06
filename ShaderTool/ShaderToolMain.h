#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_ShaderToolMain.h"
#include "DefaultScene.h"
#include "ShaderManager.h"
#include <CEngine.h>
#include "ShaderCreator.h"
#include "ProjectManager.h"
#include "SceneManager.h"
#include "Timeline.h"

class CSyntaxHighlighter;
class CCodeEditorE;

//#define SHIP_DEMO

class CShaderToolMain : public QMainWindow
{
	Q_OBJECT

public:
	CShaderToolMain(QWidget *parent = Q_NULLPTR);
	const QString m_WindowName = "Orbitor";

protected:
	virtual void paintEvent(QPaintEvent* evt) override;

public slots:
	void OnCompileClicked();
	void OnFullscreen();

private:
	Ui::ShaderToolMain m_MainUi;
	CCodeEditorE* m_CodeEditor;
	CSyntaxHighlighter* m_SyntaxHighlighter;
	CDefaultScene* m_pDefaultScene;
	CShaderCreator m_ShaderCreator;
	CSceneManager m_SceneManager;
	CProjectManager m_ProjectManager;
	CTimeline m_Timeline;

private:
	void SetupCodeEditor();
	void SetupTWScene();
};
