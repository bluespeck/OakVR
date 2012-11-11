#include "Texture.h"
#include "IRenderer.h"

namespace ro3d
{
	namespace Render
	{

		Texture::Texture(void)
		{
		}


		Texture::~Texture(void)
		{
		}

		//void Texture::Init(const ro3d::Core::StringId &id, AdditionalInitParams *)
		//{ 
		//	m_id = id;
		//}
		//
		//void Texture::Load()
		//{
		//	m_state = eRS_Loading;
		//	// Create GE texture
		//	ro3d::Engine::GetInstance()->GetRenderer()->CreateTexture(this);
		//	m_state = eRS_Ready;
		//}

		//void Texture::Reload()
		//{
		//}

		//void Texture::Release()
		//{
		//	ro3d::Engine::GetInstance()->GetRenderer()->ReleaseTexture(this);
		//	m_state = eRS_Released;
		//}
	} // namespace Render
}	// namespace ro3d
