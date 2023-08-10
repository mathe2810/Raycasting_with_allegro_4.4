/*
#include <stdio.h>
#include "allegro.h"
#include "math.h"






//
// Created by mathe on 02/08/2023.
//


#define P2 (M_PI/2)
#define P3 (3*M_PI/2)
#define DR 0.0174533

int depth[120];

int map[]=
        {
        2,2,2,2,2,3,2,2,
        2,0,1,0,0,0,0,2,
        2,0,1,0,0,0,0,2,
        2,0,4,0,0,0,0,2,
        2,0,1,1,4,2,0,2,
        2,0,0,0,0,0,0,2,
        2,0,3,1,2,0,0,2,
        2,2,2,2,2,2,3,2
        };

int mapF[]=          //floors
        {
                0,0,0,0,0,0,0,0,
                0,0,0,0,1,1,0,0,
                0,0,0,0,2,0,0,0,
                0,0,0,0,0,0,0,0,
                0,0,2,0,0,0,0,0,
                0,0,0,0,0,0,0,0,
                0,1,1,1,1,0,0,0,
                0,0,0,0,0,0,0,0,
        };

int mapC[]=          //ceiling
        {
                0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,
        };



float degToRad(float a) { return (float)(a*M_PI/180.0);}

float FixAng(float a){ if(a>359){ a-=360;} if(a<0){ a+=360;} return a;}

float dist(float ax, float ay, float bx,float by, float ang)
{
    return (sqrtf((bx-ax)*(bx-ax)+(by-ay)*(by-ay)));
}


void drawRays3D(BITMAP *buffer, t_map *Map, t_player *Player)
{
    int r, mx, my, mp, dof,red,green,blue; float  rx,ry,ra,xo,yo, distT;
    ra=Player->pa-(float)DR*30; if(ra<0){ ra+=2*(float)M_PI;} if(ra>2*(float)M_PI){ ra-=2*(float)M_PI;}
    for(r=0;r<120;r++)
    {
        int vmt,hmt;
       dof=0;
       float distH=1000000,hx=Player->px,hy=Player->py;
       float aTan= -1/ tanf(ra);
       if(ra>M_PI){    ry=(((int)Player->py>>6)<<6)-0.0001; rx=(Player->py-ry)*aTan+Player->px; yo=-64; xo=-yo*aTan; }
       if(ra<M_PI){    ry=(((int)Player->py>>6)<<6)+64;    rx=(Player->py-ry)*aTan+Player->px; yo=64;  xo=-yo*aTan; }

       if(ra==0 || ra==(float)M_PI){   rx=Player->px;  ry=Player->py;  dof=8; }
       while(dof<8){   mx=(int)(rx)>>6;    my=(int)(ry)>>6;    mp=my*Map->mapX+mx;

           if(mp>0 && mp<Map->mapX*Map->mapY && map[mp]>0){ hmt=map[mp]-1;  hx=rx; hy=ry; distH= dist(Player->px,Player->py,hx,hy,ra); dof=8; }
           else{   rx+=xo; ry+=yo; dof+=1; }
       }

       dof=0;
       float distV=1000000,vx=Player->px,vy=Player->py;
       float nTan= -tanf(ra);
       if(ra>P2 && ra< P3){    rx=(((int)Player->px>>6)<<6)-0.0001; ry=(Player->px-rx)*nTan+Player->py; xo=-64; yo=-xo*nTan; }
       if(ra<P2 || ra > P3){    rx=(((int)Player->px>>6)<<6)+64;    ry=(Player->px-rx)*nTan+Player->py; xo=64;  yo=-xo*nTan; }

       if(ra==0 || ra==(float)M_PI){   rx=Player->px;  ry=Player->py;  dof=8; }
       while(dof<8){   mx=(int)(rx)>>6;    my=(int)(ry)>>6;    mp=my*Map->mapX+mx;

           if(mp>0 && mp<Map->mapX*Map->mapY && map[mp]>0){  vmt=map[mp]-1; vx=rx; vy=ry; distV= dist(Player->px,Player->py,vx,vy,ra); dof=8;  }
           else{   rx+=xo; ry+=yo; dof+=1; }
       }

       float shade=1;

       if(distV<distH){ hmt=vmt; shade=0.5f;rx=vx; ry=vy; distT=distV; }
       if(distV>distH){ rx=hx; ry=hy; distT=distH;}

        //line(buffer,(int)px,(int)py,(int)rx,(int)ry, makecol(0,255,0));
       float ca=Player->pa-ra; if(ca<0){ ca+=2*(float)M_PI;} if(ca>2*(float)M_PI){ ca-=2*(float)M_PI;} distT=distT * cosf(ca);
       float lineH=((float )Map->mapS*640)/distT;
       float ty_step=32.0f/(float)lineH;
       float ty_off=0;
       if(lineH>640){ ty_off=(lineH-640)/2.0f;   lineH=640;  }
       float lineO=320-lineH/2;
       float ty=ty_off*ty_step;//+hmt*32
       float tx;
       if(shade==1){tx=(int)(rx/2.0)%32; if(ra>180){tx=31-tx;}}
       else        {tx= (int)(ry/2.0)%32; if(ra>90&& ra<270){tx=31-tx;}}

       depth[r]=distH;

       for(int y=0;y<(int)lineH;y++)
       {
            */
