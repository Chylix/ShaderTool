#pragma once
#include <qstring.h>
#include <vector>
#include <limits>
#include "ui_ShaderToolMain.h"
#include "ISerializer.h"

//class CodeEditor;
class CShaderManangerButton;

#define UNDEFINED_CONNECT_SLOT 473748

struct SShaderCode
{
	QString code;
	int slot;
};

class CShaderManager : public QObject, public ISerializer
{
	Q_OBJECT

public slots:
	void OnAddShaderClick();

public:
	CShaderManager();
	~CShaderManager();

	void Initialize(CCodeEditorE* pCodeEditor, Ui_ShaderToolMain* pShaderTool);
	void ChangeActiveEditorShaderTo(size_t slot);
	void RemoveShader(size_t slot);
	std::vector<SShaderCode>* GetShaders();
	void AddShader(QString code = QString());
	void AddButton(size_t connectToSlot = UNDEFINED_CONNECT_SLOT);


	void SetActive();
	void SetDisable();

	//ISerializer
	const char* SaveData() final;
	void LoadData(const char* pData) final;
	std::string buffer;
	//~ISerializer

private:
	void ChangeActiveButton(int slot);
	void Reset();

private:
	//This is the default shader code
	const QString m_DefaultShaderCode = 
		"struct PS_Data\n"
		"{\n"
		"	float4 position : SV_POSITION;\n"
		"	float2 uv : UV;\n"
		"};\n "
		"//Default Pixel Shader\n"
		"float4 PS_Main(PS_Data input) : SV_TARGET\n"
		"{\n"
		"	float4 color = float4(input.uv, 0.5+0.5*sin(GlobalTime), 1.0f);\n"
		"	return color;\n"
		"}";

private:
	CCodeEditorE* m_pCodeEditorHandle;
	QHBoxLayout* m_pLayout;
	std::vector<SShaderCode> m_Shaders;
	std::vector<CShaderManangerButton*> m_Buttons;
	size_t m_CurrentWorkingSlot;
	bool m_IsActive = true;
};
