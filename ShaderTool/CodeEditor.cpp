#include "codeeditor.h"
#include "LineNumberArea.h"
#include <QPainter>
#include <QTextBlock>
#include "Console.h"

CCodeEditorE::CCodeEditorE(QWidget *parent) 
	: QPlainTextEdit(parent) 
	, m_ErrorLine(-1)
	, m_CurrentShaderSlot(0)
{
	lineNumberArea = new LineNumberArea(this);

	connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
	connect(this, SIGNAL(updateRequest(QRect, int)), this, SLOT(updateLineNumberArea(QRect, int)));
	connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

	this->setFrameStyle(QFrame::NoFrame);

	const int tabStop = 2;  // 4 characters

	m_Font.setFamily("Courier");
	//m_Font.setFixedPitch(true);
	m_Font.setPointSize(m_FontSize);
	this->setFont(m_Font);

	QFontMetrics metrics(m_Font);
	this->setTabStopWidth(tabStop * metrics.width(' '));

	QPalette p = this->palette();
	p.setColor(QPalette::Base, m_BackgroundColor);
	this->setPalette(p);

	m_Shaders.push_back(QString()); //cant be empty

	updateLineNumberAreaWidth(0);
	highlightCurrentLine();
}

int CCodeEditorE::lineNumberAreaWidth()
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

void CCodeEditorE::SetText(QString text)
{
	QTextCharFormat fmt;
	fmt.setForeground(QBrush(QColor(255, 255, 255)));
	this->mergeCurrentCharFormat(fmt);

	this->clear();
	this->textCursor().insertText(text);
}

void CCodeEditorE::SetErrorLine(int line)
{
	m_ErrorLine = line;
	highlightErrorLine();
	repaint();
}

void CCodeEditorE::RemoveErrorLine()
{
	m_ErrorLine = -1;
	highlightCurrentLine();
	repaint();
}

void CCodeEditorE::updateLineNumberAreaWidth(int /* newBlockCount */)
{
	setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void CCodeEditorE::resizeEvent(QResizeEvent *e)
{
	QPlainTextEdit::resizeEvent(e);

	QRect cr = contentsRect();
	lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void CCodeEditorE::highlightCurrentLine()
{
	if (m_ErrorLine == -1)
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
}

void CCodeEditorE::highlightErrorLine()
{
	QList<QTextEdit::ExtraSelection> extraSelections;

	if (!isReadOnly()) {
		QTextEdit::ExtraSelection selection;

		QTextCursor a = textCursor();
		
		QTextBlock block = firstVisibleBlock();

		for (size_t i = 0; i < m_ErrorLine-1; i++)
		{
			block = block.next();
		}

		a.setPosition(block.position());

		selection.format.setBackground(QColor(140, 0, 0));
		selection.format.setProperty(QTextFormat::FullWidthSelection, true);
		selection.cursor = a;
		selection.cursor.clearSelection();
		extraSelections.append(selection);
	}

	setExtraSelections(extraSelections);
}

void CCodeEditorE::updateLineNumberArea(const QRect &rect, int dy)
{
	if (dy)
		lineNumberArea->scroll(0, dy);
	else
		lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

	if (rect.contains(viewport()->rect()))
		updateLineNumberAreaWidth(0);
}

void CCodeEditorE::wheelEvent(QWheelEvent* event)
{
	if (m_IsZooming == false)
		return;

	m_FontSize += event->delta() / 120;

	if (m_FontSize < m_MinFontSize)
		m_FontSize = m_MinFontSize;
	else if(m_FontSize > m_MaxFontSize)
		m_FontSize = m_MaxFontSize;

	m_Font.setFamily("Courier");
	m_Font.setFixedPitch(true);
	m_Font.setPointSize(m_FontSize);

	CConsole::Instance().PrintText(std::to_string(m_FontSize));

	this->setFont(m_Font);
}

void CCodeEditorE::keyPressEvent(QKeyEvent* pEvent)
{
	if(pEvent->key() == Qt::Key_Control)
	{
		m_IsZooming = true;
	}

	QPlainTextEdit::keyPressEvent(pEvent);
}

void CCodeEditorE::keyReleaseEvent(QKeyEvent* pEvent)
{
	if (pEvent->key() == Qt::Key_Control)
	{
		m_IsZooming = false;
	}

	QPlainTextEdit::keyReleaseEvent(pEvent);
}

void CCodeEditorE::lineNumberAreaPaintEvent(QPaintEvent *event)
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
			painter.setFont(m_Font);
			painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
				Qt::AlignRight, number);
		}

		block = block.next();
		top = bottom;
		bottom = top + (int)blockBoundingRect(block).height();
		++blockNumber;
	}
}

