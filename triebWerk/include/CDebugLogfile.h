#pragma once

#include <Windows.h>
#include <stdio.h>
#include <string>

#define DebugLogfile CDebugLogfile::Instance()

#define MAX_BUFFER 1024
#define L_FAIL false
#define L_OK true

namespace triebWerk
{
	class CDebugLogfile
	{
	public:
		enum class ELogType
		{
			Warning,
			Error,
			Text
		};

	private:
		FILE* m_pFile;
		bool m_ErrorOccurred;
        bool m_Created;

	public:
		static CDebugLogfile& Instance();

	private:
		CDebugLogfile();
		~CDebugLogfile();

	public:
		void CreateLogfile(const char* a_LogfileName);
		void WriteTopic(const char*  a_Topic, unsigned int a_Size);
		void LogText(const char* a_Text);
		void LogText(ELogType a_LogType, bool a_List, const char* a_Text);
		void LogText(ELogType a_LogType, const char* a_Text);
		void LogfText(const char* a_Text, ...);
		void LogfText(ELogType a_LogType, const char* a_Text, ...);
		void LogfText(ELogType a_LogType, bool a_List, const char* a_Text, ...);
		void FunctionResult(const char* a_pFunctionName, bool a_Result);
	};
}
