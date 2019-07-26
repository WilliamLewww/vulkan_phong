#version 460

layout (location = 0) out vec4 fragmentColor;

layout (binding = 0) uniform UniformBufferObject {
	vec4 color;
} ubo;

void main() {
	fragmentColor = vec4(1.0, 0.0, 0.0, 1.0);
}