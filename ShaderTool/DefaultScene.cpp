#include "DefaultScene.h"
#include "Console.h"

CDefaultScene::CDefaultScene()
	: m_CurrentShaderCount(0)
{

}

CDefaultScene::~CDefaultScene()
{

}

void CDefaultScene::SetTimeline(CTimeline * pTimeline)
{
	m_pTimeline = pTimeline;
}

void CDefaultScene::UpdateMaterial(std::vector<triebWerk::CMaterial*>* pMaterials)
{
	size_t r = pMaterials->size();

	m_pPostEffect->Clear();

	do
	{
		m_pPostEffect->RemoveMaterial(r - 1);
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

void CDefaultScene::ReplaceLoadedTextures(const size_t slot, const char* a_pShaderTexture)
{
	m_LoadedTextures[slot] = a_pShaderTexture;
}

void CDefaultScene::RemoveLoadedTextures(const size_t slot)
{
	m_LoadedTextures.erase(m_LoadedTextures.begin() + slot);
}

void CDefaultScene::UpdateUsedTextures(int slot, std::vector<int> usedSlot)
{
	for (size_t i = 0; i < usedSlot.size(); ++i)
	{
		if (usedSlot[i] > m_LoadedTextures.size())
		{
			std::string error = "Texture slot " + std::to_string(usedSlot[i]) + " doesn't exist!";
			CConsole::Instance().PrintText(error, CConsole::EPrintType::Warning);
			usedSlot.erase(usedSlot.begin() + i);
		}
	}

	SShaderTextureHolder t;
	t.ShaderSlot = slot;
	t.SlotUsed = usedSlot;

	m_UsedTextures.push_back(t);
}

void CDefaultScene::ClearLoadedTextures()
{
	m_LoadedTextures.clear();
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
	float time = m_pTimeline->UpdateTime(twTime->GetDeltaTime(), twTime->GetTimeSinceStartup());

	float res[2];
	
	res[0] = twEngine.m_pViewport->GetViewportWidth();
	res[1] = twEngine.m_pViewport->GetViewportHeight();
	
	for (size_t i = 0; i < m_CurrentShaderCount; i++)
	{
		m_pPostEffect->GetMaterial(i)->m_ConstantBuffer.SetValueInBuffer(4, &time);
		m_pPostEffect->GetMaterial(i)->m_ConstantBuffer.SetValueInBuffer(5, &res);
	}

	//for (size_t i = 0; i < m_UsedTextures.size(); i++)
	//{
	//	for (size_t y = 0; y < m_UsedTextures[i].size(); y++)
	//	{
	//		auto e = m_UsedTextures[i];
	//		int slot = e[y]-1;
	//		m_pPostEffect->GetMaterial(i)->m_pPixelShader.SetTexture(i, twResourceManager->GetTexture2D(m_LoadedTextures[slot].c_str()));
	//	}
	//	
	//}


	if (m_LoadedTextures.size() == 0)
		return;

	for (SShaderTextureHolder& holder : m_UsedTextures)
	{
		triebWerk::CMaterial* currentMat = m_pPostEffect->GetMaterial(holder.ShaderSlot);
		if (currentMat == nullptr)
			continue;


		for (size_t i = 0; i < holder.SlotUsed.size(); ++i)
		{
			int slot = holder.SlotUsed[i]-1;
			if (slot < m_LoadedTextures.size())
			{
				currentMat->m_pPixelShader.SetTexture(i, twResourceManager->GetTexture2D(m_LoadedTextures[slot].c_str()));
			}
		}

	}

}

void CDefaultScene::End()
{
}


