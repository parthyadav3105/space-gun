#version 330 core

layout (location=0) in vec4 pos;
out vec2 texcoordinate;

uniform mat4 projection;
uniform mat4 model;

void main()
{  gl_Position=projection*model*vec4(pos.x,pos.y,0.0,1.0);
    texcoordinate=vec2(pos.z,1-pos.w);
}
