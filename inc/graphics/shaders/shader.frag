#version 330 core

out vec4 FragColor;

in vec2 texCoord;

//sampler2D is a special value that will load the desired texture,
// this is done when we bind the desired texture in OpenGL.
uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float texRatio;

void main()
{
    //FragColor = vec4(ourColor, 1.0);
    FragColor = texture(texture1, texCoord);
}
