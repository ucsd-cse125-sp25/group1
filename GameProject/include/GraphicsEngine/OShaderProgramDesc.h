#pragma once

struct OShaderProgramDesc {
	const wchar_t* vertexShaderFilePath; // wide characters, handle Unicode/character sets that require more than 8 bits per character
	const wchar_t* fragmentShaderFilePath;
};