/*int c=(255*All_Textures[(int)ty*32+(int)tx])*shade;
            if(hmt==0){ rectfill(buffer,r*8+530,y+(int)lineO,r*8+530+8,y+(int)lineO, makecol(c,c/2.0,c/2.0));}
            if(hmt==1){ rectfill(buffer,r*8+530,y+(int)lineO,r*8+530+8,y+(int)lineO, makecol(c/2.0,c,c/2.0));}
            if(hmt==2){ rectfill(buffer,r*8+530,y+(int)lineO,r*8+530+8,y+(int)lineO, makecol(c,c/2.0,c));}
            if(hmt==3){ rectfill(buffer,r*8+530,y+(int)lineO,r*8+530+8,y+(int)lineO, makecol(c/2.0,c,c));}*//*


            int pixel=((int)ty*32+(int)tx)*3+(hmt*32*32*3);
            red=All_Textures2[pixel+0]*shade;
            green=All_Textures2[pixel+1]*shade;
            blue=All_Textures2[pixel+2]*shade;
           rectfill(buffer,r*8,y+(int)lineO,r*8+8,y+(int)lineO, makecol(red,green,blue));

            ty+=ty_step;
        }

        */
/*for(int y=(int)(lineO+lineH);y<640;y++)
        {
            float dy=(float )y-(640.0f/2.0f), raFix=cosf(degToRad(FixAng(pa-ra)));
            tx=(px/2.0f) + (cosf(ra)*158*2*32/dy/raFix);
            ty=(py/2.0f)-(sinf(ra)*158*2*32/dy/raFix);
            mp=mapF[(int)(ty/32.0f)*mapX+(int)(tx/32.0f)]*32*32;
            if(mp<0){mp=0;}
            if(mp>12191){mp=12191;}
            int pixel=(((int)(ty)&31)*32 + ((int)(tx)&31))*3+mp*3;
            red=All_Textures2[pixel+0];
            green=All_Textures2[pixel+1];
            blue=All_Textures2[pixel+2];
            rectfill(buffer,r*8,y,r*8+8,y, makecol(red,green,blue));

            //float c=255*All_Textures[((int)(ty)&31)*32 + ((int)(tx)&31)+mp]*0.7;
            //rectfill(buffer,r*8+530,y,r*8+530+8,y, makecol(c/2.0,c/1.3,c/3.0));


            mp=mapC[(int)(ty/32.0f)*mapX+(int)(tx/32.0f)]*32*32;
            //c=255*All_Textures[((int)(ty)&31)*32 + ((int)(tx)&31)+mp]*0.7;
            //rectfill(buffer,r*8+530,320-y,r*8+530+8,320-y, makecol(c,c,c));
            if(mp<0){mp=0;}
            if(mp>12191){mp=12191;}
            pixel=(((int)(ty)&31)*32 + ((int)(tx)&31))*3+mp*3;
            red=All_Textures2[pixel+0];
            green=All_Textures2[pixel+1];
            blue=All_Textures2[pixel+2];
            if(mp>0){rectfill(buffer,r*8,640-y,r*8+8,640-y, makecol(red,green,blue));}

        }*//*



       ra+=(float )DR/2; if(ra<0){ ra+=2*(float)M_PI;} if(ra>2*(float)M_PI){ ra-=2*(float)M_PI;}
    }
}

void initAllegro()
{
    allegro_init();
    set_color_depth(desktop_color_depth());
    if(set_gfx_mode(GFX_AUTODETECT_WINDOWED,960,640,0,0)!=0)
    {
        allegro_message("Prblm gfx");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    install_keyboard();
    install_mouse();
}

void drawSky(BITMAP * buffer,t_player *Player)
{
    for(int y=0;y<40;y++)
    {
        for(int x=0;x<120;x++)
        {

            int xo=(int)Player->pa*4-x;if(xo<0){xo+=120;} xo=xo%120;
            int pixel=(y*32+xo)*3;
            int red=sky[pixel+0];
            int green=sky[pixel+1];
            int blue=sky[pixel+2];
            rectfill(buffer,x*8,y*8,x*8+8,y*8, makecol(red,green,blue));
        }
    }
}

void drawSprite(BITMAP*buffer,t_player *Player,sprite *sp)
{
    float sx=sp[0].x-Player->px; //temp float variables
    float sy=sp[0].y-Player->py;
    float sz=sp[0].z;

    float CS=cosf(Player->pa), SN=sinf(Player->pa); //rotate around origin
    float a=sy*CS+sx*SN;
    float b=sx*CS-sy*SN;
    sx=a; sy=b;

    sx=(sx*108.0f/sy)+(120.0f/2); //convert to screen x,y
    sy=(sz*108.0f/sy)+(80.0f/2);

    printf("%d %d   %d %d\n",(int)sx*8,(int)sy*8,(int)Player->px,(int)Player->py);

    circlefill(buffer,(int)sx*8,(int)sy*8,8, makecol(255,255,0));

}






int main() {

    initAllegro();
    BITMAP *buffer= create_bitmap(SCREEN_W,SCREEN_H);
    t_map Map=map_init();
    t_player Player=player_init();
    sprite sp[4];
    sp[0].type=1; sp[0].state=1; sp[0].map=0; sp[0].x=(int)2*64; sp[0].y=(int)5*64; sp[0].z=-10;
    while(!key[KEY_ESC])
    {
        clear_bitmap(buffer);
        drawSky(buffer,&Player);
        rectfill(buffer,0,300,960,640, makecol(0,200,0));
        drawRays3D(buffer,&Map,&Player);
        drawSprite(buffer,&Player,sp);
        drawMap2D(buffer,&Map,map);
        drawPlayer(buffer,&Player,sp);
        line(buffer,SCREEN_W/2,SCREEN_H/2-10,SCREEN_W/2,SCREEN_H/2+10, makecol(255,0,0));
        line(buffer,SCREEN_W/2-10,SCREEN_H/2,SCREEN_W/2+10,SCREEN_H/2, makecol(255,0,0));
        buttons(0.25f,&Map,&Player, map);
        blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        rest(6);
    }
    allegro_exit();
    return 0;
}
END_OF_MAIN()
*/

