#include <stdio.h>
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>

int main(int argc, char** argv) {

    const char* img_path = "res/small-dog.png";
    const char* depth_img_path = "res/small-dog.png";

    Image img = LoadImage(img_path);

    int scale = 2;

    InitWindow(img.width*scale, img.height*scale, img_path);
    SetTargetFPS(60);
    
    // Set default internal texture (1px white) and rectangle to be used for shapes drawing
    Texture2D defaultTexture = {
        .format = RL_PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,
        .width = 1,
        .height = 1,
        .mipmaps = 0,
        .id = rlGetTextureIdDefault()
    };
    SetShapesTexture(defaultTexture, (Rectangle){ 0.0f, 0.0f, 1.0f, 1.0f });


    Shader testShader = LoadShader(NULL, "shader/test.glsl");
    Shader noiseShader = LoadShader(NULL, "shader/noise.glsl");

    int noise_seed_loc = GetShaderLocation(noiseShader, "noiseSeed");

    int time_loc = GetShaderLocation(testShader, "time");
    int mouse_loc = GetShaderLocation(testShader, "mouse");
    int depth_texture_loc = GetShaderLocation(testShader, "depthTexture");

    Texture2D tex = LoadTextureFromImage(img);
    Texture2D depthTex = LoadTexture(depth_img_path);

    RenderTexture2D renderTex = LoadRenderTexture(img.width, img.height);
    RenderTexture2D renderSwap = LoadRenderTexture(img.width, img.height);

    SetTextureWrap(tex, TEXTURE_WRAP_CLAMP);
    SetTextureWrap(depthTex, TEXTURE_WRAP_CLAMP);


    
    while (!WindowShouldClose()) {
        HideCursor();

        float time = GetTime();
        // Vector2 mouse = (Vector2){ 0.5, 0.5 };
        Vector2 mouse =  Vector2Divide(GetMousePosition(), (Vector2){ GetRenderWidth(), GetRenderHeight() });

        BeginTextureMode(renderTex);
            BeginShaderMode(noiseShader);
                SetShaderValue(noiseShader, noise_seed_loc, &time, SHADER_UNIFORM_FLOAT);
                DrawRectangle(0, 0, img.width, img.height, WHITE);
                // DrawTexture(tex, 0, 0, WHITE);
            EndShaderMode();
        EndTextureMode();

        for (int i = 0; i < 10; ++i) {

            BeginTextureMode(renderSwap);
                BeginShaderMode(testShader);
                    SetShaderValueTexture(testShader, depth_texture_loc, depthTex);
                    SetShaderValue(testShader, time_loc, &time, SHADER_UNIFORM_FLOAT);
                    SetShaderValue(testShader, mouse_loc, &mouse, SHADER_UNIFORM_VEC2);
                    DrawTexturePro(renderTex.texture, (Rectangle){ 0, 0, (float)depthTex.width, -(float)depthTex.height }, (Rectangle){ 0, 0, (float)depthTex.width, (float)depthTex.height}, (Vector2){ 0, 0 }, 0.0f, WHITE);
                EndShaderMode();
            EndTextureMode();
            
            // swap textures
            RenderTexture2D tmp = renderSwap;
            renderSwap = renderTex;
            renderTex = tmp;
        }

        BeginDrawing();
            DrawTextureEx(renderTex.texture, (Vector2){ 0.0, 0.0 }, 0.0, 1.0*scale, WHITE);
        EndDrawing();


    }

    CloseWindow();

    return 0;
}
