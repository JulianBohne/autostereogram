#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;

uniform sampler2D patternTex;

out vec4 finalColor;

void main() {

	// Need to flip the uv :|
	vec2 uv = texture(texture0, fragTexCoord).xy * vec2(1.0, -1.0) + vec2(0.0, 1.0);

	finalColor = texture(patternTex, uv);
}