#pragma once
#include <CTexture2D.h>
#include <CVertexShader.h>
#include <CPixelShader.h>
#include <CGeometryShader.h>
#include <CConstantBuffer.h>
#include <CID.h>
#include <CDebugLogfile.h>

namespace triebWerk
{
	class CMaterial
	{
	public:
		CVertexShader m_pVertexShader;
		CPixelShader m_pPixelShader;
		CGeometryShader m_pGeometryShader;
		CConstantBuffer m_ConstantBuffer;
		CID m_ID;

	public:
		CMaterial();
		~CMaterial();

	public:
		void SetMaterial(const CMaterial* a_pMaterial);
	};
}