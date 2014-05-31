#pragma once

#include "Object.h"
#include "Math/Matrix.h"
#include "Math/Vector3.h"
#include "Math/MathUtils.h"
#include "Updateable.h"

#include <initializer_list>
#include <string>

using oakvr::math::Vector3;

namespace oakvr
{
	namespace render
	{
		class Camera : public Updateable
		{
		public:	
			Camera() = delete;
			Camera(const std::string &, const Vector3 &pos, const Vector3 &target, const Vector3 &up);
			Camera(const std::string &, const std::initializer_list<Vector3> &);
			~Camera();

			void Update(float dt) override {}

			const Vector3 &GetPosition( ) const { return m_position; }
			const Vector3 &GetForward() const		{ return m_forward; }
			const Vector3 &GetUp( ) const		{ return m_up; }
			Vector3 GetRight() const { return m_forward.Cross(m_up); }
			oakvr::math::Matrix ComputeViewMatrix() const;
			
			void SetPosition( const Vector3 & position )	{ m_position = position; }
			void SetLook(const Vector3& forward)			{ m_forward = forward; }
			void SetUp( const Vector3& up )					{ m_up = up; }
			
			void Rotate( float alpha, float beta, float gamma );	// angles around x,y,z axes [radians]
			inline void Translate(float x, float y, float z) { Translate({ x, y, z }); }
			inline void Translate(const oakvr::math::Vector3 &displacement) { m_position += displacement; }

			const std::string &GetId() const { return m_id; }
			
		private:
			std::string m_id;

		protected:
			Vector3		m_position;
			Vector3		m_forward;
			Vector3		m_up;
		};
	} // namespace Render
}
