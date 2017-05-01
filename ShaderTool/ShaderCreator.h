#pragma once
#include <string>
#include <CEngine.h>

class CShaderCreator
{
public:
	CShaderCreator();
	~CShaderCreator();
public:
	triebWerk::CMaterial* CreateShader(std::string& a_String);
	std::vector<std::string> GetLatestErrors();
private:
	void GetUsedTexture(std::string& a_String);

};