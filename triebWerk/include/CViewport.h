#pragma once
#include <Windows.h>

namespace triebWerk
{
	class CGraphics;
	class CSceneManager;

	class CViewport
	{
	public:
		CViewport(HWND a_ViewportHandle, CGraphics* a_pGraphics, CSceneManager* a_pManager);
		~CViewport();

	public:
		void Resize(unsigned int a_Width, unsigned int a_Height);
		HWND GetViewportHandle();

		unsigned int GetViewportWidth();
		unsigned int GetViewportHeight();

	private:
		HWND m_ViewportHandle;

		CGraphics* m_pGraphicHandle;
		CSceneManager* m_pSceneManagerHandle;

		unsigned int m_ViewportHeight;
		unsigned int m_ViewportWidth;

	};
}
