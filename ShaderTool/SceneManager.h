#pragma once
#include <qstring.h>
#include <vector>
#include "ui_ShaderToolMain.h"
#include "ISerializer.h"
#include <qspinbox.h>
#include "ShaderManager.h"

class CSceneButton;
class CCodeEditorE;
class CTexturePainter;

struct SSceneListener
{
	virtual void SceneChanged() = 0;
};

struct CScene
{
	CScene(std::string& name, size_t order, std::vector<CTexturePainter::SShaderTexture>& textures, CShaderManager* pShaderManager)
		: m_SceneName(name)
		, m_SceneOrder(order)
		, m_TextureNames(textures)
		, m_pShaderManager(pShaderManager)
		, m_DurationTime(1.0f)
	{
		m_DurationTime = 1.0f;
	}

	std::string m_SceneName;
	std::vector<CTexturePainter::SShaderTexture> m_TextureNames;
	CShaderManager* m_pShaderManager;
	float m_DurationTime;
	size_t m_SceneOrder;

	void Release()
	{
		if (m_pShaderManager)
		{
			m_pShaderManager->Release();
			delete m_pShaderManager;
		}
	}
};

class CSceneManager : public QObject, public ISerializer
{
	Q_OBJECT

public slots:
	void OnAddSceneClick();
	void OnOrderChanged(int newVal);
	void OnDurationChanged(double newVal);

public:
	CSceneManager();
	~CSceneManager();

public:
	void Initialize(Ui_ShaderToolMain* pShaderTool, CCodeEditorE* pCodeEditor, CTexturePainter* m_pTexturePainterHandle, QDoubleSpinBox* pStart, QSpinBox* pOrder);

	void ChangeActiveSceneTo(const size_t slot);
	void AddScene();
	void AddButton();
	void RemoveScene(const size_t slot);

	void SafeTimeValues();
	void ChangeTimeValuesToScene(size_t slot);

	void UpdateOrder();

	void NotifyListeners();
	void RegisterListener(SSceneListener* pListener);
	void UnregisterListener(SSceneListener* pListener);

	CScene* GetActiveScene() const;
	std::vector<CScene*>& GetAllScenesInOrder();


	//TODO: Implement ISerializer functions.
	//ISerializer
	const char* SaveData() final;
	void LoadData(CSerializerChunk* pData) final;
	std::string buffer;
	//~ISerializer

private:
	std::vector<CScene*> m_Scenes;
	std::vector<CSceneButton*> m_Buttons;
	QHBoxLayout* m_pSceneLayout;
	QPushButton* m_pAddButton;
	size_t m_CurrentActiveScene;
	CCodeEditorE* m_pCodeEditorHandle;
	CTexturePainter* m_pTexturePainterHandle;
	Ui_ShaderToolMain* m_pMainUI;
	QDoubleSpinBox* m_pDurationEdit;
	QSpinBox* m_pOrderEdit;
	std::vector<SSceneListener*> m_Listeners;
};
