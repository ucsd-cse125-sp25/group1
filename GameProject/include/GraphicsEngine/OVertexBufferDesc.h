#pragma once
#include <GraphicsEngine/OVertexAttribute.h>

struct OVertexBufferDesc {
	void* verticesList = nullptr;	// The vertices in our object
	unsigned int vertexSize = 0;	// Size of each vertex
	unsigned int listSize = 0;		// Number of vertices in the list
	
	OVertexAttribute* attributesList = nullptr;
	unsigned int attributeListSize = 0;
};