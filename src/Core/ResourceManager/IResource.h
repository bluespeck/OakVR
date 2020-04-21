#pragma once

#include "Utils/StringId.h"

#include <mutex>

namespace oakvr
{
	namespace core{class ResourceManager; }
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
			
		inline auto SetState(ResourceState resourceState) -> void;
		inline ResourceState GetState() const;
		inline StringId GetId() const;
		inline ResourceType GetType() const;
		
		inline bool operator==(const IResource& res) const;
		inline auto IsReady() const -> bool;
		
	private:
		friend class oakvr::core::ResourceManager;
		auto _Init()  -> void{ this->Init(); }
		auto _Load()  -> void{ this->Load(); }
		auto _Reload()  -> void{ this->Reload(); }
		auto _Release()  -> void{ this->Release(); }

	protected:
		StringId m_id;
		ResourceState m_state;
		ResourceType m_type;
		

		virtual auto Init()  -> void= 0;
		virtual auto Load()  -> void= 0;
		virtual auto Reload()  -> void= 0;
		virtual auto Release()  -> void= 0;
			
	};

	// --------------------------------------------------------------------------------
	inline auto IResource::IsReady() const -> bool
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
	inline auto IResource::SetState(ResourceState resourceState) -> void
	{
		m_state = resourceState;
	}

	inline IResource::ResourceType IResource::GetType() const
	{
		return m_type;
	}

	// --------------------------------------------------------------------------------
	inline auto IResource::operator==(const IResource& res) const -> bool
	{
		return GetId() == res.GetId();
	}
}	// namespace oakvr
