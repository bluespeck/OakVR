
#if OAK3D_RENDERER == OAK3D_RENDERER_OPENGL

// include the OpenGL library file
//#pragma comment (lib, "Opengl32.lib")

#include <cassert>



#include <windows.h>
#include <wingdi.h>
//#include <GLEW/include/GL/glew.h>
#include <gl/gl.h>
#include <gl/glu.h>
//#include <SOIL/include/SOIL.h>

//#include <gl/wglext.h>


//#include "Oak3D/Engine.h"

#include "OpenGLRenderer.h"
#include "OpenGLDebugTextRenderer.h"

#include "Renderer/IRenderer/RenderWindow.h"
#include "Renderer/IRenderer/RendererUtils.h"
#include "Renderer/IRenderer/VertexBuffer.h"
#include "Renderer/IRenderer/IndexBuffer.h"
#include "Renderer/IRenderer/Texture.h"
#include "Renderer/IRenderer/Color.h"

#include "Math/Matrix.h"
#include "Math/Transform.h"
#include "Renderer/IRenderer/Shader.h"

#include "FileIO/File.h"
//#include "ResourceManager/Image.h"


namespace Oak3D
{
	namespace Render
	{
		// --------------------------------------------------------------------------------
		OpenGLRenderer::OpenGLRenderer()
			: m_pDevice(nullptr)
			, m_pCurrentVertexBuffer(nullptr)
			, m_pCurrentIndexBuffer(nullptr)
			, m_bPerspectiveProjection(true)
		{			
		}

		// --------------------------------------------------------------------------------
		void OpenGLRenderer::Initialize()
		{
			m_mainThreadId = GetCurrentThreadId();
			HWND hWnd = reinterpret_cast<HWND>(m_pRenderWindow->GetOSHandle());
			HDC hdc = GetDC(hWnd);

			SetWindowTextW(hWnd, L"Oak3D [OpenGL]");
			/////
			// create OpenGL device

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
						
//			assert(glewInit() == GLEW_OK);
						
			InitializeStateObjects();

//			m_shaderProgramId = glCreateProgram();

			m_bInitialized = true;
		}

		// --------------------------------------------------------------------------------
		void OpenGLRenderer::InitializeStateObjects()
		{
			/////
			// create projection matrices
			m_pPerspectiveProjectionMatrix = new Math::Matrix();
			m_pOrthographicProjectionMatrix = new Math::Matrix();
			glMatrixMode(GL_PROJECTION);
			*m_pPerspectiveProjectionMatrix = Math::Transform::CreatePerspectiveProjectionTransform(3.141592f * 0.25f, 1.25f, 1.0f, 1000.0f);
			*m_pOrthographicProjectionMatrix = Math::Transform::CreateOthographicProjectionTransform(0.0f, (float)m_pRenderWindow->GetWidth(), 0.0f, (float)m_pRenderWindow->GetHeight(), 1.0f, 1000.0f);
			

			glCullFace(GL_BACK);
			glFrontFace(GL_CW);
			glEnable(GL_CULL_FACE);
		}

		// --------------------------------------------------------------------------------
		void OpenGLRenderer::ClearBackground(const Color &color)
		{
			glClearColor(color.r, color.g, color.b, color.a);
			glClear(GL_COLOR_BUFFER_BIT);
		}

		// --------------------------------------------------------------------------------
		void OpenGLRenderer::BeginDraw()
		{
			m_pCurrentIndexBuffer = nullptr;
			m_pCurrentVertexBuffer = nullptr;
			m_pCurrentVertexShader = nullptr;
			m_pCurrentPixelShader = nullptr;
		}
		
		// --------------------------------------------------------------------------------
		void OpenGLRenderer::EndDraw()
		{

		}

		// --------------------------------------------------------------------------------
		void OpenGLRenderer::SwapBuffers()
		{
			::SwapBuffers(wglGetCurrentDC());
		}

		// --------------------------------------------------------------------------------
		void OpenGLRenderer::Cleanup()
		{	
			wglMakeCurrent (NULL, NULL) ; 
			wglDeleteContext ((HGLRC)m_pDevice);
			wglDeleteContext( (HGLRC)m_pWorkerThreadDevice);
		}

