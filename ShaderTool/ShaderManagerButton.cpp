#include "ShaderManagerButton.h"
#include "ShaderManager.h"

void CShaderManangerButton::mousePressEvent(QMouseEvent *e)
{
	if (e->button() == Qt::RightButton)
		Remove();
	else if (e->button() == Qt::LeftButton)
		Change();
}

void CShaderManangerButton::Init(const size_t shaderSlot, CShaderManager* pParent)
{
	m_Slot = shaderSlot;
	m_pParent = pParent;

	this->setStyleSheet(
		".CShaderManangerButton\n"
		"{\n"
		"background-color: rgb(56, 56, 56);\n"
		"text-color: rgb(255, 255, 255);\n"
		"border: 0;\n"
		"color:  rgb(255, 255, 255);\n"
		"font-family: Consolas, serif;\n"
		"}\n"
		"CShaderManangerButton:hover {\n"
		"    background-color: rgb(66, 66, 66);\n"
		"}"
	);
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void CShaderManangerButton::UpdateSlot(size_t newSlot)
{
	m_Slot = newSlot;
}

void CShaderManangerButton::SetAsActive(bool state)
{
	if (!
		state)
	{
		this->setStyleSheet(
			".CShaderManangerButton\n"
			"{\n"
			"background-color: rgb(56, 56, 56);\n"
			"text-color: rgb(255, 255, 255);\n"
			"border: 0;\n"
			"color:  rgb(255, 255, 255);\n"
			"font-family: Consolas, serif;\n"
			"}\n"
			"CShaderManangerButton:hover {\n"
			"    background-color: rgb(66, 66, 66);\n"
			"}"
		);
	}
	else
	{
		this->setStyleSheet(
			".CShaderManangerButton\n"
			"{\n"
			"background-color: rgb(76, 76, 76);\n"
			"text-color: rgb(255, 255, 255);\n"
			"border: 0;\n"
			"color:  rgb(255, 255, 255);\n"
			"font-family: Consolas, serif;\n"
			"}\n"
			"CShaderManangerButton:hover {\n"
			"    background-color: rgb(66, 66, 66);\n"
			"}"
		);
	}


}

void CShaderManangerButton::Remove()
{
	m_pParent->RemoveShader(m_Slot);
}

void CShaderManangerButton::Change()
{
	m_pParent->ChangeActiveEditorShaderTo(m_Slot);
}
