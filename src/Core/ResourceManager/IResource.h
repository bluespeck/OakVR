#ifndef __OAK3D_INCLUDE_CORE_IRESOURCE_H__
#define __OAK3D_INCLUDE_CORE_IRESOURCE_H__

#include <string>
#include "Core/Utils/StringId.h"

namespace Oak3D
{
	namespace Core
	{
		class IResource
		{
		public:
			
			// helper struct that is passed to the init function with specific initialization
			// params that the derived resource classes specify in their own version of the struct
			// which will be inherited from this one
			struct AdditionalInitParams	
			{							
				virtual ~AdditionalInitParams(){}
			};

			enum ResourceState
			{
				eRS_Uninitialized,
				eRS_Loading,
				eRS_Ready,
				eRS_Released
			};

			IResource() : m_id(1), m_refCount(1), m_state(eRS_Uninitialized) {}
			virtual ~IResource() {}
	
			virtual void Init(const StringId &id, AdditionalInitParams *pInitParams) = 0;
			virtual void Load() = 0;
			virtual void Reload() = 0;
			virtual void Release() = 0;

			inline void SetState(ResourceState resourceState);
			inline ResourceState GetState();
			inline Core::StringId GetId();

			inline bool IsReady();

		protected:
			friend class ResourceManager;

			Core::StringId m_id;
			ResourceState m_state;
			int m_refCount;

			
		};

		inline bool IResource::IsReady()
		{
			return m_state == eRS_Ready;
		}

		inline Core::StringId IResource::GetId()
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
