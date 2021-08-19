#include "charater.h"
#include <math.h>

// the state of character
enum {STOP = 0, MOVE, ATK};
//the state of enemy
enum {LIVE=0,DIE,Just_DIE};
//the state of bullet
enum {ACTIVE=0, NON_ACTIVE};

typedef struct bullet_mine
{
    int x, y; // the position of image
    int width, height; // the width and height of image
    int state; // the state of character
    bool dir;// left: false, right: true
    ALLEGRO_BITMAP *bullet_pic;
}Bullet_mine;

typedef struct character
{
    int x, y; // the position of image
    int chara_HP=5;
    int width, height; // the width and height of image
    bool dir; // left: false, right: true
    int state; // the state of character
    ALLEGRO_BITMAP *img_move[2];
    ALLEGRO_BITMAP *img_atk[2];
    ALLEGRO_SAMPLE_INSTANCE *atk_Sound;
    ALLEGRO_SAMPLE_INSTANCE *chara_hurt_sound;
    int anime; // counting the time of animation
    int anime_time; // indicate how long the animation
    int bullet_num=10000;
    Bullet_mine bullet[10000];
}Character;

typedef struct bullet_enemy
{
    int x, y; // the position of image
    int width, height; // the width and height of image
    int state; // the state of character
    ALLEGRO_BITMAP *bullet_pic;
    ALLEGRO_SAMPLE_INSTANCE *atk_Sound;
}Bullet_enemy;

typedef struct enemy
{
    int x, y; // the position of image
    int width, height; // the width and height of image
    int state; // the state of character
    ALLEGRO_BITMAP *enemy_pic;
    ALLEGRO_BITMAP *enemy_die_pic;
    ALLEGRO_SAMPLE_INSTANCE *die_sound;
    int bullet_num=100;
    Bullet_enemy bullet[100];
}Enemy;

//variables
Character chara;
Bullet_mine my_bullet[10000];
Enemy enemy[2000]; //enemy total number
bool shoot_bullet = true;
bool chara_been_shoot=false;
// ALLEGRO Variables
ALLEGRO_SAMPLE *sample = NULL;
ALLEGRO_SAMPLE *enemy_die_sample = NULL;
ALLEGRO_SAMPLE *chara_hurt;
ALLEGRO_TRANSFORM camera;

bool My_Collision(int sx, int sy, int enemy_width, int enemy_height, int bullet_sx, int bullet_sy, int bullet_ex, int bullet_ey){
    int ex = sx + enemy_width;
    int ey = sy + enemy_height;

    //printf("%d %d %d %d\n", sy, ey, bullet_sy, bullet_ey);
    if ((bullet_ex > sx||bullet_sx<ex )&& bullet_sy > sy && bullet_ey < ey) {
        return true;
    }
    return false;
}

bool Enemy_Collision(int sx, int sy, int chara_width, int chara_height, int bullet_sx, int bullet_sy, int bullet_ex, int bullet_ey){
    int ex = sx + chara_width;
    int ey = sy + chara_height;

    if ( ex>bullet_sx&&ex<bullet_ex&& bullet_sy>sy&&bullet_ey < ey) {
        return true;
    }
    return false;
}

void CameraUpdate(float *cameraPosition,float x,float y,int width,int height){
    cameraPosition[0] = -(WIDTH/2)+(x+width/2);
    if (cameraPosition[0] > stage_width-WIDTH/2-chara.width*2){
        cameraPosition[0] = stage_width-WIDTH/2-chara.width*2;
    }
    if (cameraPosition[0]<0) {
        cameraPosition[0] = 0;
    }
}

