
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_RENDER_CAMERA_H__
#define __OAK3D_INCLUDE_RENDER_CAMERA_H__

#include "Object.h"
#include "Math/Matrix.h"
#include "Math/Vector3.h"
#include "Math/MathUtils.h"

using Oak3D::Math::Vector3;

namespace Oak3D
{
	namespace Render
	{
		class Camera: public Object
		{
		public:	
			Camera();
			Camera(const Vector3 &pos, const Vector3 &look, const Vector3 &up);
			~Camera();

			const Vector3 &GetPosition( ) const { return m_position; }
			const Vector3 &GetLook( ) const		{ return m_look; }
			const Vector3 &GetUp( ) const		{ return m_up; }
			
			void SetPosition( const Vector3 & position )	{ m_position = position; }
			void SetLook( const Vector3& look )				{ m_look = look; }
			void SetUp( const Vector3& up )					{ m_up = up; }
			

			void Rotate( float alpha, float beta, float gamma );	// angles around x,y,z axes [radians]
			void Translate(float x, float y, float z);
			void Update( float dt );

		protected:
			Vector3		m_position;
			Vector3		m_look;
			Vector3		m_up;
		};
	} // namespace Render
}

#endif
