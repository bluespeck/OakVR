
// --------------------------------------------------------------------------------
// Written by      Mihai Tudorache 2011
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_TRANSFORM_H__
#define __OAK3D_INCLUDE_TRANSFORM_H__

#include "Matrix.h"

namespace Oak3D
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
		};

	}
}

#endif
