#pragma once
#include <qwidget.h>

class D3DRenderWidget : public QWidget {
	Q_OBJECT
		Q_DISABLE_COPY(D3DRenderWidget)

public slots:
	void ChangeFullscreen();

public:
	D3DRenderWidget(QWidget* parent = NULL);
	virtual ~D3DRenderWidget();
	virtual QPaintEngine* paintEngine() const { return NULL; }

	void SetViewLayout(QLayout* pLayout) { m_pLayout = pLayout; }

protected:
	virtual void resizeEvent(QResizeEvent* evt);
	virtual void paintEvent(QPaintEvent* evt);
	virtual void focusOutEvent(QFocusEvent* event);
private:
	bool m_InFullscreen;
	QLayout* m_pLayout;
	QSize m_Size;

};
