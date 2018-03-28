#include "SceneManager.h"
#include "SceneButton.h"
#include "ShaderManager.h"
#include "SerializerChunk.h"
#include "Timeline.h"
#include "TimelineWidget.h"
#include "Scene.h"
#include <string>  

CSceneManager::CSceneManager()
{

}
CSceneManager::~CSceneManager()
{
}

void CSceneManager::OnOrderChanged(int newVal)
{
	if (newVal == m_CurrentActiveScene || newVal > m_Scenes.size()-1 || newVal < 0)
		return;

	std::swap(m_Scenes[m_CurrentActiveScene], m_Scenes[newVal]);

	UpdateOrder();

	m_CurrentActiveScene = newVal;
}

void CSceneManager::OnAddSceneClick()
{
	// Ignore first scene
	if (m_Scenes.size() != 0)
		m_Scenes[m_CurrentActiveScene]->m_pShaderManager->SetDisable();

	AddScene();
	NotifyListeners();
}

void CSceneManager::Initialize(Ui_ShaderToolMain* pShaderTool, CCodeEditorE* pCodeEditor, CTexturePainter* pTexturePainter, CTimeline* pTimeline)
{
	m_pMainUI = pShaderTool;
	m_pCodeEditorHandle = pCodeEditor;
	m_pTexturePainterHandle = pTexturePainter;
	m_pSceneWidget = m_pMainUI->SceneWidget;
	m_pTimeline = pTimeline;

	m_pSceneWidget->Initialize(this);

	connect(pShaderTool->AddScene, SIGNAL(clicked()), this, SLOT(OnAddSceneClick()));

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

	m_Scenes[m_CurrentActiveScene]->m_pShaderManager->SetDisable();
	m_Scenes[slot]->m_pShaderManager->SetActive();

	m_CurrentActiveScene = slot;

	// Set the textures of the new scene
	m_pTexturePainterHandle->SetTextures(m_Scenes[m_CurrentActiveScene]->m_TextureNames);

	// TODO: Add event sytem to properly retrigger compilation
	// Pretty bad hack to recompile the shaders ....
	m_pMainUI->CompileButton->click();

	m_pSceneWidget->SetActiveScene(slot);
}

void CSceneManager::AddScene()
{
	std::vector<CTexturePainter::SShaderTexture> a;
	CScene* pScene = new CScene(std::to_string(m_Scenes.size()), m_Scenes.size(), std::vector<CTexturePainter::SShaderTexture>(), new CShaderManager());
	pScene->m_SceneName = "Scene_";
	pScene->m_SceneName += std::to_string(m_Scenes.size());
	m_Scenes.push_back(pScene);
	pScene->m_pShaderManager->Initialize(m_pCodeEditorHandle, m_pMainUI);

	m_pSceneWidget->AddScene(pScene);

	ChangeActiveSceneTo(m_Scenes.size() - 1);
}

void CSceneManager::RemoveScene(const size_t slot)
{
	// You can't delete the first scene, there has to be always atleast one scene
	if (slot == 0 || m_pTimeline->IsPlaying())
		return;

	// If we are going to delete the current scene fall back to the default one
	if (m_CurrentActiveScene == slot)
		ChangeActiveSceneTo(0);

	if (slot < m_CurrentActiveScene)
		m_CurrentActiveScene--;


	m_pSceneWidget->RemoveScene(slot);

	// Clean up memory
	m_Scenes[slot]->Release();

	m_Scenes.erase(m_Scenes.begin() + slot);

	UpdateOrder();

	NotifyListeners();
}

void CSceneManager::UpdateOrder()
{
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

void CSceneManager::ChangeSizeOrder(const size_t slot, const size_t changeToSlot)
{
	std::swap(m_Scenes.at(slot), m_Scenes.at(changeToSlot));

	UpdateOrder();
}

void CSceneManager::OnTimelineMove(int time)
{
	m_pSceneWidget->OnTimelineMove(time);
}

void CSceneManager::UpdateSceneDuration(const size_t slot, const float newTime)
{
	m_Scenes[slot]->m_DurationTime = newTime;
}

bool CSceneManager::IsPlaying() const
{
	return m_pTimeline->IsPlaying();
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
	buffer.clear();

	// Get textures
	auto textures = m_pTexturePainterHandle->GetLoadedTexture();
	m_Scenes[m_CurrentActiveScene]->m_TextureNames = textures;

	for (auto* scene : m_Scenes)
	{
		buffer.append("-- Scene --\n");
		buffer.append(scene->m_SceneName);
		buffer.append("\n");
		buffer.append(std::to_string(scene->m_DurationTime));
		buffer.append("\n");
		buffer.append(std::to_string(scene->m_TextureNames.size()));
		buffer.append("\n");
		for (auto s : scene->m_TextureNames)
		{
			buffer.append(s.path.toStdString());
			buffer.append("\n");
		}
		buffer.append(scene->m_pShaderManager->SaveData());
		buffer.append("----\n");
	}

	return buffer.c_str();
}

void CSceneManager::LoadData(CSerializerChunk* pData)
{
	size_t slot = 0;
	size_t iter = 0;
	size_t iterSceneEnd = 0;

	// Disable shader manager before clearing the scenes (so the layout stays clear)
	for (auto* scene : m_Scenes)
	{
		scene->m_pShaderManager->SetDisable();
	}

	m_Scenes.clear();
	m_pSceneWidget->Clear();

	m_CurrentActiveScene = 0;

	bool breakS = false;

	for (size_t i = 0; breakS == false; i++)
	{
		if (pData->IsChunkEnd())
			break;

		OnAddSceneClick();

		size_t sceneEnd = pData->GetChunk().find("----", iterSceneEnd) + 4;
		auto a = pData->GetLine();
		m_Scenes[slot]->m_SceneName = pData->GetLine();
		m_Scenes[slot]->m_DurationTime = std::stof(pData->GetLine());

		size_t texNum = std::stoi(pData->GetLine());
		std::vector<std::string> paths;
		for (size_t i = 0; i < texNum; ++i)
		{
			paths.push_back(pData->GetLine());
		}
		m_pTexturePainterHandle->AddTextures(paths);

		auto a3 = pData->GetLine();

		std::string sceneString = pData->GetChunk().substr(iterSceneEnd, sceneEnd - iterSceneEnd).c_str();

		CSerializerChunk d(sceneString.c_str());

		m_Scenes[slot]->m_pShaderManager->LoadData(&d);

		while (pData->GetLine() != "----")
		{
		}

		iterSceneEnd = sceneEnd;
		iter++;
		slot++;
	}

	m_pSceneWidget->CalculateRects();
	m_pSceneWidget->repaint();
}


