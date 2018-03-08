#include "Timeline.h"
#include "Console.h"
#include "SceneManager.h"
#include <sstream>
#include <qpoint>
#include <iomanip>

#include <qgraphicsitem.h>

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
	//Reset();

	CConsole::Instance().PrintText("Timeline: Start playing", CConsole::EPrintType::Text);
	m_IsPlaying = true;

	m_IsStoped = false;
	m_IsPaused = false;
	m_IsEditing = false;

	m_pAudioWidget->PlayAudio();

	// Force to start from the first scene
	m_pSceneManager->ChangeActiveSceneTo(0);

	m_pTimeline->OnPlay();

	auto scenes = m_pSceneManager->GetAllScenesInOrder();

	for (auto* scene : scenes)
	{
		float time = scene->m_DurationTime;
		m_SceneTimes.push(time);
	}
}

void CTimeline::OnPause()
{
	m_IsPaused = !m_IsPaused;
}

void CTimeline::OnStop()
{
	m_IsPaused = false;
	m_IsEditing = false;
	m_IsStoped = true;

	Reset();
}

void CTimeline::OnPlayScene()
{
	m_IsPlaying = true;

	float time = m_pSceneManager->GetActiveScene()->m_DurationTime;
	m_SceneTimes.push(time);

	auto scenes = m_pSceneManager->GetAllScenesInOrder();

	float seconds = 0;

	for (size_t i = 0; i < scenes.size(); ++i)
	{
		if (i == m_pSceneManager->GetActiveScene()->m_SceneOrder)
			break;

		seconds += scenes[i]->m_DurationTime;
	}

	m_Time = seconds;

	int milli = SECONDS_TO_MILLISECONDS(seconds);

	m_pAudioWidget->PlayAudioAtPosition(milli);

	std::string message = "Timeline: Start playing Scene";
	message.append(std::to_string(m_pSceneManager->GetActiveScene()->m_SceneOrder));

	CConsole::Instance().PrintText(message.c_str(), CConsole::EPrintType::Text);
}

void CTimeline::OnTimelineEdit(int a)
{
	//if (m_IsPlaying)
	//{
	//	Reset();
	//	// Set the timeline to the actual time again
	//	m_pTimeline->setValue(a);
	//}

	//m_IsEditing = true;

	//auto scenes = m_pSceneManager->GetAllScenesInOrder();
	// 
	//float delta = 0;

	//for (size_t i = 0; i < scenes.size(); ++i)
	//{
	//	delta += SECONDS_TO_MILLISECONDS(scenes[i]->m_DurationTime);

	//	if (a <= delta)
	//	{
	//		m_pSceneManager->ChangeActiveSceneTo(i);
	//		break;
	//	}
	//}

	//m_EditTime = a;
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
	//m_pPlayButton = pPlayButton;
	m_pTimeline = pSlider;
	m_pSceneManager = pSceneManager;
	m_pAudioWidget = pAudioPlayer;
	m_pTimeDisplay = pTime;

	connect(pPlayButton, SIGNAL(released()), this, SLOT(OnPlay()));
	connect(pPauseButton, SIGNAL(released()), this, SLOT(OnPause()));
	connect(pStopButton, SIGNAL(released()), this, SLOT(OnStop()));

	//connect(pSlider, SIGNAL(sliderMoved(int)), this, SLOT(OnTimelineEdit(int)));
	//connect(pSlider, SIGNAL(sliderReleased()), this, SLOT(OnFinishedEdit()));
	//connect(pSlider, SIGNAL(doubleClicked()), this, SLOT(OnPlayScene()));

	pSceneManager->RegisterListener(this);

	m_pTimeline->SetTimeLine(this);

	SceneChanged();
}

void CTimeline::Reset()
{
	m_PassedTime = 0;
	m_Time = 0;
	//m_pTimeline->setValue(0);
	std::queue<float> empty;
	m_SceneTimes.swap(empty);
	m_IsPlaying = false;

	m_pTimeline->OnStop();

	m_pTimeline->SetCurrentTime(0);

	m_pAudioWidget->StopAudio();
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

	//m_pTimeline->SetTotalTime(m_PlayDuration);
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

		//m_pTimeline->setValue(time);

		std::string a = std::to_string(m_Time);
		a += " Passed:";
		a += std::to_string(m_PassedTime);

		m_pTimeline->SetCurrentTime(m_Time);

		CConsole::Instance().PrintText(a.c_str(), CConsole::EPrintType::Text);

		if (m_SceneTimes.size() != 0 && m_PassedTime > m_SceneTimes.front())
		{
			size_t slot = m_pSceneManager->GetActiveScene()->m_SceneOrder + 1;
			m_pSceneManager->ChangeActiveSceneTo(slot);
			m_PassedTime = 0.0f;
			m_SceneTimes.pop();
		}

		if (m_SceneTimes.size() == 0)
		{
			Reset();
			CConsole::Instance().PrintText("Timeline: Stop playing", CConsole::EPrintType::Text);
		}

		return m_Time;
	}
	else if (m_IsPlaying == false && m_IsStoped == true)
	{
		return timeSinceStartUp;
	}
	

	//else if(m_IsStoped)
	//{
	//	auto millisec = (float)MILLISCEONDS_TO_SECONDS((float)m_EditTime);
	//	std::string a = std::to_string(millisec);
	//	CConsole::Instance().PrintText(a.c_str(), CConsole::EPrintType::Text);
	//	return millisec;
	//}

	return timeSinceStartUp;
}

void CTimeline::OnEdit(bool start, int time)
{
	if (m_IsStoped)
	{
		m_IsEditing = start;
		m_EditTime = time;

		if (start != false)
		{
			m_Time = time;
			m_PassedTime = time;
		}

		std::string a = std::to_string(m_Time);
		a += " Passed:";
		a += std::to_string(m_PassedTime);
		CConsole::Instance().PrintText(a.c_str(), CConsole::EPrintType::Text);
	}
}
