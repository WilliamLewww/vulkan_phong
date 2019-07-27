#version 460

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_textureCoordinate;

layout (location = 0) out vec2 v_textureCoordinate;

layout (binding = 0) uniform CoordinateObject {
	mat4 modelMatrix;
	mat4 viewMatrix;
	mat4 projectionMatrix;
} coordinateObject;

void main() {
    gl_Position = vec4(a_position, 1.0);

    v_textureCoordinate = a_textureCoordinate;
}