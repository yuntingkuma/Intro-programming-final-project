#include "global.h"

// variables for global usage
const float FPS = 60.0;
const int WIDTH = 600;
const int HEIGHT = 400;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *fps = NULL;
bool key_state[ALLEGRO_KEY_MAX] = {false};
bool judge_next_window = false;

int count_sec = 0;
int count_enemy = 0;
int window=1;///
int menu_select=0;///
int enemy_HP=5;
int chara_HP=5;
float cameraPosition[2]={0,0};
int stage_width;
