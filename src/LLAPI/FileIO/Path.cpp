#include "Path.h"

namespace oakvr
{
	namespace core
	{
		namespace io
		{
			namespace path
			{
				// --------------------------------------------------------------------------------
				PathType GetParentPath(const PathType &path)
				{
					auto pos = path.rfind(GetPathSeparator());
					return (pos != std::string::npos) ? path.substr(0, pos) : "";
				}

				// --------------------------------------------------------------------------------
				PathType GetFileName(const PathType &path)
				{
					size_t pos = path.rfind(GetPathSeparator());
					return (pos != std::string::npos ) ? path.substr(pos + 1) : "";
				}

				// --------------------------------------------------------------------------------
				PathType GetExtension(const PathType &path)
				{
					auto pos = path.rfind('.');
					return (pos != std::string::npos ) ? path.substr(pos + 1) : "";
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