//------------------------YouTube-3DSage----------------------------------------
//Full video: https://www.youtube.com/watch?v=w0Bm4IA-Ii8
//WADS to move player, E open door after picking up the key

#include <stdlib.h>
#include <allegro.h>
#include <math.h>
#include "stdio.h"
#include "time.h"

#include "textures/All_Textures.h"
#include "textures/sky.h"
#include "textures/title.h"
#include "textures/won.h"
#include "textures/lost.h"
#include "textures/sprites.h"
#include "textures/sprites_2.h"


float degToRad(float a) { return (float)(a*M_PI/180.0);}
float FixAng(float a){ if(a>359){ a-=360;} if(a<0){ a+=360;} return a;}
float distance(float ax,float ay, float bx,float by,float ang){ return cosf(degToRad(ang))*(bx-ax)-sinf(degToRad(ang))*(by-ay);}
float Distance(float ax,float ay, float bx,float by){ return sqrtf((bx-ax)*(bx-ax)+(by-ay)*(by-ay));}
float px,py,pdx,pdy,pdx2,pdy2,pdx3,pdy3,pa;
int gameState=0, timer=0; //game state. init, start screen, game loop, win/lose
float fade=0;             //the 3 screens can fade up from black

//-----------------------------MAP----------------------------------------------
#define mapX  8      //map width
#define mapY  8      //map height
#define mapS 64      //map cube size

//Edit these 3 arrays with values 0-4 to create your own level!
int mapW[]=          //walls
        {
                1,1,1,1,2,2,2,2,
                6,0,0,1,0,0,0,2,
                1,0,0,4,0,2,0,2,
                1,5,4,5,0,0,0,2,
                2,0,0,0,0,0,0,1,
                2,0,0,0,0,4,0,1,
                2,0,0,0,0,0,0,1,
                1,1,1,1,1,1,1,1,
        };

int mapW2[]=          //walls
        {
                1,1,1,1,2,2,2,2,
                6,0,0,0,0,0,0,2,
                1,0,0,0,0,0,0,2,
                1,0,0,0,0,0,0,2,
                2,0,0,0,0,0,0,1,
                2,0,0,0,0,0,0,1,
                2,0,0,0,0,0,0,1,
                1,1,1,1,1,1,1,1,
        };

int mapF[]=          //floors
        {
                0,0,0,0,0,0,0,0,
                0,0,0,0,2,2,2,0,
                0,0,0,0,6,0,2,0,
                0,0,8,0,2,7,6,0,
                0,0,2,0,0,0,0,0,
                0,0,2,0,8,0,0,0,
                0,1,1,1,1,0,8,0,
                0,0,0,0,0,0,0,0,
        };

int mapC[]=          //ceiling
        {
                0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,
        };


void drawMap2D(BITMAP *buffer)
{
    int x,y,xo,yo;
    for(y=0;y<mapY;y++)
    {
        for(x=0;x<mapX;x++)
        {

            xo=x*mapS/2; yo=y*mapS/2;
            if(mapW[y*mapX+x]>0){ rectfill(buffer,xo+1, yo+1,mapS/2+xo-1,mapS/2+yo-1, makecol(255,255,255));} else{ rectfill(buffer,xo+1, yo+1,mapS+xo-1,mapS+yo-1, makecol(0,0,0));}

        }
    }
}//-----------------------------------------------------------------------------




