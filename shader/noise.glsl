#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;

uniform float noiseSeed = 0.0;

out vec4 finalColor;

void main() {
	// Random expression from here: https://gist.github.com/patriciogonzalezvivo/670c22f3966e662d2f83
	finalColor = vec4(vec3(fract(sin(dot(fragTexCoord + noiseSeed, vec2(12.9898, 4.1414))) * 43758.5453)), 1.0);
	// finalColor = vec4(fragTexCoord, 0.0, 1.0);
	// finalColor = texture(texture0, fragTexCoord);
}