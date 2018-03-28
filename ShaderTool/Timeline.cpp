#include "Timeline.h"
#include "Console.h"
#include "SceneManager.h"
#include <sstream>
#include <qpoint>
#include <iomanip>
#include <CEngine.h>
#include <qgraphicsitem.h>
#include "ShaderToolMain.h"

#define SECONDS_TO_MILLISECONDS(sec) sec * 1000;
#define MILLISCEONDS_TO_SECONDS(milli) milli / 1000;

CTimeline::CTimeline()
{
}

CTimeline::~CTimeline()
{

}

void CTimeline::OnPlay()
{
#ifdef SHIP_DEMO
	//Reset();
	twTime->ResetDeltaTime();
#endif
	CConsole::Instance().PrintText("Timeline: Start playing", CConsole::EPrintType::Text);
	m_IsPlaying = true;

	m_IsStoped = false;
	m_IsPaused = false;
	m_IsEditing = false;

	int n = SECONDS_TO_MILLISECONDS(m_EditTime);

	m_pAudioWidget->PlayAudioAtPosition(n + m_MoveOffset);

	// Force to start from the first scene
	m_pSceneManager->ChangeActiveSceneTo(0);

	m_pTimeline->OnPlay();

	auto scenes = m_pSceneManager->GetAllScenesInOrder();

	float delta = 0;

	for (auto* scene : scenes)
	{
		delta += scene->m_DurationTime;
		if (delta > m_EditTime)
		{
			if (m_SceneTimes.size() == 0)
			{
				float b = delta - scene->m_DurationTime;

				float a = (m_EditTime - b);
				m_PassedTime = a;
			}

			SPlayScene play;
			play.sceneSlot = scene->m_SceneOrder;
			play.time = scene->m_DurationTime;

			m_SceneTimes.push(play);
		}
	}

	m_pSceneManager->ChangeActiveSceneTo(m_SceneTimes.front().sceneSlot);
}

void CTimeline::OnPause()
{
	m_IsPaused = !m_IsPaused;
	m_pAudioWidget->PauseAudio(m_IsPaused);
}

void CTimeline::OnStop()
{
	m_EditTime = 0;
	m_IsPaused = false;
	m_IsEditing = false;
	m_IsStoped = true;

	Reset();
}

void CTimeline::OnTimelineEdit(int time)
{
	auto scenes = m_pSceneManager->GetAllScenesInOrder();
	 
	float delta = 0;

	for (size_t i = 0; i < scenes.size(); ++i)
	{
		delta += scenes[i]->m_DurationTime;

		if (time <= delta)
		{
			m_pSceneManager->ChangeActiveSceneTo(i);
			break;
		}
	}

}

void CTimeline::OnFinishedEdit()
{
	Reset();
}

QString CTimeline::ConvertTimeToDisplay(float time)
{
	float a, b;

	a = modf(time, &b);

	float pi = a;
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << pi;
	std::string s = stream.str();

	s.erase(0, 2);

	QString string(std::to_string((int)b).c_str());
	if (string.size() == 1)
		string.insert(0, "0");
	string.append(":");
	string.append(s.c_str());

	return string;
}

QString GetTimeAsString(const float time)
{
	float a, b;

	a = modf(time, &b);

	float pi = a;
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << pi;
	std::string s = stream.str();

	s.erase(0, 2);

	QString string(std::to_string((int)b).c_str());
	if (string.size() == 1)
		string.insert(0, "0");
	string.append(":");
	string.append(s.c_str());

	return string;
}

float SecondsToMinutes(const int seconds)
{
	int min = seconds / 60;
	if (min < 1)
		return seconds * 0.01f;
	else
	{
		float e = seconds % 60;
		float out = min;
		out += e * 0.01f;
		return out;
	}
}


void CTimeline::Initialize(CSceneManager* pSceneManager, CTimelineWidget* pSlider, QPushButton* pPlayButton, CAudioWidget* pAudioPlayer, QPushButton* pPauseButton, QPushButton* pStopButton, QLineEdit* pTime)
{
	m_pTimeline = pSlider;
	m_pSceneManager = pSceneManager;
	m_pAudioWidget = pAudioPlayer;
	m_pTimeDisplay = pTime;

	connect(pPlayButton, SIGNAL(released()), this, SLOT(OnPlay()));
	connect(pPauseButton, SIGNAL(released()), this, SLOT(OnPause()));
	connect(pStopButton, SIGNAL(released()), this, SLOT(OnStop()));

	pSceneManager->RegisterListener(this);

	m_pTimeline->SetTimeLine(this);

	SceneChanged();
}

void CTimeline::Reset()
{
	m_PassedTime = 0;
	m_Time = 0;
	m_EditTime = 0;
	std::queue<SPlayScene> empty;
	m_SceneTimes.swap(empty);

	m_IsPlaying = false;

	m_pTimeline->OnStop();

	m_pTimeline->SetCurrentTime(0);

	m_pAudioWidget->StopAudio();
}

bool CTimeline::IsPlaying() const
{
	return !m_IsStoped;
}

void CTimeline::OnTimelineMove(int time)
{
	m_pSceneManager->OnTimelineMove(time);
	m_MoveOffset = time;
}

void CTimeline::SceneChanged()
{
	auto scenes = m_pSceneManager->GetAllScenesInOrder();

	m_PlayDuration = 0;

	for (auto* scene : scenes)
	{
		float time = scene->m_DurationTime;
		m_PlayDuration += time;//SECONDS_TO_MILLISECONDS(time);
	}
}

float CTimeline::UpdateTime(float deltaTime, float timeSinceStartUp)
{
	m_pTimeline->repaint();

	m_pTimeDisplay->setText(ConvertTimeToDisplay(SecondsToMinutes(m_Time)));

	if (m_IsEditing == true)
	{
		return m_EditTime;
	}
	else if (m_IsPaused)
	{
		return m_Time;
	}
	else if (m_IsPlaying)
	{
		m_Time += deltaTime;
		m_PassedTime += deltaTime;

		auto time = m_Time;

		std::string a = std::to_string(m_Time);
		a += " Passed:";
		a += std::to_string(m_PassedTime);

		m_pTimeline->SetCurrentTime(m_Time);

		if (m_SceneTimes.size() != 0 && m_PassedTime > m_SceneTimes.front().time)
		{
			size_t slot = m_pSceneManager->GetActiveScene()->m_SceneOrder + 1;
			m_pSceneManager->ChangeActiveSceneTo(slot);
			m_PassedTime = 0.0f;
			m_SceneTimes.pop();
		}

		if (m_SceneTimes.size() == 0)
		{
			Reset();

#ifdef SHIP_DEMO
			quick_exit(0);
#endif // SHIP_DEMO

			CConsole::Instance().PrintText("Timeline: Stop playing", CConsole::EPrintType::Text);
		}

		return m_Time;
	}
	else if (m_IsPlaying == false && m_IsStoped == true)
	{
		return timeSinceStartUp;
	}
	
	return timeSinceStartUp;
}

void CTimeline::OnEdit(bool start, int time)
{
	if (m_IsStoped)
	{
		m_IsEditing = start;
		m_EditTime = time;

		OnTimelineEdit(time);

		if (start != false)
		{
			m_Time = time;
		}
	}
}
