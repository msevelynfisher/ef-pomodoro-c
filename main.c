#include <stdio.h>
#include <string.h>
#include <raylib.h>


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
  DrawText(buffer, 30, 15, 50, c);
}


void draw_cycles_done(int cycles_done) {
  for (int i = 0; i < cycles_done; i += 1) {
    DrawText("*", 200 + 20 * i, 15, 20, GRAY);
  }
}


void draw_hotkeys(bool is_paused) {
  char* txt = is_paused ? "[SPACE] Continue" : "[SPACE] Pause";
  DrawText(txt, 200, 38, 20, GRAY);
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
  SetTraceLogLevel(LOG_WARNING);
  InitWindow(400, 80, "Pomodoro Timer");
  SetTargetFPS(60);

  int frames_remaining = FRAMES_WORK;
  bool is_paused = true;
  bool is_break = false;
  int cycles_done = 0;

  int frame_count = 0;
  while (!WindowShouldClose()) {
    frame_count += 1;

    BeginDrawing();
    ClearBackground(BLACK);

    // draw current time
    if (!is_paused || frame_count % 60 < 30) {
      draw_time_remaining(frames_remaining, is_break ? BLUE : RED);
    }

    // draw markings for the number of complete cycles
    draw_cycles_done(cycles_done);

    // draw hotkeys
    if (IsWindowFocused()) {
      draw_hotkeys(is_paused);
    }

    // count down
    if (!is_paused && frames_remaining > 0) {
      frames_remaining -= 1;
    }

    // handle no time remaining
    if (!is_paused && frames_remaining == 0) {
      if (!is_break) {
        cycles_done += 1;
      }
      is_break = !is_break;
      is_paused = true;
      frames_remaining = is_break ? FRAMES_BREAK : FRAMES_WORK;
    }

    // handle pause key
    if (IsKeyPressed(KEY_SPACE)) {
      is_paused = !is_paused;
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}


int main() {
  return app();
}
