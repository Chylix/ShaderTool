#pragma once
#include <vector>
#include "ShaderManager.h"

class CScene
{
public:
	CScene(std::string& name, size_t order, std::vector<CTexturePainter::SShaderTexture>& textures, CShaderManager* pShaderManager)
		: m_SceneName(name)
		, m_SceneOrder(order)
		, m_TextureNames(textures)
		, m_pShaderManager(pShaderManager)
		, m_DurationTime(10.0f)
	{
	}

	std::string m_SceneName;
	std::vector<CTexturePainter::SShaderTexture> m_TextureNames;
	CShaderManager* m_pShaderManager;
	float m_DurationTime;
	size_t m_SceneOrder;

	void Release()
	{
		if (m_pShaderManager)
		{
			m_pShaderManager->Release();
			delete m_pShaderManager;
		}
	}
};
