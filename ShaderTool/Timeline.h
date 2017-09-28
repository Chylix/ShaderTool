#pragma once
#include <queue>
#include <qslider.h>
#include <qpushbutton.h>
#include <qobject.h>
#include "SceneManager.h"

class CTimeline : public QObject, public SSceneListener
{
	Q_OBJECT

public:
	CTimeline();
	~CTimeline();

	void Initialize(CSceneManager* pSceneManager, QSlider* timeline, QPushButton* button);
	float UpdateTime(float deltaTime, float timeSinceStartUp);

	virtual void SceneChanged() final;

	void Reset();

public slots:
	void OnPlay();
	void OnTimelineEdit(int);
	void OnFinishedEdit();

private:
	QSlider* m_pTimeline;
	QPushButton* m_pPlayButton;
	CSceneManager* m_pSceneManager;
	
	std::queue<float> m_SceneTimes;

	bool m_IsEditing = false;
	bool m_IsPlaying = false;

	int m_EditTime = 0;

	float m_Time = 0;
	float m_PassedTime = 0;
	float m_PlayDuration = 0;
};
