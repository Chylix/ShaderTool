#include "ShaderToolMain.h"
#include "SyntaxHighlighter.h"
#include "D3DRenderWidget.h"
#include "Console.h"
#include <QLayout.h>
#include <CEngine.h>
#include <qlayout.h>
#include <qshortcut.h>


CShaderToolMain::CShaderToolMain(QWidget *parent)
	: QMainWindow(parent)
	, m_CodeEditor(nullptr)
{
	m_MainUi.setupUi(this);

	setWindowTitle(m_WindowName);

	SetupCodeEditor();

	m_pDefaultScene = new CDefaultScene();

	twSceneManager->AddScene(m_pDefaultScene, "Default");
	twSceneManager->SetActiveScene("Default");

	connect(m_MainUi.compileButton, SIGNAL(clicked()), this, SLOT(OnCompileClicked()));
	QShortcut *shortcut = new QShortcut(QKeySequence("Ctrl+S"), this);
	QObject::connect(shortcut, SIGNAL(activated()), this, SLOT(OnCompileClicked()));

	CConsole::Instance().Initialize(m_MainUi.textEdit);
	m_ProjectManager.Initialize(m_MainUi.OpenProject, m_MainUi.SaveProject);
	
	//What ever this needs to be moved
	m_ProjectManager.RegisterSerializer(&m_ShaderManager, "3BBA1716-3F89-49F1-B23D-724039F3A9C8");
}

void CShaderToolMain::OnFullscreen()
{
	m_MainUi.viewport->ChangeFullscreen();
}

void CShaderToolMain::SetupCodeEditor()
{
	m_CodeEditor = m_MainUi.plainTextEdit;

	m_SyntaxHighlighter = new CSyntaxHighlighter(m_CodeEditor->document());

	m_ShaderManager.Initialize(m_CodeEditor, &m_MainUi);
}

void CShaderToolMain::OnCompileClicked()
{
	m_MainUi.viewport->ForceResize();

	std::vector<SShaderCode>* shaders = m_ShaderManager.GetShaders();

	std::vector<triebWerk::CMaterial*> materials;

	static_cast<CDefaultScene*>(twSceneManager->m_pActiveScene->m_pScene)->ClearUsedTextures();

	for (size_t i = 0; i < shaders->size(); ++i)
	{
		materials.push_back(m_ShaderCreator.CreateShader(shaders->at(i).code.toStdString(), i));
	}

	m_pDefaultScene->UpdateMaterial(&materials);

	auto errors = twResourceManager->GetShaderGenerator()->GetLatestErrorMessages();
	
	//TODO: fixed this double none error problem
	//only a workaround
	//errors.ErrorMessages.erase(errors.ErrorMessages.begin());

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