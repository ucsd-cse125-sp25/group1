#include<GraphicsEngine/GEngine.h>
GEngine::GEngine(){}

GEngine::~GEngine(){}

void GEngine::clear() {
	glClearColor(0.949f, 0.800f, 1.000f, 1);
	glClear(GL_COLOR_BUFFER_BIT);	// Clears screen to whatever is set to be the clear color
}

void GEngine::setViewport(const ORect& size) {
	glViewport(size.left, size.top, size.width, size.height);
}

void GEngine::setShaderProgram() {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    this->shaderProgram = shaderProgram;
}

std::shared_ptr<OVertexArrayObject> GEngine::createVertexArrayObject(const OVertexBufferDesc& data) {
	return std::make_shared<OVertexArrayObject>(data);
}

std::shared_ptr<OShaderProgram> GEngine::createShaderProgram(const OShaderProgramDesc& desc) {
    return std::make_shared<OShaderProgram>(desc);
}

void GEngine::setVertexArrayObject(const std::shared_ptr<OVertexArrayObject>& vao){
	glBindVertexArray(vao->getId());
}


void GEngine::setShaderProgram(const std::shared_ptr<OShaderProgram>& program) {
    glUseProgram(program->getId());
}
void GEngine::drawTriangles(unsigned int vertexCount, unsigned int offset) {
	glDrawArrays(GL_TRIANGLES, offset, vertexCount);
}
