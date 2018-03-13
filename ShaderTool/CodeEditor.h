#pragma once
#include <qplaintextedit.h>

class CCodeEditorE : public QPlainTextEdit
{
	Q_OBJECT

public:
	CCodeEditorE(QWidget *parent = 0);

	void lineNumberAreaPaintEvent(QPaintEvent *event);
	int lineNumberAreaWidth();

	void SetText(QString text);
	void SetErrorLine(int line);
	void RemoveErrorLine();

protected:
	void resizeEvent(QResizeEvent *event) override;

	private slots:
	void updateLineNumberAreaWidth(int newBlockCount);
	void highlightCurrentLine();
	void highlightErrorLine();
	void updateLineNumberArea(const QRect &, int);

private:
	QWidget *lineNumberArea;
	int m_CurrentShaderSlot;
	std::vector<QString> m_Shaders;
	const QColor m_BackgroundColor = QColor(56, 56, 56);
	const QColor m_FontColor = Qt::white;
	const QColor m_SelectedLineColor = QColor(73, 73, 73);
	int m_ErrorLine;

	QFont m_Font;
};