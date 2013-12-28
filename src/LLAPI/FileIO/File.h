#pragma once

#include "FileIO.h"


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

			File(PathType filepath);
			~File();
			
			static bool Exists(PathType filepath);
			static OffsetType Size(PathType filepath);

			OffsetType Size();
			
			void Open(FileOpenMode eFileOpenMode);
			void Close();

			OffsetType Read(uint8_t *buffer, OffsetType bufferSize, OffsetType bytesToRead, OffsetType offset = 0);
			OffsetType Write(uint8_t *buffer, OffsetType bufferSize, OffsetType bytesToWrite, OffsetType offset = 0);
			
			PathType GetFilePathWithoutFileName();
			PathType GetFilePath() { return m_filePath; } // also includes file name
			PathType GetFileName();
			bool IsOpen() { return m_bFileOpened; }
			FileOpenMode GetFileOpenMode() { return m_eFileOpenMode; }

		private:
			FileImpl *m_pImpl;
			bool m_bFileOpened;
			FileOpenMode m_eFileOpenMode;
			PathType m_filePath;
		};
	}
}
