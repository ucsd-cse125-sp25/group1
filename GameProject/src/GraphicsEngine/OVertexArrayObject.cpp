#include <GraphicsEngine/OVertexArrayObject.h>
#include <glad/glad.h>

/**
* TODO: Before you add this to the graphics engine, make sure you clear these questions
* 1. What are the flags and parameters of glVertexAttribPointer?
* 2. What does glBufferData do?
* 3. What's this line for glBindVertexArray(0)?
*/

OVertexArrayObject::OVertexArrayObject(const OVertexBufferData& data) {
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
	
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId)
	glBufferData(GL_ARRAY_BUFFER, data.vertexSize * data.listSize, data.verticesList, GL_STATIC_DRAW);

	/**
	* Creating our first attribute, which will be position. W
	* Index 0 means this is the first attribute
	* 3 means there will be 3 data points
	* GL_FLOAT means our attribute is of type float
	* Last 0 argument is the offset from the first attribute. Since this is the first attribute, there's no offset
	*/ 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, data.vertexSize, 0);
	glEnableVertexAttribArray(0); // Lets us use this attribute for data array. Our first attribute's index is 0, so we pass 0.
	glBindVertexArray(0);

}

OVertexArrayObject::~OVertexArrayObject() {
	glDeleteBuffers(1, &vertexBufferId);
	glDeleteVertexArrays(1, &vertexArrayObjectId);
}