#pragma once

#include <string>
#include <cstdint>


namespace oakvr
{
	namespace Core
	{
		class File
		{
		public:
			struct FileImpl;
			enum class FileOpenMode
			{
				unknown = 0,
				read,
				write,
				readAndWrite,
				append,
			};

			File(std::string filepath);
			~File();
			
			static bool Exists(std::string filepath);
			static unsigned long Size(std::string filepath);

			unsigned long Size();
			
			void Open(FileOpenMode eFileOpenMode);
			void Close();

			uint32_t Read(unsigned char *buffer, uint32_t bufferSize, uint32_t bytesToRead, uint32_t offset = 0);
			uint32_t Write(uint8_t *buffer, uint32_t bufferSize, uint32_t bytesToWrite, uint32_t offset = 0);
			
			std::string GetFilePathWithoutFileName();
			std::string GetFilePath() { return m_filePath; } // also includes file name
			std::string GetFileName();
			bool IsOpen() { return m_bFileOpened; }
			FileOpenMode GetFileOpenMode() { return m_eFileOpenMode; }

		private:
			FileImpl *m_pImpl;
			bool m_bFileOpened;
			FileOpenMode m_eFileOpenMode;
			std::string m_filePath;
		};
	}
}
