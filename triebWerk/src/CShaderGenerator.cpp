#include <CShaderGenerator.h>

triebWerk::CShaderGenerator::CShaderGenerator()
	: m_CompileErrors(false)
	, m_pDefaultVSByteCode(nullptr)
	, m_pDefaultPSByteCode(nullptr)
	, m_pDefaultGSByteCode(nullptr)
	, m_ClearMessages(false)
	, m_ShaderGenNum(0)
{
}

triebWerk::CShaderGenerator::~CShaderGenerator()
{
}

bool triebWerk::CShaderGenerator::Initialize(CGraphics * a_pGraphicHandle, const char * a_pDefaultShader)
{
	m_pGraphicHandle = a_pGraphicHandle;


	CompileVertexShader(a_pDefaultShader, &m_pDefaultVSByteCode);
	
	CompilePixelShader(a_pDefaultShader, &m_pDefaultPSByteCode);


	return true;
}

std::vector<std::string> triebWerk::CShaderGenerator::GetLatestErrorMessages()
{
	m_ClearMessages = true;

	return m_LatestErrorMessages;
}

bool triebWerk::CShaderGenerator::GenerateShader(const char * a_pShaderPath, CMaterial * a_pMaterialOut)
{
	ID3DBlob* vertexShader = nullptr;
	ID3DBlob* pixelShader = nullptr;
	ID3DBlob* geomShader = nullptr;

	//Compile all possible shader
	const char* vertexError = CompileVertexShader(a_pShaderPath, &vertexShader);
	if (vertexError != nullptr)
	{
		vertexShader = m_pDefaultVSByteCode;
		LogErrors(vertexError);
	}

	const char* pixelError = CompilePixelShader(a_pShaderPath, &pixelShader);
	if (pixelError != nullptr)
	{
		pixelShader = m_pDefaultPSByteCode;
		LogErrors(pixelError);
	}

	//Set material name
	std::string name = a_pShaderPath;
	name = name.substr(name.rfind("\\") + 1, name.size() - name.rfind("\\"));
	name = name.substr(0, name.find("."));
	name += std::to_string(m_ShaderGenNum);
	a_pMaterialOut->m_ID.SetName(name);

	m_ShaderGenNum++;

	//Generate Material

	SetConstantBuffers(vertexShader, &a_pMaterialOut->m_ConstantBuffer);

	a_pMaterialOut->m_ConstantBuffer.InitializeConstantBufffer(m_pGraphicHandle->GetDevice());

	CreateVertexShader(m_pGraphicHandle, vertexShader, &a_pMaterialOut->m_pVertexShader);

	CreatePixelShader(m_pGraphicHandle, pixelShader, &a_pMaterialOut->m_pPixelShader);

	//if (m_pGSByteCode != nullptr)
	//	CreateGeometryShader(m_pGraphicHandle, &a_pMaterialOut->m_pGeometryShader);

	return true;
}

void triebWerk::CShaderGenerator::WriteCompileError(ID3DBlob * a_pMessage)
{
	if (a_pMessage != nullptr)
	{
		LPVOID pCompileErrors = a_pMessage->GetBufferPointer();
		const char* pMessage = (const char*)pCompileErrors;
		std::cout << pMessage << std::endl;
	}
}

const char * triebWerk::CShaderGenerator::CompileVertexShader(const char * a_pShaderPath, ID3DBlob** m_pOutShaderBinary)
{
	ID3DBlob* pErrorMessage;
	HRESULT hResult;

	//Cast shader path to widechar 
	WCHAR shaderPath[MAX_PATH] = { 0 };
	MultiByteToWideChar(0, 0, a_pShaderPath, static_cast<int>(strlen(a_pShaderPath)), shaderPath, MAX_PATH);

	//Vertex Shader----------------------------
	hResult = D3DCompileFromFile(shaderPath, 0, 0, m_VSEntryPoint.c_str(), "vs_5_0", m_CompileFlags, 0, m_pOutShaderBinary, &pErrorMessage);
	if (FAILED(hResult))
	{
		return (char*)pErrorMessage->GetBufferPointer();
	}
	else
	{
		return nullptr;
	}
}

