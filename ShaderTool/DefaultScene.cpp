#include "DefaultScene.h"

CDefaultScene::CDefaultScene()
{

}

CDefaultScene::~CDefaultScene()
{

}

void CDefaultScene::UpdateMaterial(triebWerk::CMaterial * a_pNewMaterial)
{
	//if(m_pEntity != nullptr)
	//twActiveWorld->RemoveEntity(m_pEntity);
	m_pPostEffect->RemoveMaterial(0);
	m_pPostEffect->AddMaterial(a_pNewMaterial);
	//m_pEntity = nullptr;
}

void CDefaultScene::UpdateLoadedTextures(const char * a_pShaderTexture)
{
	m_LoadedTextures.push_back(a_pShaderTexture);
}

void CDefaultScene::UpdateUsedTextures(int a_Slot)
{
	m_UsedTextures.push_back(a_Slot);
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
	
	m_pPostEffect->GetMaterial(0)->m_ConstantBuffer.SetValueInBuffer(4, &time);

	//for (size_t i = 0; i < m_LoadedTextures.size(); i++)
	//{
	//	m_pPostEffect->GetMaterial(0)->m_pPixelShader.SetTexture(i, twResourceManager->GetTexture2D(m_LoadedTextures[i].c_str()));
	//}

	for (size_t i = 0; i < m_UsedTextures.size(); i++)
	{
		m_pPostEffect->GetMaterial(0)->m_pPixelShader.SetTexture(i, twResourceManager->GetTexture2D(m_LoadedTextures[m_UsedTextures[i]].c_str()));
	}

	m_pPostEffectMaterial->m_ConstantBuffer.SetValueInBuffer(5, &res);
}

void CDefaultScene::End()
{
}


