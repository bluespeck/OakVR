#include "File.h"
#include "Log/Log.h"
#include <cstdio>
#include <cstring>




namespace oakvr
{
	namespace Core
	{
		// --------------------------------------------------------------------------------
		struct File::FileImpl
		{
			FILE *pFileHandle;
		};

		// --------------------------------------------------------------------------------
		File::File(std::string filepath)
			: m_bFileOpened(false) , m_eFileOpenMode(FileOpenMode::unknown), m_filePath(filepath)
		{
			m_pImpl = new FileImpl;
			m_bFileOpened = false;
		}

		// --------------------------------------------------------------------------------
		File::~File()
		{
			if(m_bFileOpened)
				Close();
			delete m_pImpl;
		}

		// --------------------------------------------------------------------------------
		bool File::Exists(std::string filepath)
		{
			struct stat st;
			if(stat(filepath.c_str(), &st ))
			{
				Log::PrintError("stat(%s, %p) error code(errno) %d",filepath.c_str(), &st, errno);
				return false;
			}
			return st.st_size != 0;
		}

		// --------------------------------------------------------------------------------
		unsigned long File::Size(std::string filepath)
		{
			struct stat st; 
			if(stat(filepath.c_str(), &st ))
			{
				Log::PrintError("stat(%s, %p) error code(errno) %d.\n",filepath.c_str(), &st, errno);
				return false;
			}

			return st.st_size;
		}

		// --------------------------------------------------------------------------------
		unsigned long File::Size()
		{
			return Size(m_filePath);
		}

		// --------------------------------------------------------------------------------
		void File::Open(FileOpenMode eFileOpenMode)
		{

			char mode[4];
			switch(eFileOpenMode)
			{
			case FileOpenMode::read:
				strcpy(mode, "r");
				break;
			case FileOpenMode::write:
				strcpy(mode, "w");
				break;
			case FileOpenMode::append:
				strcpy(mode, "a");
				break;
			case FileOpenMode::readAndWrite:
				strcpy(mode, "a");
				break;
			default:
				strcpy(mode, "r");
			}

			m_pImpl->pFileHandle = fopen(m_filePath.c_str(), mode);
			if(!m_pImpl->pFileHandle)
				Log::PrintError("File could not be opened (%s). Errno is %d.", m_filePath.c_str(), errno);
			m_bFileOpened = m_pImpl->pFileHandle != nullptr;
		}

		// --------------------------------------------------------------------------------
		void File::Close()
		{
			if(fclose(m_pImpl->pFileHandle))
				Log::PrintError("File could not be closed (%s). Errno is %d.", m_filePath.c_str(), errno );

			m_eFileOpenMode = FileOpenMode::unknown;
			m_pImpl->pFileHandle = nullptr;
			m_bFileOpened = false;
		}

		// --------------------------------------------------------------------------------
		uint32_t File::Read(uint8_t *buffer, uint32_t bufferSize, uint32_t bytesToRead, uint32_t offset)
		{
			if(offset + bytesToRead > bufferSize) 
			{
				Log::PrintError("Reading from %s; attempt to read past buffer limit!\n", m_filePath.c_str());
				return 0;
			}
			
			uint32_t fileSize = Size();
			
			if(bytesToRead == 0)
				return fread(buffer + offset, 1, fileSize - offset, m_pImpl->pFileHandle);
				
			if(bytesToRead > fileSize)
			{
				Log::PrintError("Reading from %s; attempt to read more than the file size!\n", m_filePath.c_str());
				return 0;
			}
			
			return fread(buffer + offset, 1, bytesToRead, m_pImpl->pFileHandle);
		}

		// --------------------------------------------------------------------------------
		uint32_t File::Write(uint8_t *buffer, uint32_t bufferSize, uint32_t bytesToWrite, uint32_t offset)
		{
			if(offset + bytesToWrite > bufferSize)
			{
				Log::PrintError("Writing to %s; attempt to write past buffer limit!\n", m_filePath.c_str());
				exit(1);
			}
			
			return fwrite(buffer + offset, bytesToWrite, 1, m_pImpl->pFileHandle);
		}
	}
}
