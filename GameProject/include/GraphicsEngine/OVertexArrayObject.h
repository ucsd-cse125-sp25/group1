#pragma once
#include <GraphicsEngine/OVertexBufferData.h>
/**
* A vertex array object (VAO) encapsulates all the data associated 
* with the vertices (by extention, the vertex processor). It doesn't store
* actual data values for vertices (position, color), but rather how these data 
* values are laid out. This could be, for example, pointers to vertex buffers, 
* layout specifications, vertex attributes, etc.
*/
class OVertexArrayObject {
public:
	OVertexArrayObject(const OVertexBufferData& data);
	~OVertexArrayObject();
	unsigned int getId();
private:
	unsigned int vertexBufferId = 0;
	unsigned int vertexArrayObjectId = 0;
};