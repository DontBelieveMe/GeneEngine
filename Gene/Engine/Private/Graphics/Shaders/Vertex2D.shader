#define SHADER_VERTEX2D(varName) \
std::string varName = "\n\
#version 130\n\
\n\
in vec3      position;\n\
in vec3      color;\n\
in vec2      uv;\n\
in float     texId;\n\
\n\
out vec3     passColor;\n\
out vec2     passUv;\n\
out float    passTexId;\n\
out float    passVertexType;\n\
\n\
uniform mat4 u_Projection;\n\
uniform mat4 u_View = mat4(1.0);\n\
\n\
void main()\n\
{\n\
    gl_Position = u_View * u_Projection * vec4(position, 1.0);\n\
    passColor = color;\n\
    passUv = uv;\n\
    passTexId = texId;\n\
}"
