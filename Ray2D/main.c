#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>

#define PI 3.1415926535
#define P2 PI/2
#define P3 3*PI/2
#define DR 0.0174533

int FOV = 60; // in degrees

#define fullWindowRender 1
int renderWidth = 640;
int renderHeight = 480;
#define renderOffsetY 0
#define renderOffsetX 0
int rayDetail = 180;
#define dynamicDetalization 0
#define screenWidth 540
#define screenHeight 480
#define frameRate 60

#define mapX  24
#define mapY  15
#define mapS 64

int map[]=
{
 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,
 1,0,1,0,1,0,1,0,0,0,1,0,0,0,1,1,1,12,1,11,1,10,1,1,
 1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,1,
 1,0,1,0,1,0,1,0,0,0,1,1,1,0,4,0,0,0,0,0,0,0,0,1,
 1,0,0,0,1,0,1,0,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,9,
 1,1,1,0,1,0,0,0,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1,
 1,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,8,
 1,0,1,1,1,0,1,1,0,1,0,1,1,0,1,0,0,0,0,0,0,0,0,1,
 1,0,0,0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,7,
 1,1,1,0,1,0,1,0,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0,1,
 1,0,0,0,1,0,1,0,1,0,0,0,0,0,1,1,3,1,5,1,6,1,1,1,
 1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,
 1,0,1,1,0,1,1,0,1,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,
 1,0,0,1,0,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,
 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,
};


void msleep(unsigned int milliseconds) {

    sfClock *clock = sfClock_create();

    sfTime time = sfClock_getElapsedTime(clock);

    sfInt64 microseconds = sfTime_asMicroseconds(time);

    sfInt64 target_microseconds = microseconds + (milliseconds * 1000);


    while (microseconds < target_microseconds) {

        time = sfClock_getElapsedTime(clock);

        microseconds = sfTime_asMicroseconds(time);

    }


    sfClock_destroy(clock);

}

sfTexture* brickwall[64];
sfTexture* sampleTexture[64];
sfTexture* rickroll[64];
sfTexture* ssyplogo[64];
sfTexture* yaroslav[64];
sfTexture* sanya[64];
sfTexture* igor[64];
sfTexture* tanya[64];
sfTexture* roma[64];
sfTexture* svyatoslav[64];
sfTexture* lisa[64];
sfTexture* natali[64];
void load(){
    for (int i = 0; i < 64; i++){
        sfIntRect sfr = {i, 0, 1, 64};
        sfTexture* brick = sfTexture_createFromFile("wallx64.png", &sfr);
        brickwall[i] = brick;
    }
    for (int i = 0; i < 64; i++){
        sfIntRect sfr = {i, 0, 1, 3642};
        sfTexture* brick = sfTexture_createFromFile("doorx64.png", &sfr);
        sampleTexture[i] = brick;
    }
    for (int i = 0; i < 64; i++){
        sfIntRect sfr = {i, 0, 1, 64};
        sfTexture* brick = sfTexture_createFromFile("qrx64.png", &sfr);
        rickroll[i] = brick;
    }
    for (int i = 0; i < 64; i++){
        sfIntRect sfr = {i, 0, 1, 64};
        sfTexture* brick = sfTexture_createFromFile("ssyp.png", &sfr);
        ssyplogo[i] = brick;
    }
        for (int i = 0; i < 64; i++){
        sfIntRect sfr = {i, 0, 1, 64};
        sfTexture* brick = sfTexture_createFromFile("yaroslav.png", &sfr);
        yaroslav[i] = brick;
    }
        for (int i = 0; i < 64; i++){
        sfIntRect sfr = {i, 0, 1, 64};
        sfTexture* brick = sfTexture_createFromFile("sanya.png", &sfr);
        sanya[i] = brick;
    }
            for (int i = 0; i < 64; i++){
        sfIntRect sfr = {i, 0, 1, 64};
        sfTexture* brick = sfTexture_createFromFile("igor.png", &sfr);
        igor[i] = brick;
    }
            for (int i = 0; i < 64; i++){
        sfIntRect sfr = {i, 0, 1, 64};
        sfTexture* brick = sfTexture_createFromFile("tanya.png", &sfr);
        tanya[i] = brick;
    }
            for (int i = 0; i < 64; i++){
        sfIntRect sfr = {i, 0, 1, 64};
        sfTexture* brick = sfTexture_createFromFile("roma.png", &sfr);
        roma[i] = brick;
    }
            for (int i = 0; i < 64; i++){
        sfIntRect sfr = {i, 0, 1, 64};
        sfTexture* brick = sfTexture_createFromFile("svyatoslav.png", &sfr);
        svyatoslav[i] = brick;
    }
            for (int i = 0; i < 64; i++){
        sfIntRect sfr = {i, 0, 1, 64};
        sfTexture* brick = sfTexture_createFromFile("lisa.png", &sfr);
        lisa[i] = brick;
    }
            for (int i = 0; i < 64; i++){
        sfIntRect sfr = {i, 0, 1, 64};
        sfTexture* brick = sfTexture_createFromFile("natali.png", &sfr);
        natali[i] = brick;
    }
}

