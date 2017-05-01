#include "..\include\CViewport.h"
#include <CGraphics.h>
#include <CSceneManager.h>

triebWerk::CViewport::CViewport(HWND a_ViewportHandle, CGraphics* a_pGraphic, CSceneManager* a_pManager)
{
	m_ViewportHandle = a_ViewportHandle;
	m_pGraphicHandle = a_pGraphic;
	m_pSceneManagerHandle = a_pManager;
}

triebWerk::CViewport::~CViewport()
{
}

void triebWerk::CViewport::Resize(unsigned int a_Width, unsigned int a_Height)
{
	m_pGraphicHandle->UpdateSwapchainConfiguration();
	if(m_pSceneManagerHandle->m_pActiveScene != nullptr)
		m_pSceneManagerHandle->m_pActiveScene->m_pScene->m_pWorld->m_pUIWorld->SetScreenResolution(a_Width, a_Height);
	m_ViewportWidth = a_Width;
	m_ViewportHeight = a_Height;
	DebugLogfile.LogfText("Resized Viewport: %i,%i\n", a_Width, a_Height);
}

HWND triebWerk::CViewport::GetViewportHandle()
{
	return m_ViewportHandle;
}

unsigned int triebWerk::CViewport::GetViewportWidth()
{
	return m_ViewportWidth;
}

unsigned int triebWerk::CViewport::GetViewportHeight()
{
	return m_ViewportHeight;
}
