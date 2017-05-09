#pragma once
#include <QPushButton>
#include <QMouseEvent>

class CShaderManager;

class CShaderManangerButton : public QPushButton
{
	Q_OBJECT

public:
	void Init(const size_t shaderSlot, CShaderManager* pParent);
	void UpdateSlot(size_t newSlot);
	void SetAsActive(bool state);

private slots:
	void mousePressEvent(QMouseEvent *e);

private:
	size_t m_Slot;
	CShaderManager* m_pParent;
	void Remove();
	void Change();
};