#pragma once
#include <SDL.h>
#include <SDL_mixer.h>

//#define ABOUT_MESSAGE "This game was created by kra53n " \
//                      "(https://github.com/kra53n) for programming course " \
//                      "project in the 1st year of university. He is really " \
//                      "tired to do it. When he choosed this project he didn't " \
//                      "expect how hard it will be."
#define ABOUT_MESSAGE "Курсовую работу по программированию по теме 'Аркадный " \
                      "космический симулятор' выполнил студент БГТУ группы " \
                      "О-21-ИВТ-2-ПО-Б Бахтин Григорий"
#define ABOUT_FONTNAME "assets/fonts/MontserratAlternates-Regular.otf"


// GAME CONFIGURATION

enum GAME_STATES
{
    GAME_STATE_MENU,
    GAME_STATE_PLAY,
    GAME_STATE_SETTINGS,
    GAME_STATE_ABOUT,
    GAME_STATE_EXIT,

    GAME_STATE_LEVELS,

    GAME_STATE_SOLO,
    GAME_STATE_SEAT,

    GAME_STATE_LOOSE,
    GAME_STATE_WIN,

    GAME_STATE_PLAYER1_WIN,
    GAME_STATE_PLAYER2_WIN,
};

struct Keys
{
    bool w          = false;
    bool s          = false;
    bool a          = false;
    bool d          = false;
    bool space      = false;

    bool left       = false;
    bool right      = false;
    bool up         = false;
    bool down       = false;
    bool rctrl      = false;

    bool enter      = false;
    bool escape     = false;

    bool leftClick  = false;
    int  mouse_x;
    int  mouse_y;
};


// MUSIC CONFIGURATION

#define MUSIC_MAIN_THEME   "assets/audio/music/Space Music Royalty Free - Music Unlimited - No Copyright Music.wav"
#define MUSIC_ABOUT_THEME  "assets/audio/music/unɔuɐƆ (NOITIDE AGES) [prod. ScrewStache].wav"

enum MUSIC_EFFECTS_TYPES
{
    MUSIC_BULLET_1,
	MUSIC_BULLET_2,
	MUSIC_BUTTON,
	MUSIC_COLLIDED,
	MUSIC_DESTROYED,
	MUSIC_BULLET_ENEMY,
	MUSIC_LOOSE,
};

#define MUSIC_EFFECTS_NUM 7

struct MUSIC_EFFECT_INFO
{
    int         effect;
    const char* filename;
    Mix_Chunk*  chunk;
};

extern MUSIC_EFFECT_INFO MusicEffects[MUSIC_EFFECTS_NUM];


// LEVEL CONFIGURAION

#define LEVEL_FILE_FILENAME     "config/levels/levels.txt"
#define LEVEL_FONT_SIZE         80
#define LEVEL_VERTICAL_DISTANCE 15
#define LEVEL_DELAY_BUTTONS     100
#define LEVEL_FONT_TRANSPARENT  100
#define LEVEL_BONUS_TIME        10'000
#define LEVEL_BONUS_TIME_COEFF  100


// LEVEL CONFIGURAION

#define RECORD_FILENAME_PREFIX  "data/records_in_"
#define RECORD_FILENAME_POSTFIX "_level.txt"


// MENU CONFIGURATION

#define         MENU_FONTNAME                 "assets/fonts/Voyager Heavy.otf"
#define         MENU_FONT_SIZE                50
#define         MENU_FONT_VERTICAL_DISTANCE   40
#define         MENU_DELAY_BUTTONS            200

const SDL_Color COLOR_OF_ACTIVE_OPTION      = { 255, 0, 0, 255 };
const SDL_Color COLOR_OF_NON_ACTIVE_OPTION  = { 150, 150, 220, 255 };

struct MENU_INFO
{
    const char* name;
    int         mode;
};

#define MAIN_MENU_NUM 4

const MENU_INFO MAIN_MENU[MAIN_MENU_NUM] = {
    { "start",    GAME_STATE_PLAY     },
    { "settings", GAME_STATE_SETTINGS },
    { "about",    GAME_STATE_ABOUT    },
    { "exit",     GAME_STATE_EXIT     },
};

#define MODE_MENU_NUM 2

const MENU_INFO MODE_MENU[MODE_MENU_NUM] = {
    { "solo",     GAME_STATE_LEVELS },
    { "hot-seat", GAME_STATE_SEAT   },
};


// BACKGROUND CONFIGURATION

#define BACKGROUND_FILENAMES_NUM 4
#define BACKOGRUND_MOVE_SPEED    6

const char FILENAMES[BACKGROUND_FILENAMES_NUM][41] = {
    "assets/images/backgrounds/bg1.png",
    "assets/images/stars/Nebula Aqua-Pink.png",
    "assets/images/stars/Nebula Blue.png",
    "assets/images/stars/Nebula Red.png",
};


