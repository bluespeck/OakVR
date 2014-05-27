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
#if defined(OAKVR_WINDOWS32) || defined(OAKVR_WINDOWS64)
					return "\\";
#else
					return "/";
#endif
				}

				PathType GetParentPath(const PathType &path);
				PathType GetFileName(const PathType &path);
				PathType GetExtension(const PathType &path);
				PathType GetStem(const PathType &path);	// filename without the extension
				
			}	// namespace path
		}	// namespace io
	}	// namespace core
}	// namespace oakvr
