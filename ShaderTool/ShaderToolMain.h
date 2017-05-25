#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_ShaderToolMain.h"
#include "DefaultScene.h"
#include "ShaderManager.h"
#include <CEngine.h>
#include "ShaderCreator.h"
#include "ProjectManager.h"

class CSyntaxHighlighter;
class CodeEditor;

class CShaderToolMain : public QMainWindow
{
	Q_OBJECT

public:
	CShaderToolMain(QWidget *parent = Q_NULLPTR);
	const QString m_WindowName = "ShaderTool";

protected:

public slots:
	void OnCompileClicked();
	void OnFullscreen();

private:
	Ui::ShaderToolMain m_MainUi;
	CodeEditor* m_CodeEditor;
	CSyntaxHighlighter* m_SyntaxHighlighter;
	CDefaultScene* m_pDefaultScene;
	CShaderCreator m_ShaderCreator;
	CShaderManager m_ShaderManager;
	CProjectManager m_ProjectManager;

private:
	void SetupCodeEditor();
};
