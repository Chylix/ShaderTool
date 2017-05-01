#pragma once
#include <QWidget>
#include <QPaintEvent>
#include <QPixmap>
#include <QPainter>

class QPainter;

class CTexturePainter : public QWidget {
	Q_OBJECT

public:
	struct SShaderTexture
	{
		QPixmap map;
		QString name;
	};


public:
	CTexturePainter(QWidget *parent = 0);
	std::vector<SShaderTexture>& GetLoadedTexture();

protected:
	void paintEvent(QPaintEvent* e);
	virtual void dragEnterEvent(QDragEnterEvent* e);
	virtual void dropEvent(QDropEvent * e);

private:
	int m_DefaultTextureSize;
	int m_DefaultTexturesPerRow = 5;
	std::vector<SShaderTexture> m_Pictures;
	QPainter* m_pCurrentPainter;
	int m_YParam = 0;
	int m_XParam = 0;

private:
	void DrawTextAndField(const int iter);
	void DrawBackground();

};