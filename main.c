#include "raylib.h"

int main() {
  InitWindow(400, 300, "Pomodoro Timer");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    EndDrawing();
  }

  CloseWindow();
}
