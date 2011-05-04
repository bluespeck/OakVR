
// --------------------------------------------------------------------------------
// Copyright      Mihai Tudorache 2011
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_MATHUTILS_H__
#define __OAK3D_INCLUDE_MATHUTILS_H__

#define MAX(a, b) (((a) < (b))? (a) : (b))
#define MIN(a, b) (((a) < (b))? (b) : (a))
#define BOUND(x, a, b) (MAX((b), MIN((x), (a))))
#define PI 3.14159265358979f
#define DEG2RAD(deg) ((180 / PI) * (deg))
#define RAD2DEG(rad) ((PI / 180) * (rad))

#endif
