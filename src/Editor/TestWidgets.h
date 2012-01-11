#ifndef _OAK3D_EDITOR_TESTWIDGETS_H_
#define _OAK3D_EDITOR_TESTWIDGETS_H_

#include <Leaf3D/Button.h>

struct TestButton
{
	TestButton()
	{
		b.SetPosition(100, 100);
		b.SetDepth(0);
		b.SetSize(64, 32);
	}

	Oak3D::Leaf3D::Button b;
};

extern TestButton tb;


#endif
