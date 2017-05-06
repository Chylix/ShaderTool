#include "DefaultScene.h"

CDefaultScene::CDefaultScene()
	: m_CurrentShaderCount(0)
{

}

CDefaultScene::~CDefaultScene()
{

}

void CDefaultScene::UpdateMaterial(std::vector<triebWerk::CMaterial*>* pMaterials)
{
	size_t r = pMaterials->size();

	do
	{
		m_pPostEffect->RemoveMaterial(r-1);
		r--;
	} while (r > 0);

	for (size_t i = 0; i < pMaterials->size(); i++)
	{
		m_pPostEffect->AddMaterial(pMaterials->at(i));
	}

	m_CurrentShaderCount = m_pPostEffect->GetMaterialCount();
}

void CDefaultScene::UpdateLoadedTextures(const char * a_pShaderTexture)
{
	m_LoadedTextures.push_back(a_pShaderTexture);
}

void CDefaultScene::UpdateUsedTextures(std::vector<int> usedSlot)
{
	m_UsedTextures.push_back(usedSlot);
}

void CDefaultScene::ClearUsedTextures()
{
	m_UsedTextures.clear();
}

triebWerk::CEntity* ent;

void CDefaultScene::Start()
{
	twResourceManager->LoadAllFilesInFolder("data");

	//Create something to draw on
	ent = twActiveWorld->CreateEntity();
	ent->m_Transform.SetPosition(0, 0, 0);
	ent->m_Transform.SetRotationDegrees(0.0f, 0, 0);
	ent->m_Transform.SetScale(10, 10, 1);

	auto fogMesh = twRenderer->CreateMeshDrawable();
	fogMesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_cube");
	fogMesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardColor"));
	float a[4];
	a[0] = 0.0f;
	a[1] = 0.0f;
	a[2] = 0.0f;
	a[3] = 1.0f;

	fogMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &a);
	ent->SetDrawable(fogMesh);

	twActiveWorld->AddEntity(ent);

	//Create PostEffect
	m_pEntity = twActiveWorld->CreateEntity();

	m_pPostEffect = twRenderer->CreatePostEffecthDrawable();

	m_pPostEffectMaterial = m_pPostEffect->AddMaterial(twResourceManager->GetMaterial("DefaultRenderTarget"));

	m_pEntity->SetDrawable(m_pPostEffect);

	twActiveWorld->AddEntity(m_pEntity);
}

void CDefaultScene::Update()
{
	float time = twTime->GetTimeSinceStartup();

	float res[2];
	
	res[0] = twEngine.GetViewportWidth();
	res[1] = twEngine.GetViewportHeight();
	
	for (size_t i = 0; i < m_CurrentShaderCount; i++)
	{
		m_pPostEffect->GetMaterial(i)->m_ConstantBuffer.SetValueInBuffer(4, &time);
		m_pPostEffect->GetMaterial(i)->m_ConstantBuffer.SetValueInBuffer(5, &res);
	}

	//for (size_t i = 0; i < m_LoadedTextures.size(); i++)
	//{
	//	m_pPostEffect->GetMaterial(0)->m_pPixelShader.SetTexture(i, twResourceManager->GetTexture2D(m_LoadedTextures[i].c_str()));
	//}

	for (size_t i = 0; i < m_UsedTextures.size(); i++)
	{
		for (size_t y = 0; y < m_UsedTextures[i].size(); y++)
		{
			auto e = m_UsedTextures[i];
			m_pPostEffect->GetMaterial(i)->m_pPixelShader.SetTexture(i, twResourceManager->GetTexture2D(m_LoadedTextures[e[y]].c_str()));
		}
		
	}
}

void CDefaultScene::End()
{
}


