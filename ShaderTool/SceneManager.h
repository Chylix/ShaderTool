#pragma once
#include <qstring.h>
#include <vector>
#include "ui_ShaderToolMain.h"
#include "ISerializer.h"

class CShaderManager;
class CSceneButton;
class CCodeEditorE;
class CTexturePainter;

struct CScene
{
	CScene(std::string& name, size_t order, std::vector<CTexturePainter::SShaderTexture>& textures, CShaderManager* pShaderManager)
		: m_SceneName(name)
		, m_SceneOrder(order)
		, m_TextureNames(textures)
		, m_pShaderManager(pShaderManager)
	{
	}

	std::string m_SceneName;
	size_t m_SceneOrder;
	std::vector<CTexturePainter::SShaderTexture> m_TextureNames;
	CShaderManager* m_pShaderManager;

	void Release()
	{
		if (m_pShaderManager)
			delete m_pShaderManager;
	}
};

class CSceneManager : public QObject, public ISerializer
{
	Q_OBJECT

public slots:
	void OnAddSceneClick();

public:
	CSceneManager();
	~CSceneManager();

public:
	void Initialize(Ui_ShaderToolMain* pShaderTool, CCodeEditorE* pCodeEditor, CTexturePainter* m_pTexturePainterHandle);

	void ChangeActiveSceneTo(const size_t slot);
	void AddScene();
	void AddButton();
	void RemoveScene(const size_t slot);

	CScene* GetActiveScene() const;

	//TODO: Implement ISerializer functions.
	//ISerializer
	const char* SaveData() final;
	void LoadData(const char* pData) final;
	std::string buffer;
	//~ISerializer

private:
	std::vector<CScene*> m_Scenes;
	std::vector<CSceneButton*> m_Buttons;
	QLayout* m_pSceneLayout;
	QPushButton* m_pAddButton;
	size_t m_CurrentActiveScene;
	CCodeEditorE* m_pCodeEditorHandle;
	CTexturePainter* m_pTexturePainterHandle;
	Ui_ShaderToolMain* m_pMainUI;
};
