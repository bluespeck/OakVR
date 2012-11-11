#include "Directory.h"

#if OAK3D_OS == OAK3D_OS_WINDOWS
#include <cstdio>
#include <cassert>
#include <windows.h>

namespace ro3d
{
	namespace Core
	{
		// --------------------------------------------------------------------------------
		struct Directory::DirectoryImpl
		{
			std::string path;
		};

		// --------------------------------------------------------------------------------
		Directory::Directory(std::string path)
		{
			m_pImpl = new DirectoryImpl;
			m_pImpl->path = path;
		}

		// --------------------------------------------------------------------------------
		Directory::~Directory()
		{
			delete m_pImpl;
		}

		// --------------------------------------------------------------------------------
		bool Directory::Exists(std::string path)
		{
			return GetFileAttributesA(path.c_str()) != INVALID_FILE_ATTRIBUTES;
		}

		// --------------------------------------------------------------------------------
		std::vector<Directory::DirEntry> Directory::GetEntryList()
		{
			std::string searchString = m_pImpl->path + "/*";
			std::vector<DirEntry> result;

			WIN32_FIND_DATAA findFileData;
			HANDLE hFind = FindFirstFileA(searchString.c_str(), &findFileData);
			if(hFind != INVALID_HANDLE_VALUE)			
			{
				do
				{
					DirEntry dirEntry;
					dirEntry.path = findFileData.cFileName;
					dirEntry.type = (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)? DirEntry::EntryType::directory : DirEntry::EntryType::file;
					result.push_back(dirEntry);
				}
				while( FindNextFileA(hFind, &findFileData) );
			}
			FindClose(hFind);
			
			return result;
		}

		// --------------------------------------------------------------------------------
		std::vector<std::string> Directory::GetFileList(bool bRecursive)
		{
			return GetFileList(m_pImpl->path + "/*", bRecursive);
		}

		// --------------------------------------------------------------------------------
		std::vector<std::string> Directory::GetFileList(std::string path, bool bRecursive)
		{
			WIN32_FIND_DATAA findFileData;
			std::vector<std::string> result;

			HANDLE hFind = FindFirstFileA(path.c_str(), &findFileData);
			if(hFind == INVALID_HANDLE_VALUE)
				return result;

			do
			{
				if(!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				{
					result.push_back(path + "/" + findFileData.cFileName);
				}
				else if(bRecursive)
				{
					std::vector<std::string> temp = GetFileList(path + "/" + findFileData.cFileName, bRecursive);
					result.insert(result.end(), temp.begin(), temp.end());
				}
			}
			while( FindNextFileA(hFind, &findFileData) );
			FindClose(hFind);

			return result;
		}
	}
}

#endif
