#pragma once

#include "Object.h"
#include "Frustum.h"
#include "Matrix.h"

struct IDirect3DDevice9;

class CCamera: public CObject
{
public:	
	CCamera( const CCamera & camera );
	CCamera( const CCamera * pCamera );
	CCamera();
	~CCamera();

	void                SetFOV           ( float FOV ) { m_frustum.m_fFOV = FOV; m_bProjDirty = true; }
    void                SetViewport      ( long Left, long Top, long Width, long Height, float NearClip, float FarClip );
    //void                UpdateRenderView ( IDirect3DDevice9 *pD3DDevice );
    //void                UpdateRenderProj ( IDirect3DDevice9 *pD3DDevice );
    const CMatrix	&   GetProjMatrix    ( );    
    float               GetFOV           ( ) const { return m_frustum.m_fFOV;  }
    float               GetNearClip      ( ) const { return m_frustum.m_fNear; }
    float               GetFarClip       ( ) const { return m_frustum.m_fFar; }    
	void				ResetProjMatrix	 ( ) { m_bProjDirty = TRUE; }

	const CVector3	&	GetPosition      ( ) const { return m_frustum.m_vecPosition;   }
    const CVector3	&	GetLook          ( ) const { return m_frustum.m_vecForward;  }
    const CVector3	&	GetUp            ( ) const { return m_frustum.m_vecUp;    }
    const CVector3	&	GetRight         ( ) const { return m_frustum.m_vecRight; }
    const CMatrix	&	GetViewMatrix    ( );

	const CFrustum &	GetFrustum		() const { return m_frustum; }

	virtual void        SetPosition      ( const CVector3 & position ) { m_frustum.m_vecPosition = position; m_bViewDirty = true; m_bFrustumDirty = true; }
	void                SetLook          ( const CVector3& vector ) { m_frustum.m_vecForward  = vector; }
    void                SetUp            ( const CVector3& vector ) { m_frustum.m_vecUp    = vector; }
    void                SetRight         ( const CVector3& vector ) { m_frustum.m_vecRight = vector; }

	bool                BoundsInFrustum  ( const CVector3 & vMin, const CVector3 & vMax );
	bool                BoundsCompletlyInFrustum  ( const CVector3 & Min, const CVector3 & Max );
	bool				BoundsInFrustum  ( class CRenderComponent *pRenderComponent );
	bool				BoundsCompletlyInFrustum( CRenderComponent *pRenderComponent );

	
	virtual void        Rotate				( float x, float y, float z );	// in degrees
	virtual void        Move				( ULONG Direction, float Distance );
	virtual void        Move				( const CVector3 & vecShift );
	virtual void        Update				( float dt );
	virtual void		ProcessInput		( float dt );
	virtual void        SetCameraDetails ( const CCamera * pCamera )     {}

	virtual int GetCameraID( ) const { return m_eCameraID; }

protected:
	CFrustum		m_frustum;

	CMatrix			m_matView;              // Cached view matrix
	CMatrix			m_matProj;              // Cached projection matrix    

	bool            m_bViewDirty;           // View matrix dirty ?
	bool            m_bProjDirty;           // Proj matrix dirty ?
	bool            m_bFrustumDirty;        // Are the frustum planes dirty ?

	float           m_fPitch;               // camera pitch
	float           m_fRoll;                // camera roll
	float           m_fYaw;                 // camera yaw
};