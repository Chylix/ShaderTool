#pragma once
#include <CFileReader.h>

class CProjectFileReader : triebWerk::CFileReader
{
public:
	CProjectFileReader();
	virtual ~CProjectFileReader();

public:
	void LoadData(const char* pPath);
	std::string GetSerializerChunk(const char* pSerializerGuid);

private:
	std::string m_Buffer;
	size_t m_Iterator;
};