int v = 0;


float degToRad(int a) { return a*M_PI/180.0;}
int NEED2D = 0;
int oldmpos = 0;

typedef struct {
int w,a,s,d,f;
}ButtonKeys; ButtonKeys Keys;

void drawMap2D(sfRenderWindow* window)
{
 int x,y,xo,yo;
 for(y=0;y<mapY;y++)
 {
  for(x=0;x<mapX;x++)
  {

    xo=x*mapS; yo=y*mapS;
    sfConvexShape* quad = sfConvexShape_create();
    sfConvexShape_setPointCount(quad, 4);
    sfConvexShape_setPoint(quad, 0, (sfVector2f){0 + xo + 1, 0 + yo + 1});
    sfConvexShape_setPoint(quad, 1, (sfVector2f){0 + xo + 1, mapS + yo - 1});
    sfConvexShape_setPoint(quad, 2, (sfVector2f){mapS + xo - 1, mapS + yo - 1});
    sfConvexShape_setPoint(quad, 3, (sfVector2f){mapS + xo - 1, 0 + yo + 1});

    if(map[y*mapX+x]>0){ sfConvexShape_setFillColor(quad, sfColor_fromRGB(255, 255, 255));} else{ sfConvexShape_setFillColor(quad, sfColor_fromRGB(0, 0, 0));}

    sfRenderWindow_drawConvexShape(window, quad, NULL);

    sfConvexShape_destroy(quad);

  }
 }
}

////////////////////////////* PLAYER THINGS *///////////////////////////////
float px, py, pdx, pdy, pa;

void drawPlayer2D(sfRenderWindow* window){
    sfCircleShape* player = sfCircleShape_create();
    sfCircleShape_setRadius(player, 3);
    sfCircleShape_setFillColor(player, sfColor_fromRGB(255, 220, 40));
    sfCircleShape_setPosition(player, (sfVector2f){px - 2, py - 2});
    sfRenderWindow_drawCircleShape(window, player, NULL);

    sfVertex lines[2];
    lines[0].color = sfColor_fromRGB(255, 220, 40);
    lines[0].position = {px, py};
    lines[1].color = sfColor_fromRGB(255, 220, 40);
    lines[1].position = {px + pdx * 5, py + pdy * 5};
    sfRenderWindow_drawPrimitives(window, lines, 2, sfLinesStrip, NULL);

}

