
#include "Camera.h"

#include "Engine.h"
#include "RenderEngine.h"
#include "RenderComponent.h"
#include "Matrix.h"
#include "Mesh.h"
#include "MathUtils.h"
#include "Input.h"

CCamera::CCamera()
{	
	m_eCameraID = eCID_Standard;

	m_frustum.m_vecRight        = CVector3( 1.0f, 0.0f, 0.0f );
	m_frustum.m_vecUp           = CVector3( 0.0f, 1.0f, 0.0f );
	m_frustum.m_vecForward		= CVector3( 0.0f, 0.0f, 1.0f );
	m_frustum.m_vecPosition		= CVector3( 0.0f, 0.0f, 0.0f );

	m_frustum.m_fFOV	= 45.0f;
	m_frustum.m_fNear	= 1.0f;
	m_frustum.m_fFar	= 1000.0f;


	
	m_fPitch = 0.0f;
	m_fRoll  = 0.0f;
	m_fYaw   = acosf( CVector3( 0.0f, 0.0f, 1.0f ).Dot(m_frustum.m_vecForward) );
	if ( m_frustum.m_vecForward.x < 0.0f ) m_fYaw = -m_fYaw;

	// Internal features are dirty by default
	m_bViewDirty      = true;
	m_bProjDirty      = true;
	m_bFrustumDirty   = true;

	// Set matrices to identity
	m_matView = m_matProj = CMatrix::g_matIdentity;
}

CCamera::CCamera( const CCamera * pCamera )
{
	m_eCameraID = pCamera->m_eCameraID;
    // Reset / Clear all required values
	m_frustum	= pCamera->m_frustum;
        
	m_fPitch = pCamera->m_fPitch;
	m_fRoll  = pCamera->m_fRoll;
	m_fYaw   = acosf( CVector3( 0.0f, 0.0f, 1.0f ).Dot(m_frustum.m_vecForward) );
	if ( m_frustum.m_vecForward.x < 0.0f ) m_fYaw = -m_fYaw;

    // Internal features are dirty by default
    m_bViewDirty      = true;
    m_bProjDirty      = true;
    m_bFrustumDirty   = true;

    // Set matrices to identity
    m_matView = m_matProj = CMatrix::g_matIdentity;
}

CCamera::~CCamera()
{
}

const CMatrix& CCamera::GetProjMatrix()
{
	// Only update matrix if something has changed
	if ( m_bProjDirty ) 
	{     
		// Set the perspective projection matrix
		D3DXMatrixPerspectiveFovLH( &m_matProj, D3DXToRadian( m_frustum.m_fFOV ),  (float)CEngine::GetRenderEngine()->GetViewportWidth() / (float)CEngine::GetRenderEngine()->GetViewportHeight(), m_frustum.m_fNear, m_frustum.m_fFar );

		// Proj Matrix has been updated
		m_bProjDirty = false;
	}

	// Return the projection matrix.
	return m_matProj;
}

const CMatrix& CCamera::GetViewMatrix()
{
	// Only update matrix if something has changed
	if ( m_bViewDirty ) 
	{
		CVector3 vecAt = m_frustum.m_vecPosition + m_frustum.m_vecForward;
		D3DXMatrixLookAtLH(&m_matView, &m_frustum.m_vecPosition, &vecAt, &m_frustum.m_vecUp);
		
		// View Matrix has been updated
		m_bViewDirty = false;

	} // End If View Dirty

	// Return the view matrix.
	return m_matView;
}

