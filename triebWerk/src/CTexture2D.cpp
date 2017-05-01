#include <CTexture2D.h>

triebWerk::CTexture2D::CTexture2D() : m_pShaderResourceView(nullptr), m_pTexture(nullptr)
{
}

triebWerk::CTexture2D::~CTexture2D()
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
	}
	if (m_pShaderResourceView != nullptr)
	{
		m_pShaderResourceView->Release();
	}
}

void triebWerk::CTexture2D::SetTexture(unsigned int a_Width, unsigned int a_Height, ID3D11Texture2D * a_Texture, ID3D11ShaderResourceView * a_ShaderView)
{
	if (m_pShaderResourceView != nullptr)
	{
		m_pShaderResourceView->Release();
		m_pShaderResourceView = nullptr;
	}

	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
		
	m_Height = a_Height;
	m_Width = a_Width;
	m_pShaderResourceView = a_ShaderView;
	m_pTexture = a_Texture;
}

ID3D11ShaderResourceView * triebWerk::CTexture2D::GetShaderResourceView() const
{
	return m_pShaderResourceView;
}

ID3D11Texture2D * triebWerk::CTexture2D::GetD3D11Texture() const
{
	return m_pTexture;
}

unsigned int triebWerk::CTexture2D::GetHeight() const
{
	return m_Height;
}

unsigned int triebWerk::CTexture2D::GetWidth() const
{
	return m_Width;
}