void character_init(){
    // load character images
    for(int i = 1 ; i <= 2 ; i++){
        char temp[50];
        sprintf( temp, "./image/char_move%d.png", i );
        chara.img_move[i-1] = al_load_bitmap(temp);
    }
    for(int i = 1 ; i <= 2 ; i++){
        char temp[50];
        sprintf( temp, "./image/char_atk%d.png", i );
        chara.img_atk[i-1] = al_load_bitmap(temp);
    }
    // load effective sound
    sample = al_load_sample("./sound/bang.wav");
    chara.atk_Sound  = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(chara.atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(chara.atk_Sound, al_get_default_mixer());

    // initial the geometric information of character
    chara.width = al_get_bitmap_width(chara.img_move[0]);
    chara.height = al_get_bitmap_height(chara.img_move[0]);
    chara.x = 0;
    chara.y = HEIGHT/2;
    chara.dir = false;

    // initial the animation component
    chara.state = STOP;
    chara.anime = 0;
    chara.anime_time = 25;
}

void charater_process(ALLEGRO_EVENT event){
    // process the animation
    if( event.type == ALLEGRO_EVENT_TIMER ){
        if( event.timer.source == fps ){
            chara.anime++;
            chara.anime %= chara.anime_time;
        }
    // process the keyboard event
    }else if( event.type == ALLEGRO_EVENT_KEY_DOWN ){
        key_state[event.keyboard.keycode] = true;
        chara.anime = 0;
    }else if( event.type == ALLEGRO_EVENT_KEY_UP ){
        key_state[event.keyboard.keycode] = false;
        shoot_bullet = true;
    }
}
void charater_update(){
    // use the idea of finite state machine to deal with different state
    if( key_state[ALLEGRO_KEY_UP] ){
        if(chara.y>=5){
           chara.y -= 5;
        }
        chara.state = MOVE;
    }else if( key_state[ALLEGRO_KEY_LEFT] ){
        chara.dir = false;
        if(chara.x>=5){
            chara.x -= 5;
        }
        chara.state = MOVE;
    }else if( key_state[ALLEGRO_KEY_DOWN] ){
        if(chara.y<=HEIGHT-chara.height){
           chara.y += 5;
        }
        chara.state = MOVE;
    }else if( key_state[ALLEGRO_KEY_RIGHT] ){
        chara.dir = true;
        if(chara.x<=stage_width-chara.width){
                chara.x += 5;
        }
        chara.state = MOVE;
    }else if( key_state[ALLEGRO_KEY_RCTRL] && shoot_bullet ){
        //printf("Insert is pressed!\n");
        chara.state = ATK;
        int temp_bullet_idx=10000-chara.bullet_num;
        my_bullet[temp_bullet_idx].dir=chara.dir;
        my_bullet[temp_bullet_idx].bullet_pic= al_load_bitmap("./image/bullet_mine.png");
        my_bullet[temp_bullet_idx].width = al_get_bitmap_width(my_bullet[temp_bullet_idx].bullet_pic);
        my_bullet[temp_bullet_idx].height = al_get_bitmap_height(my_bullet[temp_bullet_idx].bullet_pic);
        int start_chara_bullet_x=chara.x,start_chara_bullet_y=chara.y;
        my_bullet[temp_bullet_idx].x=start_chara_bullet_x;
        my_bullet[temp_bullet_idx].y=(start_chara_bullet_y+start_chara_bullet_y+chara.height)/2;
        my_bullet[temp_bullet_idx].state = ACTIVE;
        //printf("temp_bullet_idx:%d\n",temp_bullet_idx);
        chara.bullet_num--;
        shoot_bullet = false;
    }else if( chara.anime == chara.anime_time-1 ){
        chara.anime = 0;
        chara.state = STOP;
    }else if ( chara.anime == 0 ){
        chara.state = STOP;
    }
    //camera
    CameraUpdate(cameraPosition,chara.x,chara.y,chara.width,chara.height);
    al_identity_transform(&camera);
    al_translate_transform(&camera,-cameraPosition[0],-cameraPosition[1]);
    al_use_transform(&camera);

    //3 enemies show up every 3 seconds
    if (count_sec % 300 == 0){
        for(int i=count_enemy; i<count_enemy+3; i++){
            int start_bullet_x,start_bullet_y;//in case bullet confined with enemy
            enemy[i].x = cameraPosition[0]+WIDTH + rand() % 128;
            start_bullet_x=enemy[i].x;
            enemy[i].y =  rand() % 300;
            start_bullet_y=enemy[i].y;
            while(((enemy[i-1].y-enemy[i].y)>=(enemy[0].height)*-1)&&((enemy[i-1].y-enemy[i].y)<=(enemy[0].height))){
                enemy[i].y =  rand() % 300;
            }
            enemy[i].enemy_pic =  al_load_bitmap("./image/enemy_attack.png");
            enemy[i].width = al_get_bitmap_width(enemy[i].enemy_pic);
            enemy[i].height = al_get_bitmap_height(enemy[i].enemy_pic);
            enemy[i].state=LIVE;
            //print bullet
            int k=100-enemy[i].bullet_num;
            enemy[i].bullet[k].bullet_pic=al_load_bitmap("./image/bullet_enemy.png");
            enemy[i].bullet[k].width=al_get_bitmap_width(enemy[i].bullet[0].bullet_pic);
            enemy[i].bullet[k].height=al_get_bitmap_height(enemy[i].bullet[0].bullet_pic);
            enemy[i].bullet[k].x=start_bullet_x;
            enemy[i].bullet[k].y=start_bullet_y;
            enemy[i].bullet[k].state=ACTIVE;
            enemy[i].bullet_num--;
        }
        count_enemy += 3;
    }
    //enemy&enemy's bullet update
    for(int i=0; i<count_enemy; i++){
            if((enemy[i].state!=DIE)||(enemy[i].state!=Just_DIE)){
                    enemy[i].x -= 1;
            }
           enemy[i].bullet[0].x-=3;
    }
    //my bullet update
    for(int i=0;i<=10000-chara.bullet_num;i++){
        if((my_bullet[i].x>stage_width)||(my_bullet[i].x<0)){
            continue;
        }
        if (my_bullet[i].dir==true){
            my_bullet[i].x+=10;
        }else{
            my_bullet[i].x-=10;
        }
    }

    //my bullet state and detection
    int bullet_sx, bullet_sy, bullet_ex, bullet_ey;
    for(int i=0;i<count_enemy;i++){
        for(int j=0;j <10000-chara.bullet_num;j++){
            if (my_bullet[j].state == NON_ACTIVE || enemy[i].state == DIE||enemy[i].state==Just_DIE){
                continue;
            }
            bullet_sx = my_bullet[j].x;
            bullet_sy = my_bullet[j].y;
            bullet_ex = bullet_sx + my_bullet[j].width;
            bullet_ey = bullet_sy + my_bullet[j].height;

            //detect collision and effective collision
            if (My_Collision(enemy[i].x, enemy[i].y, enemy[i].width, enemy[i].height, bullet_sx, bullet_sy, bullet_ex, bullet_ey)){
                enemy_HP--;
                my_bullet[j].state = NON_ACTIVE;
                enemy[i].state = Just_DIE;
                //initiate explosion picture
                enemy[i].enemy_die_pic = al_load_bitmap("./image/enemy_die1.png");
                //explosion sound
                enemy_die_sample = al_load_sample("./sound/enemy_die_explosion.wav");
                enemy[i].die_sound  = al_create_sample_instance(enemy_die_sample);
                al_set_sample_instance_playmode(enemy[i].die_sound, ALLEGRO_PLAYMODE_ONCE);
                al_attach_sample_instance_to_mixer(enemy[i].die_sound, al_get_default_mixer());
                al_set_sample_instance_gain(enemy[i].die_sound, 1.5) ;
                printf("enemy_HP:%d\n",enemy_HP);
            }
        }
    }

    //detect enemy bullet hit on character
    int enemy_bullet_sx,enemy_bullet_sy,enemy_bullet_ex,enemy_bullet_ey;

    for(int i=0;i<count_enemy;i++){
            //int k=100-enemy[i].bullet_num;
             if (enemy[i].bullet[0].state == NON_ACTIVE){
                continue;
            }
            enemy_bullet_sx = enemy[i].bullet[0].x;
            enemy_bullet_sy = enemy[i].bullet[0].y;
            enemy_bullet_ex = enemy_bullet_sx+enemy[i].bullet[0].width;
            enemy_bullet_ey = enemy_bullet_sy+enemy[i].bullet[0].height;
            if ((Enemy_Collision(chara.x, chara.y, chara.width, chara.height, enemy_bullet_sx, enemy_bullet_sy, enemy_bullet_ex, enemy_bullet_ey))&&(enemy_bullet_ex>chara.x)){
                enemy[i].bullet[0].state=NON_ACTIVE;
            }
            if(enemy[i].bullet[0].state==NON_ACTIVE){
                    chara_HP--;
                    chara_hurt = al_load_sample("./sound/hit_target.mp3");
                    chara.chara_hurt_sound  = al_create_sample_instance(chara_hurt);
                    al_set_sample_instance_playmode(chara.chara_hurt_sound, ALLEGRO_PLAYMODE_ONCE);
                    al_attach_sample_instance_to_mixer(chara.chara_hurt_sound, al_get_default_mixer());
                    al_set_sample_instance_gain(chara.chara_hurt_sound, 5) ;
                    chara_been_shoot=true;
                    printf("chara_hp:%d\n",chara_HP);
            }
    }

    if(enemy_HP<=0){
        judge_next_window=true;
    }
    if (chara_HP<=0){
        judge_next_window=true;
    }
}

void character_draw(){
    // with the state, draw corresponding image
    //if enemies die,don't print
    for(int i=0; i<count_enemy; i++){
        if ((enemy[i].state == DIE)){
            continue;
        }else if (enemy[i].state == Just_DIE){
            al_draw_bitmap(enemy[i].enemy_die_pic, enemy[i].x,  enemy[i].y,0);
            al_play_sample_instance(enemy[i].die_sound);
            enemy[i].state = DIE;
            continue;
        }
        al_draw_bitmap(enemy[i].enemy_pic, enemy[i].x, enemy[i].y,0);
    }
    for(int i=0; i<count_enemy; i++){

            if(enemy[i].bullet[0].state==NON_ACTIVE){

                if(chara_been_shoot==true){
                        al_play_sample_instance(chara.chara_hurt_sound);
                        chara_been_shoot=false;
                }

                continue;
            }
            al_draw_bitmap(enemy[i].bullet[0].bullet_pic, enemy[i].bullet[0].x, enemy[i].bullet[0].y, 0);
    }
    for(int i=0;i<10000-chara.bullet_num;i++){
            if (my_bullet[i].state == ACTIVE){
                if (my_bullet[i].dir==true){
                        al_draw_bitmap(my_bullet[i].bullet_pic,my_bullet[i].x,my_bullet[i].y,0);
                }else{
                        al_draw_bitmap(my_bullet[i].bullet_pic,my_bullet[i].x,my_bullet[i].y,ALLEGRO_FLIP_HORIZONTAL);
                }
            }
    }

    if( chara.state == STOP ){
        if( chara.dir )
            al_draw_bitmap(chara.img_move[0], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
        else
            al_draw_bitmap(chara.img_move[0], chara.x, chara.y, 0);
    }else if( chara.state == MOVE ){
        if( chara.dir ){
            if( chara.anime < chara.anime_time/2 ){
                al_draw_bitmap(chara.img_move[0], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
            }else{
                al_draw_bitmap(chara.img_move[1], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
            }
        }else{
            if( chara.anime < chara.anime_time/2 ){
                al_draw_bitmap(chara.img_move[0], chara.x, chara.y, 0);
            }else{
                al_draw_bitmap(chara.img_move[1], chara.x, chara.y, 0);
            }
        }
    }else if( chara.state == ATK ){
        if( chara.dir ){
            if( chara.anime < chara.anime_time/2 ){
                al_draw_bitmap(chara.img_atk[0], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
            }else{
                al_draw_bitmap(chara.img_atk[1], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
                al_play_sample_instance(chara.atk_Sound);
            }

        }else{
            if( chara.anime < chara.anime_time/2 ){
                al_draw_bitmap(chara.img_atk[0], chara.x, chara.y, 0);

            }else{
                al_draw_bitmap(chara.img_atk[1], chara.x, chara.y, 0);
                al_play_sample_instance(chara.atk_Sound);

            }
        }
    }

}
void character_destory(){
    for(int i=0 ; i<=1 ; i++){
            al_destroy_bitmap(chara.img_atk[i]);
            al_destroy_bitmap(chara.img_move[i]);
    }
    al_destroy_sample_instance(chara.atk_Sound);
    for(int i=0; i<count_enemy; i++){
        if ((enemy[i].state == DIE)||(enemy[i].state==Just_DIE)){
                al_destroy_sample_instance(enemy[i].die_sound);
        }
    }
     al_destroy_sample_instance(chara.chara_hurt_sound);
}
