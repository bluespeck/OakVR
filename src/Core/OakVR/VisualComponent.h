#pragma once

#include "ObjectComponent.h"
#include "TransformComponent.h"

#include "Utils/RenderUtils.h"
#include "Renderer/Renderer/Material.h"
#include "Renderer/Renderer/Mesh.h"

namespace oakvr
{
	class VisualComponent : public ObjectComponent
	{
	public:
		VisualComponent(ObjectSharedPointer pObject) : ObjectComponent(pObject) {}
		virtual ~VisualComponent() override {}

		auto SetMeshFromResource(StringId resourceId) -> void;
		auto GetMesh() -> render::MeshSharedPointer;

		virtual	auto GetComponentObjectType() const noexcept -> oakvr::ObjectComponentId override { return oakvr::ObjectComponentId::visual; }
		virtual	auto GetComponentObjectTypeAsString() const noexcept -> std::string override { return "VisualComponent"s; }

		static	auto GetComponentClassType() -> oakvr::ObjectComponentId { return oakvr::ObjectComponentId::visual; }
		static 	auto GetComponentClassTypeAsString() -> std::string { return "VisualComponent"s; }

	private:
		render::MeshSharedPointer m_pMesh;
	};

	using VisualComponentSharedPointer = sp < VisualComponent > ;

	inline auto VisualComponent::GetMesh() -> render::MeshSharedPointer
	{
		return m_pMesh;
	}
}