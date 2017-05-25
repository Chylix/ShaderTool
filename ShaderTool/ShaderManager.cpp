#include "ShaderManager.h"
#include "CodeEditor.h"
#include "ShaderManagerButton.h"

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
	AddShader();
	AddButton();
}


void CShaderManager::Initialize(CodeEditor * pCodeEditor, Ui_ShaderToolMain* pShaderTool)
{
	m_pCodeEditorHandle = pCodeEditor;
	connect(pShaderTool->addShader, SIGNAL(clicked()), this, SLOT(OnAddShaderClick()));

	m_pLayout = pShaderTool->shaderLayout;

	m_pLayout->setMargin(0);
	m_pLayout->setContentsMargins(QMargins(0, 0, 0, 0));
	m_pLayout->setSpacing(0);

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

void CShaderManager::RemoveShader(size_t slot)
{
	//You can't delete the first shader
	if (slot == 0)
		return;

	delete m_Buttons[slot];
	m_Shaders.erase(m_Shaders.begin() + slot);

	//m_pLayout->removeWidget(m_Buttons[slot]);

	m_Buttons.erase(m_Buttons.begin() + slot);

	for (size_t i = 0; i < m_Buttons.size(); i++)
	{
		m_Buttons[i]->UpdateSlot(i);
	}

	//TODO: implement a proper changing function
	if (slot == m_CurrentWorkingSlot)
	{
		m_CurrentWorkingSlot = 0;
		m_pCodeEditorHandle->SetText(m_Shaders[0].code);
	}
}

std::vector<SShaderCode>* CShaderManager::GetShaders()
{
	//TODO: remove this workarond of saving the current shader
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

void CShaderManager::AddButton()
{
	QString a = QString::number(static_cast<int>(m_Shaders.size()));

	CShaderManangerButton* btn1 = new CShaderManangerButton();
	connect(btn1, SIGNAL(rightClicked()), this, SLOT(RemoveShader()));

	btn1->setText("Shader_" + QString(a));
	m_pLayout->addWidget(btn1);

	m_Buttons.push_back(btn1);

	int a2 = m_Shaders.size() - 1;
	btn1->Init(a2, this);
}

const char * CShaderManager::SaveData()
{
	for (size_t i = 0; i < m_Shaders.size(); i++)
	{
		buffer.append(m_Shaders[i].code.toStdString());
		buffer.append("\n~\n");
	}

	return buffer.c_str();
}

void CShaderManager::LoadData(const char * pData)
{
	Reset();

	std::string data = pData;

	size_t q = 0;
	size_t iterator = 0;
	size_t iter = 0;

	while (q != std::string::npos)
	{
		SShaderCode shader;
		q = data.find("~", iterator);

		if (q == std::string::npos)
			break;

		if (iter == 0)
		{
			m_Shaders[iter].code = QString(data.substr(iterator, q - 1).c_str());
			m_Shaders[iter].slot = m_Shaders.size();
			m_pCodeEditorHandle->SetText(m_Shaders[0].code);
			m_CurrentWorkingSlot = 0;
			ChangeActiveButton(0);
		}
		else
		{
			AddShader(QString(data.substr(iterator, q - iterator - 1).c_str()));
			AddButton();
		}

		iterator = q + 1;

		iter++;
	}




}

void CShaderManager::ChangeActiveButton(int slot)
{
	//change the current one to be deactive
	m_Buttons[m_CurrentWorkingSlot]->SetAsActive(false);
	//change the new slot to active
	m_Buttons[slot]->SetAsActive(true);
}

void CShaderManager::Reset()
{
	for (int i = 0; i < m_Buttons.size(); i++)
		RemoveShader(i);
}
