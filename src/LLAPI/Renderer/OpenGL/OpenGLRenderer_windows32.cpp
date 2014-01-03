
#include "Common.h"
#include "Renderer/Renderer/Renderer.h"

#include "Renderer/Renderer/RendererCommon.h"
#include "Renderer/Renderer/RendererUtils.h"
#include "Renderer/Renderer/VertexBuffer.h"
#include "Renderer/Renderer/IndexBuffer.h"
#include "Renderer/Renderer/Texture.h"
#include "Renderer/Renderer/Color.h"

#include "Math/Matrix.h"
#include "Math/Transform.h"
#include "Renderer/Renderer/Shader.h"

#include "FileIO/File.h"
#include "Log/Log.h"
//#include "ResourceManager/Image.h"

#include <cassert>
#include <memory>


namespace oakvr
{
	namespace render
	{
		class Renderer::RendererImpl
		{
		public:

			HGLRC m_hRenderContext;             // OpenGL device interface (context)
			void *m_pWorkerThreadDevice;		// worker thread context
			long m_mainThreadId;
			long m_shaderProgramId;
		};

		// --------------------------------------------------------------------------------
		Renderer::Renderer()
			: m_pImpl{ new RendererImpl() }
		{
		}

		Renderer::~Renderer()
		{

		}

		// --------------------------------------------------------------------------------
		bool Renderer::Initialize()
		{
			//m_mainThreadId = GetCurrentThreadId();
			HWND hWnd = reinterpret_cast<HWND>(m_pRenderWindow->GetOSHandle());
			
			//SetWindowTextA(hWnd, "oakvr [OpenGL]");

			HDC hdc = GetDC(hWnd);

			/////
			// create OpenGL device


			PIXELFORMATDESCRIPTOR pfd = { 0 };
			pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
			pfd.nVersion = 1;
			pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
			pfd.iPixelType = PFD_TYPE_RGBA;
			pfd.cRedBits = 8;
			pfd.cGreenBits = 8;
			pfd.cBlueBits = 8;
			pfd.cColorBits = 24;
			pfd.cAlphaBits = 8;
			pfd.cDepthBits = 24;
			pfd.cStencilBits = 8;
			pfd.iLayerType = PFD_MAIN_PLANE;

			int  iPixelFormat;

			// get the device context's best, available pixel format match  
			iPixelFormat = ChoosePixelFormat(hdc, &pfd);

			// make that match the device context's current pixel format  
			SetPixelFormat(hdc, iPixelFormat, &pfd);

			m_pImpl->m_hRenderContext = wglCreateContext(hdc);

			if (!m_pImpl->m_hRenderContext)
			{
				Log::PrintInfo("WGL context creation failed!");
				return false;
			}
			
			if(FALSE == wglMakeCurrent(hdc, (HGLRC)m_pImpl->m_hRenderContext))
			{
				Log::PrintInfo("WGL context could not be made current on the current thread!");
				return false;
			}
			
			
			//			m_shaderProgramId = glCreateProgram();

			glCullFace(GL_BACK);
			glFrontFace(GL_CW);
			glEnable(GL_CULL_FACE);
			ReleaseDC(hWnd, hdc);

			Log::PrintInfo("OpenGL renderer successfully initialized!");
			m_bInitialized = true;

			return true;
		}

		void Renderer::SetRenderWindow(std::shared_ptr<RenderWindow> pRenderWindow)
		{
			m_pRenderWindow = pRenderWindow;
		}

		// --------------------------------------------------------------------------------
		void Renderer::ClearBackground(const Color &color)
		{
			glClearColor(color.r, color.g, color.b, color.a);
			glClear(GL_COLOR_BUFFER_BIT);
		}

		// --------------------------------------------------------------------------------
		void Renderer::BeginDraw()
		{

		}

		// --------------------------------------------------------------------------------
		void Renderer::EndDraw()
		{

		}