const char * triebWerk::CShaderGenerator::CompilePixelShader(const char * a_pShaderPath, ID3DBlob** m_pOutShaderBinary)
{
	ID3DBlob* pErrorMessage;
	HRESULT hResult;

	//Cast shader path to widechar 
	WCHAR shaderPath[MAX_PATH] = { 0 };
	MultiByteToWideChar(0, 0, a_pShaderPath, static_cast<int>(strlen(a_pShaderPath)), shaderPath, MAX_PATH);

	//Vertex Shader----------------------------
	hResult = D3DCompileFromFile(shaderPath, 0, 0, m_PSEntryPoint.c_str(), "ps_5_0", m_CompileFlags, 0, m_pOutShaderBinary, &pErrorMessage);
	if (FAILED(hResult))
	{
		return (char*)pErrorMessage->GetBufferPointer();
	}
	else
	{
		return nullptr;
	}
}

const char * triebWerk::CShaderGenerator::CompileGeometryShader(const char * a_pShaderPath, ID3DBlob** m_pOutShaderBinary)
{
	ID3DBlob* pErrorMessage;
	HRESULT hResult;

	//Cast shader path to widechar 
	WCHAR shaderPath[MAX_PATH] = { 0 };
	MultiByteToWideChar(0, 0, a_pShaderPath, static_cast<int>(strlen(a_pShaderPath)), shaderPath, MAX_PATH);

	//Vertex Shader----------------------------
	hResult = D3DCompileFromFile(shaderPath, 0, 0, m_GSEntryPoint.c_str(), "gs_5_0", m_CompileFlags, 0, m_pOutShaderBinary, &pErrorMessage);
	if (FAILED(hResult))
	{
		return (char*)pErrorMessage->GetBufferPointer();
	}
	else
	{
		return nullptr;
	}
}

void triebWerk::CShaderGenerator::SetInputLayout(ID3DBlob * a_pShaderByteCode, CGraphics * a_pGraphicHandle, IShader * a_pShader)
{
	HRESULT hResult;

	ID3D11ShaderReflection* pReflector = nullptr;
	hResult = D3DReflect(a_pShaderByteCode->GetBufferPointer(), a_pShaderByteCode->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&pReflector);

	D3D11_SHADER_DESC shaderDescription;

	pReflector->GetDesc(&shaderDescription);

	D3D11_INPUT_ELEMENT_DESC* inputLayoutDesc = new D3D11_INPUT_ELEMENT_DESC[shaderDescription.InputParameters];

	for (UINT i = 0; i < shaderDescription.InputParameters; i++)
	{
		D3D11_INPUT_ELEMENT_DESC element;

		D3D11_SIGNATURE_PARAMETER_DESC inputDesc;
		pReflector->GetInputParameterDesc(i, &inputDesc);

		std::string semanticName = inputDesc.SemanticName;
		size_t sematicInstancePosition = semanticName.find("INST"); //The "INST" declares this parameter as D3D11_INPUT_PER_INSTANCE_DATA

		if (sematicInstancePosition != std::string::npos)
		{
			element.InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
			element.InputSlot = 1;
			element.InstanceDataStepRate = 1;
		}
		else
		{
			element.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			element.InputSlot = 0;
			element.InstanceDataStepRate = 0;
		}

		element.SemanticName = inputDesc.SemanticName;
		element.SemanticIndex = inputDesc.SemanticIndex;
		element.Format = DetermineInputFormat(inputDesc);
		element.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT; //convenience to define the current element directly after the previous one, including any packing if necessary.

		if (sematicInstancePosition != std::string::npos)
		{
			a_pShader->m_InputInstanceDescriptions.push_back(element);
		}

		inputLayoutDesc[i] = element;
	}

	ID3D11InputLayout * layout = nullptr;

	hResult = a_pGraphicHandle->GetDevice()->CreateInputLayout(inputLayoutDesc, shaderDescription.InputParameters, a_pShaderByteCode->GetBufferPointer(), a_pShaderByteCode->GetBufferSize(), &layout);

	delete inputLayoutDesc;
	pReflector->Release();

	a_pShader->SetInputLayout(layout);
}

