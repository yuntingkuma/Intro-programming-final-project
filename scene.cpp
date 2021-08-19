#include "scene.h"

////memu have not done yet
////keyboard wasd can't not input
ALLEGRO_FONT *font = NULL;
ALLEGRO_FONT *font_about = NULL;
ALLEGRO_FONT*font_about_2=NULL;
ALLEGRO_FONT*font_win1=NULL;
ALLEGRO_FONT*font_win2=NULL;
ALLEGRO_FONT*font_lose1=NULL;
ALLEGRO_FONT*font_lose2=NULL;
ALLEGRO_BITMAP *background = NULL;
ALLEGRO_BITMAP *background_shin_figure = NULL;
ALLEGRO_BITMAP *background_enemy_figure = NULL;
ALLEGRO_BITMAP *background_enemy_5_hp[5] = {NULL};
ALLEGRO_BITMAP *background_enemy_0_hp[5] = {NULL};
ALLEGRO_BITMAP *background_chara_5_hp[5] = {NULL};
ALLEGRO_BITMAP *background_chara_0_hp[5] = {NULL};
ALLEGRO_BITMAP *background_menu = NULL;
ALLEGRO_BITMAP *background_menu2 = NULL;
ALLEGRO_BITMAP *background_about = NULL;
ALLEGRO_BITMAP *background_lose = NULL;
ALLEGRO_BITMAP *background_win = NULL;
ALLEGRO_SAMPLE *song2=NULL;
ALLEGRO_SAMPLE *song_lose=NULL;
ALLEGRO_SAMPLE *song_win=NULL;
ALLEGRO_SAMPLE_INSTANCE *sample_instance2;
ALLEGRO_SAMPLE_INSTANCE *sample_instance_lose;
ALLEGRO_SAMPLE_INSTANCE *sample_instance_win;
// function of menu
void menu_init(){
    if ((window==1)&&(menu_select==0)){ ////
        font = al_load_ttf_font("./font/BebasNeue-Regular.ttf",20,0);
        background_menu = al_load_bitmap("./image/menu.jpg");
        background_menu2 = al_load_bitmap("./image/menu1.jpg");
    }else if((window==3)&&(menu_select==1)){
        font_about = al_load_ttf_font("./font/jf-openhuninn-1.1.ttf",12,0);
        font_about_2 = al_load_ttf_font("./font/BebasNeue-Regular.ttf",20,0);
        background_about = al_load_bitmap("./image/undertaker_original.jpg");
    }
}
void menu_process(ALLEGRO_EVENT event){
    if (event.type == ALLEGRO_EVENT_KEY_UP){
            if (event.keyboard.keycode==ALLEGRO_KEY_UP){
                if ((menu_select > 0)&&(window==1)){
                    menu_select -= 1;
                    printf("W:menu_select:%d\n",menu_select);
                }else if (window==1){
                    menu_select = 2;
                    printf("W2:menu_select:%d\n",menu_select);
                }
            }else if(event.keyboard.keycode==ALLEGRO_KEY_DOWN){
                if(window==1){
                    menu_select = (menu_select + 1) % 3;
                    printf("S:menu_select:%d\n",menu_select);
                }
            }else if(event.keyboard.keycode==ALLEGRO_KEY_BACKSPACE){

                    printf("S1:menu_select:%d\n",menu_select);
                    judge_next_window = true;

            }else if(event.keyboard.keycode==ALLEGRO_KEY_ENTER){
                printf("enter:menu_select:%d\n",menu_select);
                judge_next_window = true;
            }
    }
}
void menu_draw(){
    if(window==1){
        al_clear_to_color(al_map_rgb(0,71,125));
        al_draw_bitmap(background_menu,0,0,0);
        al_draw_bitmap(background_menu2,  (WIDTH*3)/4-45, HEIGHT/5, 0);

        //draw menu_select
        for(int i=40 ; i<=120; i=i+40){
            al_draw_filled_rectangle( (WIDTH*3)/4-90,  HEIGHT/2+5+i, (WIDTH*3)/4+70,HEIGHT/2+35+i, al_map_rgb(255, 255, 255));
        }

        char menu_text[3][25]={"Press 'Enter' to start","About","Exit"};
        for (int i=0,j=0 ; i<=80 ; i=i+40,j++){
            al_draw_text(font, al_map_rgb(0,0,0), (WIDTH*3)/4-10, HEIGHT/2+50+i , ALLEGRO_ALIGN_CENTRE, menu_text[j]);
        }

        if (menu_select==0){
            al_draw_rectangle( (WIDTH*3)/4-90,  HEIGHT/2+45, (WIDTH*3)/4+70,HEIGHT/2+75, al_map_rgb(0, 0, 0),5);
        }else if(menu_select==1){
            al_draw_rectangle( (WIDTH*3)/4-90,  HEIGHT/2+85, (WIDTH*3)/4+70,HEIGHT/2+115, al_map_rgb(0,0, 0),5);
        }else if(menu_select==2){
            al_draw_rectangle( (WIDTH*3)/4-90,  HEIGHT/2+125, (WIDTH*3)/4+70,HEIGHT/2+155, al_map_rgb(0,0,0),5);
        }

    }else if(window==3){
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_bitmap(background_about,WIDTH/2-20,HEIGHT/5-40,0);
        //draw about_text
        al_draw_text(font_about_2,al_map_rgb(255,255,255),WIDTH/4-30,HEIGHT/13,0,"ABOUT");
        char about_text[12][70]={ "聖馬格諾利亞共和國每天都遭受著鄰國的無","的無人機「軍團」的侵略。幸好，共和國也",
        "成功研發出同型兵器「破壞神」來應對其攻","勢，並勉強在沒有人員傷亡的情況下，化解", "來自鄰國的威脅---表面上是如此。共和國官",
       "方對國民聲稱沒有人員傷亡，但是，實際上","傷亡者並非為零。因為在共合國全八十五個","行政區之外的「不存在的第 86 區」中，一",
       "群少年少女 正以 「有人駕駛的無人機」 ，","日夜奮戰不懈。率領一群年輕人出生入死的","少年辛，和身處遙遠後方，透過特殊通訊指揮",
       "他們的指揮官蕾娜，將會保護隊員和共合國的安全。"};
       for ( int i=0 ; i<=11 ; i++ ){
                al_draw_text(font_about, al_map_rgb(255,255,255), 35, HEIGHT*(2+i)/14, 0,about_text[i]);
       }
        //draw guideline
        al_draw_filled_rectangle((WIDTH*3)/4-70, HEIGHT*11/14, (WIDTH*3)/4+70,HEIGHT*13/14, al_map_rgb(255, 255, 255));
        char guide_text[3][35]={"方向鍵控制無人機移動","右Ctril發射砲彈攻擊軍團","按Enter返回menu"};
        for (int i=0,j=0 ; i<=40 ; i=i+20,j++){
                al_draw_text(font_about, al_map_rgb(0,0,0), (WIDTH*3)/4, (HEIGHT*11/14)+i, ALLEGRO_ALIGN_CENTRE, guide_text[j]);
        }
    }
}
void menu_destroy(){
    if(window==1){
        al_destroy_font(font);
        al_destroy_bitmap(background_menu2);
        al_destroy_bitmap(background_menu);
    }else if(window==3){
        al_destroy_bitmap(background_about);
        al_destroy_font(font_about);
        al_destroy_font(font_about_2);
    }else if (window==2){
        al_destroy_bitmap(background);
        al_destroy_bitmap(background_shin_figure);
        al_destroy_bitmap(background_enemy_figure);
        for (int i=0;i<5;i++){
            al_destroy_bitmap(background_enemy_5_hp[i]);
            al_destroy_bitmap(background_enemy_0_hp[i]);
        }
        character_destory();
        al_destroy_sample_instance(sample_instance2);
    }
}