void CCamera::Rotate( float x, float y, float z )
{
	CMatrix matRotate;
	matRotate.BuildYawPitchRoll(D3DXToRadian(-y), D3DXToRadian(-x), D3DXToRadian(z));
	m_matView *= matRotate;

	// Update our vectors
	m_frustum.m_vecRight = CVector3(m_matView._11, m_matView._21, m_matView._31);
	m_frustum.m_vecUp = CVector3(m_matView._12, m_matView._22, m_matView._32);
	m_frustum.m_vecForward = CVector3(m_matView._13, m_matView._23, m_matView._33);
	
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


bool CCamera::BoundsInFrustum( CRenderComponent *pRenderComponent )
{
	// First calculate the frustum planes if frustum changed
	if(m_bFrustumDirty)
	{
		CMatrix matVP; 
		CMatrix::Multiply( matVP, GetViewMatrix(), GetProjMatrix() ); 
		m_frustum.ComputePlanesFromMatrix( matVP );
		m_bFrustumDirty = false;
	}

	CMesh *pMesh = pRenderComponent->GetMesh();	

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

bool CCamera::BoundsCompletlyInFrustum( CRenderComponent *pRenderComponent )
{
	// First calculate the frustum planes if frustum changed
	if(m_bFrustumDirty)
	{
		CMatrix matVP; 
		CMatrix::Multiply( matVP, GetViewMatrix(), GetProjMatrix() ); 
		m_frustum.ComputePlanesFromMatrix( matVP );
		m_bFrustumDirty = false;
	}

	CMesh *pMesh = pRenderComponent->GetMesh();	

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

bool CCamera::BoundsInFrustum( const CVector3 & vMin, const CVector3 & vMax )
{
	// First calculate the frustum planes if frustum changed
	if(m_bFrustumDirty)
	{
		CMatrix matVP; 
		CMatrix::Multiply( matVP, GetViewMatrix(), GetProjMatrix() ); 
		m_frustum.ComputePlanesFromMatrix( matVP );
		m_bFrustumDirty = false;
	}

	CAABB aabb;
	aabb.m_vecLeftBottomFront = vMin;
	aabb.m_vecRightTopBack = vMax;
	if(m_frustum.Inside(aabb))
		return true;
	else
		return false;
	
}

bool CCamera::BoundsCompletlyInFrustum  ( const CVector3 & vMin, const CVector3 & vMax )
{
	// First calculate the frustum planes if frustum changed
	if(m_bFrustumDirty)
	{
		CMatrix matVP; 
		CMatrix::Multiply( matVP, GetViewMatrix(), GetProjMatrix() ); 
		m_frustum.ComputePlanesFromMatrix( matVP );
		m_bFrustumDirty = false;
	}

	CAABB aabb;
	aabb.m_vecLeftBottomFront = vMin;
	aabb.m_vecRightTopBack = vMax;
	if(m_frustum.CompletlyInside(aabb))
		return true;
	else
		return false;
	
}

void CCamera::Update(float dt)
{
	ProcessInput(dt);
}

void CCamera::ProcessInput( float dt )
{	
	CInput *pInput = CEngine::GetInput();
	if(!pInput)
		return;
		
	ULONG direction = 0;
	int	x = 0, y = 0;
	
	// Check the relevant keys
	if ( pInput->IsKeyDown( VK_UP ) ) direction |= CCamera::eCD_Forward;
	if ( pInput->IsKeyDown( VK_DOWN ) ) direction |= CCamera::eCD_Backward;
	if ( pInput->IsKeyDown( VK_LEFT ) ) direction |= CCamera::eCD_Left;
	if ( pInput->IsKeyDown( VK_RIGHT ) ) direction |= CCamera::eCD_Right;
	if ( pInput->IsKeyDown( VK_PRIOR ) ) direction |= CCamera::eCD_Up;
	if ( pInput->IsKeyDown( VK_NEXT ) ) direction |= CCamera::eCD_Down;

	if(pInput->IsLBDown())
		pInput->GetMousePosDelta(x, y);

	// Update if we have moved

	if ( direction > 0 || x != 0.0f || y != 0.0f )
	{
		// Rotate our camera
		if ( x || y ) 
		{
			Rotate( y * dt * 15, x * dt * 15, 0.0f );
		} // End if any rotation

		// Any Movement ?
		if ( direction ) 
		{
			float speed;
			if( pInput->IsKeyDown( VK_RCONTROL ) ) 
				speed = 100.0f; 
			else 
				speed = 50.0f;
			Move( direction, speed * dt );

		} // End if any movement

	} // End if camera moved

	if(pInput->IsDragging())
	{
		CEngine *pEngine = CEngine::GetInstance();
		pEngine->AddEngineInfoText(_T("\nIs dragging - "));	
		TCHAR pos[30];
		_stprintf( pos, _T("%d %d - %d %d"), pInput->GetDragStartPos().x, pInput->GetDragStartPos().y, pInput->GetMousePosition().x, pInput->GetMousePosition().y );
		pEngine->AddEngineInfoText( pos );	
	}
}

void CCamera::Move( ULONG direction, float fDistance )
{
    CVector3 vecShift = CVector3( 0, 0, 0 );

    // Which direction are we moving ?
    if ( direction & eCD_Forward  ) vecShift += m_frustum.m_vecForward	* fDistance;
    if ( direction & eCD_Backward ) vecShift -= m_frustum.m_vecForward	* fDistance;
    if ( direction & eCD_Right    ) vecShift += m_frustum.m_vecRight	* fDistance;
    if ( direction & eCD_Left     ) vecShift -= m_frustum.m_vecRight	* fDistance;
    if ( direction & eCD_Up       ) vecShift += m_frustum.m_vecUp		* fDistance;
    if ( direction & eCD_Down     ) vecShift -= m_frustum.m_vecUp		* fDistance;

    // Update camera vectors
    if ( direction ) Move( vecShift );
}

void CCamera::Move( const CVector3 &vecShift )
{
    m_frustum.m_vecPosition += vecShift; 
	m_bViewDirty = true; 
	m_bFrustumDirty = true;
}