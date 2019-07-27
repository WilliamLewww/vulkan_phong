#version 460

layout (location = 0) in vec2 v_textureCoordinate;

layout (location = 0) out vec4 fragmentColor;

layout (binding = 1) uniform sampler2D textureSampler;

void main() {
	fragmentColor = texture(textureSampler, v_textureCoordinate);
}