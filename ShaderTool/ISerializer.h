#pragma once
class CSerializerChunk;

class ISerializer
{
public:
	ISerializer() {};
	virtual ~ISerializer() {};

public:
	virtual const char* SaveData() = 0;
	virtual void LoadData(CSerializerChunk* pData) = 0;
};
