#pragma once
#include <qwidget.h>
#include "CodeEditor.h"

class LineNumberArea : public QWidget
{
public:
	LineNumberArea(CCodeEditorE *editor) : QWidget(editor) {
		codeEditor = editor;
	}

	QSize sizeHint() const override {
		return QSize(codeEditor->lineNumberAreaWidth(), 0);
	}

protected:
	void paintEvent(QPaintEvent *event) override {
		codeEditor->lineNumberAreaPaintEvent(event);
	}

private:
	CCodeEditorE *codeEditor;
};