#pragma once

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
	void PrintText(const char* pText, EPrintType);

private:
	QTextEdit* m_pConsoleWidget;
};