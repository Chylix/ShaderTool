#include "ShaderToolMain.h"
#include "SyntaxHighlighter.h"
#include "D3DRenderWidget.h"
#include <QLayout.h>
#include <CEngine.h>

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
	QFont font;
	font.setFamily("Consolas");
	font.setFixedPitch(true);
	font.setPointSize(10);

	m_MainUi.textEdit->setFont(font);

	m_CodeEditor = m_MainUi.plainTextEdit;

	m_CodeEditor->SetText(m_ShaderDefaultCode);
	m_SyntaxHighlighter = new CSyntaxHighlighter(m_CodeEditor->document());

}

void CShaderToolMain::OnCompileClicked()
{
	QString shaderTextToCompile = m_CodeEditor->toPlainText();

	triebWerk::CMaterial* mat = m_ShaderCreator.CreateShader(shaderTextToCompile.toStdString());

	m_pDefaultScene->UpdateMaterial(mat);

	auto errors = m_ShaderCreator.GetLatestErrors();

	errors.erase(errors.begin());

	if (errors.size() == 0)
	{
		m_MainUi.textEdit->setTextColor(Qt::darkGreen);
		m_MainUi.textEdit->setText("Compilation successful");
	}
	else
	{
		QString string;
		for (auto error : errors)
		{
			string.append(error.c_str());
			string.append("\n");
		}

		m_MainUi.textEdit->setTextColor(Qt::darkRed);
		m_MainUi.textEdit->setText(string);
	}
}