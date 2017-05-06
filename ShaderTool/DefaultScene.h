#pragma once
#include <CEngine.h>

class CDefaultScene : public triebWerk::IScene
{

public:
	CDefaultScene();
	~CDefaultScene();

	void UpdateMaterial(std::vector<triebWerk::CMaterial*>* pMaterials);
	void UpdateLoadedTextures(const char* a_pShaderTexture);
	void UpdateUsedTextures(std::vector<int> usedSlot);
	void ClearUsedTextures();

	void Start() final;
	void Update() final;
	void End() final;

private:
	triebWerk::CPostEffectDrawable* m_pPostEffect;
	triebWerk::CMaterial* m_pPostEffectMaterial;
	triebWerk::CMaterial* m_pPostEffectMaterial2;
	triebWerk::CMaterial* m_pMaterial;
	triebWerk::CEntity* m_pEntity;
	std::vector<std::string> m_LoadedTextures;
	std::vector<std::vector<int>> m_UsedTextures;
	size_t m_CurrentShaderCount;

};
