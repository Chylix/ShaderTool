#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_ShaderToolMain.h"
#include "DefaultScene.h"
#include <CEngine.h>
#include "ShaderCreator.h"

class CSyntaxHighlighter;
class CodeEditor;

class CShaderToolMain : public QMainWindow
{
	Q_OBJECT

public:
	CShaderToolMain(QWidget *parent = Q_NULLPTR);
	const QString m_WindowName = "ShaderTool";
	const QString m_ShaderDefaultCode =
		"struct PS_Data\n"
		"{\n"
		"  float4 position : SV_POSITION;\n"
		"  float2 uv : UV;\n"
		"};\n"
		"\n"
		"//Default Pixel Shader\n"
		"float4 PS_Main(PS_Data input) : SV_TARGET\n"
		"{\n"
		"  float4 color = float4(input.uv, 0.5+0.5*sin(GlobalTime), 1.0f);\n"
		"  return color;\n"
		"}";

protected:

public slots:
	void OnCompileClicked();

private:
	Ui::ShaderToolMain m_MainUi;
	CodeEditor* m_CodeEditor;
	CSyntaxHighlighter* m_SyntaxHighlighter;
	CDefaultScene* m_pDefaultScene;
	CShaderCreator m_ShaderCreator;


private:
	void SetupCodeEditor();
};

