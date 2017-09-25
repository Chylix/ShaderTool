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
	if (m_IsActive == true)
	{
		AddShader();
		AddButton();
	}
}


void CShaderManager::Initialize(CCodeEditorE * pCodeEditor, Ui_ShaderToolMain* pShaderTool)
{
	m_pCodeEditorHandle = pCodeEditor;
	connect(pShaderTool->AddShaderButton, SIGNAL(clicked()), this, SLOT(OnAddShaderClick()));

	m_pLayout = pShaderTool->ShaderLayout;

	//Add the default shader.
	OnAddShaderClick();
	m_Shaders[m_CurrentWorkingSlot].code = m_DefaultShaderCode;

	m_pLayout->setSizeConstraint(QLayout::SizeConstraint::SetMaximumSize);

	//Set the default shader.
	m_pCodeEditorHandle->SetText(m_Shaders[0].code);
	ChangeActiveButton(0);
}

void CShaderManager::ChangeActiveEditorShaderTo(size_t slot)
{
	// If you want to change to a slot which doesn't exist or we already are working in this slot.
	if ((slot > (m_Shaders.size() - 1) || slot == m_CurrentWorkingSlot) && m_IsActive)
		return;

	if (m_IsActive)
	{
		ChangeActiveButton(slot);
		
		m_Shaders[m_CurrentWorkingSlot].code = m_pCodeEditorHandle->toPlainText();
	}

	m_pCodeEditorHandle->SetText(m_Shaders[slot].code);
	m_CurrentWorkingSlot = slot;
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

void CShaderManager::SetActive()
{
	if (m_IsActive == true)
		return;

	for (size_t i = 0; i < m_Shaders.size(); ++i)
	{
		AddButton(i);
		ChangeActiveEditorShaderTo(i);
	}

	//TODO: Rember which shader was active before
	// Set the last shader to active after switching sceen
	for (size_t i = 0; i < m_Buttons.size(); ++i)
	{
		m_Buttons[i]->SetAsActive(false);
	}

	m_CurrentWorkingSlot = m_Buttons.size()-1;
	m_Buttons[m_CurrentWorkingSlot]->SetAsActive(true);

	m_IsActive = true;
}

void CShaderManager::SetDisable()
{
	if (m_IsActive == false)
		return;

	for (CShaderManangerButton* button : m_Buttons)
	{
		m_pLayout->removeWidget(button);
		delete button;
	}

	m_Buttons.clear();

	m_IsActive = false;
}


void CShaderManager::AddButton(size_t connectToShader)
{
	QString a = QString::number(static_cast<int>(m_Shaders.size()));

	CShaderManangerButton* btn1 = new CShaderManangerButton();
	connect(btn1, SIGNAL(rightClicked()), this, SLOT(RemoveShader()));

	btn1->setText("Shader_" + QString(a));
	m_pLayout->addWidget(btn1);

	m_Buttons.push_back(btn1);

	size_t slot = connectToShader;

	if(connectToShader == UNDEFINED_CONNECT_SLOT)
		slot = m_Shaders.size() - 1;

	btn1->Init(slot, this);
}

const char * CShaderManager::SaveData()
{
	//for (size_t i = 0; i < m_Shaders.size(); i++)
	//{
	//	buffer.append(m_Shaders[i].code.toStdString());
	//	buffer.append("\n~\n");
	//}

	//return buffer.c_str();
	return nullptr;
}

void CShaderManager::LoadData(const char * pData)
{
	/*Reset();

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
	}*/
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
