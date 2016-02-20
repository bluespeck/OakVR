#include "Dae2Oak.h"

#include "Utils/Buffer.h"
#include "Utils/BufferReader.h"
#include "Utils/BufferWriter.h"
#include "Utils/RenderUtils.h"
#include "Windows.h"
#include <TinyXML2/tinyxml2.h>

#include <fstream>
#include <algorithm>
#include <sstream>
#include <type_traits>
#include <tuple>

namespace oakvr
{
	namespace tools
	{
		/* oakvr mesh format:
				signature: 4 bytes (OKVR)
				numberOfSubmeshes: 4 bytes
				submeshOffset: 4 bytes	| repeat numberOfSubmeshes times
				submeshSize: 4 bytes	|

				------ submesh 0
				numberOfVertices: 4 bytes
				numberOfChannels: 4 byte
				channeltypes: numberOfChannels bytes
				vertices: numberOfVertices * (numberOfChannels  * channelsize[channel])

				numberOfIndices: 4 bytes
				indexStride: 4 bytes
				primitiveTopology: 4 bytes
				indices: numberOfIndices * indexStride

				numberOfTextures: 4 bytes
					textureNameLength: 4 bytes				| repeat numberOfTextures times
					textureName: textureNameLength bytes	|

				materialNameLength: 4 bytes
				materialName: materialNameLength
				
				------ end submesh 0
				------ submesh 1
				...
				------ end submesh 1
				...


		*/

		unsigned int CountChildElems(tinyxml2::XMLElement *pElem, const std::string &childElemName)
		{
			unsigned int count = 0;
			for (auto it = pElem->FirstChildElement(childElemName.c_str()); it; it = it->NextSiblingElement(childElemName.c_str()))
				++count;
			return count;
		}

		auto SourcesAsVertexBuffer(std::vector<std::pair<oakvr::render::VertexElementDescriptor::Semantic, std::vector<float>>> &&sources, std::vector< uint32_t > &indices)
			-> oakvr::core::MemoryBuffer
		{
			std::vector<uint32_t> strides;	// in floats
			uint32_t vertexStride = 0; // in bytes

			// Create vertex description
			for (const auto &e : sources)
			{
				uint32_t channelStride = oakvr::render::VertexElementDescriptor(e.first).size;
				vertexStride += channelStride;
				strides.emplace_back(channelStride / sizeof(float));
			}

			oakvr::core::MemoryBuffer mb(sizeof(uint32_t) + sizeof(uint32_t) + sources.size() * sizeof(oakvr::render::VertexElementDescriptor::Semantic) + indices.size() / sources.size() * vertexStride);
			auto buffWriter = oakvr::core::MakeBufferWriter(mb);
			
			// numberOfVertices
			buffWriter.Write(static_cast<uint32_t>(indices.size() / sources.size() ));

			// numberOfChannels
			buffWriter.Write(static_cast<uint32_t>(sources.size()));

			// channel types
			for (auto &e : sources)
			{
				buffWriter.Write(e.first);
			}

			// vertex data
			for (size_t i = 0; i < indices.size(); i += sources.size())
			{
				for (size_t sourceIndex = 0; sourceIndex < sources.size(); ++sourceIndex)
				{
					if (sources[sourceIndex].first != oakvr::render::VertexElementDescriptor::Semantic::color)
						for (size_t floatIndex = 0; floatIndex < strides[sourceIndex]; ++floatIndex)
							buffWriter.Write(sources[sourceIndex].second[indices[i + sourceIndex] * strides[sourceIndex] + floatIndex]);
					else
					{
						for (size_t floatIndex = 0; floatIndex < 3; ++floatIndex)
							buffWriter.Write(sources[sourceIndex].second[indices[i + sourceIndex] * 3 + floatIndex]);
						buffWriter.Write(1.0f);
					}
				}
			}
			
			return mb;
			/*
			//------submesh 0
			//	numberOfVertices: 4 bytes
			//	numberOfChannels : 4 bytes
			//	channeltypes : numberOfChannels bytes
			//	vertices : numberOfVertices * (numberOfChannels  * channelsize[channel])
			auto it = std::find_if(sources.begin(), sources.end(), [](std::pair<oakvr::render::VertexElementDescriptor::Semantic, std::vector<float>> &e)->bool
				{ return e.first == oakvr::render::VertexElementDescriptor::Semantic::position; }
			);
			if (it != sources.end())
			{
				std::vector<uint32_t> strides;
				uint32_t vertexStride = 0;
				std::vector<size_t> sourcePositions;
				// Create vertex description
				for (const auto &e : sources)
				{
					uint32_t channelStride = oakvr::render::VertexElementDescriptor(e.first).size;
					vertexStride += channelStride;
					strides.emplace_back(channelStride);
					sourcePositions.emplace_back(0);	// initialize all to 0 here and adjust later
				}

				// numberOfVertices
				size_t numVertices = it->second.size() / 3;
				
				oakvr::core::MemoryBuffer mb(sizeof(uint32_t) + sizeof(uint32_t) + sources.size() * sizeof(oakvr::render::VertexElementDescriptor::Semantic) + numVertices * vertexStride);
				auto buffWriter = oakvr::core::MakeBufferWriter(mb);

				buffWriter.Write(static_cast<uint32_t>(numVertices));
				// numberOfChannels
				buffWriter.Write(static_cast<uint32_t>(sources.size()));
				// channel types
				for (auto &e : sources)
				{
					buffWriter.Write(e.first);
				}

				for (size_t i = 0; i < numVertices; ++i)
				{
					int index = i * sources.size();
					for (size_t j = 0; j < sources.size(); ++j)
					{
						std::string outputStr = std::string("\n") + std::to_string(index) + std::string(" --- ") + std::to_string(sources[j].second[indices[index + j] * strides[j] / 4]);
						OutputDebugString(outputStr.c_str());
						buffWriter.Write(&(sources[j].second[indices[index + j] * strides[j] / 4]), strides[j]);
						// here the number of vertices used by the mesh is different from the initial source provided...
						// so use another buffer to write these into and count them; iterate over indices instead of vertices
						// actually no... use vertices, and if you find doubles, just add those also... the whole function should change
					}
				}
				return mb;
			}
			
			oakvr::core::MemoryBuffer mb(sizeof(uint32_t) + sizeof(uint32_t));
			auto buffWriter = oakvr::core::MakeBufferWriter(mb);

			buffWriter.Write(static_cast<uint32_t>(0));
			buffWriter.Write(static_cast<uint32_t>(0));
			
			return mb;
			*/
		}

