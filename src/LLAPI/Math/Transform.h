#pragma once

#include "Matrix.h"

namespace oakvr
{
	namespace Math
	{

		class Transform : public Matrix
		{
		public:
			Transform(void);			

			void SetRotationX( float angle );
			void SetRotationY( float angle );
			void SetRotationZ( float angle );
			void SetIdentity();

			static Transform CreateRotationX( float angle );
			static Transform CreateRotationY( float angle );
			static Transform CreateRotationZ( float angle );

			static Transform CreatePerspectiveProjectionTransform(float fov, float aspect, float znear, float zfar);
			static Transform CreateOthographicProjectionTransform(float left, float right, float bottom, float top, float near, float far);
		};

	} // namespace Math
} // namespace oakvr
