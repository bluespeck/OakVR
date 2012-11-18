#pragma once

#include <string>
#include "Utils/StringID.h"

namespace ro3d
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

			enum class ResourceState
			{
				uninitialized,
				loading,
				ready,
				unloading
			};

			IResource() : m_id(1), m_refCount(1), m_state(ResourceState::uninitialized) {}
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
			return m_state == ResourceState::ready;
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
}	// namespace ro3d

