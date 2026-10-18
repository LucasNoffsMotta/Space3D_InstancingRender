#version 330 core

out vec4 FragColor;
in vec2 TextCoord;

uniform sampler2D screenTexture;
uniform int postProcessEffect;
uniform int colorScaleEffectNumber;

const float offset = 1.0 / 300.0;  

float blurKernel[9] = float[] (
    1.0 / 16, 2.0 / 16, 1.0 / 16,
    2.0 / 16, 4.0 / 16, 2.0 / 16,
    1.0 / 16, 2.0 / 16, 1.0 / 16  
);

float edgeDetectionKernel[9] = float[] (
        1, 1, 1,
        1, -8, 1,
        1, 1, 1  
);

bool applyKernelEffect = false;
bool applyColorScaleEffect = false;


void main()
{
    vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // top-left
        vec2( 0.0f,    offset), // top-center
        vec2( offset,  offset), // top-right
        vec2(-offset,  0.0f),   // center-left
        vec2( 0.0f,    0.0f),   // center-center
        vec2( offset,  0.0f),   // center-right
        vec2(-offset, -offset), // bottom-left
        vec2( 0.0f,   -offset), // bottom-center
        vec2( offset, -offset)  // bottom-right    
    );

    float kernel[9];

    if (postProcessEffect == 1)
    {
        kernel = blurKernel;
        applyKernelEffect = true;
    }

    else if (postProcessEffect == 2)
    {
        kernel = edgeDetectionKernel;
        applyKernelEffect = true;
    }

    else if (postProcessEffect == -1 && colorScaleEffectNumber == 1)
    {
        applyColorScaleEffect = true;
    }
    
    if (applyKernelEffect) 
    {
         vec3 sampleTex[9];

        for(int i = 0; i < 9; i++)
        {
            sampleTex[i] = vec3(texture(screenTexture, TextCoord.st + offsets[i]));
        }

        vec3 col = vec3(0.0);

        for(int i = 0; i < 9; i++)
            col += sampleTex[i] * kernel[i];
    
        FragColor = vec4(col, 1.0);
    }

    else if(applyColorScaleEffect)
    {
         FragColor = vec4(texture(screenTexture, TextCoord));
         float average = 0.2126 * FragColor.r + 0.7152 * FragColor.g + 0.0722 * FragColor.b;
         FragColor = vec4(average, average, average, 1.0);
    }

    else
    {
         // FragColor = vec4(texture(screenTexture, TextCoord));
         //FragColor = vec4(TextCoord.x, TextCoord.y, 0, 1);
         //FragColor = vec4(1, 0,0,1);


//         FragColor = vec4(texture(screenTexture, TextCoord));
//         float average = 0 * FragColor.r + 0.7152 * FragColor.g + 0 * FragColor.b;
//         FragColor = vec4(average, average, average, 1.0);


         // 1. Amostra a cor da cena original
        vec4 sceneColor = texture(screenTexture, TextCoord);

        // 2. Calcula a luminância (proporção RGB: 30% Vermelho, 59% Verde, 11% Azul)
        float luminance = dot(sceneColor.rgb, vec3(0.3, 0.59, 0.11));

        // 3. Amplifica áreas escuras (simula o ganho da lente de visão noturna)
        float boosted = luminance * 100;

        // 4. Aplica a tonalidade verde clássica de fósforo
        vec3 greenTint = vec3(0.1, 0.95, 0.2);
        vec3 nightVisionColor = boosted * greenTint;

        // 6. Efeito de vinheta (escurece as bordas da tela)
        vec2 uv = TextCoord * (1.0 - TextCoord.yx);
        float vignette = uv.x * uv.y * 15.0;
        vignette = clamp(pow(vignette, 0.25), 0.0, 1.0);
        nightVisionColor *= vignette;

        FragColor = vec4(nightVisionColor, 1.0);


    }
}  