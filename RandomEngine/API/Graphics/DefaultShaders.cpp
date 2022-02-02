#include "DefaultShaders.hpp"

namespace
{
    const char* vsh = R"raw(
void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

    // transform the texture coordinates
	gl_TexCoord[0] = gl_MultiTexCoord0;

    // forward the vertex color
    gl_FrontColor = gl_Color;
})raw";
    const char* fsh = R"raw(
uniform sampler2D texture;

void main()
{
    // lookup the pixel in the texture
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

    // multiply it by the color
    gl_FragColor = gl_Color * pixel;
})raw";
}

namespace random_engine
{
    sf::Shader* DefaultShaders::getSpriteShader()
    {
        static sf::Shader* shader = nullptr;
        if (not shader)
        {
            shader = new sf::Shader;
            shader->loadFromMemory(vsh, fsh);
        }
        return shader;
    }
}