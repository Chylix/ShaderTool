#include "SceneManager.h"
#include "SceneButton.h"
#include "ShaderManager.h"

CSceneManager::CSceneManager()
{

}
CSceneManager::~CSceneManager()
{

}

void CSceneManager::OnAddSceneClick()
{
	// Ignore first scene
	if (m_Scenes.size() != 0)
		m_Scenes[m_CurrentActiveScene]->m_pShaderManager->SetDisable();

	AddScene();
	AddButton();
}

void CSceneManager::Initialize(Ui_ShaderToolMain* pShaderTool, CCodeEditorE* pCodeEditor, CTexturePainter* pTexturePainter)
{
	m_pMainUI = pShaderTool;
	m_pSceneLayout = pShaderTool->SceneLayout;
	m_pCodeEditorHandle = pCodeEditor;
	m_pTexturePainterHandle = pTexturePainter;

	connect(pShaderTool->AddSceneButton, SIGNAL(clicked()), this, SLOT(OnAddSceneClick()));

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

	m_Buttons[m_CurrentActiveScene]->SetAsActive(false);
	m_Buttons[slot]->SetAsActive(true);

	m_Scenes[m_CurrentActiveScene]->m_pShaderManager->SetDisable();
	m_Scenes[slot]->m_pShaderManager->SetActive();

	m_CurrentActiveScene = slot;

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

	for (size_t i = 0; i < m_Buttons.size(); ++i)
		m_Buttons[i]->UpdateSlot(i);
}

CScene* CSceneManager::GetActiveScene() const
{
	return m_Scenes[m_CurrentActiveScene];
}

const char* CSceneManager::SaveData()
{
	return nullptr;
}

void CSceneManager::LoadData(const char * pData)
{
}
