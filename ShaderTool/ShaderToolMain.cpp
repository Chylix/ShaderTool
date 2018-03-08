#include "ShaderToolMain.h"
#include "SyntaxHighlighter.h"
#include "D3DRenderWidget.h"
#include "CodeEditor.h"
#include "Console.h"
#include <QLayout.h>
#include <CEngine.h>
#include <qlayout.h>
#include <qshortcut.h>
#include <qsplitter.h>

CShaderToolMain::CShaderToolMain(QWidget *parent)
	: QMainWindow(parent)
	, m_CodeEditor(nullptr)
{
	m_MainUi.setupUi(this);
	m_MainUi.centralWidget->layout()->setSpacing(0);
	m_MainUi.centralWidget->layout()->setMargin(0);

	setWindowTitle(m_WindowName);

	connect(m_MainUi.CompileButton, SIGNAL(clicked()), this, SLOT(OnCompileClicked()));

	QShortcut *shortcut = new QShortcut(QKeySequence("Ctrl+S"), this);
	QObject::connect(shortcut, SIGNAL(activated()), this, SLOT(OnCompileClicked()));

	SetupTWScene();

	CConsole::Instance().Initialize(m_MainUi.Console);

	m_ProjectManager.Initialize(m_MainUi.LoadProjectButton, m_MainUi.SaveProjectButton);
	
	m_SceneManager.Initialize(&m_MainUi, m_MainUi.CodeEditor, m_MainUi.ResourceViewport, nullptr , nullptr);

	m_MainUi.Viewport->SetViewLayout(m_MainUi.ViewportLayout);

	m_Timeline.Initialize(&m_SceneManager, m_MainUi.Timeline, 
		m_MainUi.Play, m_MainUi.AudioWidget, 
		m_MainUi.Pause, m_MainUi.Stop, m_MainUi.Time);

	SetupCodeEditor();

	//TODO: Move this to the scene manager
	m_ProjectManager.RegisterSerializer(&m_SceneManager, "3BBA1716-3F89-49F1-B23D-724039F3A9C8");
}

void CShaderToolMain::OnFullscreen()
{
	m_MainUi.Viewport->ChangeFullscreen();
}

void CShaderToolMain::SetupCodeEditor()
{
	m_CodeEditor = m_MainUi.CodeEditor; 

	int aea;

	std::function<void(void*)> a = [&aea](void* p)
	{
		aea = 0;
	};

	m_SyntaxHighlighter = new CSyntaxHighlighter(m_CodeEditor->document());
}

void CShaderToolMain::SetupTWScene()
{
	m_pDefaultScene = new CDefaultScene();
	twSceneManager->AddScene(m_pDefaultScene, "Default");
	twSceneManager->SetActiveScene("Default");
	m_pDefaultScene->SetTimeline(&m_Timeline);
}

void CShaderToolMain::OnCompileClicked()
{
	std::vector<SShaderCode>* shaders = m_SceneManager.GetActiveScene()->m_pShaderManager->GetShaders();

	std::vector<triebWerk::CMaterial*> materials;

	static_cast<CDefaultScene*>(twSceneManager->m_pActiveScene->m_pScene)->ClearUsedTextures();

	for (size_t i = 0; i < shaders->size(); ++i)
	{
		materials.push_back(m_ShaderCreator.CreateShader(shaders->at(i).code.toStdString(), i));
	}

	m_pDefaultScene->UpdateMaterial(&materials);

	auto errors = twResourceManager->GetShaderGenerator()->GetLatestErrorMessages();

	m_CodeEditor->RemoveErrorLine();

	for (auto errorLine : errors.ErrorLines)
	{
		m_CodeEditor->SetErrorLine(errorLine - m_ShaderCreator.m_ShaderLineCount);
	}

	if (errors.ErrorMessages.size() == 0)
	{
		CConsole::Instance().PrintText("Compilation successful", CConsole::EPrintType::Success);
	}
	else
	{
		std::string string;
		for (auto error : errors.ErrorMessages)
		{
			string.append(error);
			string.append("\n");
		}
	
		CConsole::Instance().PrintText(string.c_str(), CConsole::EPrintType::Error);
	}
}