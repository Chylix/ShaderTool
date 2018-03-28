#include "SceneWidget.h"
#include "Scene.h"
#include "SceneWidget.h"
#include "TimelineWidget.h"
#include "Console.h"
#include "SceneManager.h"
#include <sstream>
#include <iomanip>
#include "TimeUtils.h"

CSceneWidget::CSceneWidget(QWidget* pParent)
{
	m_mouseMovePos = QPoint(-1, -1);
}

void CSceneWidget::focusOutEvent(QFocusEvent* event)
{
	m_mouseMovePos = QPoint(-1, -1);
	repaint();
}

void CSceneWidget::paintEvent(QPaintEvent * pEvent)
{
	QPainter painter(this);
	m_pCurrentPainter = &painter;

	m_pCurrentPainter->fillRect(rect(), Qt::gray);

	this->setMouseTracking(true);

	for (size_t i = 0; i < m_Scenes.size(); i++)
	{
		QColor drawColor = QColor(50, 50, 50);

		if (i == m_activeScene)
		{
			drawColor = QColor(60, 60, 60);
		}

		if (m_Scenes[i].rect.contains(m_mouseMovePos) == true && m_MoveScene == false && m_AdjustingScene == false)
		{
			drawColor = QColor(70, 70, 70);
		}

		if (m_MoveSceneSlot != -1 && i == m_MoveSceneSlot)
		{
			drawColor = QColor(30, 70, 30);
		}

		m_pCurrentPainter->fillRect(m_Scenes[i].rect, drawColor);

		QPen penHText(QColor(180, 180, 180));
		m_pCurrentPainter->setPen(penHText);
		QFont f("Times", 7, QFont::Normal);
		m_pCurrentPainter->setFont(f);
		m_pCurrentPainter->drawText(QPoint(m_Scenes[i].rect.x() + 10, height()/2), QString(m_Scenes[i].pScene->m_SceneName.c_str()));
	}

	DrawTimeAjusters();

	m_mouseMovePos = QPoint(-1, -1);
}

void CSceneWidget::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);
	repaint();
}

void CSceneWidget::mousePressEvent(QMouseEvent* pEvent)
{
	if (pEvent->button() == Qt::LeftButton)
	{
		for (size_t i = 0; i < m_Scenes.size(); i++)
		{
			if (m_Scenes[i].adjustRect.contains(pEvent->pos()))
			{
				m_AdjustScene = i;
				m_AdjustingScene = true;
				m_AdjustStartPoint = pEvent->pos();
				m_AdjustDelta = m_Scenes[i].pScene->m_DurationTime;
				this->setCursor(QCursor(Qt::SizeHorCursor));
				return;
			}
		}

		for (size_t i = 0; i < m_Scenes.size(); i++)
		{
			if (m_Scenes[i].rect.contains(pEvent->pos()))
			{
				m_MoveSceneSlot = i;
				m_MoveScene = true;
				return;
			}
		}
	}
}

void CSceneWidget::mouseMoveEvent(QMouseEvent* pEvent)
{
	m_mouseMovePos = pEvent->pos();

	if (m_MoveScene == true && m_pSceneManager->IsPlaying() == false)
	{
		for (size_t i = 0; i < m_Scenes.size(); i++)
		{
			if (m_Scenes[i].rect.contains(pEvent->pos()))
			{
				ChangeSceneOrder(m_MoveSceneSlot, i);
			}
		}
	}

	if (m_AdjustingScene == true && m_pSceneManager->IsPlaying() == false)
	{
		AdjustScene(pEvent->pos());
	}

	SetCursor(pEvent->pos());

	repaint();
}

void CSceneWidget::mouseReleaseEvent(QMouseEvent* pEvent)
{
	if (pEvent->button() == Qt::LeftButton)
	{
		for (size_t i = 0; i < m_Scenes.size(); i++)
		{
			if (m_Scenes[i].rect.contains(pEvent->pos()))
			{
				if (!m_pSceneManager->IsPlaying())
				{
					m_pSceneManager->ChangeActiveSceneTo(i);
				}
			}
		}

		this->setCursor(QCursor());

		m_MoveSceneSlot = -1;
		m_MoveScene = false;

		m_AdjustingScene = false;
		m_AdjustScene = 0;
		m_AdjustStartPoint = QPoint();
		m_AdjustDelta = 0;
	}
	else if (pEvent->button() == Qt::RightButton)
	{
		for (size_t i = 0; i < m_Scenes.size(); i++)
		{
			if (m_Scenes[i].rect.contains(pEvent->pos()))
			{
				m_pSceneManager->RemoveScene(i);
			}
		}
	}
}

