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
				auto GetParentPath(const PathType &path) -> PathType
				{
					auto pos = path.rfind(GetPathSeparator());
					return (pos != std::string::npos) ? path.substr(0, pos) : "";
				}

				// --------------------------------------------------------------------------------
				auto GetFileName(const PathType &path) -> PathType
				{
					size_t pos = path.rfind(GetPathSeparator());
					return (pos != std::string::npos ) ? path.substr(pos + 1) : "";
				}

				// --------------------------------------------------------------------------------
				auto GetExtension(const PathType &path) -> PathType
				{
					auto pos = path.rfind('.');
					return (pos != std::string::npos ) ? path.substr(pos + 1) : "";
				}

				// --------------------------------------------------------------------------------
				auto GetStem(const PathType &path) -> PathType
				{
					auto filename = GetFileName(path);
					auto pos = filename.rfind('.');
					return (pos != std::string::npos) ? filename.substr(0, pos) : "";
				}
			}	// namespace path
		}	// namespace io
	}	// namespace core
}	// namespace oakvr
