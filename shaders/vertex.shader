#version 330 core

layout (location = 0) in vec3 aPos;

layout (location = 1) in vec3 aColor;

out vec3 ourColor;
uniform float xOffset;
uniform float yOffset;

out vec3 vertexColour;

void main()
{

   // gl_Position  = vec4(-aPos.x,-aPos.y,-aPos.z, 1.0);
   gl_Position = vec4(aPos.x + xOffset, aPos.y+ yOffset, aPos.z, 1.0); // add the xOffset to the x position of the vertex position
   ourColor = aColor;
   vertexColour = vec3(aPos.x + xOffset, aPos.y+ yOffset, aPos.z);
};