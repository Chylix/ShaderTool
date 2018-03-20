#pragma once
#include <qstring.h>
#include <vector>
#include "ui_ShaderToolMain.h"
#include "ISerializer.h"
#include <qspinbox.h>
#include "ShaderManager.h"
#include "Scene.h"
#include "SceneWidget.h"

class CSceneButton;
class CCodeEditorE;
class CTexturePainter;
class CTimeline;
class CTimelineWidget;
class CSceneWidget;

struct SSceneListener
{
	virtual void SceneChanged() = 0;
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
	void Initialize(Ui_ShaderToolMain* pShaderTool, CCodeEditorE* pCodeEditor, CTexturePainter* m_pTexturePainterHandle, CTimeline* pTimeline);

	void ChangeActiveSceneTo(const size_t slot);
	void AddScene();
	void RemoveScene(const size_t slot);

	void SafeTimeValues();
	void ChangeTimeValuesToScene(size_t slot);

	void ChangeSizeOrder(const size_t slot, const size_t changeToSlot);

	void OnTimelineMove(int time);

	void UpdateSceneDuration(const size_t slot, const float newTime);

	bool IsPlaying() const;

	void UpdateOrder();

	void NotifyListeners();
	void RegisterListener(SSceneListener* pListener);
	void UnregisterListener(SSceneListener* pListener);

	CScene* GetActiveScene() const;
	std::vector<CScene*>& GetAllScenesInOrder();

	//ISerializer
	const char* SaveData() final;
	void LoadData(CSerializerChunk* pData) final;
	std::string buffer;
	//~ISerializer

private:
	typedef std::vector<SSceneListener*> SceneListeners;

	std::vector<CScene*> m_Scenes;
	QHBoxLayout*         m_pSceneLayout;
	QPushButton*         m_pAddButton;
	size_t               m_CurrentActiveScene;
	CCodeEditorE*        m_pCodeEditorHandle;
	CTexturePainter*     m_pTexturePainterHandle;
	Ui_ShaderToolMain*   m_pMainUI;
	SceneListeners       m_Listeners;
	CTimeline*           m_pTimeline;
	CTimelineWidget      m_pTimelineWidget;
	CSceneWidget*        m_pSceneWidget;
};
