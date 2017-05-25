#pragma once
#include "ui_ShaderToolMain.h"
#include <vector>
#include "ISerializer.h"

class CProjectManager : public QObject
{
private:
	struct SSerializer
	{
		std::string string;
		ISerializer* serializer;
	};

	Q_OBJECT

public slots:
	void OnOpenProject();
	void OnSaveProject();

public:
	void Initialize(QPushButton* pOpen, QPushButton* pSave);
	void RegisterSerializer(ISerializer* pSerializer, const char* guid);

public:
	CProjectManager();
	~CProjectManager();

private:
	void FetchProjectInformation();

private:
	const QString m_FileType = "Project File (*.spf)";

	QPushButton* m_pOpenButton;
	QPushButton* m_pSaveButton;
	std::vector<SSerializer> m_Serializer;
};