typedef struct       //All veriables per sprite
{
    int type;           //static, key, enemy
    int state;          //on off
    int map;            //texture to show
    float x,y,z;        //position
}sprite; sprite sp[4];
int depth[120];      //hold wall line depth to compare for sprite depth


int mouseTurnX()
{
    int mouseX=mouse_x;
    rest(1);
    if(mouse_x>mouseX)
    {
        return 1;
    }
    else if(mouse_x<mouseX)
    {
        return 2;
    }
    else
    {
        return 0;
    }
}

void drawSprite(BITMAP *buffer, int *MapW)
{
    int x,y,s;
    if(px<sp[0].x+30 && px>sp[0].x-30 && py<sp[0].y+30 && py>sp[0].y-30){ sp[0].state=0;} //pick up key
    if(px<sp[3].x+30 && px>sp[3].x-30 && py<sp[3].y+30 && py>sp[3].y-30){ gameState=4;} //enemy kills

    //enemy attack
    int spx=(int)sp[3].x>>6,          spy=(int)sp[3].y>>6;          //normal grid position
    int spx_add=((int)sp[3].x+15)>>6, spy_add=((int)sp[3].y+15)>>6; //normal grid position plus     offset
    int spx_sub=((int)sp[3].x-15)>>6, spy_sub=((int)sp[3].y-15)>>6; //normal grid position subtract offset
    if(sp[3].x>px && MapW[spy*8+spx_sub]==0){ sp[3].x-=1;}
    if(sp[3].x<px && MapW[spy*8+spx_add]==0){ sp[3].x+=1;}
    if(sp[3].y>py && MapW[spy_sub*8+spx]==0){ sp[3].y-=1;}
    if(sp[3].y<py && MapW[spy_add*8+spx]==0){ sp[3].y+=1;}

    for(s=0;s<4;s++)
    {
        int red,blue,green;
        float sx=sp[s].x-px; //temp float variables
        float sy=sp[s].y-py;
        float sz=sp[s].z;

        float CS=cosf(degToRad(pa)), SN=sinf(degToRad(pa)); //rotate around origin
        float a=sy*CS+sx*SN;
        float b=sx*CS-sy*SN;
        sx=a; sy=b;

        sx=(float)(sx*108.0/sy)+(120.0f/2); //convert to screen x,y
        sy=(float)(sz*108.0/sy)+( 80.0f/2);

        int scale=(int)(32*80/b);   //scale sprite based on distance
        if(scale<0){ scale=0;} if(scale>120){ scale=120;}

        //texture
        float t_x=0, t_y=31, t_x_step=31.5f/(float)scale, t_y_step=32.0f/(float)scale;

        for(x=(int)(sx-(float)scale/2);x<(int)(sx+(float)scale/2);x++)
        {
            t_y=31;
            for(y=0;y<scale;y++)
            {
                if(sp[s].state==1 && x>0 && x<120 && b<(float)depth[x])
                {
                    int pixel=((int)t_y*32+(int)t_x)*3+(sp[s].map*32*32*3);
                    if(sp[s].type==3)
                    {
                        red   =sprites_2[pixel+0];
                        green =sprites_2[pixel+1];
                        blue  =sprites_2[pixel+2];
                    }
                    else
                    {
                        red   =sprites[pixel+0];
                        green =sprites[pixel+1];
                        blue  =sprites[pixel+2];
                    }
                    if(red!=255&&green!=0&&blue!=255) //dont draw if purple
                    {
                        rectfill(buffer,x*8,(int)sy*8-y*8,x*8+8,(int)sy*8-y*8+8, makecol(red,green,blue)); //draw point
                    }
                    t_y-=t_y_step; if(t_y<0){ t_y=0;}
                }
            }
            t_x+=t_x_step;
        }
    }
}

//------------------------PLAYER------------------------------------------------
void drawPlayer2D(BITMAP *buffer)
{
    circlefill(buffer,px/2,py/2,4, makecol(255,0,0));
    circlefill(buffer,sp[3].x/2,sp[3].y/2,4, makecol(255,255,0));
    line(buffer,px/2,py/2,px/2+pdx/2*20,py/2+pdy/2*20, makecol(255,255,0));
    line(buffer,px/2,py/2,px/2+pdx2/2*20,py/2+pdy2/2*20, makecol(255,255,0));
    line(buffer,px/2,py/2,px/2+pdx3/2*20,py/2+pdy3/2*20, makecol(255,255,0));
}