void triebWerk::CShaderGenerator::SetConstantBuffers(ID3DBlob * a_pShaderByteCode, CConstantBuffer * a_pConstantBuffer)
{
	HRESULT hResult;

	ID3D11ShaderReflection* pReflector = nullptr;
	hResult = D3DReflect(a_pShaderByteCode->GetBufferPointer(), a_pShaderByteCode->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&pReflector);

	D3D11_SHADER_DESC shaderDescription;

	pReflector->GetDesc(&shaderDescription);

	for (UINT i = 0; i < shaderDescription.ConstantBuffers; i++)
	{
		ID3D11ShaderReflectionConstantBuffer* pConstantBuffer = pReflector->GetConstantBufferByIndex(i);
		pConstantBuffer->GetDesc(&a_pConstantBuffer->m_BuffferDescription);

		for (UINT j = 0; j < a_pConstantBuffer->m_BuffferDescription.Variables; j++)
		{
			ID3D11ShaderReflectionVariable* pVariable = pConstantBuffer->GetVariableByIndex(j);
			D3D11_SHADER_VARIABLE_DESC variableDesc;
			pVariable->GetDesc(&variableDesc);

			a_pConstantBuffer->m_Variables.push_back(variableDesc);

			ID3D11ShaderReflectionType* pType = pVariable->GetType();
			D3D11_SHADER_TYPE_DESC typeDesc;
			pType->GetDesc(&typeDesc);

			a_pConstantBuffer->m_Types.push_back(typeDesc);
		}
	}

	//TODO: Think about GeomShader !!
	//if (shaderDescription.ConstantBuffers == 0 && m_pGSByteCode != nullptr)
	//{
	//	SetConstantBuffers(m_pGSByteCode, a_pConstantBuffer);
	//}
}

void triebWerk::CShaderGenerator::SetBoundResources(ID3DBlob * a_pShaderByteCode, IShader * a_PShader)
{
	HRESULT hResult;

	ID3D11ShaderReflection* pReflector = nullptr;
	hResult = D3DReflect(a_pShaderByteCode->GetBufferPointer(), a_pShaderByteCode->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&pReflector);

	D3D11_SHADER_DESC shaderDescription;

	pReflector->GetDesc(&shaderDescription);

	for (size_t i = 0; i < shaderDescription.BoundResources; ++i)
	{
		D3D11_SHADER_INPUT_BIND_DESC resourceDesc;
		pReflector->GetResourceBindingDesc(static_cast<UINT>(i), &resourceDesc);

		if (resourceDesc.Type == D3D_SIT_TEXTURE)
		{
			a_PShader->m_TextureDescriptions.push_back(resourceDesc);
		}

		if (resourceDesc.Type == D3D_SIT_SAMPLER)
		{
			a_PShader->m_SamplerDescriptions.push_back(resourceDesc);
		}
	}
}

void triebWerk::CShaderGenerator::CreateVertexShader(CGraphics * a_pGraphicHandle, ID3DBlob* a_pShaderByteCode, CVertexShader * a_pShaderOut)
{
	HRESULT hResult;

	SetInputLayout(a_pShaderByteCode, a_pGraphicHandle, a_pShaderOut);

	SetBoundResources(a_pShaderByteCode, a_pShaderOut);

	a_pShaderOut->InitializeTextureBuffer();

	hResult = a_pGraphicHandle->GetDevice()->CreateVertexShader(a_pShaderByteCode->GetBufferPointer(), a_pShaderByteCode->GetBufferSize(), NULL, &a_pShaderOut->m_pD3DVertexShader);

	if (FAILED(hResult))
	{
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Warning, false, "Warning: Vertex Shader could not be created!");
	}

	a_pShaderOut->CreateInstanceData();
}

void triebWerk::CShaderGenerator::CreatePixelShader(CGraphics * a_pGraphicHandle, ID3DBlob* a_pShaderByteCode, CPixelShader * a_pShaderOut)
{
	HRESULT hResult;

	SetBoundResources(a_pShaderByteCode, a_pShaderOut);

	a_pShaderOut->InitializeTextureBuffer();

	hResult = a_pGraphicHandle->GetDevice()->CreatePixelShader(a_pShaderByteCode->GetBufferPointer(), a_pShaderByteCode->GetBufferSize(), NULL, &a_pShaderOut->m_pD3DPixelShader);

	if (FAILED(hResult))
	{
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Warning, false, "Warning: Pixel Shader could not be created!");
	}
}

