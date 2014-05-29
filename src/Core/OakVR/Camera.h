#pragma once

#include "Object.h"
#include "Math/Matrix.h"
#include "Math/Vector3.h"
#include "Math/MathUtils.h"

#include <initializer_list>
#include <string>

using oakvr::math::Vector3;

namespace oakvr
{
	namespace render
	{
		class Camera
		{
		public:	
			Camera() = delete;
			Camera(const std::string &, const Vector3 &pos, const Vector3 &look, const Vector3 &up);
			Camera(const std::string &, const std::initializer_list<Vector3> &);
			~Camera();

			const Vector3 &GetPosition( ) const { return m_position; }
			const Vector3 &GetLook( ) const		{ return m_look; }
			const Vector3 &GetUp( ) const		{ return m_up; }
			oakvr::math::Matrix ComputeViewMatrix() const;
			
			void SetPosition( const Vector3 & position )	{ m_position = position; }
			void SetLook( const Vector3& look )				{ m_look = look; }
			void SetUp( const Vector3& up )					{ m_up = up; }
			
			void Rotate( float alpha, float beta, float gamma );	// angles around x,y,z axes [radians]
			void Translate(float x, float y, float z);

			const std::string &GetId() const { return m_id; }
			
		private:
			std::string m_id;
			Vector3		m_position;
			Vector3		m_look;
			Vector3		m_up;
		};
	} // namespace Render
}
