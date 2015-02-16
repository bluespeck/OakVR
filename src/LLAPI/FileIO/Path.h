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

				inline auto GetPathSeparator() -> PathType
				{
#if defined(OAKVR_WINDOWS32) || defined(OAKVR_WINDOWS64)
					return "\\";
#else
					return "/";
#endif
				}

				inline auto GetParentPath(const PathType &path) -> PathType
				{
					auto pos = path.rfind(GetPathSeparator());
					return (pos != std::string::npos) ? path.substr(0, pos) : "";
				}

				// --------------------------------------------------------------------------------
				inline auto GetFileName(const PathType &path) -> PathType
				{
					size_t pos = path.rfind(GetPathSeparator());
					return (pos != std::string::npos) ? path.substr(pos + 1) : "";
				}

				// --------------------------------------------------------------------------------
				inline auto GetExtension(const PathType &path) -> PathType
				{
					auto pos = path.rfind('.');
					return (pos != std::string::npos) ? path.substr(pos + 1) : "";
				}

				// --------------------------------------------------------------------------------
				inline auto GetStem(const PathType &path) -> PathType
				{
					auto filename = GetFileName(path);
					auto pos = filename.rfind('.');
					return (pos != std::string::npos) ? filename.substr(0, pos) : "";
				}
				
			}	// namespace path
		}	// namespace io
	}	// namespace core
}	// namespace oakvr
