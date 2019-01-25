#version 330 core

in vec2 texcoordinate;
out vec4 color;

uniform sampler2D tex;

void main()
{  vec4 texcolor=texture(tex,texcoordinate);

    color=texcolor;
}
