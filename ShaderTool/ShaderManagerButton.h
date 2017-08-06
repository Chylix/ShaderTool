#pragma once
#include <QLineEdit>
#include <QMouseEvent>

class CShaderManager;

class CShaderManangerButton : public QLineEdit
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

private:
	const int m_MaximumButtonSize = 30;
};