		auto ReadDaeSources(tinyxml2::XMLElement *submeshElement, std::vector<std::pair<std::string, oakvr::render::VertexElementDescriptor::Semantic>> &&inputChannels)
			-> std::vector<std::pair<oakvr::render::VertexElementDescriptor::Semantic, std::vector<float>>>
		{
			decltype(ReadDaeSources(submeshElement, std::move(inputChannels))) sources;

			for (auto sourceElem = submeshElement->FirstChildElement("source"); sourceElem; sourceElem = sourceElem->NextSiblingElement("source"))
			{
				std::string id = sourceElem->Attribute("id");
				for (auto &e : inputChannels)
				{
					const std::string channelId = e.first.substr(1);
					if (channelId == id)
					{
						std::vector<float> source;
						auto floatArray = sourceElem->FirstChildElement("float_array");
						source.reserve(floatArray->IntAttribute("count"));
						std::stringstream sourceStream(floatArray->GetText());
						while (sourceStream)
						{
							float f;
							sourceStream >> f;
							source.push_back(f);
						}
						sources.emplace_back(std::make_pair(e.second, source));
						break;
					}
				}
			}

			return sources;
		}

		auto ReadInputChannels(tinyxml2::XMLElement *submeshElement) -> std::vector<std::pair<std::string, oakvr::render::VertexElementDescriptor::Semantic>>
		{
			decltype(ReadInputChannels(submeshElement)) inputChannels;
			// --- read vertices input elems
			auto vertsElem = submeshElement->FirstChildElement("vertices");
			if (vertsElem)
			{
				for (auto inputElem = vertsElem->FirstChildElement("input"); inputElem; inputElem = inputElem->NextSiblingElement("input"))
				{
					std::string semanticStr = inputElem->Attribute("semantic");
					if (semanticStr == "POSITION")
						inputChannels.emplace_back(inputElem->Attribute("source"), oakvr::render::VertexElementDescriptor::Semantic::position);
					else if (semanticStr == "NORMAL")
						inputChannels.emplace_back(inputElem->Attribute("source"), oakvr::render::VertexElementDescriptor::Semantic::normal);
					else if (semanticStr == "COLOR")
						inputChannels.emplace_back(inputElem->Attribute("source"), oakvr::render::VertexElementDescriptor::Semantic::color);
					else if (semanticStr == "TEXCOORD")
						inputChannels.emplace_back(inputElem->Attribute("source"), oakvr::render::VertexElementDescriptor::Semantic::tex_coord);
				}
			}

			// --- read polylist input elems
			auto polyElem = submeshElement->FirstChildElement("polylist");
			if (polyElem)
			{
				for (auto inputElem = polyElem->FirstChildElement("input"); inputElem; inputElem = inputElem->NextSiblingElement("input"))
				{
					std::string semanticStr = inputElem->Attribute("semantic");
					int offset = inputElem->IntAttribute("offset");
					if (offset >= inputChannels.size())
						inputChannels.resize(offset + 1);

					if (semanticStr == "VERTEX")
					{
						bool found = false;
						for (auto &e : inputChannels)
						{
							if (e.second == oakvr::render::VertexElementDescriptor::Semantic::position)
							{
								found = true;
								break;
							}
						}
						if (!found)
							inputChannels[offset] = std::make_pair(inputElem->Attribute("source"), oakvr::render::VertexElementDescriptor::Semantic::position);
					}
					else if (semanticStr == "NORMAL")
						inputChannels[offset] = std::make_pair(inputElem->Attribute("source"), oakvr::render::VertexElementDescriptor::Semantic::normal);
					else if (semanticStr == "COLOR")
						inputChannels[offset] = std::make_pair(inputElem->Attribute("source"), oakvr::render::VertexElementDescriptor::Semantic::color);
					else if (semanticStr == "TEXCOORD")
						inputChannels[offset] = std::make_pair(inputElem->Attribute("source"), oakvr::render::VertexElementDescriptor::Semantic::tex_coord);
				}
			}

			return inputChannels;
		}

