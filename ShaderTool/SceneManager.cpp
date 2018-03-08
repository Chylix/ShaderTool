#include "SceneManager.h"
#include "SceneButton.h"
#include "ShaderManager.h"
#include "SerializerChunk.h"
#include <string>  

CSceneManager::CSceneManager()
{

}
CSceneManager::~CSceneManager()
{

}

void clearLayout(QLayout *layout)
{
QLayoutItem *item;
while ((item = layout->takeAt(0))) {
	if (item->layout()) {
		clearLayout(item->layout());
		delete item->layout();
	}
	if (item->widget()) {
		//delete item->widget();
	}
	delete item;
}
}

void CSceneManager::OnOrderChanged(int newVal)
{
	// Ignore invalid input
	if (newVal == m_CurrentActiveScene || newVal > m_Scenes.size()-1 || newVal < 0)
		return;

	std::swap(m_Scenes[m_CurrentActiveScene], m_Scenes[newVal]);

	clearLayout(m_pSceneLayout);
	//m_pSceneLayout->removeWidget(m_Buttons[m_CurrentActiveScene]);
	//m_pSceneLayout->insertWidget(newVal, m_Buttons[m_CurrentActiveScene]);

	std::swap(m_Buttons[m_CurrentActiveScene], m_Buttons[newVal]);

	for (auto* button : m_Buttons)
	{
		m_pSceneLayout->addWidget(button);
	}

	UpdateOrder();

	m_CurrentActiveScene = newVal;
}

void CSceneManager::OnAddSceneClick()
{
	// Ignore first scene
	if (m_Scenes.size() != 0)
		m_Scenes[m_CurrentActiveScene]->m_pShaderManager->SetDisable();

	AddScene();
	AddButton();

	NotifyListeners();
}

void CSceneManager::OnDurationChanged(double newVal)
{
	SafeTimeValues();
}

void CSceneManager::Initialize(Ui_ShaderToolMain* pShaderTool, CCodeEditorE* pCodeEditor, CTexturePainter* pTexturePainter, QDoubleSpinBox* pDuration, QSpinBox* pOrder)
{
	m_pMainUI = pShaderTool;
	m_pSceneLayout = pShaderTool->SceneLayout;
	m_pCodeEditorHandle = pCodeEditor;
	m_pTexturePainterHandle = pTexturePainter;
	m_pDurationEdit = pDuration;
	m_pOrderEdit = pOrder;

	connect(pShaderTool->AddScene, SIGNAL(clicked()), this, SLOT(OnAddSceneClick()));
	//connect(pShaderTool->OrderEdit, SIGNAL(valueChanged(int)), this, SLOT(OnOrderChanged(int)));
	//connect(pShaderTool->DurationEdit, SIGNAL(valueChanged(double)), this, SLOT(OnDurationChanged(double)));

	m_CurrentActiveScene = 0;

	//Add the default scene
	OnAddSceneClick();
}

void CSceneManager::ChangeActiveSceneTo(const size_t slot)
{
	if (slot > (m_Scenes.size() - 1) || slot == m_CurrentActiveScene)
		return;

	// Save the textures of the current scene
	auto textures = m_pTexturePainterHandle->GetLoadedTexture();
	m_Scenes[m_CurrentActiveScene]->m_TextureNames = textures;

	SafeTimeValues();

	m_Buttons[m_CurrentActiveScene]->SetAsActive(false);
	m_Buttons[slot]->SetAsActive(true);

	m_Scenes[m_CurrentActiveScene]->m_pShaderManager->SetDisable();
	m_Scenes[slot]->m_pShaderManager->SetActive();

	m_CurrentActiveScene = slot;

	ChangeTimeValuesToScene(slot);

	// Set the textures of the new scene
	m_pTexturePainterHandle->SetTextures(m_Scenes[m_CurrentActiveScene]->m_TextureNames);

	// TODO: Add event sytem to properly retrigger compilation
	// Pretty bad hack to recompile the shaders ....
	m_pMainUI->CompileButton->click();
}

void CSceneManager::AddScene()
{
	std::vector<CTexturePainter::SShaderTexture> a;
	CScene* pScene = new CScene(std::to_string(m_Scenes.size()), m_Scenes.size(), std::vector<CTexturePainter::SShaderTexture>(), new CShaderManager());
	m_Scenes.push_back(pScene);
	pScene->m_pShaderManager->Initialize(m_pCodeEditorHandle, m_pMainUI);
}

