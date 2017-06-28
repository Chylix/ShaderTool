#include "SceneManager.h"
#include "SceneButton.h"

CSceneManager::CSceneManager()
{

}
CSceneManager::~CSceneManager()
{

}

void CSceneManager::OnAddSceneClick()
{
	AddScene();
	AddButton();
}

void CSceneManager::Initialize(Ui_ShaderToolMain* pShaderTool)
{
	m_pSceneLayout = pShaderTool->scene;

	connect(pShaderTool->addScene, SIGNAL(clicked()), this, SLOT(OnAddSceneClick()));

	//Add the default scene
	OnAddSceneClick();
}

void CSceneManager::AddScene()
{
	m_Scenes.push_back(CScene());
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
}

const char * CSceneManager::SaveData()
{
	return nullptr;
}

void CSceneManager::LoadData(const char * pData)
{
}
