#include "ShaderCreator.h"
#include <Shlobj.h>
#include <CFileWriter.h>
#include "DefaultScene.h"

CShaderCreator::CShaderCreator()
{

}

CShaderCreator::~CShaderCreator()
{

}

triebWerk::CMaterial* CShaderCreator::CreateShader(std::string & a_String)
{
	GetUsedTexture(a_String);
	std::string constBuffer =
		"cbuffer constBuffer\n"
		"{\n"
		"float4x4 world;\n"
		"float4x4 projection;\n"
		"float4x4 view;\n"
		"float IsInstanced;\n"
		"float GlobalTime;\n"
		"float2 GlobalResolution;\n"
		"};\n"
		"SamplerState GlobalSampler;\n"
		"\n";

	a_String.insert(0, constBuffer);

	CHAR my_documents[MAX_PATH];
	HRESULT result = SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents);
	std::string path = my_documents;
	path += "\\shader.hlsl";

	triebWerk::CFileWriter writer;

	if (writer.MakeFile(path.c_str()) == false)
		return nullptr;

	writer.WriteAll(a_String);
	writer.SaveFile();

	triebWerk::CMaterial* mat = new triebWerk::CMaterial();

	twResourceManager->GetShaderGenerator()->GenerateShader(path.c_str(), mat);

	return mat;
}

std::vector<std::string> CShaderCreator::GetLatestErrors()
{
	return twResourceManager->GetShaderGenerator()->GetLatestErrorMessages();
}

void CShaderCreator::GetUsedTexture(std::string & a_String)
{
	size_t iter = 0;
	size_t pos = 0;

	while (pos != std::string::npos)
	{
		pos = a_String.find(": SLOT", iter);
		if (pos == std::string::npos)
			break;

		pos += 6;

		int pos2 = a_String.find(";", iter);
		std::string a = a_String.substr(pos, pos2 - (pos));
		iter += pos2 + a.size();
		static_cast<CDefaultScene*>(twSceneManager->m_pActiveScene->m_pScene)->UpdateUsedTextures(stoi(a));
	}
}
