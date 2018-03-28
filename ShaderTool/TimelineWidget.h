#pragma once
#include <QWidget>
#include <QPaintEvent>
#include <QPixmap>
#include <QPainter>
#include <qplaintextedit.h>
#include <qpoint.h>

#define SCROLL_TIME_BUTTON Qt::RightButton
#define SET_TIME_BUTTON Qt::LeftButton

#define TIME_LINE_STEP_SIZE 6

class CTimeline;

class CTimelineWidget : public QWidget {
	Q_OBJECT

public:
	CTimelineWidget(QWidget *parent = 0);

	void SetCurrentTime(float time);
	void SetTotalTime(float time);

	void SetTimeLine(CTimeline* pTimeLine) { m_pTimeline = pTimeLine; }

	//void SetPlayTime();
	void OnPlay() { m_IsPlaying = true; }
	void OnPause() { m_timeIndicatorPos = 0; }
	void OnStop() 
	{ 
		m_IsPlaying = false;
		m_timeIndicatorPos = 0;
	}

	const int m_stepSize = TIME_LINE_STEP_SIZE;

protected:
	//QWidget
	void paintEvent(QPaintEvent* e);
	virtual void dragEnterEvent(QDragEnterEvent* e);
	virtual void dropEvent(QDropEvent * e);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);

	virtual void wheelEvent(QWheelEvent* event);
	//~QWidget

private:
	void DrawTimeAxis();
	void DrawScaleLines();
	void DrawTimeIndicator();



	int GetTimePosFromWidget(const int x) const;

	void CalculateZoomPos(QPoint pos, float s);
private:
	void AddZoomValue(int secondToZoom, const int strength);

private:
	struct SZoomInfo
	{
		int SecondToZoom;
		int ZoomStrength;
		int iter;

		SZoomInfo(int secondToZoom, int zoomStrength)
			: SecondToZoom(secondToZoom)
			, ZoomStrength(zoomStrength)
			, iter(0)
		{}

		void AddStrength(int strength)
		{
			ZoomStrength += strength;
		}
	};

private:
	//Const values
	const QColor m_TextColor = QColor(255, 255, 255);
	const QColor m_BackgroundColor = QColor(46, 46, 46);
	int m_NumberOfTimeInterval = 15;


	const int m_NumberOfScaleLines = 12;

	const QPoint m_TimeIndicatorSize = QPoint(2, 10);

	const QColor m_TimeIndicatorColor = QColor(23, 50, 200);

	 int m_TimeZoomFactor = 1;

	const int m_ZoomStepsThreshold[5] = { -60, -30, 0, 30, 60 };
	const int m_ZoomStepsTime[5] = { 1, 5, 15, 30, 60 };
	//~const

private:
	QPainter* m_pCurrentPainter = nullptr;
	int m_TotalDuration = 120; // in seconds

	int m_timeScrollMovePrevXPos = 0;
	int m_timeScrollMoveOffset = 0;

	bool m_isTimeScrollMove = false;

	bool m_isSettingTime = false;
	int m_timeIndicatorPos = 0;
	std::vector<SZoomInfo> m_ZoomedSeconds;

	CTimeline* m_pTimeline = 0;

	QPoint m_lastPoint;

	float m_CurrentTime = 0.00f;
	bool m_IsEditing = false;
	bool m_IsPlaying = false;

	float m_Opacity = 0.7f;

	int m_ZoomSecond = 0;

	int steps = 0;

	int m_ScrollValue = 0;
};
