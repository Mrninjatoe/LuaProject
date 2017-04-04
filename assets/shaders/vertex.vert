#version 440 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 UV;

out vec2 vPos;
out vec3 vColor;
out vec2 vUV;

uniform mat4 vp;
uniform mat4 m;

void main(){
	gl_Position = vp * m * vec4(position.x, position.y, 0, 1.0);
	vPos = vec2(m * vec4(position, 0, 1.0)).xy;
	vColor = color;
	vUV = UV;
}