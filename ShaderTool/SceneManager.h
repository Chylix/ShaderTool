#pragma once
#include <qstring.h>
#include <vector>
#include "ui_ShaderToolMain.h"
#include "ISerializer.h"

class CShaderManager;

class CSceneManager : public QObject, public ISerializer
{
	Q_OBJECT



public:
	CSceneManager();
	~CSceneManager();

private:
	//void ChangeActiveButton(int slot);
	//void Reset();

private:
	std::vector<CShaderManager*> m_SceneShader;
};
