
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_CORE_DIRECTORY_H__
#define __OAK3D_INCLUDE_CORE_DIRECTORY_H__

#include <string>
#include <vector>

namespace Oak3D
{
	namespace Core
	{
		class Directory
		{
		public:
			struct DirEntry
			{
				std::string path;
				enum EntryType
				{
					eET_File,
					eET_Directory
				} type;
			};
			
			struct DirectoryImpl;
						
			Directory(std::string path);
			~Directory();

			
			std::vector<DirEntry> GetEntryList();			
			std::vector<std::string> GetFileList(bool bRecursive = false);

			static bool Exists(std::string path);
			static std::vector<DirEntry> GetEntryList(std::string path);
			static std::vector<std::string> GetFileList(std::string path, bool bRecursive = false);

		private:
			

			DirectoryImpl *m_pImpl;
		};
	}
}

#endif
