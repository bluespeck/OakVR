
#include "Camera.h"

#include "../Math/Matrix.h"
#include "../Utils/AABB.h"

namespace Oak3D
{
	namespace Core
	{

		Camera::Camera()
		{	
			m_frustum.m_vecRight        = Oak3D::Math::Vector3( 1.0f, 0.0f, 0.0f );
			m_frustum.m_vecUp           = Oak3D::Math::Vector3( 0.0f, 1.0f, 0.0f );
			m_frustum.m_vecForward		= Oak3D::Math::Vector3( 0.0f, 0.0f, 1.0f );
			m_frustum.m_vecPosition		= Oak3D::Math::Vector3( 0.0f, 0.0f, 0.0f );

			m_frustum.m_fFOV	= 45.0f;
			m_frustum.m_fNear	= 1.0f;
			m_frustum.m_fFar	= 1000.0f;



			m_fPitch = 0.0f;
			m_fRoll  = 0.0f;
			m_fYaw   = acosf( Oak3D::Math::Vector3( 0.0f, 0.0f, 1.0f ).Dot(m_frustum.m_vecForward) );
			if ( m_frustum.m_vecForward.x < 0.0f ) m_fYaw = -m_fYaw;
						
			// Set matrices to identity
			m_matView = m_matProj = Oak3D::Math::Matrix::CreateIdentityMatrix();
		}

		Camera::Camera( const Camera * pCamera )
		{			
			// Reset / Clear all required values
			m_frustum	= pCamera->m_frustum;

			m_fPitch = pCamera->m_fPitch;
			m_fRoll  = pCamera->m_fRoll;
			m_fYaw   = acosf( Oak3D::Math::Vector3( 0.0f, 0.0f, 1.0f ).Dot(m_frustum.m_vecForward) );
			if ( m_frustum.m_vecForward.x < 0.0f ) m_fYaw = -m_fYaw;

			// Internal features are dirty by default
			m_bViewDirty      = true;
			m_bProjDirty      = true;
			m_bFrustumDirty   = true;

			// Set matrices to identity
			m_matView = m_matProj = Oak3D::Math::Matrix::CreateIdentityMatrix();
		}

		Camera::~Camera()
		{
		}

		void Camera::Rotate( float x, float y, float z )
		{
			Oak3D::Math::Matrix matRotate;
			matRotate.SetYawPitchRoll(-y, -x, z);
			m_matView = m_matView * matRotate;

			// Update our vectors
			m_frustum.m_vecRight = Oak3D::Math::Vector3(m_matView._11, m_matView._21, m_matView._31);
			m_frustum.m_vecUp = Oak3D::Math::Vector3(m_matView._12, m_matView._22, m_matView._32);
			m_frustum.m_vecForward = Oak3D::Math::Vector3(m_matView._13, m_matView._23, m_matView._33);

			m_fPitch = BOUND(m_fYaw + y, -89.9f, 89.9f);
			m_fRoll = BOUND(m_fRoll + z, -20.f, 20.f);
			if ( x )
			{
				m_fPitch += x;
				// Ensure yaw (in degrees) wraps around between 0 and 360
				while ( m_fPitch >  360.0f ) m_fPitch -= 360.0f;
				while ( m_fPitch <  0.0f   ) m_fPitch += 360.0f;
			} 

			// Set view matrix as dirty
			//m_bViewDirty = true;

			// Frustum is now dirty by definition
			m_bFrustumDirty = true;
		}

		/*
		bool Camera::BoundsInFrustum( CRenderComponent *pRenderComponent )
		{
			// First calculate the frustum planes if frustum changed
			if(m_bFrustumDirty)
			{
				Oak3D::Math::Matrix matVP; 
				Oak3D::Math::Matrix::Multiply( matVP, GetViewMatrix(), GetProjMatrix() ); 
				m_frustum.ComputePlanesFromMatrix( matVP );
				m_bFrustumDirty = false;
			}

			Oak3D::Core::Mesh *pMesh = pRenderComponent->GetMesh();	

			if(!pMesh->IsLoaded())
				return false;

			CFrustum frustum = m_frustum;
			CMatrix matWorldToObj;	
			D3DXMatrixTranspose(&matWorldToObj, &pRenderComponent->GetWorldMatrix());

			for(int i = 0; i < frustum.eFP_NumPlanes; ++i)		
			{
				// planes are already normalised by ComputePlanesFromMatrix
				D3DXPlaneTransform(&frustum.m_planes[i], &frustum.m_planes[i], &matWorldToObj);
				D3DXPlaneNormalize(&frustum.m_planes[i], &frustum.m_planes[i]);
			}

			return frustum.Inside(pMesh->GetBoundingBox());		
		}

		bool Camera::BoundsCompletlyInFrustum( CRenderComponent *pRenderComponent )
		{
			// First calculate the frustum planes if frustum changed
			if(m_bFrustumDirty)
			{
				CMatrix matVP; 
				CMatrix::Multiply( matVP, GetViewMatrix(), GetProjMatrix() ); 
				m_frustum.ComputePlanesFromMatrix( matVP );
				m_bFrustumDirty = false;
			}

			Mesh *pMesh = pRenderComponent->GetMesh();	

			if(!pMesh->IsLoaded())
				return false;

			CFrustum frustum = m_frustum;
			CMatrix matWorldToObj;	
			D3DXMatrixTranspose(&matWorldToObj, &pRenderComponent->GetWorldMatrix());

			for(int i = 0; i < frustum.eFP_NumPlanes; ++i)		
			{
				// planes are already normalised by ComputePlanesFromMatrix
				D3DXPlaneTransform(&frustum.m_planes[i], &frustum.m_planes[i], &matWorldToObj);
				D3DXPlaneNormalize(&frustum.m_planes[i], &frustum.m_planes[i]);
			}

			return frustum.CompletlyInside(pMesh->GetBoundingBox());		
		}

		bool Camera::BoundsInFrustum( const CVector3 & vMin, const CVector3 & vMax )
		{
			// First calculate the frustum planes if frustum changed
			if(m_bFrustumDirty)
			{
				CMatrix matVP; 
				CMatrix::Multiply( matVP, GetViewMatrix(), GetProjMatrix() ); 
				m_frustum.ComputePlanesFromMatrix( matVP );
				m_bFrustumDirty = false;
			}

			AABB aabb;
			aabb.m_vecLeftBottomFront = vMin;
			aabb.m_vecRightTopBack = vMax;
			if(m_frustum.Inside(aabb))
				return true;
			else
				return false;

		}

		bool Camera::BoundsCompletlyInFrustum  ( const CVector3 & vMin, const CVector3 & vMax )
		{
			// First calculate the frustum planes if frustum changed
			if(m_bFrustumDirty)
			{
				Oak3D::Math::Matrix matVP; 
				Oak3D::Math::Matrix::Multiply( matVP, GetViewMatrix(), GetProjMatrix() ); 
				m_frustum.ComputePlanesFromMatrix( matVP );
				m_bFrustumDirty = false;
			}

			Oak3D::Utils::AABB aabb;
			aabb.m_vecLeftBottomFront = vMin;
			aabb.m_vecRightTopBack = vMax;
			if(m_frustum.CompletlyInside(aabb))
				return true;
			else
				return false;

		}
		*/

		void Camera::Update(float dt)
		{		
		}

	}	// namespace Core
}	// namespace Oak3D