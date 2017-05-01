#pragma once
#include <d3d11.h>
#include <Windows.h>
#include <d3dcompiler.h>
#include <CFileReader.h>
#include <CGraphics.h>
#include <CVertexShader.h>
#include <CPixelShader.h>
#include <CGeometryShader.h>
#include <CMaterial.h>
#include <string>
#include <CDebugLogfile.h>

namespace triebWerk
{
	class CShaderGenerator : CFileReader
	{
	private:
		const static UINT m_CompileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;

		const std::string m_VSEntryPoint = "VS_Main";
		const std::string m_PSEntryPoint = "PS_Main";
		const std::string m_HSEntryPoint = "HS_Main";
		const std::string m_GSEntryPoint = "GS_Main";
		const std::string m_DSEntryPoint = "DS_Main";
		const std::string m_CSEntryPoint = "CS_Main";

		unsigned int m_ShaderGenNum;

		bool m_CompileErrors;

	private:
		ID3DBlob* m_pDefaultVSByteCode;
		ID3DBlob* m_pDefaultPSByteCode;
		ID3DBlob* m_pDefaultGSByteCode;

		CGraphics* m_pGraphicHandle;

		bool m_ClearMessages;
		std::vector<std::string> m_LatestErrorMessages;
		//ID3DBlob* m_pDefaultHSByteCode;
		//ID3DBlob* m_pDefaultDSByteCode;
		//ID3DBlob* m_pDefaultCSByteCode;

	public:
		CShaderGenerator();
		~CShaderGenerator();

	public:
		bool Initialize(CGraphics* a_pGraphicHandle, const char* a_pDefaultShader);

		std::vector<std::string> GetLatestErrorMessages();

		bool GenerateShader(const char* a_pShaderPath, CMaterial* a_pMaterialOut);

	private:
		//TODO: Write this errors into the log
		void WriteCompileError(ID3DBlob* a_pMessage);
		const char* CompileVertexShader(const char* a_pShaderPath, ID3DBlob** m_pOutShaderBinary);
		const char* CompilePixelShader(const char* a_pShaderPath, ID3DBlob** m_pOutShaderBinary);
		const char* CompileGeometryShader(const char* a_pShaderPath, ID3DBlob** m_pOutShaderBinary);


		void SetInputLayout(ID3DBlob* a_pShaderByteCode, CGraphics* a_pGraphicHandle, IShader* a_pShader);
		void SetConstantBuffers(ID3DBlob* a_pShaderByteCode, CConstantBuffer* a_pConstantBuffer);
		void SetBoundResources(ID3DBlob* a_pShaderbyteCode, IShader* a_PShader);
		void CreateVertexShader(CGraphics* a_pGraphicHandle, ID3DBlob* a_pShaderByteCode, CVertexShader* a_pShaderOut);
		void CreatePixelShader(CGraphics* a_pGraphicHandle, ID3DBlob* a_pShaderByteCode, CPixelShader* a_pShaderOut);
		//void CreateGeometryShader(CGraphics* a_pGraphicHandle, CGeometryShader* a_pShaderOut);


		////TODO: Create all other shader
		//void CreateHullShader();

		//void CreateDomainShader();
		//void CreateComputeShader();

		void LogErrors(const char* a_pErrorMessage);

	private:
		DXGI_FORMAT DetermineInputFormat(const D3D11_SIGNATURE_PARAMETER_DESC& a_rSignature);
	};
}