void CSceneManager::AddButton()
{
	QString a = QString::number(static_cast<int>(m_Scenes.size()));

	CSceneButton* btn1 = new CSceneButton();
	connect(btn1, SIGNAL(rightClicked()), this, SLOT(RemoveShader()));

	btn1->setText("Scene_" + QString(a));
	m_pSceneLayout->addWidget(btn1);

	m_Buttons.push_back(btn1);

	int a2 = m_Scenes.size() - 1;
	btn1->Init(a2, this);
	ChangeActiveSceneTo(m_Scenes.size() - 1);
}

void CSceneManager::RemoveScene(const size_t slot)
{
	// You can't delete the first scene, there has to be always atleast one scene
	if (slot == 0)
		return;

	// If we are going to delete the current scene fall back to the default one
	if (m_CurrentActiveScene == slot)
		ChangeActiveSceneTo(0);

	m_pSceneLayout->removeWidget(m_Buttons[slot]);
	delete m_Buttons[slot];

	m_Buttons.erase(m_Buttons.begin() + slot);

	// Clean up memory
	m_Scenes[slot]->Release();

	m_Scenes.erase(m_Scenes.begin() + slot);

	UpdateOrder();

	NotifyListeners();
}

void CSceneManager::SafeTimeValues()
{
	//if((float)m_pDurationEdit->value() != m_Scenes[m_CurrentActiveScene]->m_DurationTime)
	//{
	//	m_Scenes[m_CurrentActiveScene]->m_DurationTime = (float)m_pDurationEdit->value();

	//	NotifyListeners();
	//}
}
	
void CSceneManager::UpdateOrder()
{
	for (size_t i = 0; i < m_Buttons.size(); ++i)
		m_Buttons[i]->UpdateSlot(i);

	for (size_t i = 0; i < m_Scenes.size(); ++i)
		m_Scenes[i]->m_SceneOrder = i;
}

void CSceneManager::NotifyListeners()
{
	for (size_t i = 0; i < m_Listeners.size(); i++)
	{
		m_Listeners[i]->SceneChanged();
	}
}

void CSceneManager::RegisterListener(SSceneListener * pListener)
{
	m_Listeners.push_back(pListener);
}

void CSceneManager::UnregisterListener(SSceneListener * pListener)
{
	for (size_t i = 0; i < m_Listeners.size(); i++)
	{
		if (m_Listeners[i] == pListener)
		{
			m_Listeners.erase(m_Listeners.begin() + i);
		}
	}
}

void CSceneManager::ChangeTimeValuesToScene(size_t slot)
{
	//m_pDurationEdit->setValue((double)m_Scenes[slot]->m_DurationTime);
	//m_pOrderEdit->setValue((double)m_Scenes[slot]->m_SceneOrder);
}

CScene* CSceneManager::GetActiveScene() const
{
	return m_Scenes[m_CurrentActiveScene];
}

std::vector<CScene*>& CSceneManager::GetAllScenesInOrder()
{
	return m_Scenes;
}

const char* CSceneManager::SaveData()
{
	for (auto* scene : m_Scenes)
	{
		buffer.append("-- Scene --\n");
		buffer.append(scene->m_SceneName);
		buffer.append("\n");
		buffer.append(std::to_string(scene->m_DurationTime));
		buffer.append("\n");
		buffer.append(scene->m_pShaderManager->SaveData());
		buffer.append("----\n");
	}

	return buffer.c_str();
}

void CSceneManager::LoadData(CSerializerChunk* pData)
{
	size_t slot = m_CurrentActiveScene;
	size_t iter = 0;
	size_t iterSceneEnd = 0;

	bool breakS = false;

	for (size_t i = 0; breakS == false; i++)
	{
		if (pData->IsChunkEnd())
			break;

		if (iter > 0)
		{
			OnAddSceneClick();
		}

		size_t sceneEnd = pData->GetChunk().find("----", iterSceneEnd);
		auto a = pData->GetLine();
		m_Scenes[slot]->m_SceneName = pData->GetLine();
		m_Scenes[slot]->m_DurationTime = std::stof(pData->GetLine());
		auto a3 = pData->GetLine();

		std::string sceneString = pData->GetChunk().substr(iterSceneEnd, sceneEnd - iterSceneEnd).c_str();

		CSerializerChunk d(sceneString.c_str());

		m_Scenes[slot]->m_pShaderManager->LoadData(&d);

		while (pData->GetLine() != "----")
		{
		}

		iterSceneEnd += sceneEnd + 4;
		iter++;
		slot++;
	}


}


