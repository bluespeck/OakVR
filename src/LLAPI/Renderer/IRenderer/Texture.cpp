#include "Texture.h"
#include "IRenderer.h"

namespace oakvr
{
	namespace Render
	{

		Texture::Texture(void)
		{
		}


		Texture::~Texture(void)
		{
		}

		//void Texture::Init(const oakvr::Core::StringId &id, AdditionalInitParams *)
		//{ 
		//	m_id = id;
		//}
		//
		//void Texture::Load()
		//{
		//	m_state = eRS_Loading;
		//	// Create GE texture
		//	oakvr::Engine::GetInstance()->GetRenderer()->CreateTexture(this);
		//	m_state = eRS_Ready;
		//}

		//void Texture::Reload()
		//{
		//}

		//void Texture::Release()
		//{
		//	oakvr::Engine::GetInstance()->GetRenderer()->ReleaseTexture(this);
		//	m_state = eRS_Released;
		//}
	} // namespace Render
}	// namespace oakvr
