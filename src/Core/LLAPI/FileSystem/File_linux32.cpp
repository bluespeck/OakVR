#include "File.h"

#include <cstdio>
#include <cassert>
#include <sys\types.h>
#include <sys\stat.h> 

namespace Oak3D
{
	namespace Core
	{
		// --------------------------------------------------------------------------------
		struct File::FileImpl
		{
			std::string filepath;
			bool bIsOpen;
			FILE *pFileHandle;			
			File::FileOpenMode eFileOpenMode;
		};

		// --------------------------------------------------------------------------------
		File::File(std::string filepath)
		{
			m_pImpl = new FileImpl;
			m_pImpl->filepath = filepath;
			m_pImpl->bIsOpen = false;
		}

		// --------------------------------------------------------------------------------
		File::~File()
		{
			if(IsOpen())
			{				
				Close();
			}
			delete m_pImpl;
		}

		// --------------------------------------------------------------------------------
		bool File::Exists(std::string filepath)
		{
			return GetFileAttributesA(filepath.c_str()) != INVALID_FILE_ATTRIBUTES;
		}

		unsigned long File::Size(std::string filepath)
		{
			struct __stat64 fileStat; 
			if(_stat64( filepath.c_str(), &fileStat ))
				return 0; 
			return (unsigned long)fileStat.st_size;
		}

		unsigned long File::Size()
		{
			return Size(m_pImpl->filepath);
		}

		// --------------------------------------------------------------------------------
		void File::Open(FileOpenMode eFileOpenMode)
		{

			char mode[4];
			switch(eFileOpenMode)
			{
			case eFOM_OpenRead:
				strcpy_s(mode, "r");
				break;
			case eFOM_OpenWrite:
				strcpy_s(mode, "w");
				break;
			case eFOM_OpenAppend:
				strcpy_s(mode, "a");
				break;
			default:
				strcpy_s(mode, "r");
			}

			m_pImpl->pFileHandle = fopen(m_pImpl->filepath.c_str(), mode);
			m_pImpl->bIsOpen = m_pImpl->pFileHandle != nullptr;
		}

		// --------------------------------------------------------------------------------
		void File::Close()
		{
			fclose(m_pImpl->pFileHandle);
			m_pImpl->pFileHandle = nullptr;
			m_pImpl->bIsOpen = false;
		}

		// --------------------------------------------------------------------------------
		bool File::IsOpen()
		{
			return m_pImpl->bIsOpen;
		}

		// --------------------------------------------------------------------------------
		uint32_t File::Read(uint8_t *buffer, uint32_t bufferSize, uint32_t bytesToRead, uint32_t offset)
		{
			assert((bufferSize > 0) && (offset + bytesToRead < bufferSize) && "Buffer overflow!");
			if(bytesToRead == 0)
			{
				uint32_t fileSize = Size();
				return fread(buffer + offset, 1, fileSize - offset, m_pImpl->pFileHandle);
			}
			return fread(buffer + offset, 1, bytesToRead, m_pImpl->pFileHandle);
		}

		// --------------------------------------------------------------------------------
		void File::Write(uint8_t *buffer, uint32_t bufferSize, uint32_t bytesToWrite, uint32_t offset)
		{
			assert((offset + bytesToWrite < bufferSize) && "Buffer overflow!");
			fwrite(buffer + offset, bytesToWrite, 1, m_pImpl->pFileHandle);
		}
	}
}

#endif