//---------------------------Draw Rays and Walls--------------------------------
void drawRays2D(BITMAP *buffer, int *MapW)
{
    int r,mx,my,mp,dof,side; float vx,vy,rx,ry,ra,xo,yo,disV,disH;

    ra=FixAng(pa+30);                                                              //ray set back 30 degrees

    for(r=0;r<120;r++)
    {
        int vmt=0,hmt=0;                                                              //vertical and horizontal map texture number
        //---Vertical---
        dof=0; side=0; disV=100000;
        float Tan=tanf(degToRad(ra));
        if(cosf(degToRad(ra))> 0.001){ rx=(((int)px>>6)<<6)+64;      ry=(px-rx)*Tan+py; xo= 64; yo=-xo*Tan;}//looking left
        else if(cosf(degToRad(ra))<-0.001){ rx=(((int)px>>6)<<6) -0.0001; ry=(px-rx)*Tan+py; xo=-64; yo=-xo*Tan;}//looking right
        else { rx=px; ry=py; dof=8;}//looking up or down. no hit

        while(dof<8)
        {
            mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;
            if(mp>0 && mp<mapX*mapY && MapW[mp]>0){ vmt=MapW[mp]-1; dof=8; disV=cosf(degToRad(ra))*(rx-px)-sinf(degToRad(ra))*(ry-py);}//hit
            else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
        }
        vx=rx; vy=ry;


        //---Horizontal---
        dof=0; disH=100000;
        Tan=1.0f/Tan;
        if(sinf(degToRad(ra))> 0.001){ ry=(((int)py>>6)<<6) -0.0001; rx=(py-ry)*Tan+px; yo=-64; xo=-yo*Tan;}//looking up
        else if(sinf(degToRad(ra))<-0.001){ ry=(((int)py>>6)<<6)+64;      rx=(py-ry)*Tan+px; yo= 64; xo=-yo*Tan;}//looking down
        else{ rx=px; ry=py; dof=8;}                                                   //looking straight left or right

        while(dof<8)
        {
            mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;
            if(mp>0 && mp<mapX*mapY && MapW[mp]>0){ hmt=MapW[mp]-1; dof=8; disH=cosf(degToRad(ra))*(rx-px)-sinf(degToRad(ra))*(ry-py);}//hit
            else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
        }

        float shade=1;
        if(disV<disH){ hmt=vmt; shade=0.5f; rx=vx; ry=vy; disH=disV; }//horizontal hit first


        int ca=(int)FixAng(pa-ra); disH=disH*cosf(degToRad((float)ca));                            //fix fisheye
        int lineH =(int)((mapS*640.0f)/(disH));
        float ty_step=32.0f/(float)lineH;
        float ty_off=0;
        if(lineH>640){ ty_off=(float)((lineH-640)/2.0); lineH=640;}                            //line height and limit
        int lineOff = 320 - (lineH>>1);                                               //line offset

        depth[r]=(int)disH; //save this line's depth
        //---draw walls---
        int y;
        float ty=ty_off*ty_step;//+hmt*32;
        float tx;
        if(shade==1){ tx=(int)(rx/2.0)%32; if(ra>180){ tx=31-tx;}}
        else        { tx=(int)(ry/2.0)%32; if(ra>90 && ra<270){ tx=31-tx;}}
        for(y=0;y<lineH;y++)
        {
            int pixel=((int)ty*32+(int)tx)*3+(hmt*32*32*3);
            int red   =All_Textures[pixel+0]*shade;
            int green =All_Textures[pixel+1]*shade;
            int blue  =All_Textures[pixel+2]*shade;
            rectfill(buffer,r*8,y+lineOff,r*8+8,y+lineOff+8, makecol(red,green,blue));
            ty+=ty_step;
        }

        //---draw floors---
        for(y=lineOff+lineH;y<640;y++)
        {
            float dy=(float)(y-(640/2.0)), deg=degToRad(ra), raFix=cosf(degToRad(FixAng(pa-ra)));
            tx=px/2 + cosf(deg)*158*2*32/dy/raFix;
            ty=py/2 - sinf(deg)*158*2*32/dy/raFix;
            mp=mapF[(int)(ty/32.0)*mapX+(int)(tx/32.0)]*32*32;
            int pixel=(((int)(ty)&31)*32 + ((int)(tx)&31))*3+mp*3;
            int red   =(int)((float )All_Textures[pixel+0]*0.7);
            int green =(int)((float )All_Textures[pixel+0]*0.7);
            int blue  =(int)((float )All_Textures[pixel+0]*0.7);
            rectfill(buffer,r*8,y,r*8+8,y+8, makecol(red,green,blue));

            //---draw ceiling---
            mp=mapC[(int)(ty/32.0)*mapX+(int)(tx/32.0)]*32*32;
            pixel=(((int)(ty)&31)*32 + ((int)(tx)&31))*3+mp*3;
            red   =All_Textures[pixel+0];
            green =All_Textures[pixel+1];
            blue  =All_Textures[pixel+2];
            if(mp>0){ rectfill(buffer,r*8,640-y,r*8+8,640-y+8, makecol(red,green,blue));}
        }

        ra=FixAng(ra-0.5f);                                                               //go to next ray, 60 total
    }
}//-----------------------------------------------------------------------------


