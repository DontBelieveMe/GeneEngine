/*
https://www.opengl.org/sdk/docs/tutorials/ClockworkCoders/varying.php look into for GLES?
*/
#define SHADER_FRAGMENT2D(varName) \
    std::string varName = "\
#version 300 es\n\
\n\
precision highp float;\n\
precision highp int;\n\
\n\
out vec4 color;\n\
\n\
in vec3 passColor;\n\
in vec2 passUv;\n\
in float passTexId;\n\
\n\
uniform sampler2D textureSamplers[16];\n\
\n\
void main()\n\
{\n\
    if (passTexId < 0.0f)\n\
    {\n\
        color = vec4(passColor.rgb, 1.0f);\n\
    }\n\
    else {\n\
        int texId = int(passTexId);\n\
        switch (texId) {\n\
            case 0: color = texture(textureSamplers[0], passUv); break;\n\
            case 1: color = texture(textureSamplers[1], passUv); break;\n\
            case 2: color = texture(textureSamplers[2], passUv); break;\n\
            case 3: color = texture(textureSamplers[3], passUv); break;\n\
            case 4: color = texture(textureSamplers[4], passUv); break;\n\
            case 5: color = texture(textureSamplers[5], passUv); break;\n\
            case 6: color = texture(textureSamplers[6], passUv); break;\n\
            case 7: color = texture(textureSamplers[7], passUv); break;\n\
            case 8: color = texture(textureSamplers[8], passUv); break;\n\
            default: color = texture(textureSamplers[0], passUv); break;\n\
        }\n\
        \n\
        color = color * vec4(passColor, 1);\n\
        \n\
    }\n\
}"