		// --------------------------------------------------------------------------------
		void Renderer::Cleanup()
		{
#	if defined(OAKVR_WINDOWS32) || defined(OAKVR_WINDOWS64)
			wglMakeCurrent(NULL, NULL);
			wglDeleteContext((HGLRC)m_pImpl->m_hRenderContext);
#	else


#	endif
		}

		// --------------------------------------------------------------------------------
		void Renderer::Update(float dt)
		{
			static VertexBuffer vb;
			vb.Create(3, 3 * sizeof(float));


			m_pRenderWindow->SwapBuffers();
		}

		// --------------------------------------------------------------------------------
		void Renderer::CreateShader(Shader *pShader)
		{
#	if defined(OAKVR_WINDOWS32) || defined(OAKVR_WINDOWS64)
			//if (GetCurrentThreadId() != m_mainThreadId)
			//{
			//	wglMakeCurrent(GetDC(reinterpret_cast<HWND>(m_pRenderWindow->GetOSHandle())), (HGLRC)m_pWorkerThreadDevice);
			//}
#	else

#	endif
			//			GLenum shaderType;
			switch (pShader->GetType())
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
			printf("[oakvr] OpenGL shader compilation has failed: %s\n", infoLog);
			exit(1);
			}

			pShader->SetCompiledShader((void *)shaderId);

			delete[] buff;
			file.Close();
			*/
		}

		// --------------------------------------------------------------------------------
		void Renderer::ReleaseShader(Shader *pShader)
		{
			if (pShader == nullptr)
				return;
			//			glDeleteShader((GLuint)pShader->GetCompiledShader());
		}

		// --------------------------------------------------------------------------------
		void Renderer::CreateTexture(Texture *pTexture)
		{
#	if defined(OAKVR_WINDOWS32) || defined(OAKVR_WINDOWS64)
//			if (GetCurrentThreadId() != m_mainThreadId)
//				wglMakeCurrent(GetDC(reinterpret_cast<HWND>(m_pRenderWindow->GetOSHandle())), (HGLRC)m_pWorkerThreadDevice);
#	endif
			GLuint texId;

			glGenTextures(1, &texId);

			//			oakvr::Core::Image *pImage = oakvr::Engine::GetResourceManager()->GetResource<oakvr::Core::Image>(pTexture->GetId().GetStrId().c_str());
			// Separate resources on unique threads
			//			assert("Could not load texture from file!" && texId > 0);

			pTexture->SetData((void *)texId);

			glBindTexture(GL_TEXTURE_2D, texId);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}

		// --------------------------------------------------------------------------------
		void Renderer::ReleaseTexture(Texture *pTexture)
		{
			GLuint tex = (GLuint)pTexture->GetData();
			glDeleteTextures(1, &tex);
		}

