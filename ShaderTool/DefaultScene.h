#pragma once
#include <CEngine.h>

class CDefaultScene : public triebWerk::IScene
{

public:
	CDefaultScene();
	~CDefaultScene();

	void UpdateMaterial(triebWerk::CMaterial* a_pNewMaterial);
	void UpdateLoadedTextures(const char* a_pShaderTexture);
	void UpdateUsedTextures(int usedSlot);
	void ClearUsedTextures();

	void Start() final;
	void Update() final;
	void End() final;

private:
	triebWerk::CPostEffectDrawable* m_pPostEffect;
	triebWerk::CMaterial* m_pPostEffectMaterial;
	triebWerk::CMaterial* m_pMaterial;
	triebWerk::CEntity* m_pEntity;
	std::vector<std::string> m_LoadedTextures;
	std::vector<int> m_UsedTextures;

};
