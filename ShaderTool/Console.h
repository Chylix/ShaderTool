#pragma once
#include <sstream>
#include <string.h>

class QTextEdit;

class CConsole
{
public:
	enum class EPrintType
	{
		Text,
		Error,
		Warning,
		Success
	};

private:
	CConsole();
	~CConsole();

public:
	static CConsole& Instance();

	void Initialize(QTextEdit* widget);
	void PrintText(const char* pText, EPrintType type = EPrintType::Text);
	void PrintText(std::string text, EPrintType type = EPrintType::Text);

	void PrintShaderError(const char* pError);

private:
	QTextEdit* m_pConsoleWidget;
};