
// --------------------------------------------------------------------------------
// Copyright      Mihai Tudorache 2011
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_GRAPHICSENGINE_H__
#define __OAK3D_INCLUDE_GRAPHICSENGINE_H__

namespace Oak3D
{
	namespace Core
	{
		class RenderWindow;

		class GraphicsEngine
		{
		public:
			GraphicsEngine():m_pRenderWindow(nullptr){}
			virtual ~GraphicsEngine();

			virtual void Initialize(){}
			virtual void Update( float dt ){}
			virtual void Render(void){}
			virtual void Cleanup() {}

			void SetRenderWindow( RenderWindow *pRenderWindow );

		protected:
			RenderWindow *m_pRenderWindow;
		};
	}
}

#endif
