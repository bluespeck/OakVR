#include "Path.h"

namespace oakvr
{
	namespace core
	{
		namespace io
		{
			namespace path
			{

#if defined(OAKVR_WINDOWS32) || defined(OAKVR_WINDOWS64)
				PathType g_pathSeparator = "\\";
#else
				PathType g_pathSeparator = "/";
#endif
				// --------------------------------------------------------------------------------
				PathType GetParentPath(const PathType &path)
				{
					auto pos = path.rfind(g_pathSeparator);
					return (pos != std::string::npos) ? path.substr(0, pos) : "";
				}

				// --------------------------------------------------------------------------------
				PathType GetFileName(const PathType &path)
				{
					auto pos = path.rfind(g_pathSeparator);
					return (pos != std::string::npos && pos <= path.size()) ? path.substr(pos + 1) : "";
				}

				// --------------------------------------------------------------------------------
				PathType GetExtension(const PathType &path)
				{
					auto pos = path.rfind('.');
					return (pos != std::string::npos && pos <= path.size()) ? path.substr(pos + 1) : "";
				}

				// --------------------------------------------------------------------------------
				PathType GetStem(const PathType &path)
				{
					auto filename = GetFileName(path);
					auto pos = filename.rfind('.');
					return (pos != std::string::npos) ? filename.substr(0, pos) : "";
				}
			}	// namespace path
		}	// namespace io
	}	// namespace core
}	// namespace oakvr
