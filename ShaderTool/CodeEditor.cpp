#include "CodeEditor.h"
#include "LineNumberArea.h"
#include <QPainter>
#include <QTextBlock>

CodeEditor::CodeEditor(QWidget *parent) 
	: QPlainTextEdit(parent) 
	, m_ErrorLine(-1)
	, m_CurrentShaderSlot(0)
{
	lineNumberArea = new LineNumberArea(this);

	connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
	connect(this, SIGNAL(updateRequest(QRect, int)), this, SLOT(updateLineNumberArea(QRect, int)));
	connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

	m_Font.setFamily("Consolas");
	m_Font.setFixedPitch(true);
	m_Font.setPointSize(9);
	this->setFont(m_Font);

	QPalette p = this->palette();
	p.setColor(QPalette::Base, m_BackgroundColor);
	this->setPalette(p);

	m_Shaders.push_back(QString()); //cant be empty

	updateLineNumberAreaWidth(0);
	highlightCurrentLine();
}

int CodeEditor::lineNumberAreaWidth()
{
	int digits = 1;
	int max = qMax(1, blockCount());
	while (max >= 10) {
		max /= 10;
		++digits;
	}

	int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;

	return space;
}

void CodeEditor::SetText(QString text)
{
	QTextCharFormat fmt;
	fmt.setForeground(QBrush(QColor(255, 255, 255)));
	this->mergeCurrentCharFormat(fmt);

	this->clear();
	this->textCursor().insertText(text);
}

void CodeEditor::SetErrorLine(int line)
{
	m_ErrorLine = line;
	repaint();
}

void CodeEditor::RemoveErrorLine()
{
	m_ErrorLine = -1;
	repaint();
}

void CodeEditor::updateLineNumberAreaWidth(int /* newBlockCount */)
{
	setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void CodeEditor::resizeEvent(QResizeEvent *e)
{
	QPlainTextEdit::resizeEvent(e);

	QRect cr = contentsRect();
	lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void CodeEditor::highlightCurrentLine()
{
	QList<QTextEdit::ExtraSelection> extraSelections;

	if (!isReadOnly()) {
		QTextEdit::ExtraSelection selection;

		selection.format.setBackground(m_SelectedLineColor);
		selection.format.setProperty(QTextFormat::FullWidthSelection, true);
		selection.cursor = textCursor();
		selection.cursor.clearSelection();
		extraSelections.append(selection);
	}

	setExtraSelections(extraSelections);
}

void CodeEditor::updateLineNumberArea(const QRect &rect, int dy)
{
	if (dy)
		lineNumberArea->scroll(0, dy);
	else
		lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

	if (rect.contains(viewport()->rect()))
		updateLineNumberAreaWidth(0);
}


void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
	QTextCharFormat fmt;
	fmt.setForeground(QBrush(QColor(255, 255, 255)));
	this->mergeCurrentCharFormat(fmt);

	QPainter painter(lineNumberArea);
	painter.fillRect(event->rect(), m_BackgroundColor);

	QTextBlock block = firstVisibleBlock();
	int blockNumber = block.blockNumber();
	int top = (int)blockBoundingGeometry(block).translated(contentOffset()).top();
	int bottom = top + (int)blockBoundingRect(block).height();

	while (block.isValid() && top <= event->rect().bottom()) {
		if (block.isVisible() && bottom >= event->rect().top()) {
			QString number = QString::number(blockNumber + 1);
			if(number.toInt() == m_ErrorLine)
				painter.setPen(QColor(125,0,0));
			else
				painter.setPen(m_FontColor);
			painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
				Qt::AlignRight, number);
		}

		block = block.next();
		top = bottom;
		bottom = top + (int)blockBoundingRect(block).height();
		++blockNumber;
	}
}

