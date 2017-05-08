#include "ShaderManager.h"
#include "CodeEditor.h"

CShaderManager::CShaderManager()
	: m_pCodeEditorHandle(nullptr)
	, m_CurrentWorkingSlot(0)
{
}

CShaderManager::~CShaderManager()
{
}

void CShaderManager::OnAddShaderClick()
{
	QPushButton* btn1 = new QPushButton("btn1");
	QString a = QString::number(static_cast<int>(m_Shaders.size()));

	btn1->setText("Code" + QString(a));
	btn1->setStyleSheet(
		".QPushButton\n"
		"{\n"
		"background-color: rgb(76, 76, 76);\n"
		"text-color: rgb(255, 255, 255);\n"
		"border: 0;\n"
		"color:  rgb(255, 255, 255);\n"
		"font-family: Consolas, serif;\n"
		"}\n"
		"QPushButton:hover {\n"
		"    background-color: rgb(66, 66, 66);\n"
		"}"
	);
	m_pLayout->addWidget(btn1);
	AddShader();

	m_Buttons.push_back(btn1);

	int a2 = m_Shaders.size()-1;

	connect(btn1, &QPushButton::clicked,
		[=]() { this->ChangeActiveEditorShaderTo(a2); });
}


void CShaderManager::Initialize(CodeEditor * pCodeEditor, Ui_ShaderToolMain* pShaderTool)
{
	m_pCodeEditorHandle = pCodeEditor;
	connect(pShaderTool->addShader, SIGNAL(clicked()), this, SLOT(OnAddShaderClick()));

	m_pLayout = pShaderTool->shaderLayout;

	//Add the default shader.
	OnAddShaderClick();
	m_Shaders[m_CurrentWorkingSlot].code = m_DefaultShaderCode;

	//Set the default shader.
	m_pCodeEditorHandle->SetText(m_Shaders[0].code);
	ChangeActiveButton(0);
}

void CShaderManager::ChangeActiveEditorShaderTo(size_t slot)
{
	// If you want to change to a slot which doesn't exist or we already are working in this slot.
	if (slot > (m_Shaders.size() - 1) || slot == m_CurrentWorkingSlot)
		return;

	ChangeActiveButton(slot);

	// Change to the slot and save the current one.
	if (m_CurrentWorkingSlot != slot)
	{
		m_Shaders[m_CurrentWorkingSlot].code = m_pCodeEditorHandle->toPlainText();

		m_pCodeEditorHandle->SetText(m_Shaders[slot].code);
		m_CurrentWorkingSlot = slot;
	}
}

std::vector<SShaderCode>* CShaderManager::GetShaders()
{
	//TODO: remove this workarond of savign the current shader
	m_Shaders[m_CurrentWorkingSlot].code = m_pCodeEditorHandle->toPlainText();
	return &m_Shaders;
}

void CShaderManager::AddShader(QString code)
{
	SShaderCode shader;
	shader.code = code;
	shader.slot = m_Shaders.size();

	m_Shaders.push_back(shader);
}

void CShaderManager::ChangeActiveButton(int slot)
{
	//Change current 
	m_Buttons[m_CurrentWorkingSlot]->setStyleSheet(
		".QPushButton\n"
		"{\n"
		"background-color: rgb(76, 76, 76);\n"
		"text-color: rgb(255, 255, 255);\n"
		"border: 0;\n"
		"color:  rgb(255, 255, 255);\n"
		"font-family: Consolas, serif;\n"
		"}\n"
		"QPushButton:hover {\n"
		"    background-color: rgb(66, 66, 66);\n"
		"}"
		);

	m_Buttons[slot]->setStyleSheet(
		".QPushButton\n"
		"{\n"
		"background-color: rgb(56, 56, 56);\n"
		"text-color: rgb(255, 255, 255);\n"
		"border: 0;\n"
		"color:  rgb(255, 255, 255);\n"
		"font-family: Consolas, serif;\n"
		"}\n"
		"QPushButton:hover {\n"
		"    background-color: rgb(66, 66, 66);\n"
		"}"
	);
}
