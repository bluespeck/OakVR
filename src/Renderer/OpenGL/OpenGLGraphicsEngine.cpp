
#include "Core/Config/Oak3DConfig.h"

#if OAK3D_RENDERER == OAK3D_RENDERER_OPENGL

// include the OpenGL library file
//#pragma comment (lib, "Opengl32.lib")

#include <cassert>



#include <windows.h>
#include <wingdi.h>
#include <gl/glew.h>
#include <gl/glu.h>
#include <gl/gl.h>
#include <SOIL/include/SOIL.h>

#include "Oak3D/Engine.h"

#include "OpenGLGraphicsEngine.h"
#include "OpenGLDebugText.h"

#include "Renderer/IRenderer/WindowsRenderWindow.h"
#include "Renderer/IRenderer/GraphicsEngineUtils.h"
#include "Renderer/IRenderer/VertexBuffer.h"
#include "Renderer/IRenderer/IndexBuffer.h"
#include "Renderer/IRenderer/Texture.h"

#include "Core/Math/Matrix.h"
#include "Core/Math/Transform.h"
#include "Renderer/IRenderer/Shader.h"

#include "Core/FileSystem/File.h"


namespace Oak3D
{
	namespace Render
	{
		// --------------------------------------------------------------------------------
		OpenGLGraphicsEngine::OpenGLGraphicsEngine()
			: m_pDevice(nullptr)
			, m_pDebugText(nullptr)
		{			
		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::Initialize()
		{
			m_mainThreadId = GetCurrentThreadId();
			HWND hWnd = reinterpret_cast<HWND>(m_pRenderWindow->GetOSHandle());
			HDC hdc = GetDC(hWnd);

			SetWindowTextW(hWnd, L"Oak3D [OpenGL]");
			/////
			// create Direct3D device

			PIXELFORMATDESCRIPTOR pfd = { 0 };
			pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
			pfd.nVersion = 1;
			pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
			pfd.iPixelType = PFD_TYPE_RGBA;
			pfd.cColorBits = 32;
			pfd.cDepthBits = 32;
			pfd.iLayerType = PFD_MAIN_PLANE;

			int  iPixelFormat; 

			// get the device context's best, available pixel format match  
			iPixelFormat = ChoosePixelFormat(hdc, &pfd); 

			// make that match the device context's current pixel format  
			SetPixelFormat(hdc, iPixelFormat, &pfd);

			m_pDevice = (HGLRC) wglCreateContext(hdc); 
			m_pWorkerThreadDevice = (HGLRC) wglCreateContext(hdc); 
			wglShareLists((HGLRC)m_pDevice, (HGLRC)m_pWorkerThreadDevice);

			wglMakeCurrent (hdc, (HGLRC)m_pDevice);
						
			glewInit();

			/////
			// create projection matrices
			m_pPerspectiveProjectionMatrix = new Math::Matrix();
			m_pOrthographicProjectionMatrix = new Math::Matrix();
			glMatrixMode(GL_PROJECTION);
			*m_pPerspectiveProjectionMatrix = Math::Transform::CreatePerspectiveProjectionTransform(3.141592f * 0.25f, 1.25f, 1.0f, 1000.0f);
			*m_pOrthographicProjectionMatrix = Math::Transform::CreateOthographicProjectionTransform(0.0f, (float)m_pRenderWindow->GetWidth(), 0.0f, (float)m_pRenderWindow->GetHeight(), 1.0f, 1000.0f);
			
			InitializeStateObjects();

			/////
			// initialize debug text
			m_pDebugText = new OpenGLDebugText();
			m_pDebugText->Init();

			m_shaderProgramId = glCreateProgram();
		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::InitializeStateObjects()
		{

		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::Render()
		{	
			// clear the window to a deep blue
			glClearColor(0.0f, 0.2f, 0.4f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
									
			// render 3D stuff to back buffer
			glUseProgram(m_shaderProgramId);

			// print fps on screen
			char str[128];
			sprintf(str, "FPS: %.0f", (1.0f / Oak3D::Engine::GetTimer()->GetDeltaTime()));
			m_pDebugText->OutputText(str, 10, 10);

						
			SwapBuffers(wglGetCurrentDC());
		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::Cleanup()
		{
			delete m_pDebugText;
			  
			wglMakeCurrent (NULL, NULL) ; 
			wglDeleteContext ((HGLRC)m_pDevice);
			wglDeleteContext( (HGLRC)m_pWorkerThreadDevice);
		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::Update(float dt)
		{

		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::CreateShader(Shader *pShader)
		{
			GLenum shaderType;
			switch(pShader->GetType())
			{
			case ShaderType::eST_VertexShader:
				shaderType = GL_VERTEX_SHADER;
				break;
			case ShaderType::eST_PixelShader:
				shaderType = GL_FRAGMENT_SHADER;
				break;
			default:
				assert("Unknown shader type" && 0);
				break;
			}

			GLuint shaderId = glCreateShader(shaderType);
			
			Core::File file(pShader->GetId().GetStrId());
			const uint32_t buffSize = file.Size();
			unsigned char **buff = &(new unsigned char [buffSize]);
			
			file.Open(Core::File::FileOpenMode::eFOM_OpenRead);			
			file.Read(*buff, buffSize, 0);
			

			glShaderSource(shaderId, 1, (const GLchar**)buff, nullptr);

			delete[] *buff;
			glCompileShader(shaderId);

			pShader->SetCompiledShader((void *)shaderId);
			file.Close();
		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::ReleaseShader(Shader *pShader)
		{
			if(pShader == nullptr)
				return;
			glDeleteShader((GLuint)pShader->GetCompiledShader());
		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::CreateTexture( Texture *pTexture )
		{
			if(GetCurrentThreadId() != m_mainThreadId)
				wglMakeCurrent(GetDC(reinterpret_cast<HWND>(m_pRenderWindow->GetOSHandle())), (HGLRC)m_pWorkerThreadDevice);

			GLuint texId;

			glGenTextures(1, &texId);
			
			texId = SOIL_load_OGL_texture(pTexture->GetId().GetStrId().c_str(), SOIL_LOAD_AUTO, texId, SOIL_FLAG_MULTIPLY_ALPHA);
			assert("Could not load texture from file!" && texId > 0);

			pTexture->SetData((void *)texId);

			glBindTexture(GL_TEXTURE_2D, texId);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::ReleaseTexture( Texture *pTexture )
		{
			GLuint tex = (GLuint)pTexture->GetData();
			glDeleteTextures(1, &tex);
		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::CreateVertexBuffer( VertexBuffer *pVertexBuffer )
		{
			GLuint vbId; 
			glGenBuffers(1, &vbId);
			glBindBuffer(GL_ARRAY_BUFFER, vbId);
			glBufferData(GL_ARRAY_BUFFER, pVertexBuffer->GetVertexSize() * pVertexBuffer->GetVertexCount(), nullptr, GL_DYNAMIC_DRAW);
			pVertexBuffer->SetData((void *)vbId);
		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::LockVertexBuffer( VertexBuffer *pVertexBuffer, void **ppBuff, uint32_t /*offsetToLock*/, uint32_t /*sizeToLock*/, uint32_t flags )
		{	
			int oldId = 0;
			glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &oldId);
			glBindBuffer(GL_ARRAY_BUFFER, (int)pVertexBuffer->GetData());
			*ppBuff = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
			glBindBuffer(GL_ARRAY_BUFFER, oldId);
		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::UnlockVertexBuffer( VertexBuffer *pVertexBuffer )
		{	
			int oldId = 0;
			glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &oldId);
			glBindBuffer(GL_ARRAY_BUFFER, (int)pVertexBuffer->GetData());
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, oldId);
		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::ReleaseVertexBuffer( VertexBuffer *pVertexBuffer )
		{
			GLuint id = (GLuint)pVertexBuffer->GetData();
			glDeleteBuffers(1, &id);
		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::CreateIndexBuffer( IndexBuffer *pIndexBuffer )
		{
			GLuint ibId; 
			glGenBuffers(1, &ibId);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibId);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, pIndexBuffer->GetIndexSize() * pIndexBuffer->GetIndexCount(), NULL, GL_DYNAMIC_DRAW);

			pIndexBuffer->SetData((void *)ibId);
		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::LockIndexBuffer( IndexBuffer *pIndexBuffer, void **ppBuff, uint32_t offsetToLock, uint32_t sizeToLock, uint32_t flags )
		{	
			int oldId = 0;
			glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &oldId);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (int)pIndexBuffer->GetData());
			*ppBuff = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_READ_WRITE);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, oldId);
		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::UnlockIndexBuffer( IndexBuffer *pIndexBuffer )
		{	
			int oldId = 0;
			glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &oldId);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (int)pIndexBuffer->GetData());
			glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, oldId);
		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::ReleaseIndexBuffer( IndexBuffer *pIndexBuffer )
		{
			GLuint id = (GLuint)pIndexBuffer->GetData();
			glDeleteBuffers(1, &id);
		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::OutputText( const std::string &text, uint32_t x, uint32_t y)
		{
			m_pDebugText->OutputText(text, x, y);
		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::CreateInputLayoutDesc(uint32_t vertexFormat, void *&pLayoutDesc, uint32_t &numElems)
		{
			/*
			D3DVERTEXELEMENT9 layout[12];
			numElems = 0;
			int offset = 0;
			if(vertexFormat & VertexBuffer::eVF_XYZ)
			{
				layout[numElems].Usage = D3DDECLUSAGE_POSITION;
				layout[numElems].UsageIndex = 0;
				layout[numElems].Type = D3DDECLTYPE_FLOAT3;
				layout[numElems].Stream = 0;
				layout[numElems].Offset = offset;
				layout[numElems].Method = D3DDECLMETHOD_DEFAULT;
				offset += 12;
				++numElems;
			}
			if(vertexFormat & VertexBuffer::eVF_Normal)
			{
				layout[numElems].Usage = D3DDECLUSAGE_NORMAL;
				layout[numElems].UsageIndex = 0;
				layout[numElems].Type = D3DDECLTYPE_FLOAT3;
				layout[numElems].Stream = 0;
				layout[numElems].Offset = offset;
				layout[numElems].Method = D3DDECLMETHOD_DEFAULT;
				offset += 12;
				++numElems;
			}
			if(vertexFormat & VertexBuffer::eVF_Diffuse)
			{
				layout[numElems].Usage = D3DDECLUSAGE_COLOR;
				layout[numElems].UsageIndex = 0;
				layout[numElems].Type= D3DDECLTYPE_D3DCOLOR;
				layout[numElems].Stream = 0;
				layout[numElems].Offset = offset;
				layout[numElems].Method = D3DDECLMETHOD_DEFAULT;
				offset += 16;
				++numElems;
			}

			if(vertexFormat & VertexBuffer::eVF_Tex0)
			{
				layout[numElems].Usage = D3DDECLUSAGE_TEXCOORD;
				layout[numElems].UsageIndex = 0;
				layout[numElems].Type = D3DDECLTYPE_FLOAT2;
				layout[numElems].Stream = 0;
				layout[numElems].Offset = offset;
				layout[numElems].Method = D3DDECLMETHOD_DEFAULT;
				offset += 8;
				++numElems;
			}

			pLayoutDesc = new D3DVERTEXELEMENT9[numElems];
			memcpy(pLayoutDesc, layout, numElems * sizeof(D3DVERTEXELEMENT9));
			*/
		}


		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::UseVertexBuffer( VertexBuffer *pVertexBuffer )
		{
			uint32_t vertexFormat = pVertexBuffer->GetVertexFormat();
			uint32_t vertexSize = pVertexBuffer->GetVertexSize();
			glBindBuffer(GL_ARRAY_BUFFER, (GLuint)pVertexBuffer->GetData());
			uint8_t *offset = nullptr;
			if(vertexFormat & VertexBuffer::eVF_XYZ)
			{
				glEnableClientState(GL_VERTEX_ARRAY);
				glVertexPointer(3, GL_FLOAT, vertexSize, offset);
				offset += 3 * sizeof(float);
			}
			if(vertexFormat & VertexBuffer::eVF_Normal)
			{
				glEnableClientState(GL_NORMAL_ARRAY);
				glNormalPointer(GL_FLOAT, vertexSize, offset);
				offset += 3 * sizeof(float);
			}
			if(vertexFormat & VertexBuffer::eVF_Diffuse)
			{
				glEnableClientState(GL_COLOR_ARRAY);
				glNormalPointer(GL_FLOAT, vertexSize, offset);
				offset += 4 * sizeof(float);
			}
			if(vertexFormat & VertexBuffer::eVF_Tex0)
			{	
				glClientActiveTexture(GL_TEXTURE0);
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glTexCoordPointer(2, GL_FLOAT, vertexSize, offset);
				offset += 2 * sizeof(float);
			}
		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::UseIndexBuffer( IndexBuffer *pIndexBuffer )
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (GLuint)pIndexBuffer->GetData());
		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::UsePrimitiveTopology( PrimitiveTopology primitiveTopology )
		{
			// Not available
		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::UseShader( Shader *pShader )
		{
			glAttachShader(m_shaderProgramId, (GLuint)pShader->GetCompiledShader());
			glLinkProgram(m_shaderProgramId);
			glUseProgram(m_shaderProgramId);
		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::EnableDepthBuffer()
		{
			glEnable(GL_DEPTH_TEST);
		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::DisableDepthBuffer()
		{
			glDisable(GL_DEPTH_TEST);
		}

	} // namespace Render
} // namespace Oak3D

#endif // OAK3D_RENDERER_OPENGL
