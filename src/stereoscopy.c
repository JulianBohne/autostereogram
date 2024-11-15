#include <stdio.h>
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>

int main(int argc, char** argv) {

    const char* img_path = "res/elephant-depth.png";
    const char* depth_img_path = "res/elephant-depth.png";

    Image img = LoadImage(img_path);

    int scale = 2;

    SetConfigFlags(FLAG_FULLSCREEN_MODE);

    // InitWindow(img.width*scale, img.height*scale, img_path);
    InitWindow(GetScreenWidth(), GetScreenHeight(), img_path);
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
    int depth_min_loc = GetShaderLocation(testShader, "depthMin");
    int depth_max_loc = GetShaderLocation(testShader, "depthMax");
    int eye_offset_loc = GetShaderLocation(testShader, "eyeOffset");

    Texture2D tex = LoadTextureFromImage(img);
    Texture2D depthTex = LoadTexture(depth_img_path);

    RenderTexture2D renderTex = LoadRenderTexture(img.width, img.height);
    RenderTexture2D renderSwap = LoadRenderTexture(img.width, img.height);

    SetTextureWrap(tex, TEXTURE_WRAP_CLAMP);
    SetTextureWrap(depthTex, TEXTURE_WRAP_CLAMP);

    float depthMin = -1.5;
    float depthMax = -0.5;
    float eyeOffset = 0.15;

    while (!WindowShouldClose()) {

        if (IsKeyDown(KEY_UP)) {
            depthMax += 0.01;
            printf("Set depth max to: %f\n", depthMax);
        } else if (IsKeyDown(KEY_DOWN)) {
            depthMax -= 0.01;
            printf("Set depth max to: %f\n", depthMax);
        } else if (IsKeyDown(KEY_RIGHT)) {
            depthMin += 0.01;
            printf("Set depth min to: %f\n", depthMin);
        } else if (IsKeyDown(KEY_LEFT)) {
            depthMin -= 0.01;
            printf("Set depth min to: %f\n", depthMin);
        } else if (IsKeyDown(KEY_M)) {
            eyeOffset += 0.001;
            printf("Set eye offset to: %f\n", eyeOffset);
        } else if (IsKeyDown(KEY_N)) {
            eyeOffset -= 0.001;
            printf("Set eye offset to: %f\n", eyeOffset);
        }

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
                    SetShaderValue(testShader, depth_min_loc, &depthMin, SHADER_UNIFORM_FLOAT);
                    SetShaderValue(testShader, depth_max_loc, &depthMax, SHADER_UNIFORM_FLOAT);
                    SetShaderValue(testShader, eye_offset_loc, &eyeOffset, SHADER_UNIFORM_FLOAT);
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
