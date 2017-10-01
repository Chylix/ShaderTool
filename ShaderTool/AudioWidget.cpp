#include "AudioWidget.h"
#include <qevent.h>
#include <qmimedata.h>
#include <qlist.h>
#include <CEngine.h>
#include "Console.h"

CAudioWidget::CAudioWidget(QWidget *parent)
{
	setAcceptDrops(true);
}

void CAudioWidget::PlayAudio()
{
	if(m_AudioFile.size() > 0)
		twAudio->PlayBGM(twResourceManager->GetSound(m_AudioFile.c_str()), true, false);
}

void CAudioWidget::PlayAudioAtPosition(int millisecond)
{
	if (m_AudioFile.size() > 0)
		twAudio->PlayAtPosition(twResourceManager->GetSound(m_AudioFile.c_str()), (unsigned int)millisecond);
}

void CAudioWidget::StopAudio()
{
	twAudio->StopAllSounds();
}

void CAudioWidget::paintEvent(QPaintEvent * e)
{
	QRect thisRect = rect();
	QPainter painter(this);
	m_pCurrentPainter = &painter;
	m_pCurrentPainter->fillRect(thisRect, QColor(46, 46, 46));
	QPen penHText(QColor(255, 255, 255));
	m_pCurrentPainter->setBackground(QColor(46, 46, 46));
	m_pCurrentPainter->setPen(penHText);
	QTextOption textOption = QTextOption(Qt::AlignCenter);
	m_pCurrentPainter->drawText(thisRect, QString(m_AudioFile.c_str()), textOption);
}

void CAudioWidget::dragEnterEvent(QDragEnterEvent * e)
{
	e->acceptProposedAction();
}

void CAudioWidget::dropEvent(QDropEvent * e)
{
	//Check if we accept this event
	if (!e->mimeData()->hasUrls() || !CheckFileIfSupported(e))
		return;

	std::string filePath = e->mimeData()->urls()[0].toLocalFile().toStdString();

	//Load the file

	twResourceManager->LoadSpecificFile(filePath.c_str(), true);
	m_AudioFile = twResourceManager->AbstractFileNameFromPathOne(twResourceManager->RemoveFileType(filePath)).c_str();

	this->repaint();
}

void CAudioWidget::mousePressEvent(QMouseEvent * event)
{
}

bool CAudioWidget::CheckFileIfSupported(const QDropEvent * event)
{
	auto urls = event->mimeData()->urls();

	std::string filePath = urls[0].toLocalFile().toStdString();

	triebWerk::EFileType type = twResourceManager->GetFileType(filePath);

	if (type == triebWerk::EFileType::WAV)
	{
		return true;
	}
	else
	{
		std::string warning = "Filetype is not supported: ";
		warning += twResourceManager->AbstractFileNameFromPathOne(filePath);

		CConsole::Instance().PrintText(warning.c_str(), CConsole::EPrintType::Warning);

		return false;
	}
}