void CSceneWidget::CalculateRects()
{
	int step = 0;

	//Calc "button" rects
	for (size_t i = 0; i < m_Scenes.size(); i++)
	{
		QRect rect;

		const int time = m_Scenes[i].pScene->m_DurationTime * TIME_LINE_STEP_SIZE;

		rect.setRect(step + m_TimelineOffset, 0, time, height());

		m_Scenes[i].rect = rect;

		step += time;
	}

	//Calc "splitter" rects
	for (size_t i = 0; i < m_Scenes.size(); i++)
	{
		QRect rect;
		rect = m_Scenes[i].rect;
		rect.setX((rect.x() + rect.width() - m_AdjusterWidth / 2));
		rect.setWidth(m_AdjusterWidth);

		m_Scenes[i].adjustRect = rect;
	}
}

void CSceneWidget::ChangeSceneOrder(size_t slot, size_t changeToSlot)
{
	if (changeToSlot < 0 || slot == changeToSlot)
		return;

	std::swap(m_Scenes.at(slot), m_Scenes.at(changeToSlot));
	
	m_MoveSceneSlot = changeToSlot;

	m_pSceneManager->ChangeSizeOrder(slot, changeToSlot);

	m_pSceneManager->ChangeActiveSceneTo(changeToSlot);

	CalculateRects();

	repaint();
}

void CSceneWidget::DrawTimeAjusters()
{
	for (size_t i = 0; i < m_Scenes.size(); i++)
	{
		QColor drawColor = QColor(40, 40, 40);
		m_pCurrentPainter->fillRect(m_Scenes[i].adjustRect, drawColor);
	}
}

void CSceneWidget::AdjustScene(QPoint pos)
{
	float delta = (pos - m_AdjustStartPoint).x() / TIME_LINE_STEP_SIZE;
	m_Scenes[m_AdjustScene].pScene->m_DurationTime = m_AdjustDelta + delta;

	m_pSceneManager->UpdateSceneDuration(m_AdjustScene, m_Scenes[m_AdjustScene].pScene->m_DurationTime);

	float time = 0;

	for (size_t i = 0; i <= m_AdjustScene; ++i)
	{
		time += m_Scenes[i].pScene->m_DurationTime;
	}

	CConsole::Instance().PrintText("Scene duration: " + TimeUtils::GetTimeAsString(TimeUtils::SecondsToMinutes(m_Scenes[m_AdjustScene].pScene->m_DurationTime))
		+ "\n" + "Scene end: " + TimeUtils::GetTimeAsString(TimeUtils::SecondsToMinutes(time)));

	CalculateRects();
}

void CSceneWidget::SetCursor(QPoint pos)
{
	if(m_MoveScene == false && m_AdjustingScene == false)
	{
		for (size_t i = 0; i < m_Scenes.size(); i++)
		{
			if (m_Scenes[i].adjustRect.contains(pos))
			{
				this->setCursor(QCursor(Qt::SizeHorCursor));
				break;
			}
			else
			{
				this->setCursor(QCursor());
			}
		}
	}
	else if(m_MoveScene == true)
	{
		this->setCursor(QCursor(Qt::SizeAllCursor));
	}
	else if (m_AdjustingScene == true)
	{
		this->setCursor(QCursor(Qt::SizeHorCursor));
	}
}

void CSceneWidget::Initialize(CSceneManager* pSceneManager)
{
	m_pSceneManager = pSceneManager;
}

void CSceneWidget::AddScene(CScene* pScene)
{
	m_Scenes.push_back(SDrawScene(pScene));

	CalculateRects();

	repaint();
}

void CSceneWidget::RemoveScene(size_t slot)
{
	CConsole::Instance().PrintText(m_Scenes[slot].pScene->m_SceneName + " removed");

	m_Scenes.erase(m_Scenes.begin() + slot);

	CalculateRects();

	repaint();
}

void CSceneWidget::SetActiveScene(size_t index)
{
	m_activeScene = index;
	repaint();
}

void CSceneWidget::Clear()
{
	m_Scenes.clear();
}

void CSceneWidget::OnTimelineMove(int time)
{
	m_TimelineOffset = time;

	CalculateRects();

	repaint();
}
