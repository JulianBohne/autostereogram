#include <stdio.h>
#include <raylib.h>
#include <raymath.h>

int main(int argc, char** argv) {

    const char* img_path = "res/elephant-texture.png";
    const char* depth_img_path = "res/elephant-depth.png";

    Image img = LoadImage(img_path);

    InitWindow(img.width*2, img.height*2, img_path);
    SetTargetFPS(60);

    Shader testShader = LoadShader(NULL, "shader/test.glsl");

    int time_loc = GetShaderLocation(testShader, "time");
    int mouse_loc = GetShaderLocation(testShader, "mouse");
    int depth_texture_loc = GetShaderLocation(testShader, "depthTexture");

    Texture2D tex = LoadTextureFromImage(img);
    Texture2D depthTex = LoadTexture(depth_img_path);

    SetTextureWrap(tex, TEXTURE_WRAP_CLAMP);
    SetTextureWrap(depthTex, TEXTURE_WRAP_CLAMP);
    
    while (!WindowShouldClose()) {
        float time = GetTime();
        Vector2 mouse = Vector2Divide(GetMousePosition(), (Vector2){ GetRenderWidth(), GetRenderHeight() });
        BeginDrawing();
            BeginShaderMode(testShader);
                SetShaderValueTexture(testShader, depth_texture_loc, depthTex);
                SetShaderValue(testShader, time_loc, &time, SHADER_UNIFORM_FLOAT);
                SetShaderValue(testShader, mouse_loc, &mouse, SHADER_UNIFORM_VEC2);
                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                    DrawTextureEx(depthTex, (Vector2){0.0, 0.0}, 0.0, 2.0, WHITE);
                } else {
                    DrawTextureEx(tex, (Vector2){0.0, 0.0}, 0.0, 2.0, WHITE);
                }
            EndShaderMode();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
