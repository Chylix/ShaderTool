#pragma once
#include <EngineDefines.h>
#include <CInput.h>
#include <CTime.h>
#include <CWindow.h>
#include <CFontManager.h>
#include <CResourceManager.h>
#include <CGraphics.h>
#include <CRandom.h>
#include <CRenderer.h>
#include <CSceneManager.h>
#include <CDebug.h>
#include <SEngineConfiguration.h>
#include <CViewport.h>

namespace triebWerk
{
    class CEngine
    {
    public:
        CInput* m_pInput;
        CTime* m_pTime;
		CWindow* m_pWindow;
		CGraphics* m_pGraphics;
		CResourceManager* m_pResourceManager;
		CRenderer* m_pRenderer;
        CSceneManager* m_pSceneManager;
        CFontManager* m_pFontManager;
		CDebug* m_pDebug;
		CSoundEngine* m_pSoundEngine;
		CViewport* m_pViewport;

	private:
        const double SleepTimeDivisor = 10.0;

		bool m_IsRunning;
        float m_TimePerFrame;
        float m_CurrentTime;
        float m_PhysicTimeStamp;
        float m_CurrentPhysicTime;

		//TODO: move to extra class
		int m_ViewportWidth;
		int m_ViewportHeight;

    private:
        CEngine();
        ~CEngine();

    public:
        static CEngine& Instance();

    public:
        bool Initialize();
		bool Initialize(const SEngineConfiguration& a_Config, HWND a_WindowHandle = NULL);
        bool Run();
        void Shutdown();

		//TODO: move to extra class
		int GetViewportWidth() const;
		int GetViewportHeight() const;
		void SetViewportSize(int a_Width, int a_Height);

        void Stop();
	private:
		void ProcessWindowMessages();
    };
}