void buttons(){

    if(Keys.a){ pa-=0.1; if(pa < 0){ pa += 2*PI;} pdx=cos(pa)*5; pdy=sin(pa)*5;}
    if(Keys.d){ pa+=0.1; if(pa > 2*PI){ pa -= 2*PI;} pdx=cos(pa)*5; pdy=sin(pa)*5;}

    int xo = 0; if (pdx < 0) {xo = -20;} else {xo = 20;}
    int yo = 0; if (pdy < 0) {yo = -20;} else {yo = 20;}
    int ipx = px/mapS, ipx_add_xo=(px+xo)/mapS, ipx_sub_xo=(px-xo)/mapS;
    int ipy = py/mapS, ipy_add_yo=(py+yo)/mapS, ipy_sub_yo=(py-yo)/mapS;

    if(Keys.w){
        if (map[ipy*mapX + ipx_add_xo]==0 || map[ipy*mapX + ipx_add_xo]==2){px+=pdx*0.8;}
        if (map[ipy_add_yo*mapX + ipx]==0 || map[ipy_add_yo*mapX + ipx]==2){py+=pdy*0.8;}
    }
    if(Keys.s){
        if (map[ipy_add_yo*mapX + ipx]==0 || map[ipy_add_yo*mapX + ipx]==2){px-=pdx*0.8;}
        if (map[ipy_sub_yo*mapX + ipx]==0 || map[ipy_sub_yo*mapX + ipx]==2){py-=pdy*0.8;}
    }
    if (Keys.f){
        if (map[ipy*mapX + ipx_add_xo]==2){v = 1;}
        if (map[ipy_add_yo*mapX + ipx]==2){v = 1;}
    }

}

void buttonsWorker(){
    if(sfKeyboard_isKeyPressed(sfKeyA)){ Keys.a = 1; }
    if(sfKeyboard_isKeyPressed(sfKeyD)){ Keys.d = 1; }
    if(sfKeyboard_isKeyPressed(sfKeyW)){ Keys.w = 1; }
    if(sfKeyboard_isKeyPressed(sfKeyS)){ Keys.s = 1; }
    if(sfKeyboard_isKeyPressed(sfKeyF)){ Keys.f = 1; }


}

void buttonsUnworker(){
    if(!sfKeyboard_isKeyPressed(sfKeyA)){ Keys.a = 0; }
    if(!sfKeyboard_isKeyPressed(sfKeyD)){ Keys.d = 0; }
    if(!sfKeyboard_isKeyPressed(sfKeyW)){ Keys.w = 0; }
    if(!sfKeyboard_isKeyPressed(sfKeyS)){ Keys.s = 0; }
    if(sfKeyboard_isKeyPressed(sfKeyF)){ Keys.f = 0; }

}

////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////RAYCAST DRAWING//////////////////////////////////////

float dist(float ax, float ay, float bx, float by, float ang){
    return sqrt((bx-ax) * (bx-ax) + (by-ay) * (by-ay));
}

int drawcalls = 0;

void drawbg(sfRenderWindow* window){
    sfRectangleShape* quad = sfRectangleShape_create();
    sfRectangleShape_setSize(quad, (sfVector2f){renderWidth, renderHeight/2});
    sfRectangleShape_setPosition(quad, (sfVector2f){0, 0});
    sfRectangleShape_setFillColor(quad, sfColor_fromRGB(70, 130, 245));
    if (!NEED2D) sfRenderWindow_drawRectangleShape(window, quad, NULL);
    sfRectangleShape_setSize(quad, (sfVector2f){renderWidth, renderHeight/2});
    sfRectangleShape_setPosition(quad, (sfVector2f){0, renderHeight/2});
    sfRectangleShape_setFillColor(quad, sfColor_fromRGB(60, 60, 80));
    if (!NEED2D) sfRenderWindow_drawRectangleShape(window, quad, NULL);
    sfRectangleShape_destroy(quad);
}

