#include "TimelineWidget.h"
#include "Timeline.h"

#include <iomanip>
#include <sstream>
#include <qpoint>
#include "Console.h"

CTimelineWidget::CTimelineWidget(QWidget* parent)
{
}

void CTimelineWidget::dragEnterEvent(QDragEnterEvent * e)
{
}

void CTimelineWidget::dropEvent(QDropEvent * e)
{
}

void CTimelineWidget::mousePressEvent(QMouseEvent * event)
{
	if (event->button() == SCROLL_TIME_BUTTON)
	{
		m_isTimeScrollMove = true;
	}
	else if(event->button() == SET_TIME_BUTTON)
	{
		m_isSettingTime = true;
	}
}

void CTimelineWidget::mouseMoveEvent(QMouseEvent * event)
{
	if (m_isTimeScrollMove)
	{

		if (m_timeScrollMovePrevXPos == 0)
			m_timeScrollMovePrevXPos = event->pos().x();

		m_timeScrollMoveOffset += (event->pos().x() - m_timeScrollMovePrevXPos);


		//std::string a = std::to_string(m_timeScrollMoveOffset);
		//CConsole::Instance().PrintText(a.c_str(), CConsole::EPrintType::Text);

		if(m_timeScrollMoveOffset < 0 && m_IsPlaying == false)
			m_timeIndicatorPos += (event->pos().x() - m_timeScrollMovePrevXPos);
		m_timeScrollMovePrevXPos = event->pos().x();
		
		m_timeScrollMoveOffset = std::min(m_timeScrollMoveOffset, 0);

	}

	if (m_isSettingTime)
	{
		m_pTimeline->OnEdit(true, (m_timeIndicatorPos - m_timeScrollMoveOffset) / m_stepSize);
		m_timeIndicatorPos = GetTimePosFromWidget(event->pos().x());

		//std::string a = std::to_string(m_timeIndicatorPos);
		//CConsole::Instance().PrintText(a.c_str(), CConsole::EPrintType::Text);
	}

}

void CTimelineWidget::mouseReleaseEvent(QMouseEvent * event)
{
	if (event->button() == SCROLL_TIME_BUTTON)
	{
		m_timeScrollMovePrevXPos = 0;
		m_isTimeScrollMove = false;
	}
	else if (event->button() == SET_TIME_BUTTON)
	{
		//m_pTimeline->OnEdit(false, event->pos().x() / m_stepSize);
		m_timeIndicatorPos = GetTimePosFromWidget(event->pos().x());
		m_isSettingTime = false;
	}
}

void CTimelineWidget::wheelEvent(QWheelEvent* event)
{
	//CalculateTimeZoom();
	CalculateZoomPos(event->pos(), (float)event->delta());
}

void CTimelineWidget::SetTotalTime(float time)
{
	m_TotalDuration = time;
}

void CTimelineWidget::paintEvent(QPaintEvent * e)
{
	QRect thisRect = rect();
	QPainter painter(this);
	m_pCurrentPainter = &painter;
	m_pCurrentPainter->fillRect(thisRect, m_BackgroundColor);

	DrawScaleLines();

	DrawTimeAxis();

	DrawTimeIndicator();
}

void CTimelineWidget::SetCurrentTime(float time)
{
	m_CurrentTime = time;
}

void CTimelineWidget::DrawTimeAxis()
{
	int majorSteps = 30; // Major steps of the timeline;
	int minorSteps = 5; 

	// Init QT
	QRect thisRect = rect();
	QPen penHText(m_TextColor);
	m_pCurrentPainter->setBackground(m_BackgroundColor);
	m_pCurrentPainter->setPen(penHText);

	int stepSize = m_stepSize; // TODO : Maybe this should be adjustable

	for (SZoomInfo& info : m_ZoomedSeconds)
	{
		// Calc next possible zoom second
		int test = info.SecondToZoom % minorSteps;
		test = info.SecondToZoom - test;
		if (info.SecondToZoom % minorSteps != 0)
			test += minorSteps;

		info.iter = info.ZoomStrength * (test / minorSteps);
	}

	int sizeIter = 0;

	if (m_timeScrollMoveOffset <= 0)
	{
		sizeIter = m_timeScrollMoveOffset;
	}

	int seconds = 0;

	while(sizeIter < thisRect.width())//(m_FocusTimeEnd * stepSize) + 1)
	{
		QRect rect;

		int offset = 0;
		
		// calculate zoom offset to move the time marker
		for (SZoomInfo& info : m_ZoomedSeconds)
		{
			if (seconds % minorSteps == 0 && seconds != info.SecondToZoom)
			{
				if (seconds < info.SecondToZoom)
				{
					offset += info.iter;
					info.iter -= info.ZoomStrength;
				}
				else
				{
					info.iter -= info.ZoomStrength;
					offset += info.iter;
				}
			}
		}

		//if (seconds % minorSteps == 0 && seconds != m_ZoomSecond)
		//{
		//	if (seconds < m_ZoomSecond)
		//	{
		//		offset = zoomIter;
		//		zoomIter -= m_ScrollValue;
		//	}
		//	else
		//	{
		//		zoomIter -= m_ScrollValue;
		//		offset = zoomIter;
		//	}
		//}

		if (seconds % majorSteps == 0)
		{
			rect.setRect((sizeIter - offset) - (m_TimeIndicatorSize.x() / 2), thisRect.height() - m_TimeIndicatorSize.y(), m_TimeIndicatorSize.x(), m_TimeIndicatorSize.y());

			m_pCurrentPainter->drawText(QPoint((sizeIter - offset) - 10, thisRect.height() - 22), GetTimeAsString(SecondsToMinutes(seconds)));
			m_pCurrentPainter->fillRect(rect, QColor(80, 80, 80));
		}
		else if(seconds % minorSteps == 0)
		{
			rect.setRect((sizeIter - offset) - (m_TimeIndicatorSize.x() / 2), thisRect.height() - m_TimeIndicatorSize.y() / 1.5f, m_TimeIndicatorSize.x(), m_TimeIndicatorSize.y() / 1.5f);


			if (m_Opacity > 0.6f)
			{
				QPen penHText(QColor(180 * m_Opacity, 180 * m_Opacity, 180* m_Opacity));
				m_pCurrentPainter->setPen(penHText);
				QFont f("Times", 7, QFont::Normal);
				m_pCurrentPainter->setFont(f);
				m_pCurrentPainter->drawText(QPoint((sizeIter - offset) - 10, thisRect.height() - 20), GetTimeAsString(SecondsToMinutes(seconds)));
			}

			m_pCurrentPainter->fillRect(rect, QColor(80.f * m_Opacity, 80.f * m_Opacity, 80.f * m_Opacity));
		}
		

		sizeIter += stepSize;

		seconds++;

		QPen penHText(QColor(240, 240, 240));
		m_pCurrentPainter->setPen(penHText);
		QFont f("Times", 7, QFont::Normal);
		m_pCurrentPainter->setFont(f);
	}
}

