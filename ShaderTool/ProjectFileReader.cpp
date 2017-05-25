#include "ProjectFileReader.h"

CProjectFileReader::CProjectFileReader()
	: m_Iterator(0)
{
}

CProjectFileReader::~CProjectFileReader()
{
}

void CProjectFileReader::LoadData(const char * pPath)
{
	bool error = ReadData(pPath);

	m_Buffer = GetAllData();
}

std::string CProjectFileReader::GetSerializerChunk(const char * pSerializerGuid)
{
	size_t start = m_Buffer.find(pSerializerGuid, m_Iterator) + strlen(pSerializerGuid);
	size_t end = m_Buffer.find("~" + std::string(pSerializerGuid), start);

	std::string a = m_Buffer.substr(start, end - start);

	return a;
}