void drawRays2D(sfRenderWindow* window){
    int maptileX = 0, maptileY = 0, maptile;

    float smallestdist = 10000000000;

    int r, mx, my, mp, dof;
    float rx, ry, ra, xo, yo;


    ra = pa-(DR*(FOV/2)); if (ra<0) {ra += 2*PI;} if (ra>2*PI) {ra -= 2*PI;}


    for(r=0;r<rayDetail;r++){

    //--horiz detecting--
    float disH = 1000000000, hx=px, hy=py;
    dof = 0;
    float aTan = -1/tan(ra);
    if (ra>PI){
        ry = (((int)py/mapS)*mapS) - 0.0001;
        rx=(py-ry)*aTan+px;
        yo = -mapS;
        xo = -yo*aTan;
    }
    if (ra<PI){
        ry = (((int)py/mapS)*mapS) + mapS;
        rx=(py-ry)*aTan+px;
        yo = mapS;
        xo = -yo*aTan;
    }
    if (ra==0 || ra==PI){
        rx = px;
        ry = py;
        dof = mapX;
    }
    while (dof < mapX){
        mx = (int)(rx)/mapS;
        my = (int)(ry)/mapS;
        mp = my*mapX + mx; if (mp > mapX*mapY-1) {mp = mapX*mapY-1;};

        if (mp>0 && mp < mapX*mapY && map[mp]>0){
            maptileX = map[mp];
            hx = rx;
            hy = ry;
            disH = dist(px,py,hx,hy,ra);
            dof = mapX;
        }
        else{
            rx += xo;
            ry += yo;
            dof += 1;
        }
    }


     //--vert detecting--

    float disV = 1000000000, vx=px, vy=py;
    dof = 0;
    float nTan = -tan(ra);
    if (ra>P2 && ra<P3){
        rx = (((int)px/mapS)*mapS)-0.0001;
        ry = (px-rx)*nTan+py;
        xo = -mapS;
        yo = -xo*nTan;
    }
    if (ra<P2 || ra>P3){
        rx = (((int)px/mapS)*mapS)+mapS;
        ry = (px-rx)*nTan+py;
        xo = mapS;
        yo = -xo*nTan;
    }
    if (ra==0 || ra==PI){
        rx = px;
        ry = py;
        dof = mapY;
    }
    while (dof < mapY){
        mx = (int)(rx)/mapS;
        my = (int)(ry)/mapS;
        mp = my*mapX + mx; if (mp > mapX*mapY-1) {mp = mapX*mapY-1;};
        if (mp>0 && mp < mapX*mapY && map[mp]>0){
            maptileY = map[mp];
            vx = rx;
            vy = ry;
            disV = dist(px,py,vx,vy,ra);
            dof = mapY;
        }
        else{
            rx += xo;
            ry += yo;
            dof += 1;
        }
    }

    float ctp = 1;

    if (disV < disH){
    maptile = maptileY;
        rx = vx;
        ry = vy;
        ctp = 1;
    }
    else {
    maptile = maptileX;
        rx = hx;
        ry = hy;
        ctp = 0.6;
    }

    float rayDistance = dist(px, py, rx, ry, pa);
    if (rayDistance < smallestdist) smallestdist = rayDistance;

    sfVertex lines[2];
    lines[0].color = sfColor_fromRGB(0, 204, 0);
    lines[0].position = {px, py};
    lines[1].color = sfColor_fromRGB(0, 204, 0);
    lines[1].position = {rx, ry};

    if (disV < disH) {
            rx = vx;
            ry = vy;
            disH = disV;
        }

    if (NEED2D) sfRenderWindow_drawPrimitives(window, lines, 2, sfLinesStrip, NULL);


    //--trying to set up walls--

    float ca = pa-ra; if (ca<0) {ca += 2*PI;} if (ca>2*PI) {ca -= 2*PI;} rayDistance *= cos(ca);
    float wallH=(mapS*renderHeight)/(rayDistance*1.5);

    float wallOffset = (renderHeight/2+renderOffsetY)-wallH/2;

    float tx;
    if (ctp == (float)0.6) {tx = (int)(rx)%64;}
    else {tx = (int)(ry)%64;}

    sfSprite* drawer = sfSprite_create();
    switch(maptile){
        case 1:
            sfSprite_setTexture(drawer, brickwall[(int)tx], sfFalse);
            break;
        case 2:
            sfSprite_setTexture(drawer, sampleTexture[(int)tx], sfFalse);
            break;
        case 3:
            sfSprite_setTexture(drawer, rickroll[(int)tx], sfFalse);
            break;
        case 4:
            sfSprite_setTexture(drawer, ssyplogo[(int)tx], sfFalse);
            break;
        case 5:
            sfSprite_setTexture(drawer, yaroslav[(int)tx], sfFalse);
            break;
        case 6:
            sfSprite_setTexture(drawer, sanya[(int)tx], sfFalse);
            break;

        case 7:
            sfSprite_setTexture(drawer, igor[(int)tx], sfFalse);
            break;
        case 8:
            sfSprite_setTexture(drawer, tanya[(int)tx], sfFalse);
            break;
        case 9:
            sfSprite_setTexture(drawer, roma[(int)tx], sfFalse);
            break;
        case 10:
            sfSprite_setTexture(drawer, svyatoslav[(int)tx], sfFalse);
            break;
        case 11:
            sfSprite_setTexture(drawer, lisa[(int)tx], sfFalse);
            break;
        case 12:
            sfSprite_setTexture(drawer, natali[(int)tx], sfFalse);
            break;

    }
    sfSprite_setPosition(drawer, (sfVector2f){512, 350});

    sfSprite_setPosition(drawer, (sfVector2f){r*(renderWidth/rayDetail), wallOffset});
    sfSprite_setScale(drawer, (sfVector2f){(renderWidth/rayDetail), (wallH/64)});//*(ty+1)});
    sfSprite_setColor(drawer, sfColor_fromRGB(ctp*255, ctp*255, ctp*255));
    if (!NEED2D) sfRenderWindow_drawSprite(window, drawer, NULL);
    sfSprite_destroy(drawer);
    drawcalls++;



    ra += DR/((float)(rayDetail)/FOV); if (ra<0) {ra += 2*PI;} if (ra>2*PI) {ra -= 2*PI;}



 }


}

