#include "Texture.h"
#include "Oak3D/Engine.h"
#include "IRenderer.h"

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

		void Texture::Init(const Oak3D::Core::StringId &id, AdditionalInitParams *)
		{ 
			m_id = id;
		}
		
		void Texture::Load()
		{
			m_state = eRS_Loading;
			// Create GE texture
			Oak3D::Engine::GetInstance()->GetRenderer()->CreateTexture(this);
			m_state = eRS_Ready;
		}

		void Texture::Reload()
		{
		}

		void Texture::Release()
		{
			Oak3D::Engine::GetInstance()->GetRenderer()->ReleaseTexture(this);
			m_state = eRS_Released;
		}
	} // namespace Render
}	// namespace Oak3D