		auto ReadAllIndices(tinyxml2::XMLElement *submeshElement) -> std::vector < uint32_t >
		{
			decltype(ReadAllIndices(submeshElement)) indices;
			oakvr::core::MemoryBuffer mb;
			auto polylistElem = submeshElement->FirstChildElement("polylist");
			if (polylistElem)
			{
				auto indicesElem = polylistElem->FirstChildElement("p");
				auto count = polylistElem->IntAttribute("count");
				if (indicesElem)
				{
					std::stringstream indexStream(indicesElem->GetText());

					uint32_t index;
					while (indexStream >> index)
						indices.push_back(index);
				}
			}
			return indices;
		}

		auto ReadIndices(tinyxml2::XMLElement *submeshElement, std::vector<uint32_t> &indices) -> oakvr::core::MemoryBuffer
		{
			oakvr::core::MemoryBuffer mb;
			auto polylistElem = submeshElement->FirstChildElement("polylist");
			if (polylistElem)
			{
				int numInputs = 0;
				for (auto it = polylistElem->FirstChildElement("input"); it; it = it->NextSiblingElement("input"))
					++numInputs;

				auto indicesElem = polylistElem->FirstChildElement("p");
				auto count = polylistElem->IntAttribute("count");
				if (indicesElem)
				{
					uint32_t numIndices = count * 3;
					uint32_t indexStride = sizeof(uint32_t);
					mb.Resize(sizeof(uint32_t) + sizeof(uint32_t) + sizeof(oakvr::render::PrimitiveTopology) + numIndices * indexStride);
					auto buffWriter = oakvr::core::MakeBufferWriter(mb);
					
					buffWriter.Write(numIndices);
					buffWriter.Write(indexStride);
					buffWriter.Write(oakvr::render::PrimitiveTopology::ePT_TriangleList);
					
					int numInd = count * numInputs * 3;
					for (uint32_t i = 0; i < numIndices; ++i)
						buffWriter.Write(i);
				}
			}
			return mb;
		}

		auto ReadTextureNames(tinyxml2::XMLElement *colladaElem) -> oakvr::core::MemoryBuffer
		{
			// reading the whole image library for every mesh (normally this should be done differently)
			oakvr::core::MemoryBuffer mb;
			auto imagesElem = colladaElem->FirstChildElement("library_images");
			if (imagesElem)
			{
				std::vector<std::string> textureNames;
				size_t bufferSize = sizeof(uint32_t);	// number of textures
				for (auto it = imagesElem->FirstChildElement("image"); it; it = it->NextSiblingElement("image"))
				{
					textureNames.emplace_back(it->FirstChildElement("init_from")->GetText());
					bufferSize += sizeof(uint32_t) + textureNames.back().size();
				}
				
				mb.Resize(static_cast<uint32_t>(bufferSize));
				auto buffWriter = oakvr::core::MakeBufferWriter(mb);

				buffWriter.Write(static_cast<uint32_t>(textureNames.size()));
				for (int i = 0; i < textureNames.size(); ++i)
				{
					buffWriter.Write(static_cast<uint32_t>(textureNames[i].size()));
					buffWriter.Write(textureNames[i].c_str(), textureNames[i].size());
				}
			}
			return mb;
		}

