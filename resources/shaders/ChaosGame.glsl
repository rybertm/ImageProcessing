<<<VSTEXT>>>
#version 330 core
layout(location = 0) in vec2 aPos;

uniform mat4 uMVP;

void main(void)
{
	gl_Position = uMVP * vec4(aPos, 0.0f, 1.0f);
}

<<<FSTEXT>>>
#version 330 core
out vec4 FragColor;

void main(void)
{
	FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
}