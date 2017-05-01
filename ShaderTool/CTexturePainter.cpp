#include "CTexturePainter.h"
#include <CEngine.h>
#include <qevent.h>
#include <qmimedata.h>
#include <qlist.h>
#include "DefaultScene.h"

CTexturePainter::CTexturePainter(QWidget *parent) 
	: QWidget(parent)
{
	setAcceptDrops(true);
}

void CTexturePainter::paintEvent(QPaintEvent *e) {

	QRect thisRect = rect();

	int size = thisRect.width() / m_DefaultTexturesPerRow;
	m_DefaultTextureSize = size;

	QPainter painter(this);
	m_pCurrentPainter = &painter;
	m_YParam = 0;
	m_XParam = 0;

	painter.begin(this);

	DrawBackground();

	const int rcWidth = rect().width();

	int columIter = 0;

	for (size_t i = 0; i < m_Pictures.size(); i++)
	{
		if ((rcWidth - columIter * m_DefaultTextureSize) < m_DefaultTextureSize)
		{
			m_YParam += m_DefaultTextureSize + 20;
			m_XParam = 0;
			columIter = 0;
		}

		QRect rect;
		rect.setX(m_XParam);
		rect.setY(m_YParam);
		rect.setHeight(m_DefaultTextureSize);
		rect.setWidth(m_DefaultTextureSize);
		m_Pictures[i].rect = rect;
		painter.drawPixmap(rect, m_Pictures[i].map);
		DrawTextAndField(i);
		m_XParam += m_DefaultTextureSize;
		columIter++;
	}

	painter.end();
}

void CTexturePainter::dragEnterEvent(QDragEnterEvent * e)
{
	e->acceptProposedAction();
}

void CTexturePainter::dropEvent(QDropEvent * e)
{
	if (e->mimeData()->hasUrls())
	{
		auto a = e->mimeData()->urls();

		for (size_t i = 0; i < a.size(); i++)
		{
			QString x = a[i].toLocalFile();
			std::string y = x.toStdString();
			twResourceManager->LoadSpecificFile(y.c_str(), true);
			SShaderTexture t;
			t.map = QPixmap(QString::fromStdString(y));
			std::string name = twResourceManager->AbstractFileNameFromPathOne(y);
			t.name = QString::fromStdString(twResourceManager->RemoveFileType(name));
			m_Pictures.push_back(t);
			static_cast<CDefaultScene*>(twSceneManager->m_pActiveScene->m_pScene)->UpdateLoadedTextures(t.name.toStdString().c_str());
		}
	}

	this->repaint();
}

std::vector<CTexturePainter::SShaderTexture>& CTexturePainter::GetLoadedTexture()
{
	return m_Pictures;
}

void CTexturePainter::DrawTextAndField(const int iter)
{
	QRect textRect = QRect(m_XParam, m_DefaultTextureSize + m_YParam, m_DefaultTextureSize, 20);

	m_pCurrentPainter->fillRect(textRect, QColor(46,46,46));
	QPen penHText(QColor(255, 255, 255));
	m_pCurrentPainter->setBackground(QColor(46, 46, 46));
	m_pCurrentPainter->setPen(penHText);
	QTextOption textOption = QTextOption(Qt::AlignCenter);
	m_pCurrentPainter->drawText(textRect, QString(std::to_string(iter).c_str()) + ": " + m_Pictures[iter].name, textOption);
}

void CTexturePainter::DrawBackground()
{
	m_pCurrentPainter->fillRect(rect(), QColor(76, 76, 76));

	m_pCurrentPainter->setBackground(QColor(76, 76, 76));
	m_pCurrentPainter->setBackgroundMode(Qt::BGMode::OpaqueMode);
}

void CTexturePainter::mousePressEvent(QMouseEvent * event)
{
	QPoint pos = event->pos();

	switch (event->button())
	{
	case Qt::RightButton:
	{
		if (m_Pictures.size() != 0)
		{
			size_t index = FindTextureIndexFromPosition(event->pos());
			m_Pictures.erase(m_Pictures.begin() + index);
			repaint();
		}
	}break;
	case Qt::LeftButton:
	{
		//Maybe do something here
	}break;
	}
	int a = 0;
}

size_t CTexturePainter::FindTextureIndexFromPosition(QPoint pos)
{
	for (size_t i = 0; i < m_Pictures.size(); i++)
	{
		bool isIn = m_Pictures[i].rect.contains(pos);
		if (isIn)
		{
			return i;
		}
	}

	//TODO: this is dangerous since this could be a valid return
	return 0;
}
