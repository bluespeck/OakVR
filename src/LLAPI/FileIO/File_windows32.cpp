#include "File.h"
#include "Log/Log.h"
#include <cstdio>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>


#define strcpy strcpy_s

namespace oakvr
{
namespace core
{
namespace io
{	
	// --------------------------------------------------------------------------------
	struct File::FileImpl
	{
		FILE *pFileHandle;
	};

	// --------------------------------------------------------------------------------
	File::File(const oakvr::core::io::path::PathType &filepath)
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
	bool File::Exists(const oakvr::core::io::path::PathType &filepath)
	{
		struct stat st;
		if(stat(filepath.c_str(), &st ))
		{
			Log::PrintError("stat(%s, %p) error code(errno) %d", filepath.c_str(), &st, errno);
			return false;
		}
		return st.st_size != 0;
	}

	// --------------------------------------------------------------------------------
	OffsetType File::Size(const oakvr::core::io::path::PathType &filepath)
	{
		struct stat st; 
		if(stat(filepath.c_str(), &st ))
		{
			Log::PrintError("stat(%s, %p) error code(errno) %d.\n", filepath.c_str(), &st, errno);
			return false;
		}

		return st.st_size;
	}

	// --------------------------------------------------------------------------------
	OffsetType File::Size()
	{
		return Size(m_filePath);
	}

	// --------------------------------------------------------------------------------
	void File::Open(FileOpenMode eFileOpenMode)
	{
		m_eFileOpenMode = eFileOpenMode;
		char mode[4];
		switch(eFileOpenMode)
		{
		case FileOpenMode::read:
			strcpy(mode, "rb");
			break;
		case FileOpenMode::write:
			strcpy(mode, "wb");
			break;
		case FileOpenMode::append:
			strcpy(mode, "ab");
			break;
		case FileOpenMode::readAndWrite:
			strcpy(mode, "r+b");
			break;
		default:
			strcpy(mode, "rb");
			m_eFileOpenMode = FileOpenMode::read;
			break;
		}

		errno_t err = fopen_s(&m_pImpl->pFileHandle, m_filePath.c_str(), mode);
		if(!m_pImpl->pFileHandle)
			Log::PrintError("File could not be opened (%s). Errno is %d.", m_filePath.c_str(), err);
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
	OffsetType File::Read(uint8_t *buffer, OffsetType bufferSize, OffsetType bytesToRead, OffsetType offset)
	{
		if(offset + bytesToRead > bufferSize) 
		{
			Log::PrintError("Reading from %s; attempt to read past buffer limit!\n", m_filePath.c_str());
			return 0;
		}
			
		OffsetType fileSize = Size();
			
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
	OffsetType File::Write(uint8_t *buffer, OffsetType bufferSize, OffsetType bytesToWrite, OffsetType offset)
	{
		if(offset + bytesToWrite > bufferSize)
		{
			Log::PrintError("Writing to %s; attempt to write past buffer limit!\n", m_filePath.c_str());
			exit(1);
		}
			
		return fwrite(buffer + offset, bytesToWrite, 1, m_pImpl->pFileHandle);
	}

}	// namespace io
}	// namespace core
}	// namespace oakvr
