#include "Directory.h"

#include <cstdio>
#include <cassert>
#include <windows.h>

namespace oakvr
{
namespace core
{
namespace io
{
	// --------------------------------------------------------------------------------
	struct Directory::DirectoryImpl
	{
		std::string path;
	};

	// --------------------------------------------------------------------------------
	Directory::Directory(const oakvr::core::io::path::PathType &path)
	{
		m_pImpl = std::make_unique<DirectoryImpl>();
		m_pImpl->path = path;
	}

	Directory::Directory(Directory &&dir)
	{
		m_pImpl = std::move(dir.m_pImpl);
	}

	
	// --------------------------------------------------------------------------------
	bool Directory::Exists(const oakvr::core::io::path::PathType &path)
	{
		return GetFileAttributesA(path.c_str()) != INVALID_FILE_ATTRIBUTES;
	}

	// --------------------------------------------------------------------------------
	std::vector<Directory::DirEntry> Directory::GetEntryList()
	{
		std::string searchString = m_pImpl->path + "\\*";
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
	std::vector<oakvr::core::io::path::PathType> Directory::GetFileList(bool bRecursive)
	{
		return GetFileList(m_pImpl->path, bRecursive);
	}

	// --------------------------------------------------------------------------------
	std::vector<oakvr::core::io::path::PathType> Directory::GetFileList(const oakvr::core::io::path::PathType &path, bool bRecursive)
	{
		WIN32_FIND_DATAA findFileData;
		std::vector<oakvr::core::io::path::PathType> result;

		HANDLE hFind = FindFirstFileA((path + "\\*").c_str(), &findFileData);
		if(hFind == INVALID_HANDLE_VALUE)
			return result;

		do
		{
			if(!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				result.push_back(path + "\\" + findFileData.cFileName);
			}
			else if(bRecursive && findFileData.cFileName[0] != '.')
			{
				std::vector<std::string> temp = GetFileList(path + "\\" + findFileData.cFileName, bRecursive);
				result.insert(result.end(), temp.begin(), temp.end());
			}
		}
		while( FindNextFileA(hFind, &findFileData) );
		FindClose(hFind);

		return result;
	}
}	// namespace io
}	// namespace core
}	// namespace oakvr
