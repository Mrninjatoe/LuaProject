#version 440 core
in vec2 vPos;
in vec3 vColor;
in vec2 vUV;

layout(location = 0) out vec4 fragColor;

void main(){
	fragColor = vec4(vColor, 1.0);
}