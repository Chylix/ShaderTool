#include <CPixelShader.h>

triebWerk::CPixelShader::CPixelShader()
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
