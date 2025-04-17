#include <GraphicsEngine/OVertexArrayObject.h>
#include <GraphicsEngine/OShaderErrorHandling.h>
#include <glad/glad.h>

OVertexArrayObject::OVertexArrayObject(const OVertexBufferDesc& data) {
	if (!data.listSize) OGL3D_ERROR("OVertexArrayObject | list size is null");
	if (!data.vertexSize) OGL3D_ERROR("OVertexArrayObject | vertex size is null");
	if (!data.verticesList) OGL3D_ERROR("OVertexArrayObject | vertices list is null");
	/**
	* Lets us generate n buffers and place their object names
	* in an array. A vertex array object will only handle 1 buffer,
	* which will contain all data associated with vertices.
	*/
	glGenBuffers(1, &vertexBufferId);	// ??? - I'm not sure why we pass the address of an unsinged int here. Why not use an array?

	glGenVertexArrays(1, &vertexArrayObjectId);

	/**
	* Binding the vertex array object means that from now on OpenGL
	* will store in and use the vertex attribute configuration found
	* in this VAO.
	*/
	glBindVertexArray(vertexArrayObjectId);
	
	/**
	* Similarly, binding a buffer means we're telling OpenGL to allocate 
	* memory for our buffer in the GPU and copy data in that address.
	*/
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId); // GL_ARRAY_BUFFER is a target that tells OpenGL we're gonna use this buffer to store vertex attribute data
												  // In other words, it tells us that we're binding vertexBufferId as an array buffer
	
	/**
	* glBufferData is the function we use to upload our list of vertices into the GPU for rendering.
	* GL_STATIC_DRAW is a hint that tells OpenGL we're uploading all this business once and will 
	* draw it many times.
	*/
	glBufferData(GL_ARRAY_BUFFER, data.vertexSize * data.listSize, data.verticesList, GL_STATIC_DRAW);

	/**
	* Defining our first attribute, which will be position.
	* Index 0 means this is the first attribute
	* 3 means there will be 3 data points
	* GL_FLOAT means our attribute is of type float
	* GL_FALSE means that this attribute won't be normalized
	* Last 0 argument is the offset from the first attribute. Since this is the first attribute, there's no offset
	*/ 
	for (unsigned int i = 0; i < data.attributeListSize; i++) {
		glVertexAttribPointer(
			i, 
			data.attributesList[i].numElements, 
			GL_FLOAT, 
			GL_FALSE, 
			data.vertexSize, 
			(void*)((i==0)?0:data.attributesList[i-1].numElements*sizeof(float)) // If the index is 0, there are no previous attributes, so we pass in 0. Otherwise, we pass the number of elements * size of float
		);
		glEnableVertexAttribArray(i); // Lets us use this attribute for data array. Our first attribute's index is 0, so we pass 0.
	}

	/**
	* This tells OpenGL to unbind the current array because we're done configuring it.
	* This prevents possible mess ups (accidentally configuring the VAO in some other
	* part of the code).
	*/
	glBindVertexArray(0);

}

OVertexArrayObject::~OVertexArrayObject() {
	glDeleteBuffers(1, &vertexBufferId);
	glDeleteVertexArrays(1, &vertexArrayObjectId);
}

unsigned int OVertexArrayObject::getId() {
	return vertexArrayObjectId;
}