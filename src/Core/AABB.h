#pragma once

#include "Vector3.h"

class CAABB
{
public:
	CAABB(void);
	~CAABB(void);

	CVector3 m_vecLeftBottomFront;
	CVector3 m_vecRightTopBack;
};

