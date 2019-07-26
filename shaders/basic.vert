#version 460

layout (location = 0) in vec2 a_position;

layout (binding = 0) uniform CoordinateObject {
	mat4 modelMatrix;
	mat4 viewMatrix;
	mat4 projectionMatrix;
} coordinateObject;

void main() {
    gl_Position = vec4(a_position, 0.0, 1.0);
}