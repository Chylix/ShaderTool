#pragma once
#include <queue>
#include <qslider.h>
#include <qpushbutton.h>
#include <qobject.h>
#include "SceneManager.h"

class CAudioWidget;
class CTimelineWidget;

class CTimeline : public QObject, public SSceneListener
{
	Q_OBJECT

private:
	struct SPlayScene
	{
		float time;
		size_t sceneSlot;
	};


public:
	CTimeline();
	~CTimeline();

	void Initialize(CSceneManager* pSceneManager,
		CTimelineWidget* timeline,
		QPushButton* button,
		CAudioWidget* pAudioPlayer,
		QPushButton* pPauseButton,
		QPushButton* pStopButton,
		QLineEdit* pTime);

	float UpdateTime(float deltaTime, float timeSinceStartUp);
	void OnEdit(bool start, int time);
	virtual void SceneChanged() final;
	void Reset();
	bool IsPlaying() const;

	void OnTimelineMove(int time);

public slots:
	void OnPlay();
	void OnPause();
	void OnStop();
	void OnTimelineEdit(int);
	void OnFinishedEdit();

private:
	CTimelineWidget* m_pTimeline;
	QPushButton* m_pPlayButton;
	CSceneManager* m_pSceneManager;
	CAudioWidget* m_pAudioWidget;
	QGraphicsView* m_pGraphicsView = nullptr;
	QLineEdit* m_pTimeDisplay = nullptr;

	std::queue<SPlayScene> m_SceneTimes;

	bool m_IsStoped = true;
	bool m_IsPlaying = false;
	bool m_IsPaused = false;

	int m_EditTime = 0;
	int m_MoveOffset = 0;

	bool m_IsEditing = false;
	float m_Time = 0;
	float m_PassedTime = 0;
	float m_PlayDuration = 0;

	QString ConvertTimeToDisplay(float time);
};
