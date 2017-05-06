#include "ShaderToolMain.h"
#include "SyntaxHighlighter.h"
#include "D3DRenderWidget.h"
#include <QLayout.h>
#include <CEngine.h>
#include <qlayout.h>

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
	//OnCompileClicked();

	//setAcceptDrops(true);
}

void CShaderToolMain::SetupCodeEditor()
{
	//TODO: move this to the editor
	QFont font;
	font.setFamily("Consolas");
	font.setFixedPitch(true);
	font.setPointSize(10);

	m_MainUi.textEdit->setFont(font);

	m_CodeEditor = m_MainUi.plainTextEdit;

	m_SyntaxHighlighter = new CSyntaxHighlighter(m_CodeEditor->document());

	m_ShaderManager.Initialize(m_CodeEditor, &m_MainUi);
}

void CShaderToolMain::OnCompileClicked()
{
	std::vector<SShaderCode>* shaders = m_ShaderManager.GetShaders();

	std::vector<triebWerk::CMaterial*> materials;

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
		m_MainUi.textEdit->setTextColor(Qt::darkGreen);
		m_MainUi.textEdit->setText("Compilation successful");
	}
	else
	{
		QString string;
		for (auto error : errors.ErrorMessages)
		{
			string.append(error.c_str());
			string.append("\n");
		}
	
		m_MainUi.textEdit->setTextColor(Qt::darkRed);
		m_MainUi.textEdit->setText(string);
	}
}