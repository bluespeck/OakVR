#include "Texture.h"
#include "Oak3D/Engine.h"
#include "GraphicsEngine.h"

namespace Oak3D
{
	namespace Render
	{

		Texture::Texture(void)
		{
		}


		Texture::~Texture(void)
		{
		}

		void Texture::Init(const Oak3D::Core::StringId &id)
		{ 
			m_id = id;
		}
		
		void Texture::Load()
		{
			// Create GE texture
			Oak3D::Engine::GetInstance()->GetGraphicsEngine()->CreateTexture(this);
			m_state = eRS_Ready;
		}

		void Texture::Reload()
		{
		}

		void Texture::Release()
		{
			Oak3D::Engine::GetInstance()->GetGraphicsEngine()->ReleaseTexture(this);
		}
	} // namespace Render
}	// namespace Oak3D
