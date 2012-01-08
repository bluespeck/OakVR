
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------

#ifndef __OAK3D_RENDER_INCLUDE_FRUSTUM_H__
#define __OAK3D_RENDER_INCLUDE_FRUSTUM_H__

#include "Core/Math/Matrix.h"
#include "Core/Math/Vector3.h"
#include "Renderer/IRenderer/AABB.h"

using Oak3D::Math::Vector3;
using Oak3D::Math::Matrix;
using Oak3D::Render::AABB;

namespace Oak3D
{
	namespace Render
	{


		//#include "Plane.h"

		class Frustum
		{
		public:
			enum FrustumPlane { eFP_Left, eFP_Right, eFP_Top, eFP_Bottom, eFP_Near, eFP_Far, eFP_NumPlanes };

			Frustum();

			bool Inside(const Vector3 &point) const;
			bool Inside(const Vector3 &point, float fRadius) const;
			bool Inside(const AABB &aabb) const;
			bool Inside(const AABB &aabb, float fRadius) const;
			bool CompletlyInside(const AABB &aabb) const;
			bool CompletlyInside(const AABB &aabb, float fRadius) const;

			//const Plane &GetPlane(FrustumPlane ePlane);

			void Init(float fFOV, float fAspect, float fNear, float fFar);
			void ComputePlanesFromMatrix(const Matrix &mat);

			void SetFOV( float fFOV )			{ m_fFOV	= fFOV;		}
			void SetAspect( float fAspect )		{ m_fAspect = fAspect;	}
			void SetNearDistance( float fNear ) { m_fNear	= fNear;	}
			void SetFarDistance( float fFar )	{ m_fFar	= fFar;		}



		public:
			//Plane m_planes[eFP_NumPlanes];	// planes of the frustum in camera space
			Vector3 m_nearClip[4];	// vertices of the near clip plane in camera space
			Vector3 m_farClip[4];	// vertices of the far clip plane in camera space

			float m_fFOV;	// field of view in radians
			float m_fAspect;// aspect ratio; w/h
			float m_fNear;	// near clip distance
			float m_fFar;	// far clip distance

			Vector3 m_vecForward;
			Vector3 m_vecUp;
			Vector3 m_vecRight;
			Vector3 m_vecPosition;
		};


	} // namespace Utils
} // namespace Oak3D

#endif
