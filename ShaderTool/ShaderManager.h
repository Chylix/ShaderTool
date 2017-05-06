#pragma once
#include <qstring.h>
#include <vector>
#include "ui_ShaderToolMain.h"

class CodeEditor;

struct SShaderCode
{
	QString code;
	int slot;
};

class CShaderManager : public QObject
{
	Q_OBJECT

public slots:
	void OnAddShaderClick();

public:
	CShaderManager();
	~CShaderManager();

	void Initialize(CodeEditor* pCodeEditor, Ui_ShaderToolMain* pShaderTool);
	void ChangeActiveEditorShaderTo(size_t slot);
	std::vector<SShaderCode>* GetShaders();
	void AddShader(QString code = QString());

private:
	void ChangeActiveButton(int slot);

private:
	//This is the default shader code
	const QString m_DefaultShaderCode = 
		"//Default input descriptor\n"
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

private:
	CodeEditor* m_pCodeEditorHandle;
	QVBoxLayout* m_pLayout;
	std::vector<SShaderCode> m_Shaders;
	std::vector<QPushButton*> m_Buttons;
	size_t m_CurrentWorkingSlot;
};