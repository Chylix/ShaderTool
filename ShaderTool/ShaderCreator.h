#pragma once
#include <string>
#include <CEngine.h>

class CShaderCreator
{
public:
	const int m_ShaderLineCount = 11;

public:
	CShaderCreator();
	~CShaderCreator();
public:
	triebWerk::CMaterial* CreateShader(std::string& a_String, int slot);
private:
	void GetUsedTexture(std::string& a_String, int);

};