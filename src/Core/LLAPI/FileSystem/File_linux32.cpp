#include <cstdio>
#include <sys\types.h>
#include <sys\stat.h> 

#include "File.h"

namespace Oak3D
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
			: m_bFileOpened(false) , m_eFileOpenMode(eFOM_Unknown), m_filePath(filepath)
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
				fprintf(stderr, "stat(%s, %p) error code(errno) %d",filepath.c_str(), &st, errno);
				return false;
			}
			return S_ISREG(st.st_mode) && st.st_size != 0;
		}

		// --------------------------------------------------------------------------------
		unsigned long File::Size(std::string filepath)
		{
			struct stat st; 
			if(stat(filepath.c_str(), &st ))
			{
				fprintf(stderr, "[OAK3D_ERROR] stat(%s, %p) error code(errno) %d.\n",filepath.c_str(), &st, errno);
				return false;
			}
			if(!S_IREG(st.st_mode))
			{
				printf("[OAK3D_WARNING] Oak3D::Core::File::Size called for non file object \"%s\".\n", filepath.c_str());
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
			case eFOM_OpenRead:
				strcpy(mode, "r");
				break;
			case eFOM_OpenWrite:
				strcpy(mode, "w");
				break;
			case eFOM_OpenAppend:
				strcpy(mode, "a");
				break;
			case eFOM_OpenReadAndWrite:
				strcpy(mode, "a");
				break;
			default:
				strcpy(mode, "r");
			}

			m_pImpl->pFileHandle = fopen(m_pImpl->filepath.c_str(), mode);
			m_bFileOpened = m_pImpl->pFileHandle != nullptr;
		}

		// --------------------------------------------------------------------------------
		void File::Close()
		{
			fclose(m_pImpl->pFileHandle);
			m_eFileOpenMode = eFOM_Unknown;
			m_pImpl->pFileHandle = nullptr;
			m_bFileOpened = false;
		}

		// --------------------------------------------------------------------------------
		uint32_t File::Read(uint8_t *buffer, uint32_t bufferSize, uint32_t bytesToRead, uint32_t offset)
		{
			if(offset + bytesToRead > bufferSize) 
			{
				fprintf(stderr, "[OAK3D_ERROR] Oak3D::Core::File::Read  Attempt to write past buffer limit!\n");
				return 0;
			}
			
			uint32_t fileSize = Size();
			
			if(bytesToRead == 0)
				return fread(buffer + offset, 1, fileSize - offset, m_pImpl->pFileHandle);
				
			if(bytesToRead > fileSize)
			{
				fprintf(stderr, "[OAK3D_ERROR] Oak3D::Core::File::Read  Attempt to read more than file size!\n");
				return 0;
			}
			
			return fread(buffer + offset, 1, bytesToRead, m_pImpl->pFileHandle);
		}

		// --------------------------------------------------------------------------------
		void File::Write(uint8_t *buffer, uint32_t bufferSize, uint32_t bytesToWrite, uint32_t offset)
		{
			if(offset + bytesToWrite > bufferSize)
			{
				fprintf(stderr, "[OAK3D_ERROR] Oak3D::Core::File::Write  Attempt to read past buffer limit!\n");
				return 0;
			}
			
			fwrite(buffer + offset, bytesToWrite, 1, m_pImpl->pFileHandle);
		}
	}
}