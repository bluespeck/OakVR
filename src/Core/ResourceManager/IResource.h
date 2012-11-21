#pragma once

#include "Utils/StringId.h"

namespace ro3d
{
	namespace Core{class ResourceManager; }
	enum class ResourceState
		{
			uninitialized,
			loading,
			ready,
			unloading
		};

	class IResource
	{
	public:
			
		typedef std::string ResourceType;

		IResource(const StringId &id) : m_id(id), m_state(ResourceState::uninitialized), m_type("IResource") {}
		virtual ~IResource() {}
			
		inline void SetState(ResourceState resourceState);
		inline ResourceState GetState();
		inline StringId GetId();
		ResourceType GetType() { return m_type; }

		inline bool IsReady();
		
	private:
		friend class ro3d::Core::ResourceManager;
		void _Init() { this->Init(); }
		void _Load() { this->Load(); }
		void _Reload() { this->Reload(); }
		void _Release() { this->Release(); }

	protected:
		StringId m_id;
		ResourceState m_state;
		ResourceType m_type;

		virtual void Init() = 0;
		virtual void Load() = 0;
		virtual void Reload() = 0;
		virtual void Release() = 0;
			
	};

	inline bool IResource::IsReady()
	{
		return m_state == ResourceState::ready;
	}

	inline StringId IResource::GetId()
	{
		return m_id;
	}

	// --------------------------------------------------------------------------------
	inline ResourceState IResource::GetState()
	{
		return m_state;
	}

	inline void IResource::SetState(ResourceState resourceState)
	{
		m_state = resourceState;
	}
}	// namespace ro3d
