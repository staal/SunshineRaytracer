#version 330

layout(location = 0) in vec4 vertex;
layout(location = 1) in vec3 normal;

out vec4 color;
out vec4 fragVert;
out vec3 fragNormal;

uniform mat4 matrix;
uniform vec3 lightPos;

void main(void)
{
    vec3 toLight = normalize(vec3(0.0, 0.3, 1.0));
    float angle = max(dot(normal, toLight), 0.0);
    vec3 col = vec3(0.40, 1.0, 0.0);
    color = vec4(col * 0.2 + col * 0.8 * angle, 1.0);
    color = clamp(color, 0.0, 1.0);
    
    fragNormal = normal;
    fragVert = vertex;    
    gl_Position = matrix * vertex;
}    