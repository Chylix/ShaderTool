#include "DefaultScene.h"
#include "Console.h"
#include "CTexturePainter.h"
#include <CEngine.h>
#include <qevent.h>
#include <qmimedata.h>
#include <qlist.h>

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

void CTexturePainter::dropEvent(QDropEvent * event)
{
	//Check if we accept this event
	if (!event->mimeData()->hasUrls() || !CheckFilesIfSupported(event))
		return;

	//Check if we have to replace a texture
	size_t slot = FindTextureIndexFromPosition(event->pos());

	if (slot != UINT_MAX)
	{
		ReplaceTexture(event, slot);
	}
	else
	{
		AddTexture(event);
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
	m_pCurrentPainter->drawText(textRect, QString(std::to_string(iter+1).c_str()) + ": " + m_Pictures[iter].name, textOption);
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
			static_cast<CDefaultScene*>(twSceneManager->m_pActiveScene->m_pScene)->RemoveLoadedTextures(index);
			repaint();
		}
	}break;
	case Qt::LeftButton:
	{
		//Maybe do something here
	}break;
	}
}

size_t CTexturePainter::FindTextureIndexFromPosition(QPoint pos)
{
	for (size_t i = 0; i < m_Pictures.size(); i++)
	{
		if (m_Pictures[i].rect.contains(pos))
		{
			return i;
		}
	}

	return UINT_MAX;
}

void CTexturePainter::ReplaceTexture(const QDropEvent * event, size_t slot)
{
	auto url = event->mimeData()->urls()[0]; //just take the first and ignore the others

	std::string filePath = url.toLocalFile().toStdString(); 

	//Load the file
	twResourceManager->LoadSpecificFile(filePath.c_str(), true);

	//create the texture desc
	SShaderTexture texture;
	texture.map = QPixmap(QString(filePath.c_str()));
	texture.name = GetFileName(filePath);

	//Replace the old texture
	m_Pictures[slot] = texture;

	static_cast<CDefaultScene*>(twSceneManager->m_pActiveScene->m_pScene)->ReplaceLoadedTextures(slot, texture.name.toStdString().c_str());
}

void CTexturePainter::AddTexture(const QDropEvent * event)
{
	auto urls = event->mimeData()->urls();

	for (size_t i = 0; i < urls.size(); i++)
	{
		std::string filePath = urls[i].toLocalFile().toStdString();

		//Load the file
		twResourceManager->LoadSpecificFile(filePath.c_str(), true);

		//create the texture desc
		SShaderTexture texture;
		texture.map = QPixmap(QString(filePath.c_str()));
		texture.name = GetFileName(filePath);

		m_Pictures.push_back(texture);

		static_cast<CDefaultScene*>(twSceneManager->m_pActiveScene->m_pScene)->UpdateLoadedTextures(texture.name.toStdString().c_str());
	}
}

QString CTexturePainter::GetFileName(std::string & string)
{
	return QString(twResourceManager->AbstractFileNameFromPathOne(twResourceManager->RemoveFileType(string)).c_str());
}

bool CTexturePainter::CheckFilesIfSupported(const QDropEvent* event)
{
	auto urls = event->mimeData()->urls();

	for (size_t i = 0; i < urls.size(); i++)
	{
		std::string filePath = urls[i].toLocalFile().toStdString();

		triebWerk::EFileType type = twResourceManager->GetFileType(filePath);

		if (type == triebWerk::EFileType::DDS || type == triebWerk::EFileType::PNG)
			continue;
		else
		{
			std::string warning = "Filetype is not supported: ";
			warning += twResourceManager->AbstractFileNameFromPathOne(filePath);

			CConsole::Instance().PrintText(warning.c_str(), CConsole::EPrintType::Warning);

			return false;
		}
	}

	return true;
}

void CTexturePainter::SetTextures(std::vector<CTexturePainter::SShaderTexture>& textures)
{
	CConsole::Instance().PrintText(std::to_string(textures.size()).c_str(), CConsole::EPrintType::Warning);
	m_Pictures.clear();
	m_Pictures = textures;

	static_cast<CDefaultScene*>(twSceneManager->m_pActiveScene->m_pScene)->ClearLoadedTextures();

	for (auto& texture : m_Pictures)
	{
		static_cast<CDefaultScene*>(twSceneManager->m_pActiveScene->m_pScene)->UpdateLoadedTextures(texture.name.toStdString().c_str());
	}

	// Retrigger painting to draw the new/updated textures.
	this->repaint();
}
