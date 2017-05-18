#include "Console.h"
#include <qtextedit.h>

CConsole::~CConsole()
{
}

CConsole::CConsole() 
{
}


CConsole& CConsole::Instance()
{
	static CConsole engine;
	return engine;
}

void CConsole::Initialize(QTextEdit * widget)
{
	m_pConsoleWidget = widget;

	//TODO: move this to the editor
	QFont font;
	font.setFamily("Consolas");
	font.setFixedPitch(true);
	font.setPointSize(10);

	m_pConsoleWidget->setFont(font);
}

void CConsole::PrintText(const char * pText, EPrintType type)
{
	switch (type)
	{
	case CConsole::EPrintType::Text:
		m_pConsoleWidget->setTextColor(Qt::white);
		break;
	case CConsole::EPrintType::Error:
		m_pConsoleWidget->setTextColor(Qt::darkRed);
		break;
	case CConsole::EPrintType::Warning:
		m_pConsoleWidget->setTextColor(Qt::darkYellow);
		break;
	case CConsole::EPrintType::Success:
		m_pConsoleWidget->setTextColor(Qt::darkGreen);
		break;
	}

	m_pConsoleWidget->setText(pText);
}