		// --------------------------------------------------------------------------------
		void Renderer::UseTexture(Texture *texture)
		{
			if (texture != nullptr)
			{
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, reinterpret_cast<GLuint>(texture->GetData()));
			}
			else
			{
				glDisable(GL_TEXTURE_2D);
			}

		}

		// --------------------------------------------------------------------------------
		void Renderer::DrawPrimitives(uint32_t numPrimitives, uint32_t startVertex /* = 0 */)
		{
			//GLenum pt;

			//SetMatrices();

			//UseShaderProgram();

			//glDrawArrays(pt, startVertex, numPrimitives * m_numVerticesPerPrimitive);
			glDrawArrays(GL_TRIANGLES, startVertex, numPrimitives * 3);
		}

		// --------------------------------------------------------------------------------
		/*		void Renderer::UseShaderProgram()
		{
		if(!m_pCurrentVertexShader || !m_pCurrentVertexShader->IsReady() || !m_pCurrentPixelShader || !m_pCurrentPixelShader->IsReady())
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
		printf("[oakvr] OpenGL shader program link has failed: %s\n", infoLog);
		exit(1);
		}

		glUseProgramObjectARB(m_shaderProgramId);

		}
		*/
		// --------------------------------------------------------------------------------
		void Renderer::DrawIndexedPrimitives(uint32_t numPrimitives, uint32_t /*numVertices*/, uint32_t startIndex /* = 0 */, uint32_t startVertex /* = 0 */)
		{
			/*	uint8_t numIndicesPerPrimitive = 0;
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
			*/

			glDrawArrays(GL_TRIANGLES, startVertex, numPrimitives * 3);
		}

		// --------------------------------------------------------------------------------
		void Renderer::CreateIndexBuffer(IndexBuffer *pIndexBuffer)
		{
			/*GLuint ibId;
			glGenBuffersARB(1, &ibId);
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, ibId);
			glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER, pIndexBuffer->GetIndexSize() * pIndexBuffer->GetIndexCount(), NULL, GL_DYNAMIC_DRAW);

			pIndexBuffer->SetData((void *)ibId);
			*/
		}

		// --------------------------------------------------------------------------------
		void Renderer::LockIndexBuffer(IndexBuffer *pIndexBuffer, void **ppBuff, uint32_t offsetToLock, uint32_t sizeToLock, uint32_t flags)
		{	/*
			int oldId = 0;
			glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &oldId);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (int)pIndexBuffer->GetData());
			*ppBuff = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_READ_WRITE);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, oldId);
			*/
		}

		// --------------------------------------------------------------------------------
		void Renderer::UnlockIndexBuffer(IndexBuffer *pIndexBuffer)
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
		void Renderer::ReleaseIndexBuffer(IndexBuffer *pIndexBuffer)
		{
			/*
			GLuint id = (GLuint)pIndexBuffer->GetData();
			glDeleteBuffers(1, &id);
			*/
		}

		/*		// --------------------------------------------------------------------------------
		void Renderer::CreateInputLayoutDesc(uint32_t vertexFormat, void *&pLayoutDesc, uint32_t &numElems)
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

		}
		*/

		// --------------------------------------------------------------------------------
		void Renderer::UseIndexBuffer(IndexBuffer *pIndexBuffer)
		{
			/*			if(!pIndexBuffer)
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, 0);
			else
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, (GLuint)pIndexBuffer->GetData());
			m_pCurrentIndexBuffer = pIndexBuffer;
			*/
		}

		/*		// --------------------------------------------------------------------------------
		void Renderer::UsePrimitiveTopology( PrimitiveTopology primitiveTopology )
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
		*/
		// --------------------------------------------------------------------------------
		void Renderer::UseShader(Shader *pShader)
		{
			/*
			if(pShader->GetType() == eST_VertexShader)
			{
			m_pCurrentVertexShader = pShader;
			}
			else if (pShader->GetType() == eST_PixelShader)
			{
			m_pCurrentPixelShader = pShader;
			}
			*/
		}

		/*		// --------------------------------------------------------------------------------
		void Renderer::EnableDepthBuffer()
		{
		glEnable(GL_DEPTH_TEST);
		}

		// --------------------------------------------------------------------------------
		void Renderer::DisableDepthBuffer()
		{
		glDisable(GL_DEPTH_TEST);
		}

		// --------------------------------------------------------------------------------
		oakvr::Math::Matrix Renderer::CreateViewMatrix(oakvr::Math::Vector3 eye, oakvr::Math::Vector3 lookAt, oakvr::Math::Vector3 up)
		{
		oakvr::Math::Vector3 look = (lookAt - eye).GetNormalized();
		oakvr::Math::Vector3 right = look.Cross(up).GetNormalized();
		oakvr::Math::Matrix mat;
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
		void Renderer::EnableOrtographicProjection()
		{
		m_bPerspectiveProjection = false;
		}

		// --------------------------------------------------------------------------------
		void Renderer::EnablePerspectiveProjection()
		{
		m_bPerspectiveProjection = true;
		}

		// --------------------------------------------------------------------------------
		void Renderer::EnableFillWireframe()
		{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}

		// --------------------------------------------------------------------------------
		void Renderer::EnableFillSolid()
		{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		*/
	} // namespace render
} // namespace oakvr