int HitMonster(float spx,float spy, int *MapW, BITMAP*buffer)
{
    /*int r,mx,my,mp,dof,side; float vx,vy,rx,ry,ra,xo,yo,disV,disH;

    ra=FixAng(pa);                                                              //ray set back 30 degrees
    int vmt=0,hmt=0;                                                              //vertical and horizontal map texture number
    //---Vertical---
    dof=0; side=0; disV=100000;
    float Tan=tanf(degToRad(ra));
    if(cosf(degToRad(ra))> 0.001){ rx=(((int)px>>6)<<6)+64;      ry=(px-rx)*Tan+py; xo= 64; yo=-xo*Tan;}//looking left
    else if(cosf(degToRad(ra))<-0.001){ rx=(((int)px>>6)<<6) -0.0001; ry=(px-rx)*Tan+py; xo=-64; yo=-xo*Tan;}//looking right
    else { rx=px; ry=py; dof=8;}//looking up or down. no hit

    while(dof<8)
    {
    mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;
    if(mp>0 && mp<mapX*mapY && MapW[mp]>0){ vmt=MapW[mp]-1; dof=8; disV=cosf(degToRad(ra))*(rx-px)-sinf(degToRad(ra))*(ry-py);}//hit
    else{ rx+=xo; ry+=yo; dof+=1; if(rx==spx&&ry==spy){return 1;} }                                               //check next horizontal
    }
    vx=rx; vy=ry;


    //---Horizontal---
    dof=0; disH=100000;
    Tan=1.0f/Tan;
    if(sinf(degToRad(ra))> 0.001){ ry=(((int)py>>6)<<6) -0.0001; rx=(py-ry)*Tan+px; yo=-64; xo=-yo*Tan;}//looking up
    else if(sinf(degToRad(ra))<-0.001){ ry=(((int)py>>6)<<6)+64;      rx=(py-ry)*Tan+px; yo= 64; xo=-yo*Tan;}//looking down
    else{ rx=px; ry=py; dof=8;}                                                   //looking straight left or right

    while(dof<8)
    {
      mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;
      if(mp>0 && mp<mapX*mapY && MapW[mp]>0){ hmt=MapW[mp]-1; dof=8; disH=cosf(degToRad(ra))*(rx-px)-sinf(degToRad(ra))*(ry-py);}//hit
      else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
    }

    if(disV<disH){ hmt=vmt; rx=vx; ry=vy; disH=disV; }//horizontal hit first*/


    float rx,ry;

    int mp,mx,my;

    rx=px;
    ry=py;
    for(int i=0;i<300;i++)
    {
        rx+=pdx;
        ry+=pdy;
        mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;

        if(mp>0 && mp<mapX*mapY && MapW[mp]>0)
        {
            break;
        }

        if(rx>spx-5&& rx<spx+5 && ry>spy-5&& ry<spy+5)
        {
            line(buffer,px/2,py/2,rx/2,ry/2, makecol(0,255,0));
            return 1;
        }
    }
    line(buffer,px/2,py/2,rx/2,ry/2, makecol(0,255,0));
    return 0;
}


void drawSky(BITMAP *buffer)     //draw sky and rotate based on player rotation
{int x,y;
    for(y=0;y<40;y++)
    {
        for(x=0;x<120;x++)
        {
            int xo=(int)pa*2-x; if(xo<0){ xo+=120;} xo=xo % 120; //return 0-120 based on player angle
            int pixel=(y*120+xo)*3;
            int red   =sky[pixel+0];
            int green =sky[pixel+1];
            int blue  =sky[pixel+2];
            rectfill(buffer,x*8,y*8,x*8+8,y*8+8, makecol(red,green,blue));
        }
    }
}

