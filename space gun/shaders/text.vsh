#version 330 core

layout (location = 0) in vec4 vertex;       // in this x,y stores the 2d position of the text and z,w stores the 2d position of the texture of text
out vec2 TexCoords;

uniform mat4 projection;

void main()
{
            gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);
            TexCoords = vertex.zw;
}