void CTimelineWidget::DrawScaleLines()
{
	QRect thisRect = rect();
	{
		size_t stepSize = thisRect.height() / m_NumberOfScaleLines;
		size_t iterator = 0;

		for (size_t i = 0; i < m_NumberOfScaleLines; i++)
		{
			QRect rect;

			rect.setRect(0, iterator, thisRect.width(), 2);

			m_pCurrentPainter->fillRect(rect, QColor(40, 40, 40));

			iterator += stepSize;
		}
	}
}

void CTimelineWidget::DrawTimeIndicator()
{
	QRect thisRect = rect();

	QRect rect;

	size_t pos = static_cast<size_t>((m_CurrentTime / m_TotalDuration) * (float)thisRect.width());

	std::string a = std::to_string(m_CurrentTime);
	a.append("\n");
	a.append(std::to_string(pos));

	//CConsole::Instance().PrintText(a.c_str(), CConsole::EPrintType::Text);
	if (m_IsPlaying == true)
	{
		m_timeIndicatorPos = m_CurrentTime * m_stepSize;
		m_timeIndicatorPos += m_timeScrollMoveOffset;
	}

	rect.setRect(m_timeIndicatorPos, 0, 2, thisRect.height());
	m_pCurrentPainter->fillRect(rect, m_TimeIndicatorColor);
}

int CTimelineWidget::GetTimePosFromWidget(const int x) const
{
	int test = x % m_stepSize;
	test = x - test;
	if (x % m_stepSize != 0)
		test += m_stepSize;

	return std::max(test, 0);
}

void CTimelineWidget::CalculateZoomPos(QPoint pos, float sign)
{
	////Transform delta to an -1 to 1 range
	//float val = sign / 120.0f;

	////In case we try to zoom out but we are already on the max out zoom
	//if (val < 0 && m_ScrollValue == 0)
	//	return;

	//// Reached max zoom in
	//if (val > 0 && m_ScrollValue == 90)
	//	return;

	//// Get second the user want to zoom at
	//m_ZoomSecond = static_cast<int>((pos.x()) / 4);
	//
	//// Only evaluate the x position (at least now)
	//if (m_lastPoint.x() != pos.x())
	//{
	//	m_lastPoint = pos;

	//	int s(0);
	//	for (const SZoomInfo& a : m_ZoomedSeconds)
	//	{
	//		s += a.ZoomStrength;
	//	}

	//	m_ZoomSecond = m_ZoomSecond + s * 2;
	//}

	//m_ScrollValue += m_TimeZoomFactor * val;

	//AddZoomValue(m_ZoomSecond, m_TimeZoomFactor* val);

	//// Cotrols the text opacity of the smaller time values (needs a porper system)
	//m_Opacity += 0.05f * val;

	//if (m_Opacity > 1.0f)
	//	m_Opacity = 1.0f;


	//if (m_Opacity < 0.5f)
	//	m_Opacity = 0.5f;

	//if (m_ScrollValue < 0.0f)
	//	m_ScrollValue = 0.0f;

	////Debug
	//std::string msg = "SecondToZoom :";
	//msg.append(std::to_string(m_ZoomSecond));
	//msg.append("  S: ");
	//msg.append(std::to_string(m_ScrollValue));
	//msg.append("  P: ");
	//msg.append(std::to_string((float)pos.x() / 4.0f));
	//msg.append("\n");
	//CConsole::Instance().PrintText(msg.c_str(), CConsole::EPrintType::Text);
}

QString CTimelineWidget::GetTimeAsString(const float time) const
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

float CTimelineWidget::SecondsToMinutes(const int seconds) const
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

void CTimelineWidget::AddZoomValue(int secondToZoom, const int strength)
{
	int del = -1; // Invalid

	// Check if already zoom to second
	for (size_t i = 0; i < m_ZoomedSeconds.size(); i++)
	{
		if (m_ZoomedSeconds[i].SecondToZoom == secondToZoom)
		{
			m_ZoomedSeconds[i].AddStrength(strength);

			if (m_ZoomedSeconds[i].ZoomStrength == 0)
			{
				del = (int)i;
				break;
			}

			return;
		}
	}

	// Delete from array if not needed anymore
	if (del != -1)
	{
		m_ZoomedSeconds.erase(m_ZoomedSeconds.begin() + del);
		return;
	}

	// Add new zoom second
	m_ZoomedSeconds.emplace_back(secondToZoom, strength);
}
