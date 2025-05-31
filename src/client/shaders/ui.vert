#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

uniform vec3 origin;
uniform float width;
uniform float height;
uniform float angle;

void main() {
    mat2 rotation = mat2(	// 2D rotation matrix
        cos(angle), -sin(angle),
        sin(angle),  cos(angle)
    );

	vec3 position = aPosition;
	if(position.x == -1 && position.y == 1){
		position.x = origin.x;
		position.y = origin.y;
	}
	if(position.x == 1 && position.y == 1){
		position.x = origin.x + width;
		position.y = origin.y;
	}
	if(position.x == 1 && position.y == -1){
		position.x = origin.x + width;
		position.y = origin.y - height;
	}
	if(position.x == -1 && position.y == -1){
		position.x = origin.x;
		position.y = origin.y - height;
	}
	gl_Position = vec4(position,1.0);

	ourColor = aColor;

	vec2 centeredCoords = aTexCoord - vec2(0.5);	// origin is at (0,0), subtracting (-0.5,-0.5) centers the texture at its origin;
	TexCoord = rotation * centeredCoords + vec2(0.5);	// after rotating it, place the upper left corner of the texture back at its origin
}
