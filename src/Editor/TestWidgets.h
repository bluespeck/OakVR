#ifndef __OAK3D_INCLUDE_EDITOR_TESTWIDGETS_H__
#define __OAK3D_INCLUDE_EDITOR_TESTWIDGETS_H__

#include <Leaf3D/Button.h>

struct TestButton
{
	TestButton()
	{

		Oak3D::Leaf3D::Button b1;
		Oak3D::Leaf3D::Button b2;
		Oak3D::Leaf3D::Button b3;
		Oak3D::Leaf3D::Button b4;
		Oak3D::Leaf3D::Button b5;

		b1.SetPosition(100, 100);
		b1.SetDepth(0);
		b1.SetSize(64, 32);
		
		b2.SetPosition(250, 100);
		b2.SetDepth(1);
		b2.SetSize(200, 100);

		b3.SetPosition(240, 110);
		b3.SetDepth(0);
		b3.SetSize(70, 20);

		b4.SetPosition(230, 120);
		b4.SetDepth(2);
		b4.SetSize(70, 20);

		b5.SetPosition(220, 130);
		b5.SetDepth(3);
		b5.SetSize(70, 20);

	}

		Oak3D::Leaf3D::Button b;	
	


	
};

extern TestButton tb;


#endif
