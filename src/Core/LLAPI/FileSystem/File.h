
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_CORE_FILE_H__
#define __OAK3D_INCLUDE_CORE_FILE_H__

#include <string>
#include <cstdint>


namespace Oak3D
{
	namespace Core
	{
		class File
		{
		public:
			struct FileImpl;
			enum FileOpenMode
			{
				eFOM_Unknown = 0,
				eFOM_OpenRead,
				eFOM_OpenWrite,
				eFOM_OpenReadAndWrite,
				eFOM_OpenAppend,
			};

			File(std::string filepath);
			~File();
			
			static bool Exists(std::string filepath);
			static unsigned long Size(std::string filepath);

			unsigned long Size();
			
			void Open(FileOpenMode eFileOpenMode);
			void Close();

			uint32_t Read(unsigned char *buffer, uint32_t bufferSize, uint32_t bytesToRead, uint32_t offset = 0);
			void Write(uint8_t *buffer, uint32_t bufferSize, uint32_t bytesToWrite, uint32_t offset = 0);
			
			std::string GetFilePathWithoutFileName();
			std::string GetFilePath() { return m_filePath; } // includes file name
			std::string GetFileName();
			bool IsOpen() { return m_bFileOpened; }
			FileOpenMode GetFileOpenMode() { return m_eFileOpenMode }

		private:
			FileImpl *m_pImpl;
			bool m_bFileOpened;
			FileOpenMode m_eFileOpenMode;
			std::string m_filePath;
		};
	}
}

#endif
