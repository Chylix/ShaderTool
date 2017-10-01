#include "ProjectManager.h"
#include "ShaderToolMain.h"
#include <qfiledialog.h>
#include <CFileWriter.h>
#include <ProjectFileReader.h>
#include "SerializerChunk.h"
#include <Console.h>

void CProjectManager::RegisterSerializer(ISerializer * pSerializer, const char* guid)
{
	SSerializer temp;
	temp.serializer = pSerializer;
	temp.string = guid;

	m_Serializer.push_back(temp);
}

CProjectManager::CProjectManager()
{
}

CProjectManager::~CProjectManager()
{
}

void CProjectManager::FetchProjectInformation()
{
}

void CProjectManager::OnOpenProject()
{
	QString fileName = QFileDialog::getOpenFileName(nullptr, tr("Open File"),
		"",
		m_FileType);

	if (fileName.isEmpty())
		return;

	CProjectFileReader reader;
	reader.LoadData(fileName.toStdString().c_str());
	
	for (size_t i = 0; i < m_Serializer.size(); i++)
	{
		CSerializerChunk chunk(reader.GetSerializerChunk(m_Serializer[i].string.c_str()).c_str());
		m_Serializer[i].serializer->LoadData(&chunk);

		int a = 0;
	}

	CConsole::Instance().PrintText("Project successfully loaded", CConsole::EPrintType::Success);
}

void CProjectManager::OnSaveProject()
{
	QString fileName = QFileDialog::getSaveFileName(nullptr, tr("Save File"),
		"",
		m_FileType);

	if (fileName.isEmpty())
		return;

	std::string data;

	for (size_t i = 0; i < m_Serializer.size(); i++)
	{
		data.append(m_Serializer[i].string);
		data.append("\n");
		data.append(m_Serializer[i].serializer->SaveData());
		data.append("~"+ m_Serializer[i].string);
		data.append("\n");
	}

	triebWerk::CFileWriter writer;
	writer.MakeFile(fileName.toStdString().c_str());
	writer.WriteAll(data);
	writer.SaveFile();

	CConsole::Instance().PrintText("Project successfully saved", CConsole::EPrintType::Success);
}

void CProjectManager::Initialize(QPushButton* pOpen, QPushButton* pSave)
{
	m_pOpenButton = pOpen;
	m_pSaveButton = pSave;

	connect(pOpen, SIGNAL(clicked()), this, SLOT(OnOpenProject()));
	connect(pSave, SIGNAL(clicked()), this, SLOT(OnSaveProject()));
}

