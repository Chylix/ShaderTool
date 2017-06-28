#pragma once
#include <qstring.h>
#include <vector>
#include "ui_ShaderToolMain.h"
#include "ISerializer.h"

class CShaderManager;
class CSceneButton;

struct CScene
{

};

class CSceneManager : public QObject, public ISerializer
{
	Q_OBJECT

public slots:
	void OnAddSceneClick();

public:
	CSceneManager();
	~CSceneManager();

public:
	void Initialize(Ui_ShaderToolMain* pShaderTool);

	void AddScene();
	void AddButton();

	//ISerializer
	const char* SaveData() final;
	void LoadData(const char* pData) final;
	std::string buffer;
	//~ISerializer

private:
	//void ChangeActiveButton(int slot);
	//void Reset();

private:
	std::vector<CScene> m_Scenes;
	std::vector<CSceneButton*> m_Buttons;
	QLayout* m_pSceneLayout;
	QPushButton* m_pAddButton;

};
