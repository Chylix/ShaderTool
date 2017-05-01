#include "CTexturePainter.h"
#include <CEngine.h>
#include <qevent.h>
#include <qmimedata.h>
#include <qlist.h>
#include "DefaultScene.h"

CTexturePainter::CTexturePainter(QWidget *parent) 
	: QWidget(parent)
{
	//auto files = twResourceManager->SearchFolderForAllFiles("data/Assets/Textures");

	//for (auto file : files)
	//{
	//	SShaderTexture t;
	//	t.map = QPixmap(QString::fromStdString(file.FilePath));
	//	t.name = QString::fromStdString(twResourceManager->RemoveFileType(file.FileName));
	//	m_Pictures.push_back(t);
	//}

	setAcceptDrops(true);
}

void CTexturePainter::paintEvent(QPaintEvent *e) {

	QPainter painter(this);
	m_pCurrentPainter = &painter;
	m_YParam = 0;
	m_XParam = 0;

	painter.begin(this);

	DrawBackground();

	const int rcWidth = rect().width();

	for (size_t i = 0; i < m_Pictures.size(); i++)
	{
		if ((rcWidth - i * m_DefaultTextureSize) < m_DefaultTextureSize)
		{
			//Do soemthing
			m_YParam += m_DefaultTextureSize + 20;
			m_XParam = 0;
		}

		painter.drawPixmap(m_XParam, m_YParam, m_DefaultTextureSize, m_DefaultTextureSize, m_Pictures[i].map);
		DrawTextAndField(i);
		m_XParam += m_DefaultTextureSize;
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
	QPen pen(QColor(46, 46, 46));
	m_pCurrentPainter->setPen(pen);

	QRect textRect = QRect(m_XParam, m_DefaultTextureSize + m_YParam, m_DefaultTextureSize, 20);

	m_pCurrentPainter->drawRect(textRect);
	QPen penHText(QColor(255, 255, 255));
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
