#pragma once

#include "FileIO.h"
#include "Path.h"
#include "Utils/Types.h"


namespace oakvr
{
	namespace core
	{
		namespace io
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

				File(const oakvr::core::io::path::PathType &filepath);
				File(const File&) = delete;
				File(File &&);
				~File();
			
				static bool Exists(const oakvr::core::io::path::PathType &filepath);
				static OffsetType Size(const oakvr::core::io::path::PathType &filepath);

				OffsetType Size();
			
				void Open(FileOpenMode eFileOpenMode);
				void Close();

				OffsetType Read(uint8_t *buffer, OffsetType bufferSize, OffsetType bytesToRead, OffsetType offset = 0);
				OffsetType Write(uint8_t *buffer, OffsetType bufferSize, OffsetType bytesToWrite, OffsetType offset = 0);
			
				oakvr::core::io::path::PathType GetFilePathWithoutFileName();
				oakvr::core::io::path::PathType GetFilePath() { return m_filePath; } // also includes file name
				oakvr::core::io::path::PathType GetFileName();
				bool IsOpen() { return m_bFileOpened; }
				FileOpenMode GetFileOpenMode() { return m_eFileOpenMode; }

			private:
				up<FileImpl> m_pImpl;
				bool m_bFileOpened;
				FileOpenMode m_eFileOpenMode;
				oakvr::core::io::path::PathType m_filePath;
			};
		}	// namespace io
	}	// namespace core
}	// namespace oakvr