		// --------------------------------------------------------------------------------
		void OpenGLRenderer::Update(float dt)
		{

		}

		// --------------------------------------------------------------------------------
		void OpenGLRenderer::CreateShader(Shader *pShader)
		{
			if(GetCurrentThreadId() != m_mainThreadId)
				wglMakeCurrent(GetDC(reinterpret_cast<HWND>(m_pRenderWindow->GetOSHandle())), (HGLRC)m_pWorkerThreadDevice);

//			GLenum shaderType;
			switch(pShader->GetType())
			{
			case eST_VertexShader:
//				shaderType = GL_VERTEX_SHADER;
				break;
			case eST_PixelShader:
//				shaderType = GL_FRAGMENT_SHADER;
				break;
			default:
				assert("Unknown shader type" && 0);
				break;
			}

/*			GLuint shaderId = glCreateShaderObjectARB(shaderType);
			
			Core::File file(pShader->GetId().GetStrId());
			const uint32_t buffSize = file.Size();
			uint8_t *buff = new uint8_t[buffSize];
			
			file.Open(Core::File::eFOM_OpenRead);			
			int charsRead = file.Read(buff, buffSize, 0);
			buff[charsRead] = 0;

			const GLcharARB * sources[1];
			const GLint lengths[1] = {charsRead};
			sources[0] = (GLcharARB *) buff;

			glShaderSourceARB(shaderId, 1, sources, lengths);

			glCompileShaderARB(shaderId);
			GLint compileSuccessfull;
			glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileSuccessfull);
			if( compileSuccessfull == GL_FALSE)
			{
				GLcharARB infoLog[1024];
				GLsizei charsWritten;
				glGetInfoLogARB(shaderId, 1024, &charsWritten, infoLog);
				infoLog[charsWritten] = 0;
				printf("[Oak3D] OpenGL shader compilation has failed: %s\n", infoLog);
				exit(1);
			}

			pShader->SetCompiledShader((void *)shaderId);

			delete[] buff;
			file.Close();
			*/
		}

		// --------------------------------------------------------------------------------
		void OpenGLRenderer::ReleaseShader(Shader *pShader)
		{
			if(pShader == nullptr)
				return;
//			glDeleteShader((GLuint)pShader->GetCompiledShader());
		}

		// --------------------------------------------------------------------------------
		void OpenGLRenderer::CreateTexture( Texture *pTexture )
		{
			if(GetCurrentThreadId() != m_mainThreadId)
				wglMakeCurrent(GetDC(reinterpret_cast<HWND>(m_pRenderWindow->GetOSHandle())), (HGLRC)m_pWorkerThreadDevice);

			GLuint texId;

			glGenTextures(1, &texId);
			
//			Oak3D::Core::Image *pImage = Oak3D::Engine::GetResourceManager()->GetResource<Oak3D::Core::Image>(pTexture->GetId().GetStrId().c_str());
			// Separate resources on unique threads
//			assert("Could not load texture from file!" && texId > 0);

			pTexture->SetData((void *)texId);

			glBindTexture(GL_TEXTURE_2D, texId);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}

		// --------------------------------------------------------------------------------
		void OpenGLRenderer::ReleaseTexture( Texture *pTexture )
		{
			GLuint tex = (GLuint)pTexture->GetData();
			glDeleteTextures(1, &tex);
		}

		// --------------------------------------------------------------------------------
		void OpenGLRenderer::UseTexture ( Texture *texture )
		{
			if(texture != nullptr)
			{
				glEnable( GL_TEXTURE_2D );
				glBindTexture(GL_TEXTURE_2D, (GLuint) texture->GetData());
			}
			else
			{
				glDisable( GL_TEXTURE_2D);
			}
			
		}

