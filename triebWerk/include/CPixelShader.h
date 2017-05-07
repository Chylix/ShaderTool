#pragma once
#include <IShader.h>

namespace triebWerk
{
	class CPixelShader : public IShader
	{
	public:
		ID3D11PixelShader* m_pD3DPixelShader;

	private:
		bool m_UseBackbufferTexture;

	public:
		CPixelShader();
		~CPixelShader();

	public:
		void* GetD3D11Shader() final;
		void UsesBackBufferTexture(bool usesTexture);
		bool NeedsBackBufferTexture() const; 

	};
}