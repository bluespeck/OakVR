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
			
				static auto Exists(const oakvr::core::io::path::PathType &filepath) -> bool;
				static auto Size(const oakvr::core::io::path::PathType &filepath) -> OffsetType;

				auto Size() -> OffsetType;
			
				auto Open(FileOpenMode eFileOpenMode) -> void;
				auto Close() -> void;

				auto Read(uint8_t *buffer, OffsetType bufferSize, OffsetType bytesToRead, OffsetType offset = 0) -> OffsetType;
				auto Write(uint8_t *buffer, OffsetType bufferSize, OffsetType bytesToWrite, OffsetType offset = 0) -> OffsetType;
			
				auto GetFilePathWithoutFileName() -> oakvr::core::io::path::PathType;
				auto GetFilePath() -> oakvr::core::io::path::PathType { 
																		return m_filePath; } // also includes file name
				auto GetFileName() -> oakvr::core::io::path::PathType; 
					
				auto IsOpen() -> bool { 
										return m_bFileOpened; }
				auto GetFileOpenMode() -> FileOpenMode { 
														 return m_eFileOpenMode; }

			private:
				up<FileImpl> m_pImpl;
				bool m_bFileOpened;
				FileOpenMode m_eFileOpenMode;
				oakvr::core::io::path::PathType m_filePath;
			};
		}	// namespace io
	}	// namespace core
}	// namespace oakvr
