#pragma once
#include <GraphicsEngine/OShaderProgramDesc.h>
class OShaderProgram {
public:
	OShaderProgram(const OShaderProgramDesc& desc);
	~OShaderProgram();
	enum OShaderType {
		VERTEX,
		FRAGMENT
	};
	unsigned int getId();
private:
	unsigned int programId = 0;
	unsigned int attachedShaders[2] = {};
	void attach(const wchar_t* shaderFilePath, const OShaderType& type);
	void link();
};