#include <CPixelShader.h>

triebWerk::CPixelShader::CPixelShader()
	: m_UseBackbufferTexture(false)
{
	m_ShaderType = IShader::EShaderType::Pixel;
}

triebWerk::CPixelShader::~CPixelShader()
{
}

void * triebWerk::CPixelShader::GetD3D11Shader()
{
	return m_pD3DPixelShader;
}

void triebWerk::CPixelShader::UsesBackBufferTexture(bool usesTexture)
{
	m_UseBackbufferTexture = usesTexture;
}

bool triebWerk::CPixelShader::NeedsBackBufferTexture() const
{
	return m_UseBackbufferTexture;
}
