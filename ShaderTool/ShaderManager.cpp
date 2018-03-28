#include "ShaderManager.h"
#include "CodeEditor.h"
#include "ShaderManagerButton.h"
#include "SerializerChunk.h"
#include <qlayoutitem.h>
#include "Console.h"

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
		
		// Check if this shader failed compilation
		if (m_ShaderFailed && slot == m_ErrorShaderSlot)
		{
			m_pCodeEditorHandle->SetErrorLine(m_ErrorLine);
			CConsole::Instance().PrintShaderError(m_ErrorString.c_str());
		}
		else
		{
			m_pCodeEditorHandle->RemoveErrorLine();
			//CConsole::Instance().PrintText("Compilation successful", CConsole::EPrintType::Success);
		}

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

	m_Shaders[m_CurrentWorkingSlot].code = m_pCodeEditorHandle->toPlainText();

	for (CShaderManangerButton* button : m_Buttons)
	{
		m_pLayout->removeWidget(button);
		delete button;
	}

	m_Buttons.clear();

	m_IsActive = false;
}


void CShaderManager::SetShaderError(int lineNumber, std::string errorMessage, int shaderSlot)
{
	m_ErrorString = errorMessage;
	m_ErrorShaderSlot = shaderSlot;
	m_ErrorLine = lineNumber;
	m_ShaderFailed = true;

	if (m_CurrentWorkingSlot == shaderSlot)
	{
		m_pCodeEditorHandle->SetErrorLine(m_ErrorLine);
		CConsole::Instance().PrintShaderError(m_ErrorString.c_str());
	}
}

void CShaderManager::ClearShaderError()
{
	m_ErrorString = "";
	m_ErrorShaderSlot = 0;
	m_ErrorLine = 0;
	m_ShaderFailed = false;
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

void CShaderManager::Release()
{
	this->disconnect();
}

const char * CShaderManager::SaveData()
{
	buffer.clear();

	for (size_t i = 0; i < m_Shaders.size(); i++)
	{
		buffer.append("~|~\n");
		buffer.append(m_Shaders[i].code.toStdString());
		buffer.append("\n~|~\n");
	}

	return buffer.c_str();
}

void CShaderManager::LoadData(CSerializerChunk* pData)
{
	Reset();

	std::string data = pData->GetChunk();

	size_t start = 0;
	size_t iterator = 0;
	size_t iter = 0;

	while (start != std::string::npos)
	{
		SShaderCode shader;
		start = data.find("~|~", iterator);
		if (start == std::string::npos)
			break;

		iterator = start + 3;
		size_t end = data.find("~|~", iterator);

		if (iter == 0)
		{
			std::string a = data.substr(iterator+2, end - iterator-4);
			m_Shaders[iter].code = QString(a.c_str());
			m_Shaders[iter].slot = m_Shaders.size();
			m_pCodeEditorHandle->SetText(m_Shaders[iter].code);
			m_CurrentWorkingSlot = iter;
		}
		else
		{
			AddShader(QString(data.substr(iterator+2, end - iterator - 4).c_str()));
			AddButton();
		}

		iterator = end + 3;

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
