#pragma once
#include <QWidget>
#include <QPaintEvent>
#include <QPixmap>
#include <QPainter>
#include <qplaintextedit.h>
#include "ISerializer.h"

class QPainter;

class CAudioWidget : public QWidget, public ISerializer {
	Q_OBJECT

public:
	CAudioWidget(QWidget *parent = 0);

	void PlayAudio();
	void PlayAudioAtPosition(int millisecond);
	void StopAudio();
	void PauseAudio(bool pause);

	virtual const char* SaveData();
	virtual void LoadData(CSerializerChunk* pData);

protected:
	void paintEvent(QPaintEvent* e);
	virtual void dragEnterEvent(QDragEnterEvent* e);
	virtual void dropEvent(QDropEvent * e);
	virtual void mousePressEvent(QMouseEvent *event);

private:
	bool CheckFileIfSupported(const QDropEvent* event);
	QPainter* m_pCurrentPainter = nullptr;

private:
	std::string m_AudioFile;
	std::string m_buffer;
};