		// --------------------------------------------------------------------------------
		void OpenGLRenderer::DrawPrimitives(uint32_t numPrimitives, uint32_t startVertex /* = 0 */)
		{
			GLenum pt;
			switch( m_currentPrimitiveTopology )
			{
			case ePT_PointList:
				pt = GL_POINTS;
				break;
			case ePT_LineList:
				pt = GL_LINES;
				break;
			case ePT_LineStrip:
				pt = GL_LINE_STRIP;
				break;
			case ePT_TriangleList:
				pt = GL_TRIANGLES;
				break;
			case ePT_TriangleStrip:
				pt = GL_TRIANGLE_STRIP;
				break;
			default:
				assert("Unknown primitive topology" && 0);
				break;
			}

			SetMatrices();
			
			UseShaderProgram();

			glDrawArrays(pt, startVertex, numPrimitives * m_numVerticesPerPrimitive);
			
		}

		// --------------------------------------------------------------------------------
		void OpenGLRenderer::UseShaderProgram()
		{
/*			if(!m_pCurrentVertexShader || !m_pCurrentVertexShader->IsReady() || !m_pCurrentPixelShader || !m_pCurrentPixelShader->IsReady())
			{
				glUseProgramObjectARB(0);
				return;
			}
			
			glAttachObjectARB(m_shaderProgramId, (GLuint)m_pCurrentVertexShader->GetCompiledShader());
			glAttachObjectARB(m_shaderProgramId, (GLuint)m_pCurrentPixelShader->GetCompiledShader());
			
			glLinkProgramARB(m_shaderProgramId);
			GLint linkSuccess;
			glGetProgramiv(m_shaderProgramId, GL_LINK_STATUS, &linkSuccess);
			if(!linkSuccess)
			{
				GLcharARB infoLog[1024];
				GLsizei charsWritten;
				glGetInfoLogARB(m_shaderProgramId, 1024, &charsWritten, infoLog);
				infoLog[charsWritten] = 0;
				printf("[Oak3D] OpenGL shader program link has failed: %s\n", infoLog);
				exit(1);
			}
			
			glUseProgramObjectARB(m_shaderProgramId);
*/
		}

		// --------------------------------------------------------------------------------
		void OpenGLRenderer::DrawIndexedPrimitives(uint32_t numPrimitives, uint32_t /*numVertices*/ , uint32_t startIndex /* = 0 */, uint32_t startVertex /* = 0 */)
		{
			uint8_t numIndicesPerPrimitive = 0;
			GLenum pt;
			switch( m_currentPrimitiveTopology )
			{
			case ePT_PointList:
				numIndicesPerPrimitive = 1;
				pt = GL_POINTS;
				break;
			case ePT_LineList:
				pt = GL_LINES;
				numIndicesPerPrimitive = 2;
				break;
			case ePT_LineStrip:
				pt = GL_LINE_STRIP;
				numIndicesPerPrimitive = 2;
				break;
			case ePT_TriangleList:
				pt = GL_TRIANGLES;
				numIndicesPerPrimitive = 3;
				break;
			case ePT_TriangleStrip:
				pt = GL_TRIANGLE_STRIP;
				numIndicesPerPrimitive = 3;
				break;
			default:
				assert("Unknown primitive topology" && 0);
				break;
			}

			SetMatrices();

			UseShaderProgram();

			// TODO figure out how to set first index and first vertex to use from the buffers
			glDrawElements(pt, numIndicesPerPrimitive * numPrimitives, GL_UNSIGNED_INT, 0);
			if(glGetError() != GL_NO_ERROR)
			{
				printf("glDrawElements error!");
			}
			
		}

		void OpenGLRenderer::SetMatrices()
		{
			glMatrixMode(GL_PROJECTION);
			glLoadMatrixf(m_bPerspectiveProjection ? (GLfloat *)m_pPerspectiveProjectionMatrix : (GLfloat *)m_pOrthographicProjectionMatrix);
			glMatrixMode(GL_MODELVIEW);
			glLoadMatrixf((GLfloat *)m_pViewMatrix);
		}

