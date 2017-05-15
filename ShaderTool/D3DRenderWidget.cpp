#include "D3DRenderWidget.h"
#include <CEngine.h>
#include <QTimer>
#include <QResizeEvent>
#include <qshortcut.h>
#include <qguiapplication.h>
#include <qscreen.h>

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

	m_InFullscreen = false;

	QShortcut *shortcut = new QShortcut(QKeySequence("Alt+Return"), this);
	QObject::connect(shortcut, SIGNAL(activated()), this, SLOT(ChangeFullscreen()));
}

D3DRenderWidget::~D3DRenderWidget()
{
}

void D3DRenderWidget::ChangeFullscreen()
{
	if (m_InFullscreen == true)
	{
		m_InFullscreen = false;
		this->setParent(m_pParent);
		this->resize(m_Size);
		this->showNormal();
	}
	else
	{
		m_InFullscreen = true;
		m_pParent = this->parentWidget();
		m_Size = this->size();
		this->setParent(0);
		this->showFullScreen();
	}
}

void D3DRenderWidget::resizeEvent(QResizeEvent* evt)
{
	QSize a = evt->size();
	if (m_InFullscreen)
	{
		QScreen *screen = QGuiApplication::primaryScreen();
		QRect  screenGeometry = screen->geometry();
		int height = screenGeometry.height();
		int width = screenGeometry.width();

		twViewport->Resize(width, height);
	}
	else
	{
		twViewport->Resize(a.width(), a.height());
	}

}

void D3DRenderWidget::paintEvent(QPaintEvent* evt)
{
	twEngine.Run();
}
