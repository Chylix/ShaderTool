#pragma once
#include <QLineEdit>
#include <QMouseEvent>

class CSceneManager;

class CSceneButton : public QLineEdit
{
	Q_OBJECT

public:
	void Init(const size_t shaderSlot, CSceneManager* pParent);
	void UpdateSlot(size_t newSlot);
	void SetAsActive(bool state);

	private slots:
	void mousePressEvent(QMouseEvent *e);

private:
	size_t m_Slot;
	CSceneManager* m_pParent;
	void Remove();
	void Change();
};