		// --------------------------------------------------------------------------------
		void OpenGLRenderer::CreateVertexBuffer( VertexBuffer *pVertexBuffer )
		{
/*			GLuint vbId; 
			glGenBuffersARB(1, &vbId);
			glBindBufferARB(GL_ARRAY_BUFFER, vbId);
			glBufferDataARB(GL_ARRAY_BUFFER, pVertexBuffer->GetVertexSize() * pVertexBuffer->GetVertexCount(), nullptr, GL_DYNAMIC_DRAW);
			pVertexBuffer->SetData((void *)vbId);
*/
		}

		// --------------------------------------------------------------------------------
		void OpenGLRenderer::LockVertexBuffer( VertexBuffer *pVertexBuffer, void **ppBuff, uint32_t /*offsetToLock*/, uint32_t /*sizeToLock*/, uint32_t flags )
		{	
/*			int oldId = 0;
			glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &oldId);
			glBindBufferARB(GL_ARRAY_BUFFER, (int)pVertexBuffer->GetData());
			*ppBuff = glMapBufferARB(GL_ARRAY_BUFFER, GL_READ_WRITE);
			glBindBufferARB(GL_ARRAY_BUFFER, oldId);
*/
		}

		// --------------------------------------------------------------------------------
		void OpenGLRenderer::UnlockVertexBuffer( VertexBuffer *pVertexBuffer )
		{	
/*			int oldId = 0;
			glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &oldId);
			glBindBufferARB(GL_ARRAY_BUFFER, (int)pVertexBuffer->GetData());
			glUnmapBufferARB(GL_ARRAY_BUFFER);
			glBindBufferARB(GL_ARRAY_BUFFER, oldId);
			*/
		}

		// --------------------------------------------------------------------------------
		void OpenGLRenderer::ReleaseVertexBuffer( VertexBuffer *pVertexBuffer )
		{
/*			GLuint id = (GLuint)pVertexBuffer->GetData();
			glDeleteBuffersARB(1, &id);
			*/
		}

		// --------------------------------------------------------------------------------
		void OpenGLRenderer::CreateIndexBuffer( IndexBuffer *pIndexBuffer )
		{
			/*GLuint ibId; 
			glGenBuffersARB(1, &ibId);
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, ibId);
			glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER, pIndexBuffer->GetIndexSize() * pIndexBuffer->GetIndexCount(), NULL, GL_DYNAMIC_DRAW);

			pIndexBuffer->SetData((void *)ibId);
			*/
		}

		// --------------------------------------------------------------------------------
		void OpenGLRenderer::LockIndexBuffer( IndexBuffer *pIndexBuffer, void **ppBuff, uint32_t offsetToLock, uint32_t sizeToLock, uint32_t flags )
		{	/*
			int oldId = 0;
			glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &oldId);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (int)pIndexBuffer->GetData());
			*ppBuff = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_READ_WRITE);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, oldId);
			*/
		}

		// --------------------------------------------------------------------------------
		void OpenGLRenderer::UnlockIndexBuffer( IndexBuffer *pIndexBuffer )
		{	
			/*
			int oldId = 0;
			glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &oldId);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (int)pIndexBuffer->GetData());
			glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, oldId);
			*/
		}

		// --------------------------------------------------------------------------------
		void OpenGLRenderer::ReleaseIndexBuffer( IndexBuffer *pIndexBuffer )
		{
			/*
			GLuint id = (GLuint)pIndexBuffer->GetData();
			glDeleteBuffers(1, &id);
			*/
		}

		// --------------------------------------------------------------------------------
		void OpenGLRenderer::OutputText( const std::string &text, uint32_t x, uint32_t y)
		{
			m_pDebugTextRenderer->OutputText(text, x, y);
		}

