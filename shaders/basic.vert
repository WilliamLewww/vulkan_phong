#version 460

layout (location = 0) in vec2 a_position;
layout (location = 0) out vec4 v_color;

layout(binding = 0) uniform UniformBufferObject {
	vec4 color;
} ubo;

void main() {
    gl_Position = vec4(a_position, 0.0, 1.0);

    v_color = ubo.color;
}