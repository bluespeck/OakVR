#pragma once

#include <string>

namespace oakvr
{
	namespace core
	{
		namespace io
		{
			namespace path
			{
				typedef std::string PathType;

				inline PathType GetPathSeparator()
				{
					extern PathType g_pathSeparator;
					return g_pathSeparator;
				}

				PathType GetParentPath(const PathType &path);
				PathType GetFileName(const PathType &path);
				PathType GetExtension(const PathType &path);
				PathType GetStem(const PathType &path);	// filename without the extension
				
			}	// namespace path
		}	// namespace io
	}	// namespace core
}	// namespace oakvr
