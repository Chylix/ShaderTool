#pragma once
#include <QWidget>
#include <QPaintEvent>
#include <QPixmap>
#include <QPainter>
#include <qplaintextedit.h>

class QPainter;

class CAudioWidget : public QWidget {
	Q_OBJECT

public:
	CAudioWidget(QWidget *parent = 0);

	void PlayAudio();
	void PlayAudioAtPosition(int millisecond);
	void StopAudio();

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
};