		// --------------------------------------------------------------------------------
		void OpenGLRenderer::CreateInputLayoutDesc(uint32_t vertexFormat, void *&pLayoutDesc, uint32_t &numElems)
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
		void OpenGLRenderer::UseVertexBuffer( VertexBuffer *pVertexBuffer )
		{
			if(!pVertexBuffer)
			{
//				glBindBufferARB(GL_ARRAY_BUFFER, 0);
				return;
			}
			
			uint32_t vertexFormat = pVertexBuffer->GetVertexFormat();
			uint32_t vertexSize = pVertexBuffer->GetVertexSize();
//			glBindBufferARB(GL_ARRAY_BUFFER, (GLuint)pVertexBuffer->GetData());
			m_pCurrentVertexBuffer = pVertexBuffer;
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
//				glClientActiveTexture(GL_TEXTURE0);
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glTexCoordPointer(2, GL_FLOAT, vertexSize, offset);
				offset += 2 * sizeof(float);
			}
		}

		// --------------------------------------------------------------------------------
		void OpenGLRenderer::UseIndexBuffer( IndexBuffer *pIndexBuffer )
		{
/*			if(!pIndexBuffer)
				glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, 0);
			else
				glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, (GLuint)pIndexBuffer->GetData());
*/			m_pCurrentIndexBuffer = pIndexBuffer;
		}

		// --------------------------------------------------------------------------------
		void OpenGLRenderer::UsePrimitiveTopology( PrimitiveTopology primitiveTopology )
		{
			m_currentPrimitiveTopology = primitiveTopology;
			switch(primitiveTopology)
			{
			case ePT_PointList:
				m_numVerticesPerPrimitive = 1;
				break;
			case ePT_LineList:
				m_numVerticesPerPrimitive = 2;
				break;
			case ePT_LineStrip:
				m_numVerticesPerPrimitive = 2;
				break;
			case ePT_TriangleList:
				m_numVerticesPerPrimitive = 3;
				break;
			case ePT_TriangleStrip:
				m_numVerticesPerPrimitive = 3;
				break;
			default:
				break;
			}
		}

		// --------------------------------------------------------------------------------
		void OpenGLRenderer::UseShader( Shader *pShader )
		{
			
			if(pShader->GetType() == eST_VertexShader)
			{
				m_pCurrentVertexShader = pShader;
			}
			else if (pShader->GetType() == eST_PixelShader)
			{
				m_pCurrentPixelShader = pShader;
			}
		}

		// --------------------------------------------------------------------------------
		void OpenGLRenderer::EnableDepthBuffer()
		{
			glEnable(GL_DEPTH_TEST);
		}

		// --------------------------------------------------------------------------------
		void OpenGLRenderer::DisableDepthBuffer()
		{
			glDisable(GL_DEPTH_TEST);
		}

		// --------------------------------------------------------------------------------
		Oak3D::Math::Matrix OpenGLRenderer::CreateViewMatrix(Oak3D::Math::Vector3 eye, Oak3D::Math::Vector3 lookAt, Oak3D::Math::Vector3 up)
		{
			Oak3D::Math::Vector3 look = (lookAt - eye).GetNormalized();
			Oak3D::Math::Vector3 right = look.Cross(up).GetNormalized();
			Oak3D::Math::Matrix mat;
			mat._11 = right.x;
			mat._12 = right.y;
			mat._13 = right.z;
			mat._14 = 0.0f;

			mat._21 = up.x;
			mat._22 = up.y;
			mat._23 = up.z;
			mat._24 = 0.0f;

			mat._31 = look.x;
			mat._32 = look.y;
			mat._33 = look.z;
			mat._34 = 0.0f;

			mat._41 = eye.Dot(right);
			mat._42 = eye.Dot(up);
			mat._43 = eye.Dot(look);
			mat._44 = 1.0f;

			return mat;
		}

		// --------------------------------------------------------------------------------
		void OpenGLRenderer::EnableOrtographicProjection()
		{
			m_bPerspectiveProjection = false;
		}
		
		// --------------------------------------------------------------------------------
		void OpenGLRenderer::EnablePerspectiveProjection()
		{
			m_bPerspectiveProjection = true;
		}

		// --------------------------------------------------------------------------------
		void OpenGLRenderer::EnableFillWireframe()
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}

		// --------------------------------------------------------------------------------
		void OpenGLRenderer::EnableFillSolid()
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

	} // namespace Render
} // namespace Oak3D

#endif // OAK3D_RENDERER_OPENGL
