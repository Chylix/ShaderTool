#include "SerializerChunk.h"

CSerializerChunk::CSerializerChunk(const char* data)
{
	m_Data = data;
	m_Iterator = 0;
}

CSerializerChunk::~CSerializerChunk()
{

}

std::string& CSerializerChunk::GetLine()
{
	temp.clear();

	size_t pos = m_Data.find("\r\n", m_Iterator);

	if (pos == 0)
	{(
		m_Data.erase(0, strlen("\r\n")));
		pos = m_Data.find("\r\n", m_Iterator);
	}

	temp = m_Data.substr(m_Iterator, pos - m_Iterator);

	m_Iterator += (pos - m_Iterator + strlen("\r\n"));

	return temp;
}

std::string& CSerializerChunk::GetChunk()
{
	return m_Data;
}

bool CSerializerChunk::IsChunkEnd()
{
	return 	m_Data.find("\r\n", m_Iterator) == std::string::npos;
}
