#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;


// Input uniform values
uniform sampler2D texture0;
uniform sampler2D depthTexture;

uniform float time;

uniform vec2 mouse;

uniform float h = 1.0;
uniform vec3 pos = vec3(0.0, 0.0, 1.0);
uniform float depthMin = -0.5;
uniform float depthMax = 0.25;

out vec4 finalColor;

vec2 getProjectedPos(vec3 v) {
    return (1.0 / (1.0 - v.z / h)) * v.xy;
}

// p in [-0.5,0.5]^2
vec2 projectedPosToUV(vec2 p) {
    return p + 0.5;
}

float getMinA(float v_z, float dir_z) {
    return (depthMax - v_z) / dir_z;
}

float getMaxA(float v_z, float dir_z) {
    return (depthMin - v_z) / dir_z;
}

float getAFromTargetProjX(vec3 v, vec3 w, float targetX) {
    return (targetX - (v.x - v.z*targetX/h)) / (w.x - w.z*targetX/h);
}

float getAFromTargetProjY(vec3 v, vec3 w, float targetY) {
    return (targetY - (v.y - v.z*targetY/h)) / (w.x - w.z*targetY/h);
}

vec3 rotateY(vec3 v, float angle){
    return vec3(
        cos(angle)*v.x + sin(angle)*v.z,
        v.y, 
        cos(angle)*v.z - sin(angle)*v.x
    );
}

vec3 rotateX(vec3 v, float angle){
  return vec3(
    v.x,
    cos(angle)*v.y - sin(angle)*v.z,
    cos(angle)*v.z + sin(angle)*v.y
  );
}

void main() {
    vec2 viewOffset = (mouse - 0.5);

    vec3 v   = rotateY(rotateX(pos, viewOffset.y), -viewOffset.x);
    vec3 dir = rotateY(rotateX(normalize(vec3(fragTexCoord - 0.5, -1.0)), viewOffset.y), -viewOffset.x);
    
    float a = getMinA(v.z, dir.z);
    float maxA = getMaxA(v.z, dir.z);
    float deltaA = 0.001;
    vec2 uv;

    while (a < maxA) {
        vec3 c_current = v + dir * a;
        uv = projectedPosToUV(getProjectedPos(c_current));
        float depth = texture(depthTexture, uv).x * (depthMax - depthMin) + depthMin;

        if (depth > c_current.z) break;

        a += deltaA;
    }

    finalColor = texture(texture0, uv) * fragColor;
}