// PARTICLES CONFIGURATION

#define PARTICLES_FILENAMES_NUM 3

const char PARTICLES_FILENAMES[PARTICLES_FILENAMES_NUM][41] = {
    "assets/images/backgrounds/particles1.png",
    "assets/images/backgrounds/particles2.png",
    "assets/images/backgrounds/particles3.png",
};


// BULLET CONFIGURATION

struct BULLET_INFO
{
    char     filename[40];
    int      speed;
    int      delay;
    int      damage;
    int      chunk;
};

#define BULLETS_TYPE_NUM 4

const BULLET_INFO BULLETS[BULLETS_TYPE_NUM] = {
    { "assets/images/bullets/bullet1.png", 80,  200,  5,  MUSIC_BULLET_1 },
    { "assets/images/bullets/bullet2.png", 100, 800,  10, MUSIC_BULLET_2 },
    { "assets/images/bullets/bullet3.png", 10,  1000, 3,  MUSIC_BULLET_1 },
    { "assets/images/bullets/bullet3.png", 10,  1000, 4,  MUSIC_BULLET_2 },
};


// SHIP CONFIGURATION

#define ENGINE_FRAMES_NUM 4

#define ENGINE_FILENAME      "assets/images/engine/engine_fire"
#define ENGINE_FILENAME_TYPE "png"
#define ENGINE_FRAMES         15
#define ENGINE_DELAY          100

#define SHIP_SCALE_COEFF          3
#define SHIP_DAMAGE               0.1
#define SHIP_MAX_VEL              10
#define SHIP_MAX_ANGULAR_VEL      5
#define SHIP_ANGULAR_ACC          0.5
#define SHIP_INCREASE_ANGULAR_ACC 1.05
#define SHIP_RADIUS_NARROWING     10

#define SHIP_FILENAME1 "assets/images/ships/ship1.png"
#define SHIP_FILENAME2 "assets/images/ships/ship2.png"

enum SHIP_INSTANCES { SHIP1, SHIP2 };

struct ShipActions
{
    bool up;
    bool down;
    bool left;
    bool right;
    bool shoot;
};

const ShipActions SHIP1_ACTIONS = {
    SDL_SCANCODE_W,
    SDL_SCANCODE_S,
    SDL_SCANCODE_A,
    SDL_SCANCODE_D,
    SDL_SCANCODE_SPACE,
};

const ShipActions SHIP2_ACTIONS = {
    SDL_SCANCODE_UP,
    SDL_SCANCODE_DOWN,
    SDL_SCANCODE_LEFT,
    SDL_SCANCODE_RIGHT,
    SDL_SCANCODE_RCTRL,
};


// ENEMY CONFIGURATION

#define ENEMY_FILENAME      "assets/images/enemy/enemy.png"
#define ENEMY_DAMAGE        0.25
#define ENEMY_BULLET_DAMAGE 5
#define ENEMY_HEALTH        200
#define EMEMY_MAX_SPEED     30
#define ENEMY_DELAY         100
#define ENEMY_SCALE_COEFF   4


// SCORE CONFIGURATION

#define SCORE_FONTNAME  "assets/fonts/Voyager Heavy.otf"
#define SCORE_FONT_SIZE 35


// EXPLOSION CONFIGURATION

#define EXPLOSION_FILENAME      "assets/images/explosion/explosion"
#define EXPLOSION_FILENAME_TYPE "png"
#define EXPLOSION_FRAMES         9
#define EXPLOSION_DELAY          100
#define EXPLOSION_SCALE_COEFF    4


// ASTEROIDS CONFIGURATION

struct ASTEROID_INFO
{
    char     filename[40];
    float    mass;
    unsigned health;
    unsigned damage;
};

#define ASTEROIDS_TYPE_NUM 9

const ASTEROID_INFO ASTEROIDS[ASTEROIDS_TYPE_NUM] = {
    { "assets/images/asteroids/iron.png",        7.874,      10, 2 },
    { "assets/images/asteroids/large metal.png", 10.3 * 2,   10, 2 },
    { "assets/images/asteroids/large rock.png",  4.34 * 2,   10, 2 },
    { "assets/images/asteroids/medium rock.png", 4.34 * 0.9, 10, 2 },
    { "assets/images/asteroids/rock.png",        4.34,       10, 2 },
    { "assets/images/asteroids/silicon.png",     4.6,        10, 2 },
    { "assets/images/asteroids/silver.png",      10.49,      10, 2 },
    { "assets/images/asteroids/small rock.png",  4.34 * 0.8, 10, 2 },
    { "assets/images/asteroids/titanium.png",    6.505,      10, 2 },
};
