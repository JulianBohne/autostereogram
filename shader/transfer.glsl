#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;

uniform sampler2D patternTex;

out vec4 finalColor;

void main() {

	vec2 uv = texture(texture0, fragTexCoord).xy;

	finalColor = texture(patternTex, uv);
}