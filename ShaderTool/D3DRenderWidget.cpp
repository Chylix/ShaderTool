#include "D3DRenderWidget.h"
#include <CEngine.h>
#include <QTimer>
#include <QResizeEvent>
#include <qshortcut.h>
#include <qguiapplication.h>
#include <qscreen.h>
#include <qlayout.h>
#include "ShaderToolMain.h"

D3DRenderWidget::D3DRenderWidget(QWidget* parent)
	: m_pLayout(nullptr)
{
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

	m_pLayout = this->layout();

	QShortcut *shortcut = new QShortcut(QKeySequence("Ctrl+Return"), this);
	QObject::connect(shortcut, SIGNAL(activated()), this, SLOT(ChangeFullscreen()));
}

D3DRenderWidget::~D3DRenderWidget()
{
}

void D3DRenderWidget::ForceFullscreen()
{
	m_ForcedFullscreen = true;

	m_InFullscreen = true;
	m_Size = this->size();
	this->setParent(0);
	this->showFullScreen();
	this->setFocus();
	this->setCursor(Qt::BlankCursor);
}

void D3DRenderWidget::ChangeFullscreen()
{
	if (!m_ForcedFullscreen)
	{
		if (m_InFullscreen == true)
		{
			m_InFullscreen = false;
			this->m_pLayout->addWidget(this);
			this->resize(m_Size);
			this->showNormal();
			this->unsetCursor();

		}
		else
		{
			m_InFullscreen = true;
			m_Size = this->size();
			this->setParent(0);
			this->showFullScreen();
			this->setFocus();
			this->setCursor(Qt::BlankCursor);
		}
	}

}

void D3DRenderWidget::resizeEvent(QResizeEvent* evt)
{
	QSize a = evt->size();
	if (m_InFullscreen)
	{
		//Get the highest possible screen resolution
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

void D3DRenderWidget::focusOutEvent(QFocusEvent * event)
{
	if (m_InFullscreen)
	{
		ChangeFullscreen();
	}
}

void D3DRenderWidget::keyPressEvent(QKeyEvent* event)
{
#ifdef SHIP_DEMO
	if (event->key() == Qt::Key_Escape)
	{
		quick_exit(0);
	}
#endif

}
