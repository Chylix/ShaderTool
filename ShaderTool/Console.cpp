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
	font.setFamily("Courier");
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

void CConsole::PrintText(std::string text, EPrintType type)
{
	PrintText(text.c_str(), type);
}

void CConsole::PrintShaderError(const char* pError)
{
	m_pConsoleWidget->clear();

	std::string text = pError;
	
	size_t pos;
	
	{
		pos = text.find(":", 0);

		std::string a = text.substr(0, pos);
		a.insert(a.begin(), '[');
		a.push_back(']');

		pos++;

		m_pConsoleWidget->setTextColor(Qt::darkRed);
		m_pConsoleWidget->insertPlainText(a.c_str());
	}

	{
		size_t temp = text.find(":", pos);

		std::string a = text.substr(pos, temp - pos);

		pos += (temp - pos) + 1;

		m_pConsoleWidget->setTextColor(QColor(120, 120, 120));
		m_pConsoleWidget->insertPlainText(a.c_str());
	}

	{
		size_t temp = text.find(":", pos);

		if (temp == std::string::npos)
		{
			std::string a = text.substr(pos, a.size() - pos);

			pos += temp;

			m_pConsoleWidget->setTextColor(Qt::white);
			m_pConsoleWidget->append(a.c_str());
		}
		else
		{
			std::string a = text.substr(pos, temp - pos);

			pos += (temp - pos) + 1;

			m_pConsoleWidget->setTextColor(QColor(120, 120, 120));
			m_pConsoleWidget->insertPlainText(a.c_str());

			{
				pos++;
				std::string a = text.substr(pos, a.size() - pos);

				pos += temp;

				m_pConsoleWidget->setTextColor(Qt::white);
				m_pConsoleWidget->append(a.c_str());
			}
		}
	}
}
 