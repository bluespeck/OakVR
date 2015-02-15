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
		VisualComponent(ObjectSharedPointer pObject, ObjectComponentSharedPointer pTransformComponent) : ObjectComponent(pObject), m_pTransformComponent{ std::dynamic_pointer_cast<TransformComponent>(pTransformComponent) } {}
		~VisualComponent() {}

		void SetMeshFromResource(StringId resourceId);
		auto GetMesh()->render::MeshSharedPointer;

	private:
		render::MeshSharedPointer m_pMesh;
		TransformComponentSharedPointer m_pTransformComponent;

		_OC_DECLARE_INITIALIZER_HELPERS(Visual);
	};

	using VisualComponentSharedPointer = sp < VisualComponent > ;

	inline auto VisualComponent::GetMesh()->render::MeshSharedPointer
	{
		return m_pMesh;
	}
}