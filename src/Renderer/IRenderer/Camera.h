
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_RENDER_CAMERA_H__
#define __OAK3D_INCLUDE_RENDER_CAMERA_H__

#include "Object.h"
#include "Core/Math/Matrix.h"
#include "Core/Math/Vector3.h"
#include "Core/Math/MathUtils.h"

#include "Renderer/IRenderer/Frustum.h"

using Oak3D::Math::Vector3;
using Oak3D::Math::Matrix;
using Oak3D::Render::Frustum;

namespace Oak3D
{
	namespace Render
	{
		class Camera: public Object
		{
		public:	
			Camera( const Camera & camera );
			Camera( const Camera * pCamera );
			Camera();
			~Camera();

			void                SetFOV           ( float FOV ) { m_frustum.m_fFOV = FOV; m_bProjDirty = true; }
			void                SetViewport      ( long Left, long Top, long Width, long Height, float NearClip, float FarClip );
			//void                UpdateRenderView ( IDirect3DDevice9 *pD3DDevice );
			//void                UpdateRenderProj ( IDirect3DDevice9 *pD3DDevice );
			const Matrix	&   GetProjMatrix    ( );    
			float               GetFOV           ( ) const { return m_frustum.m_fFOV;  }
			float               GetNearClip      ( ) const { return m_frustum.m_fNear; }
			float               GetFarClip       ( ) const { return m_frustum.m_fFar; }    
			void				ResetProjMatrix	 ( ) { m_bProjDirty = true; }

			const Vector3	&	GetPosition      ( ) const { return m_frustum.m_vecPosition;   }
			const Vector3	&	GetLook          ( ) const { return m_frustum.m_vecForward;  }
			const Vector3	&	GetUp            ( ) const { return m_frustum.m_vecUp;    }
			const Vector3	&	GetRight         ( ) const { return m_frustum.m_vecRight; }
			const Matrix	&	GetViewMatrix    ( );

			const Frustum &	GetFrustum		() const { return m_frustum; }

			virtual void        SetPosition      ( const Vector3 & position ) { m_frustum.m_vecPosition = position; m_bViewDirty = true; m_bFrustumDirty = true; }
			void                SetLook          ( const Vector3& vector ) { m_frustum.m_vecForward  = vector; }
			void                SetUp            ( const Vector3& vector ) { m_frustum.m_vecUp    = vector; }
			void                SetRight         ( const Vector3& vector ) { m_frustum.m_vecRight = vector; }

			bool                BoundsInFrustum  ( const Vector3 & vMin, const Vector3 & vMax );
			bool                BoundsCompletlyInFrustum  ( const Vector3 & Min, const Vector3 & Max );
			bool				BoundsInFrustum  ( class CRenderComponent *pRenderComponent );
			bool				BoundsCompletlyInFrustum( CRenderComponent *pRenderComponent );


			virtual void        Rotate				( float x, float y, float z );	// in degrees
			virtual void        Update				( float dt );
			
			virtual void        SetCameraDetails ( const Camera * pCamera )     {}

		protected:
			Frustum		m_frustum;

			Matrix			m_matView;              // Cached view matrix
			Matrix			m_matProj;              // Cached projection matrix    

			bool            m_bViewDirty;           // View matrix dirty ?
			bool            m_bProjDirty;           // Proj matrix dirty ?
			bool            m_bFrustumDirty;        // Are the frustum planes dirty ?

			float           m_fPitch;               // camera pitch
			float           m_fRoll;                // camera roll
			float           m_fYaw;                 // camera yaw
		};
	} // namespace Render
}

#endif
