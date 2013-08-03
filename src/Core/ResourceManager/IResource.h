#pragma once

#include <mutex>

#include "Utils/StringId.h"


namespace oakvr
{
	namespace Core{class ResourceManager; }
	enum class ResourceState : uint8_t
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
		inline ResourceState GetState() const;
		inline StringId GetId() const;
		inline ResourceType GetType() const;
		
		inline bool operator==(const IResource& res) const;
		inline bool IsReady() const;
		
	private:
		friend class oakvr::Core::ResourceManager;
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

	// --------------------------------------------------------------------------------
	inline bool IResource::IsReady() const
	{
		return m_state == ResourceState::ready;
	}

	// --------------------------------------------------------------------------------
	inline StringId IResource::GetId() const
	{
		return m_id;
	}

	// --------------------------------------------------------------------------------
	inline ResourceState IResource::GetState() const
	{
		return m_state;
	}

	// --------------------------------------------------------------------------------
	inline void IResource::SetState(ResourceState resourceState)
	{
		m_state = resourceState;
	}

	inline IResource::ResourceType IResource::GetType() const
	{
		return m_type;
	}

	// --------------------------------------------------------------------------------
	inline bool IResource::operator==(const IResource& res) const
	{
		return GetId() == res.GetId();
	}
}	// namespace oakvr