////////////////////////////////////////////////////////////////////////////////////


void init(){
    px=95; py=95; pa=P2;
    pdx=cos(degToRad(pa)); pdy=-sin(degToRad(pa));
}



int main()
{
    init();
    load();

    sfRenderWindow* window = sfRenderWindow_create((sfVideoMode){screenWidth, screenHeight, 32}, "simple Ray2D engine", sfDefaultStyle, NULL);
    sfRenderWindow_setFramerateLimit(window, frameRate);
    sfFloatRect view_rectangle = {0, 0, 0, 0};
    sfView* new_view = sfView_createFromRect(view_rectangle);

    sfMusic* music = sfMusic_createFromFile("bg.ogg");
    if (!music)
        return EXIT_FAILURE;
    sfMusic_setLoop(music, sfTrue);
    sfMusic_play(music);


    while (sfRenderWindow_isOpen(window))
    {

        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event))
        {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
            if (event.type == sfEvtKeyPressed){
                if(event.key.code == sfKeyQ){ sfRenderWindow_close(window);}
                if(event.key.code == sfKeyE){ NEED2D = !NEED2D;}
            }

            if (event.type == sfEvtResized){
                view_rectangle.width = event.size.width;
                view_rectangle.height = event.size.height;
                sfView_reset(new_view, view_rectangle);
                sfRenderWindow_setView(window, new_view);
            }
        }


        sfRenderWindow_clear(window, sfColor_fromRGB(0, 0, 0));
        buttonsWorker();
        buttonsUnworker();
        buttons();
        if (NEED2D) drawMap2D(window);
        drawbg(window);
        drawRays2D(window);
        printf("draw calls per frame by Rays2D func: %d\n", drawcalls);
        drawcalls = 0;
        if (NEED2D) drawPlayer2D(window);
        if (v) sfRenderWindow_close(window);;


        sfRenderWindow_display(window);
    }

    return EXIT_SUCCESS;
}
