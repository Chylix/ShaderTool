#pragma once
#include <qplaintextedit.h>

class CodeEditor : public QPlainTextEdit
{
	Q_OBJECT

public:
	CodeEditor(QWidget *parent = 0);

	void lineNumberAreaPaintEvent(QPaintEvent *event);
	int lineNumberAreaWidth();

	void SetText(QString text);

protected:
	void resizeEvent(QResizeEvent *event) override;

	private slots:
	void updateLineNumberAreaWidth(int newBlockCount);
	void highlightCurrentLine();
	void updateLineNumberArea(const QRect &, int);

private:
	QWidget *lineNumberArea;
	const QColor m_BackgroundColor = QColor(76, 76, 76);
	const QColor m_FontColor = Qt::white;
	const QColor m_SelectedLineColor = QColor(73, 73, 73);
	QFont m_Font;
};