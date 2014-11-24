#pragma once

#include "OakVR/OakVR.h"
#include "Utils/Types.h"

#include <string>

namespace oakvr
{
	namespace render
	{
		class Sprite
		{
		public:
			Sprite(const std::string &name, const oakvr::math::Vector3 &centerPosition, float width, float height, const std::string &textureName);
			~Sprite();

			auto GetTextureName() const -> std::string { return m_textureName; }
			auto GetName() const -> std::string { return m_name; }

			auto GetCenterPosition() const -> const oakvr::math::Vector3 &{ return m_center; }
			void SetCenterPosition(const oakvr::math::Vector3 &vec);

			auto GetScaleFactor() const -> float { return m_scaleFactor; }
			void SetScaleFactor(float newScaleFactor);

		protected:
			sp<oakvr::render::Mesh> m_pMesh;

			std::string m_name;
			oakvr::math::Vector3 m_center;
			float m_width, m_height;
			float m_scaleFactor = 1.0f;
			std::string m_textureName;
		};
	}
}