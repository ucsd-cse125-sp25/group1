#include <GraphicsEngine/OShaderProgram.h>
#include <GraphicsEngine/OShaderErrorHandling.h>
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

OShaderProgram::OShaderProgram(const OShaderProgramDesc& desc) {
	programId = glCreateProgram();
	attach(desc.vertexShaderFilePath, VERTEX);
	attach(desc.fragmentShaderFilePath, FRAGMENT);
	link();
}

OShaderProgram::~OShaderProgram() {
	for (unsigned int i = 0; i < 2; i++) {
		glDetachShader(programId, attachedShaders[i]);
		glDeleteShader(attachedShaders[i]);
	}
	glDeleteProgram(programId);
}

void OShaderProgram::attach(const wchar_t* shaderFilePath, const OShaderType& type) {
	std::string shaderCode;
	std::ifstream shaderStream(shaderFilePath);
	if (shaderStream.is_open()) {
		std::stringstream sstr;
		sstr << shaderStream.rdbuf();
		shaderCode = sstr.str();
		shaderStream.close();
	}
	else {
		OGL3D_WARNING("OShaderProgram | " << shaderFilePath << " not found");
		return;
	}
	unsigned int shaderId = 0;
	if (type == VERTEX)
		shaderId = glCreateShader(GL_VERTEX_SHADER);
	else if (type == FRAGMENT)
		shaderId = glCreateShader(GL_FRAGMENT_SHADER);
	auto sourcePointer = shaderCode.c_str();
	glShaderSource(shaderId, 1, &sourcePointer, NULL);
	glCompileShader(shaderId);

	// Here we're looking for shader compiled errors. Shaders may fail silently, so we have to do the checking ourselves
	int loglength = 0;
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &loglength);
	if (loglength > 0) {
		std::vector<char> errorMessage(loglength + 1);
		glGetShaderInfoLog(shaderId, loglength, NULL, &errorMessage[0]);
		OGL3D_WARNING("OShaderProgram | " << shaderFilePath << "compiled with errors" << std::endl << &errorMessage[0]);
		return;
	}

	glAttachShader(programId, shaderId);
	attachedShaders[type] = shaderId;
	OGL3D_INFO("OShaderProgram | " << shaderFilePath << "compiled successfully ^^" << std::endl);

}	

void OShaderProgram::link() {
	glLinkProgram(programId);

	int loglength = 0;
	glGetShaderiv(programId, GL_INFO_LOG_LENGTH, &loglength);
	if (loglength > 0) {
		std::vector<char> errorMessage(loglength + 1);
		glGetShaderInfoLog(programId, loglength, NULL, &errorMessage[0]);
		OGL3D_WARNING("OShaderProgram | " << &errorMessage[0]);
		return;
	}
}

unsigned int OShaderProgram::getId() {
	return programId;
}
