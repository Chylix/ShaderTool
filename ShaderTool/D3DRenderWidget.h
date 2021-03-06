#pragma once
#include <qwidget.h>

class D3DRenderWidget : public QWidget 
{
	Q_OBJECT
		Q_DISABLE_COPY(D3DRenderWidget)

public slots:
	void ChangeFullscreen();

public:
	D3DRenderWidget(QWidget* parent = NULL);
	virtual ~D3DRenderWidget();
	virtual QPaintEngine* paintEngine() const { return NULL; }

	void SetViewLayout(QLayout* pLayout) { m_pLayout = pLayout; }

public:
	void ForceFullscreen();

protected:
	virtual void resizeEvent(QResizeEvent* evt);
	virtual void paintEvent(QPaintEvent* evt);
	virtual void focusOutEvent(QFocusEvent* event);
	virtual void keyPressEvent(QKeyEvent* event);

private:
	bool m_InFullscreen = false;
	bool m_ForcedFullscreen = false;
	QLayout* m_pLayout;
	QSize m_Size;

};