SAMPLE * importeSon(char *nomDeFichier)
{
    SAMPLE *sonARendre= load_sample(nomDeFichier);
    if(!sonARendre)
    {
        allegro_message("ne peut pas ouvrir %s",nomDeFichier);
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    return sonARendre;
}

void screenGame(int v,BITMAP *buffer) //draw any full screen image. 120x80 pixels
{
    int x,y;
    int *T;
    if(v==2){ T=won;}
    if(v==3){ T=lost;}
    for(y=0;y<80;y++)
    {
        for(x=0;x<120;x++)
        {
            int pixel=(y*120+x)*3;
            int red   =(int)((float )T[pixel+0]*fade);
            int green =(int)((float )T[pixel+1]*fade);
            int blue  =(int)((float )T[pixel+2]*fade);
            rectfill(buffer,x*8,y*8,x*8+8,y*8+8, makecol(red,green,blue));
        }
    }
    if(fade<1){ fade+=0.01f;}
    if(fade>1){ fade=1;}
}


BITMAP * importeImage(char *nomDeFichier)
{
    BITMAP *imageARendre= load_bitmap(nomDeFichier,NULL);
    if(!imageARendre)
    {
        allegro_message("ne peut pas ouvrir %s",nomDeFichier);
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    return imageARendre;
}



void init()//init all variables when game starts
{
    allegro_init();
    set_color_depth(desktop_color_depth());
    if(set_gfx_mode(GFX_AUTODETECT_WINDOWED,960,640,0,0)!=0)
    {
        allegro_message("Prblm gfx");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    install_keyboard();
    install_mouse();
    install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,NULL);

    px=150; py=400; pa=90;
    pdx=cosf(degToRad(pa)); pdy=-sinf(degToRad(pa));
    pdx2=cosf(degToRad(pa)+(float )M_PI/2); pdy2=-sinf(degToRad(pa)+(float )M_PI/2);
    pdx3=cosf(degToRad(pa)-(float )(M_PI/2));  pdy3=-sinf(degToRad(pa)-(float )(M_PI/2));
    //init player
    mapW[19]=4; mapW[26]=4; //close doors

    sp[0].type=1; sp[0].state=1; sp[0].map=0; sp[0].x=1.5f*64; sp[0].y=5*64;   sp[0].z=20; //key
    sp[1].type=2; sp[1].state=1; sp[1].map=1; sp[1].x=1.5f*64; sp[1].y=4.5f*64; sp[1].z= 0; //light 1
    sp[2].type=2; sp[2].state=1; sp[2].map=1; sp[2].x=3.5f*64; sp[2].y=4.5f*64; sp[2].z= 0; //light 2
    sp[3].type=3; sp[3].state=1; sp[3].map=2; sp[3].x=2.5f*64; sp[3].y=2*64;   sp[3].z=20; //enemy
}


int displayGame(BITMAP *buffer)
{

    if(gameState==0){  fade=0; timer=0; gameState=1;} //init game
    if(gameState==1){ timer+=20; if(timer>100){ fade=0; timer=0; gameState=2;}} //start screen
    if(gameState==2) //The main game loop
    {
        drawSky(buffer);
        drawRays2D(buffer,mapW);
        drawSprite(buffer,mapW);
        drawMap2D(buffer);
        drawPlayer2D(buffer);
        HitMonster(sp[3].x,sp[3].y,mapW,buffer);
        //y position and offset
        if( (int)px>>6==1 && (int)py>>6==1 ){ fade=0; timer=0; gameState=3;} //Entered block 1, Win game!!
    }

    if(gameState==3){ screenGame(2,buffer); timer+=10; if(timer>2000){ fade=0; timer=0; gameState=0; return 1;}} //won screen
    if(gameState==4){ screenGame(3,buffer); timer+=10; if(timer>2000){ fade=0; timer=0; gameState=0;return 1;}} //lost screen
    return 0;
}



void shootPistolAnimation(BITMAP *buffer,BITMAP **animations, int frame)
{
    draw_sprite(buffer,animations[frame],300,150);
}

void Button(int *MapW)                                  //keyboard button pressed down
{


    int xo; if(pdx<0){xo=-20;}else{xo=20;}
    int yo; if(pdy<0){yo=-20;}else{yo=20;}
    int ipx=(int)(px/64.0), ipx_add_xo=(int)(((int)px+xo)/64), ipx_subb_xo=((int)px-xo)/64;
    int ipy=(int)(py/64.0), ipy_add_yo=((int)py+yo)/64, ipy_subb_yo=((int)py-yo)/64;

    int xo3; if(pdx2<0){xo3=-20;}else{xo3=20;}
    int yo3; if(pdy2<0){yo3=-20;}else{yo3=20;}
    int ipx3=(int)(px/64.0), ipx_add_xo3=(int)(((int)px+xo3)/64), ipx_subb_xo3=((int)px-xo3)/64;
    int ipy3=(int)(py/64.0), ipy_add_yo3=((int)py+yo3)/64, ipy_subb_yo3=((int)py-yo3)/64;


    if(mouseTurnX()==2){ pa+=8; pa= FixAng(pa); pdx=cosf(degToRad(pa)); pdy=-sinf(degToRad(pa)); pdx2=cosf(degToRad(pa)+(float )(M_PI/2));  pdy2=-sinf(degToRad(pa)+(float )(M_PI/2)); pdx3=cosf(degToRad(pa)-(float )(M_PI/2));  pdy3=-sinf(degToRad(pa)-(float )(M_PI/2)); }
    if(mouseTurnX()==1){ pa-=8; pa= FixAng(pa) ;pdx=cosf(degToRad(pa)); pdy=-sinf(degToRad(pa)); pdx2=cosf(degToRad(pa)+(float )(M_PI/2));  pdy2=-sinf(degToRad(pa)+(float )(M_PI/2)); pdx3=cosf(degToRad(pa)-(float )(M_PI/2));  pdy3=-sinf(degToRad(pa)-(float )(M_PI/2)); }


    if(key[KEY_W]){
        if(MapW[ipy*mapX+ipx_add_xo]==0){px+=(float)pdx*5;}
        if(MapW[ipy_add_yo*mapX+ipx]==0){py+=(float)pdy*5;}
    }
    if(key[KEY_S]){
        if(MapW[ipy*mapX+ipx_subb_xo]==0){px-=(float)pdx*5;}
        if(MapW[ipy_subb_yo*mapX+ipx]==0){py-=(float)pdy*5;}
    }

    if(key[KEY_A]){if(MapW[ipy3*mapX+ipx_add_xo3]==0){px+=pdx2*5;}
        if(MapW[ipy_add_yo3*mapX+ipx3]==0){py+=pdy2*5;}}
    if(key[KEY_D]){if(MapW[ipy3*mapX+ipx_subb_xo3]==0){px-=pdx2*5;}
        if(MapW[ipy_subb_yo3*mapX+ipx3]==0){py-=pdy2*5;}}

    if(key[KEY_E] && sp[0].state==0)             //open doors
    {
        if(pdx<0){ xo=-25;} else{ xo=25;}
        if(pdy<0){ yo=-25;} else{ yo=25;}
        ipx=px/64.0; ipx_add_xo=(px+xo)/64.0;
        ipy=py/64.0; ipy_add_yo=(py+yo)/64.0;
        if(MapW[ipy_add_yo*mapX+ipx_add_xo]==4){ MapW[ipy_add_yo*mapX+ipx_add_xo]=0;}
    }

}

int myClock(int diffAfterReset)
{
    return clock() - diffAfterReset; // Retourne le temps depuis le dernier reset
}

void myResetClock( int * diffAfterReset)
{
    *diffAfterReset = clock(); // Met le compteur au véritable temps
}

int main()
{
    init();
    int GameLoop=0;
    int volumeDist;
    int frame=1;
    int pano=128;
    float ratioDistance=0;
    int BoolAnimation=0;
    int ClockForSprite = 0, ClokcForAnimation =0; // Le moment du dernier reset
    clock_t tempsSpriteMonstre, tempsOperationDebut, tempsOperationFin, tempsAnimationShootPistol;
    char NomDeFichier[500];
    BITMAP *buffer= create_bitmap(SCREEN_W,SCREEN_H);
    BITMAP *shootPistol[5];
    for(int i=1;i<5;i++)
    {
        sprintf(NomDeFichier,"../images/shoot pistol/%d.bmp",i);
        shootPistol[i]= importeImage(NomDeFichier);
    }
    SAMPLE * pasDeMonstre= importeSon("../son/Robot pas.wav");
    play_sample(pasDeMonstre,255,128,1000,TRUE);
    while(!key[KEY_ESC])
    {
        tempsOperationDebut=clock();
        tempsSpriteMonstre= myClock(ClockForSprite);
        clear_bitmap(buffer);
        GameLoop=displayGame(buffer);
        Button(mapW);
        shootPistolAnimation(buffer,shootPistol,frame);
        line(buffer,SCREEN_W/2-10,SCREEN_H/2,SCREEN_W/2+10,SCREEN_H/2, makecol(255,0,0));
        line(buffer,SCREEN_W/2,SCREEN_H/2-10,SCREEN_W/2,SCREEN_H/2+10, makecol(255,0,0));
        if(mouse_b==1)
        {
            if(HitMonster(sp[3].x,sp[3].y,mapW,buffer))
            {
                sp[3].state= !sp[3].state;
            }
            BoolAnimation=1;
        }
        if(BoolAnimation)
        {
            tempsAnimationShootPistol= myClock(ClokcForAnimation);
            if(tempsAnimationShootPistol>75)
            {
                frame++;
                myResetClock(&ClokcForAnimation);
            }
            if(frame>4)
            {
                BoolAnimation=0;
                frame=1;
            }
        }

        blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        if(GameLoop==1)
        {
            break;
        }
        ratioDistance=Distance(sp[3].x,sp[3].y,px+pdx2*20,py+pdy2*20)/Distance(sp[3].x,sp[3].y,px+pdx3*20,py+pdy3*20);
        if(Distance(sp[3].x,sp[3].y,px+pdx2*20,py+pdy2*20)> Distance(sp[3].x,sp[3].y,px+pdx3*20,py+pdy3*20))
        {
            pano=(int)((128+50)*ratioDistance);
        }
        else if(Distance(sp[3].x,sp[3].y,px+pdx2*20,py+pdy2*20)< Distance(sp[3].x,sp[3].y,px+pdx3*20,py+pdy3*20))
        {
            pano=(int)((128-50)*ratioDistance);
        }
        else
        {
            pano=(int)(128*ratioDistance);
        }
        adjust_sample(pasDeMonstre,(int)((float)255/(Distance(sp[3].x,sp[3].y,px,py)/35)),pano,1000,TRUE);
        if(tempsSpriteMonstre>300)
        {
            sp[3].map++;
            if(sp[3].map>2)
            {
                sp[3].map=0;
            }
            myResetClock(&ClockForSprite);
        }
        tempsOperationFin=clock();
    }
    stop_sample(pasDeMonstre);
    allegro_exit();
    return 0;
}
END_OF_MAIN()


