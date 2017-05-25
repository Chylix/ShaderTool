#pragma once

class ISerializer
{
public:
	ISerializer() {};
	virtual ~ISerializer() {};

public:
	virtual const char* SaveData() = 0;
	virtual void LoadData(const char* pData) = 0;
};
