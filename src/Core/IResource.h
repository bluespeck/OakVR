#ifndef __OAK3D_INCLUDE_IRESOURCE_H__
#define __OAK3D_INCLUDE_IRESOURCE_H__

#include <string>
#include "../Utils/StringID.h"

namespace Oak3D
{
	namespace Core
	{
		class IResource
		{
		public:

			enum ResourceState
			{
				eRS_Uninitialized,
				eRS_Loading,
				eRS_Ready,
				eRS_Released
			};

			IResource() : m_id(0) {}
			virtual ~IResource() {}
	
			virtual void Init(const std::wstring &path) = 0;
			virtual void Load() = 0;
			virtual void Reload() = 0;
			virtual void Release() = 0;

			inline void SetState(ResourceState resourceState);
			inline ResourceState GetState();
			inline Utils::StringId GetId();

			inline bool IsReady();

		protected:
			Utils::StringId m_id;
			ResourceState m_state;

		};

		inline bool IResource::IsReady()
		{
			return m_state == eRS_Ready;
		}

		inline Utils::StringId IResource::GetId()
		{
			return m_id;
		}

		// --------------------------------------------------------------------------------
		inline IResource::ResourceState IResource::GetState()
		{
			return m_state;
		}

		inline void IResource::SetState(IResource::ResourceState resourceState)
		{
			m_state = resourceState;
		}

	}	// namespace Core
}	// namespace Oak3D

#endif
