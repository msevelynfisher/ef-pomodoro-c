#include "stdio.h"
#include "string.h"
#include "raylib.h"

void seconds_to_str(char* buffer, int seconds) {
  char* digits = "0123456789";

  int mins = seconds / 60;
  int secs = seconds % 60;
  buffer[0] = digits[mins/10];
  buffer[1] = digits[mins%10];
  buffer[2] = ':';
  buffer[3] = digits[secs/10];
  buffer[4] = digits[secs%10];
  buffer[5] = '\0';
}

void draw_time_remaining(int frames_remaining, Color c) {
  char buffer[16];
  seconds_to_str(buffer, frames_remaining / 60);
  DrawText(buffer, 15, 15, 50, c);
}

int test() {
  char buffer[16];
  char* status;

  seconds_to_str(buffer, 60 * 3 + 11);
  status = (strcmp(buffer, "03:11") == 0) ? "PASS" : "FAIL";
  printf("[%s] Expected '03:11'. Got '%s'.\n", status, buffer);
}

#define FRAMES_WORK (25*60*60)
#define FRAMES_BREAK (5*60*60)

#define STATE_WORK_PAUSED  0
#define STATE_WORK         1
#define STATE_BREAK_PAUSED 2
#define STATE_BREAK        3

int app() {
  InitWindow(400, 80, "Pomodoro Timer");
  SetTargetFPS(60);

  int state = STATE_WORK_PAUSED;
  int frames_remaining = FRAMES_WORK;

  int frame_count = 0;
  while (!WindowShouldClose()) {
    frame_count += 1;

    BeginDrawing();
    ClearBackground(BLACK);

    if (state == STATE_WORK_PAUSED) {
      if (frame_count % 60 < 30) {
        draw_time_remaining(frames_remaining, RED);
      }

      if (IsKeyPressed(KEY_SPACE)) state = STATE_WORK;
    } else if (state == STATE_WORK) {
      draw_time_remaining(frames_remaining, RED);

      if (frames_remaining > 0) frames_remaining -= 1;

      if (IsKeyPressed(KEY_SPACE)) {
        state = STATE_WORK_PAUSED;
      }

      if (frames_remaining == 0) {
        state = STATE_BREAK_PAUSED;
        frames_remaining = FRAMES_BREAK;
      }
    } else if (state == STATE_BREAK_PAUSED) {
      if (frame_count % 60 < 30) {
        draw_time_remaining(frames_remaining, BLUE);
      }

      if (IsKeyPressed(KEY_SPACE)) state = STATE_BREAK;
    } else /* state == STATE_BREAK */ {
      draw_time_remaining(frames_remaining, BLUE);
      
      if (frames_remaining > 0) frames_remaining -= 1;

      if (IsKeyPressed(KEY_SPACE)) {
        state = STATE_BREAK_PAUSED;
      }

      if (frames_remaining == 0) {
        state = STATE_WORK_PAUSED;
        frames_remaining = FRAMES_WORK;
      }
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}

int main() {
  return app();
}
