
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
			virtual ~GraphicsEngine(){}

			virtual void Initialize() = 0;
			virtual void Update( float dt ) = 0;
			virtual void Render(void) = 0;
			virtual void Cleanup() = 0;

			void SetRenderWindow( RenderWindow *pRenderWindow );

		protected:
			RenderWindow *m_pRenderWindow;
		};
	}
}

#endif