//void triebWerk::CShaderGenerator::CreateGeometryShader(CGraphics * a_pGraphicHandle, CGeometryShader * a_pShaderOut)
//{
//	HRESULT hResult;
//
//	SetBoundResources(m_pGSByteCode, a_pShaderOut);
//
//	a_pShaderOut->InitializeTextureBuffer();
//
//	hResult = a_pGraphicHandle->GetDevice()->CreateGeometryShader(m_pGSByteCode->GetBufferPointer(), m_pGSByteCode->GetBufferSize(), NULL, &a_pShaderOut->m_pD3DGeometryShader);
//
//	if (FAILED(hResult))
//	{
//		DebugLogfile.LogfText(CDebugLogfile::ELogType::Warning, false, "Warning: Geometry Shader could not be created!");
//	}
//}

void triebWerk::CShaderGenerator::LogErrors(const char * a_pErrorMessage)
{
	if (m_ClearMessages)
	{
		m_LatestErrorMessages.clear();
		m_ClearMessages = false;
	}

	std::string error = a_pErrorMessage;

	std::string line = error;

	//C:\Users\Chalix\Documents\shader.hlsl(11,1): error X3000: syntax error: unexpected token '}'
	size_t line1 = error.find("(")+1;
	size_t line2 = error.find(")");

	if (line1 != std::string::npos)
	{
		line = "Line " + error.substr(line1, line2 - line1);
		line += ": ";

		size_t a = error.find(": ", 0) + 2;
		std::string b = error.substr(a, error.length() - a);
		line += b;
	}

	m_LatestErrorMessages.push_back(line);
}

DXGI_FORMAT triebWerk::CShaderGenerator::DetermineInputFormat(const D3D11_SIGNATURE_PARAMETER_DESC & a_rSignature)
{
	if (a_rSignature.Mask == 15)
	{
		if (a_rSignature.ComponentType == D3D10_REGISTER_COMPONENT_UINT32)
			return DXGI_FORMAT_R32G32B32A32_UINT;
		else if (a_rSignature.ComponentType == D3D10_REGISTER_COMPONENT_SINT32)
			return DXGI_FORMAT_R32G32B32A32_SINT;
		else if (a_rSignature.ComponentType == D3D10_REGISTER_COMPONENT_FLOAT32)
			return DXGI_FORMAT_R32G32B32A32_FLOAT;
	}
	else if (a_rSignature.Mask == 0x7)
	{
		if (a_rSignature.ComponentType == D3D10_REGISTER_COMPONENT_UINT32)
			return DXGI_FORMAT_R32G32B32_UINT;
		else if (a_rSignature.ComponentType == D3D10_REGISTER_COMPONENT_SINT32)
			return DXGI_FORMAT_R32G32B32_SINT;
		else if (a_rSignature.ComponentType == D3D10_REGISTER_COMPONENT_FLOAT32)
			return DXGI_FORMAT_R32G32B32_FLOAT;
	}
	else if (a_rSignature.Mask == 0x3)
	{
		if (a_rSignature.ComponentType == D3D10_REGISTER_COMPONENT_UINT32)
			return DXGI_FORMAT_R32G32_UINT;
		else if (a_rSignature.ComponentType == D3D10_REGISTER_COMPONENT_SINT32)
			return DXGI_FORMAT_R32G32_SINT;
		else if (a_rSignature.ComponentType == D3D10_REGISTER_COMPONENT_FLOAT32)
			return DXGI_FORMAT_R32G32_FLOAT;
	}
	else if (a_rSignature.Mask == 0x1)
	{
		if (a_rSignature.ComponentType == D3D10_REGISTER_COMPONENT_UINT32)
			return DXGI_FORMAT_R32_UINT;
		else if (a_rSignature.ComponentType == D3D10_REGISTER_COMPONENT_SINT32)
			return DXGI_FORMAT_R32_SINT;
		else if (a_rSignature.ComponentType == D3D10_REGISTER_COMPONENT_FLOAT32)
			return DXGI_FORMAT_R32_FLOAT;
	}

	return DXGI_FORMAT_UNKNOWN;
}