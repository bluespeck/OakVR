#pragma once

#include <string>
#include <vector>

#include "Path.h"
#include "Utils/Types.h"

namespace oakvr::core::io
{
	class Directory
	{
	public:
		struct DirEntry
		{
			oakvr::core::io::path::PathType path;
			enum class EntryType
			{
				file,
				directory
			} type = EntryType::file;
		};
			
		struct DirectoryImpl;
						
		Directory(const oakvr::core::io::path::PathType &path);
		Directory(const Directory &dir) = delete;
		Directory(Directory &&dir);
		~Directory() = default;

			
		auto GetEntryList() -> std::vector<DirEntry>;
		auto GetFileList(bool bRecursive = false) -> std::vector<oakvr::core::io::path::PathType>;

		static auto Exists(const oakvr::core::io::path::PathType &path) -> bool;
		static auto GetEntryList(const oakvr::core::io::path::PathType &path) -> std::vector<DirEntry>;
		static auto GetFileList(const oakvr::core::io::path::PathType &path, bool bRecursive = false) -> std::vector<oakvr::core::io::path::PathType>;

	private:
		up<DirectoryImpl> m_pImpl;
	};
}	// namespace oakvr