// function of game_scene
void game_scene_init(){
    character_init();
    background = al_load_bitmap("./image/stage1.png");
    stage_width = al_get_bitmap_width(background);
    background_shin_figure = al_load_bitmap("./image/shin_figure.png");
    background_enemy_figure = al_load_bitmap("./image/enemy_figure.png");
    //load enemy hp5/hp0
    for (int i=0; i<5 ; i++){
            background_enemy_5_hp[i]= al_load_bitmap("./image/enemy_HP_5.png");
            background_enemy_0_hp[i] = al_load_bitmap("./image/enemy_HP_0.png");
    }
    //load character hp5/hp0
    for (int i=0; i<5 ; i++){
            background_chara_5_hp[i]= al_load_bitmap("./image/chara_HP_5.png");
            background_chara_0_hp[i] = al_load_bitmap("./image/chara_HP_0.png");
    }
    song2 = al_load_sample("./sound/ヒトリエ3分29秒_HITORIE.mp3");
    sample_instance2 = al_create_sample_instance(song2);
    al_set_sample_instance_playmode(sample_instance2,ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(sample_instance2,al_get_default_mixer());
    al_set_sample_instance_gain(sample_instance2,1);
    al_play_sample_instance(sample_instance2);
}

void game_scene_draw(){
    al_draw_bitmap(background, 0, 0, 0);
    al_draw_bitmap(background_shin_figure,cameraPosition[0],HEIGHT-110,0);
    al_draw_bitmap(background_enemy_figure,cameraPosition[0]+WIDTH-150,HEIGHT-90,0);
    //draw enemy/character hp
    for (int i=0,j=0;i<5;i++,j=j+30){
            al_draw_bitmap(background_enemy_5_hp[i],cameraPosition[0]+WIDTH-180-j,HEIGHT-60,0);
            al_draw_bitmap(background_chara_5_hp[i],cameraPosition[0]+130+j,HEIGHT-50,0);
    }
    if(enemy_HP==4){
            al_draw_bitmap(background_enemy_0_hp[4],cameraPosition[0]+WIDTH-300,HEIGHT-60,0);
    }else if(enemy_HP==3){
            al_draw_bitmap(background_enemy_0_hp[4],cameraPosition[0]+WIDTH-300,HEIGHT-60,0);
            al_draw_bitmap(background_enemy_0_hp[3],cameraPosition[0]+WIDTH-270,HEIGHT-60,0);
    }else if(enemy_HP==2){
            al_draw_bitmap(background_enemy_0_hp[4],cameraPosition[0]+WIDTH-300,HEIGHT-60,0);
            al_draw_bitmap(background_enemy_0_hp[3],cameraPosition[0]+WIDTH-270,HEIGHT-60,0);
            al_draw_bitmap(background_enemy_0_hp[2],cameraPosition[0]+WIDTH-240,HEIGHT-60,0);
    }else if(enemy_HP==1){
            al_draw_bitmap(background_enemy_0_hp[4],cameraPosition[0]+WIDTH-300,HEIGHT-60,0);
            al_draw_bitmap(background_enemy_0_hp[3],cameraPosition[0]+WIDTH-270,HEIGHT-60,0);
            al_draw_bitmap(background_enemy_0_hp[2],cameraPosition[0]+WIDTH-240,HEIGHT-60,0);
            al_draw_bitmap(background_enemy_0_hp[1],cameraPosition[0]+WIDTH-210,HEIGHT-60,0);
    }else if(enemy_HP<=0){
            for(int i=4,j=0;i>=0;i--,j=j+30){
                    al_draw_bitmap(background_enemy_0_hp[i],cameraPosition[0]+WIDTH-300+j,HEIGHT-60,0);
            }
    }
    if(chara_HP==4){
            al_draw_bitmap(background_chara_0_hp[4],cameraPosition[0]+250,HEIGHT-50,0);
    }else if(chara_HP==3){
            al_draw_bitmap(background_chara_0_hp[4],cameraPosition[0]+250,HEIGHT-50,0);
            al_draw_bitmap(background_chara_0_hp[3],cameraPosition[0]+220,HEIGHT-50,0);
    }else if(chara_HP==2){
            al_draw_bitmap(background_chara_0_hp[4],cameraPosition[0]+250,HEIGHT-50,0);
            al_draw_bitmap(background_chara_0_hp[3],cameraPosition[0]+220,HEIGHT-50,0);
            al_draw_bitmap(background_chara_0_hp[2],cameraPosition[0]+190,HEIGHT-50,0);
    }else if(chara_HP==1){
            al_draw_bitmap(background_chara_0_hp[4],cameraPosition[0]+250,HEIGHT-50,0);
            al_draw_bitmap(background_chara_0_hp[3],cameraPosition[0]+220,HEIGHT-50,0);
            al_draw_bitmap(background_chara_0_hp[2],cameraPosition[0]+190,HEIGHT-50,0);
            al_draw_bitmap(background_chara_0_hp[1],cameraPosition[0]+160,HEIGHT-50,0);
    }else if(chara_HP<=0){
            for(int i=4,j=0; i>=0 ; i--,j=j+30){
                    al_draw_bitmap(background_chara_0_hp[i],cameraPosition[0]+250-j,HEIGHT-50,0);
            }
    }
    character_draw();
    al_flip_display();
}
void game_scene_destroy(){
    al_destroy_sample_instance(sample_instance2);
    al_destroy_bitmap(background);
    al_destroy_bitmap(background_shin_figure);
    al_destroy_bitmap(background_enemy_figure);
    for (int i=0;i<5;i++){
        al_destroy_bitmap(background_enemy_5_hp[i]);
        al_destroy_bitmap(background_enemy_0_hp[i]);
    }
    character_destory();
}

///function of success scene
void success_scene_init(){
    font_win1= al_load_ttf_font("./font/jf-openhuninn-1.1.ttf",18,0);
    font_win2 = al_load_ttf_font("./font/BebasNeue-Regular.ttf",40,0);
    background_win = al_load_bitmap("./image/background_win.jpg");
    song_win = al_load_sample("./sound/86 - Eighty Six - Ending 2 Full-Hands Up to the Sky-by SawanoHiroyuki.mp3");
    sample_instance_win = al_create_sample_instance(song_win);
    al_set_sample_instance_playmode(sample_instance_win,ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(sample_instance_win,al_get_default_mixer());
    al_set_sample_instance_gain(sample_instance_win,1);
    al_play_sample_instance(sample_instance_win);
}

void success_scene_draw(){
    al_clear_to_color(al_map_rgb(255,255,255));
    al_draw_bitmap(background_win,cameraPosition[0]+17,0,0);
    al_draw_text(font_win2, al_map_rgb(255,255,255),cameraPosition[0]+60, 0 , ALLEGRO_ALIGN_CENTRE, "WIN");
    al_draw_text(font_win1, al_map_rgb(0,0,0), cameraPosition[0]+WIDTH/2, 305 , ALLEGRO_ALIGN_CENTRE, "一直以來，我們始終受到束縛，始終是個階下囚，");
    al_draw_text(font_win1, al_map_rgb(0,0,0), cameraPosition[0]+WIDTH/2, 305+18 , ALLEGRO_ALIGN_CENTRE, "而這樣的日子終於要結束了。");
    al_draw_text(font_win1, al_map_rgb(0,0,0), cameraPosition[0]+WIDTH/2, 305+36, ALLEGRO_ALIGN_CENTRE, "我們終於能夠決定自己的目的地，選擇自己想走的道路。");
}

void success_scene_destroy(){
    al_destroy_bitmap(background_win);
    al_destroy_sample_instance(sample_instance_win);
}

///function of end scene
void end_scene_init(){
    font_lose1= al_load_ttf_font("./font/jf-openhuninn-1.1.ttf",18,0);
    font_lose2= al_load_ttf_font("./font/BebasNeue-Regular.ttf",40,0);
    background_lose = al_load_bitmap("./image/lose.jpg");
    song_lose = al_load_sample("./sound/lose.mp3");
    sample_instance_lose = al_create_sample_instance(song_lose);
    al_set_sample_instance_playmode(sample_instance_lose,ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(sample_instance_lose,al_get_default_mixer());
    al_set_sample_instance_gain(sample_instance_lose,1);
    al_play_sample_instance(sample_instance_lose);
}

void  end_scene_draw(){
    al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_bitmap(background_lose,cameraPosition[0]+203.5,25,0);
    al_draw_text(font_lose2, al_map_rgb(255,255,255), cameraPosition[0]+30 , 30 , 0, "LOSE");
    al_draw_text(font_lose1, al_map_rgb(255,255,255), cameraPosition[0]+WIDTH/2, 325 , ALLEGRO_ALIGN_CENTRE, "就算知道自己注定要走上死刑台，但至少還能選擇走上去的方式");
}
void end_scene_destroy(){
    al_destroy_bitmap(background_lose);
    al_destroy_sample_instance(sample_instance_lose);
}
