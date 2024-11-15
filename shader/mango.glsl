#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;

out vec4 finalColor;

void main() {
	finalColor = vec4(fragTexCoord, 0.0, 1.0);
	// finalColor = texture(texture0, fragTexCoord);
}