#include "SyntaxHighlighter.h"

CSyntaxHighlighter::CSyntaxHighlighter(QTextDocument* parent)
	:QSyntaxHighlighter(parent)
{
	HighlightingRule rule;

	auto e1 = QColor(144, 120, 51);

	keywordFormat.setForeground(e1);
	keywordFormat.setFontWeight(QFont::Bold);
	QStringList keywordPatterns;
	keywordPatterns
		// ------Types------
		<< "\\bchar\\b"			// char
		<< "\\bconst\\b"		// const
		<< "\\bdouble\\b"		// double
		<< "\\bfloat\\b"		// float
		<< "\\bint\\b"			// int
		<< "\\blong\\b"			// long
		<< "\\bfloat2\\b"		// float2
		<< "\\bfloat3\\b"		// float3
		<< "\\bfloat4\\b"		// float4
		<< "\\bshort\\b"		// short
		// ------Functions------
		<< "\\babs\\b"			// abs
		<< "\\bacos\\b"			// acos
		<< "\\bacos\\b"			// acos
		<< "\\bceil\\b"			// ceil
		<< "\\bclamp\\b"		// clamp
		<< "\\bclip\\b"			// clip
		<< "\\bcos\\b"			// cos
		<< "\\bcross\\b"		// cross
		<< "\\bdegrees\\b"		// degrees
		<< "\\bdistance\\b"		// distance
		<< "\\bdot\\b"			// dot
		<< "\\bexp\\b"			// exp
		<< "\\bfoor\\b"			// floor
		<< "\\bfmod\\b"			// fmod
		<< "\\bfrac\\b"			// frac
		<< "\\blength\\b"		// length
		<< "\\blerp\\b"			// lerp
		<< "\\blog\\b"			// log
		<< "\\bmax\\b"			// max
		<< "\\bmin\\b"			// min
		<< "\\bmul\\b"			// mul
		<< "\\bnoise\\b"		// noise
		<< "\\bnormalize\\b"	// normalize
		<< "\\bpow\\b"			// pow
		<< "\\breflect\\b"		// reflect
		<< "\\bround\\b"		// round
		<< "\\bsaturate\\b"		// saturate
		<< "\\bsin\\b"			// sin
		<< "\\bsmoothstep\\b"	// smoothstep
		<< "\\bsqrt\\b"			// sqrt
		<< "\\btan\\b"			// tan
		// ------Keywords------
		<< "\\breturn\\b"
		<< "\\boperator\\b"
		<< "\\bprotected\\b"
		<< "\\bpublic\\b"
		<< "\\bsignals\\b"
		<< "\\bsigned\\b"
		<< "\\bslots\\b"
		<< "\\bstatic\\b"
		<< "\\bstruct\\b"
		<< "\\btemplate\\b"
		<< "\\btypedef\\b"
		<< "\\btypename\\b"
		<< "\\bunion\\b"
		<< "\\bunsigned\\b"
		<< "\\bvirtual\\b"
		<< "\\bvoid\\b"
		<< "\\bvolatile\\b"
		<< "\\bTexture2D\\b";
	foreach(const QString &pattern, keywordPatterns)
	{
		rule.pattern = QRegExp(pattern);
		rule.format = keywordFormat;
		highlightingRules.append(rule);
	}

	classFormat.setFontWeight(QFont::Bold);
	classFormat.setForeground(Qt::darkMagenta);
	rule.pattern = QRegExp("\\bQ[A-Za-z]+\\b");
	rule.format = classFormat;
	highlightingRules.append(rule);

	quotationFormat.setForeground(Qt::darkGreen);
	rule.pattern = QRegExp("\".*\"");
	rule.format = quotationFormat;
	highlightingRules.append(rule);

	auto e = QColor(108, 153, 187);

	functionFormat.setFontItalic(true);
	functionFormat.setForeground(e);
	rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
	rule.format = functionFormat;
	highlightingRules.append(rule);

	singleLineCommentFormat.setForeground(Qt::darkGreen);
	rule.pattern = QRegExp("//[^\n]*");
	rule.format = singleLineCommentFormat;
	highlightingRules.append(rule);

	multiLineCommentFormat.setForeground(Qt::darkGreen);

	commentStartExpression = QRegExp("/\\*");
	commentEndExpression = QRegExp("\\*/");
}

void CSyntaxHighlighter::highlightBlock(const QString & text)
{
	foreach(const HighlightingRule &rule, highlightingRules)
	{
		QRegExp expression(rule.pattern);
		int index = expression.indexIn(text);
		while (index >= 0)
		{
			int length = expression.matchedLength();
			setFormat(index, length, rule.format);
			index = expression.indexIn(text, index + length);
		}
	}

	setCurrentBlockState(0);

	int startIndex = 0;
	if (previousBlockState() != 1)
		startIndex = commentStartExpression.indexIn(text);

	while (startIndex >= 0)
	{
		int endIndex = commentEndExpression.indexIn(text, startIndex);
		int commentLength;
		if (endIndex == -1)
		{
			setCurrentBlockState(1);
			commentLength = text.length() - startIndex;
		}
		else
		{
			commentLength = endIndex - startIndex
				+ commentEndExpression.matchedLength();
		}

		setFormat(startIndex, commentLength, multiLineCommentFormat);
		startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
	}
}
