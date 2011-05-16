#include "Texture.h"
#include "Engine.h"
#include "GraphicsEngine.h"

namespace Oak3D
{
	namespace Core
	{

		Texture::Texture(void)
		{
		}


		Texture::~Texture(void)
		{
		}

		void Texture::Init(const std::wstring &path)
		{ 
			m_id.SetStrId(path);
		}
		
		void Texture::Load()
		{
			Engine::GetInstance()->GetGraphicsEngine()->CreateTexture(this);
		}

		void Texture::Reload()
		{
		}

		void Texture::Release()
		{
			Engine::GetInstance()->GetGraphicsEngine()->ReleaseTexture(this);
		}
	} // namespace Core
}	// namespace Oak3D
