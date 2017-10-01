#pragma once
#include <string>

class CSerializerChunk
{
public:
	CSerializerChunk(const char* data);
	~CSerializerChunk();

	std::string& GetLine();
	std::string& GetChunk();
	bool IsChunkEnd();

private:
	std::string m_Data;
	std::string temp;
	size_t m_Iterator = 0;
};
