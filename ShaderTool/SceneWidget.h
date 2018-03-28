#pragma once
#include <QWidget>
#include <QPaintEvent>
#include <QPixmap>
#include <QPainter>
#include <qplaintextedit.h>
#include <qpoint.h>

class CSceneManager;
class CScene;

struct SDrawScene
{
	SDrawScene(CScene* scene) : pScene(scene){};

	CScene*   pScene;
	QRect     rect;
	QRect     adjustRect;
};

class CSceneWidget : public QWidget {
	Q_OBJECT

public:
	CSceneWidget(QWidget* pParent = 0);
	void Initialize(CSceneManager* pSceneManager);

	void AddScene(CScene* pScene);
	void RemoveScene(size_t slot);
	void SetActiveScene(size_t slot);

	void CalculateRects();

	void Clear();

	void OnTimelineMove(int time);

protected:
	//QWidget
	virtual void focusOutEvent(QFocusEvent* event) override;
	void paintEvent(QPaintEvent* pEvent);
	void resizeEvent(QResizeEvent *event) override;
	//virtual void dragEnterEvent(QDragEnterEvent* pEvent);
	//virtual void dropEvent(QDropEvent* pEvent);
	virtual void mousePressEvent(QMouseEvent* pEvent);
	virtual void mouseMoveEvent(QMouseEvent* pEvent);
	virtual void mouseReleaseEvent(QMouseEvent* pEvent);
	//virtual void mouseReleaseEvent(QMouseEvent* pEvent);
	//~QWidget

	void ChangeSceneOrder(size_t slot, size_t changeToSlot);
	void DrawTimeAjusters();
	void AdjustScene(QPoint pos);
	void SetCursor(QPoint pos);

private:
	//Constants
	const int m_MaxHeight = 40;
	const int m_AdjusterWidth = 6;

private:
	CSceneManager*       m_pSceneManager;
	std::vector<SDrawScene> m_Scenes;

	QPoint m_mouseMovePos;
	int m_TimelineOffset = 0;

	//Moving Scene
	bool   m_MoveScene = false;
	int    m_MoveSceneSlot = -1;
	size_t m_activeScene = 0;
	//~Moving Scene

	//Adjusting Scene
	bool   m_AdjustingScene = false;
	size_t m_AdjustScene = 0;
	QPoint m_AdjustStartPoint;
	int    m_AdjustDelta = 0;
	//~Adjusting Scene

	//Painting
	QPainter* m_pCurrentPainter;
	//~Painting

};