		/* oakvr mesh format:
		numberOfSubmeshes: 4 bytes
		submeshOffset: 4 bytes	| repeat numberOfSubmeshes times
		submeshSize: 4 bytes	|

		------ submesh 0
		numberOfVertices: 4 bytes
		numberOfChannels: 4 byte
		channeltypes: numberOfChannels * 4 bytes
		vertices: numberOfVertices * (numberOfChannels  * channelsize[channel])

		numberOfIndices: 4 bytes
		indexStride: 4 bytes
		primitiveTopology: 4 bytes
		indices: numberOfIndices * indexStride

		numberOfTextures: 4 bytes
		textureNameLength: 4 bytes				| repeat numberOfTextures times
		textureName: textureNameLength bytes	|

		?? materialNameLength: 4 bytes
		?? materialName: materialNameLength

		------ end submesh 0
		------ submesh 1
		...
		------ end submesh 1
		...


		*/
		void Dae2Oakvr(const std::string &in, const std::string &out)
		{
			tinyxml2::XMLDocument doc;
			doc.LoadFile(in.c_str());
			auto colladaElem = doc.FirstChildElement("COLLADA");
			auto libGeomElem = colladaElem->FirstChildElement("library_geometries");
			if (libGeomElem)
			{
				uint32_t numSubMeshes = CountChildElems(libGeomElem, "geometry");

				// create a vector of memory bufferes, one for each submesh
				// create the output memory buffer at the end, based on these ; memory shouldn't be a problem since this is a a separate tool
				std::vector<oakvr::core::MemoryBuffer> meshBuffers;
				uint32_t bufferSize = (numSubMeshes * 2 + 1) * sizeof(uint32_t);
				
				for (auto submeshElem = libGeomElem->FirstChildElement("geometry"); submeshElem; submeshElem = submeshElem->NextSiblingElement("geometry"))
				{
					auto submeshEl = submeshElem->FirstChildElement("mesh");
					if (submeshEl)
					{	
						
						auto inputChannels = ReadInputChannels(submeshEl);
						auto sources = ReadDaeSources(submeshEl, std::move(inputChannels));
						auto indices = ReadAllIndices(submeshEl);
						auto buffVertices = SourcesAsVertexBuffer(std::move(sources), indices);
						auto buffIndices = ReadIndices(submeshEl, indices);
						auto buffTextureNames = ReadTextureNames(colladaElem);
						oakvr::core::MemoryBuffer mb(buffVertices.Size() + buffIndices.Size() + buffTextureNames.Size());
						auto bufferWriter = oakvr::core::MakeBufferWriter(mb);
						bufferWriter.Write(buffVertices);
						bufferWriter.Write(buffIndices);
						bufferWriter.Write(buffTextureNames);
						bufferSize += static_cast<uint32_t>(mb.Size());
						meshBuffers.push_back(std::move(mb));
					}
				}

				auto mb = oakvr::core::MemoryBuffer(bufferSize);
				{
					auto bufferWriter = oakvr::core::MakeBufferWriter(mb);
					bufferWriter.Write(numSubMeshes);
					size_t offset = (numSubMeshes * 2 + 1) * sizeof(uint32_t);	// offset of first submesh
					for (const auto &e : meshBuffers)
					{
						bufferWriter.Write(static_cast<uint32_t>(offset));
						bufferWriter.Write(static_cast<uint32_t>(e.Size()));
						offset += e.Size();
					}
					for (const auto &e : meshBuffers)
					{
						bufferWriter.Write(e);
					}
				}

				auto output = std::ofstream(out, std::ios::binary);
				output.write("OKVR", 4);
				output.write(reinterpret_cast<char *>(mb.GetDataPtr()), mb.Size());
				output.close();
				return;
			}

			std::cout << "Failed to convert " << in << " to " << out << "!" << std::endl;
		}

		
	}
}