#include "SceneButton.h"

void CSceneButton::mousePressEvent(QMouseEvent *e)
{
	if (e->button() == Qt::RightButton)
		Remove();
	else if (e->button() == Qt::LeftButton)
		Change();
}

void CSceneButton::Init(const size_t shaderSlot, CSceneManager* pParent)
{
	m_Slot = shaderSlot;
	m_pParent = pParent;

	this->setMaximumHeight(40);
	this->setCursor(Qt::ArrowCursor);
	this->setAlignment(Qt::AlignHCenter);
	this->setStyleSheet(
		".CSceneButton\n"
		"{\n"
		"background-color: rgb(56, 56, 56);\n"
		"text-color: rgb(255, 255, 255);\n"
		"border: 0;\n"
		"color:  rgb(255, 255, 255);\n"
		"font-family: Courier, serif;\n"
		"}\n"
		"CSceneButton:hover {\n"
		"    background-color: rgb(66, 66, 66);\n"
		"}"
	);
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void CSceneButton::UpdateSlot(size_t newSlot)
{
	m_Slot = newSlot;
}

void CSceneButton::SetAsActive(bool state)
{
	if (!
		state)
	{
		this->setStyleSheet(
			".CSceneButton\n"
			"{\n"
			"background-color: rgb(56, 56, 56);\n"
			"text-color: rgb(255, 255, 255);\n"
			"border: 0;\n"
			"color:  rgb(255, 255, 255);\n"
			"font-family: Courier, serif;\n"
			"}\n"
			"CSceneButton:hover {\n"
			"    background-color: rgb(66, 66, 66);\n"
			"}"
		);
	}
	else
	{
		this->setStyleSheet(
			".CSceneButton\n"
			"{\n"
			"background-color: rgb(76, 76, 76);\n"
			"text-color: rgb(255, 255, 255);\n"
			"border: 0;\n"
			"color:  rgb(255, 255, 255);\n"
			"font-family: Courier, serif;\n"
			"}\n"
			"CSceneButton:hover {\n"
			"    background-color: rgb(66, 66, 66);\n"
			"}"
		);
	}


}

void CSceneButton::Remove()
{
	//m_pParent->RemoveShader(m_Slot);
}

void CSceneButton::Change()
{
	//m_pParent->ChangeActiveEditorShaderTo(m_Slot);
}
