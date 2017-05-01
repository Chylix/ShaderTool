#include "D3DRenderWidget.h"
#include <CEngine.h>
#include <QTimer>
#include <QResizeEvent>

D3DRenderWidget::D3DRenderWidget(QWidget* parent)
{
	// Create Device
	//createDevice();
	triebWerk::SEngineConfiguration config;

	config.m_PhysicTimeStamp = 0.01f;
	config.m_TargetFPS = 0;

	config.m_Width = static_cast<unsigned int>(width());
	config.m_Height = static_cast<unsigned int>(height());
	config.m_Fullscreen = false;
	config.m_VSync = false;
	config.m_MasterVolume = 1.0f;
	config.m_BGMVolume = 0.6f;
	config.m_SFXVolume = 1.0f;

	if (twEngine.Initialize(config, (HWND)this->winId()) == false)
	{
		twEngine.Shutdown();
	}

	twEngine.m_pGraphics->SetClearColor(0.5, 0.7, 0.1, 1.0);

	setAttribute(Qt::WA_PaintOnScreen, true);
	setAttribute(Qt::WA_NativeWindow, true);

	QTimer* timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	timer->start(16);
}

D3DRenderWidget::~D3DRenderWidget()
{
}

void D3DRenderWidget::resizeEvent(QResizeEvent* evt)
{
	QSize a = evt->size();
	twViewport->Resize(a.width(), a.height());
}

void D3DRenderWidget::paintEvent(QPaintEvent* evt)
{
	twEngine.Run();
}
