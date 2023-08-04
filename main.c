#include <stdio.h>
#include "allegro.h"
#include "math.h"
#include "Textures.h"






//
// Created by mathe on 02/08/2023.
//


#define P2 (M_PI/2)
#define P3 (3*M_PI/2)
#define DR 0.0174533

float px,py,pdx,pdy,pa;
float pdx2,pdy2;
int runningvalue;

int mapX=8,mapY=8,mapS=64;


typedef struct
{
    int type;
    int state;
    int map;
    int x,y,z;
}sprite;

sprite sp[4];
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


void drawMap2D(BITMAP*buffer)
{
    int x,y,xo,yo;

    for(y=0;y<mapY;y++)
    {
        for(x=0;x<mapX;x++)
        {
            xo=x*mapS;
            yo=y*mapS;
            if(map[y*mapX+x]>0)
            {
                rectfill(buffer,xo+1,yo+1,xo+mapS-1,yo+mapS-1, makecol(255,255,255));
            }
            else
            {
                rectfill(buffer,xo+1,yo+1,xo+mapS-1,yo+mapS-1, makecol(0,0,0));
            }
        }
    }
}

float dist(float ax, float ay, float bx,float by, float ang)
{
    return (sqrtf((bx-ax)*(bx-ax)+(by-ay)*(by-ay)));
}


void drawRays3D(BITMAP *buffer)
{
    int r, mx, my, mp, dof,red,green,blue; float  rx,ry,ra,xo,yo, distT;
    ra=pa-(float)DR*30; if(ra<0){ ra+=2*(float)M_PI;} if(ra>2*(float)M_PI){ ra-=2*(float)M_PI;}
    for(r=0;r<120;r++)
    {
        int vmt,hmt;
       dof=0;
       float distH=1000000,hx=px,hy=py;
       float aTan= -1/ tanf(ra);
       if(ra>M_PI){    ry=(((int)py>>6)<<6)-0.0001; rx=(py-ry)*aTan+px; yo=-64; xo=-yo*aTan; }
       if(ra<M_PI){    ry=(((int)py>>6)<<6)+64;    rx=(py-ry)*aTan+px; yo=64;  xo=-yo*aTan; }

       if(ra==0 || ra==(float)M_PI){   rx=px;  ry=py;  dof=8; }
       while(dof<8){   mx=(int)(rx)>>6;    my=(int)(ry)>>6;    mp=my*mapX+mx;

           if(mp>0 && mp<mapX*mapY && map[mp]>0){ hmt=map[mp]-1;  hx=rx; hy=ry; distH= dist(px,py,hx,hy,ra); dof=8; }
           else{   rx+=xo; ry+=yo; dof+=1; }
       }

       dof=0;
       float distV=1000000,vx=px,vy=py;
       float nTan= -tanf(ra);
       if(ra>P2 && ra< P3){    rx=(((int)px>>6)<<6)-0.0001; ry=(px-rx)*nTan+py; xo=-64; yo=-xo*nTan; }
       if(ra<P2 || ra > P3){    rx=(((int)px>>6)<<6)+64;    ry=(px-rx)*nTan+py; xo=64;  yo=-xo*nTan; }

       if(ra==0 || ra==(float)M_PI){   rx=px;  ry=py;  dof=8; }
       while(dof<8){   mx=(int)(rx)>>6;    my=(int)(ry)>>6;    mp=my*mapX+mx;

           if(mp>0 && mp<mapX*mapY && map[mp]>0){  vmt=map[mp]-1; vx=rx; vy=ry; distV= dist(px,py,vx,vy,ra); dof=8;  }
           else{   rx+=xo; ry+=yo; dof+=1; }
       }

       float shade=1;

       if(distV<distH){ hmt=vmt; shade=0.5f;rx=vx; ry=vy; distT=distV; }
       if(distV>distH){ rx=hx; ry=hy; distT=distH;}

        //line(buffer,(int)px,(int)py,(int)rx,(int)ry, makecol(0,255,0));
       float ca=pa-ra; if(ca<0){ ca+=2*(float)M_PI;} if(ca>2*(float)M_PI){ ca-=2*(float)M_PI;} distT=distT * cosf(ca);
       float lineH=((float )mapS*640)/distT;
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
            /*int c=(255*All_Textures[(int)ty*32+(int)tx])*shade;
            if(hmt==0){ rectfill(buffer,r*8+530,y+(int)lineO,r*8+530+8,y+(int)lineO, makecol(c,c/2.0,c/2.0));}
            if(hmt==1){ rectfill(buffer,r*8+530,y+(int)lineO,r*8+530+8,y+(int)lineO, makecol(c/2.0,c,c/2.0));}
            if(hmt==2){ rectfill(buffer,r*8+530,y+(int)lineO,r*8+530+8,y+(int)lineO, makecol(c,c/2.0,c));}
            if(hmt==3){ rectfill(buffer,r*8+530,y+(int)lineO,r*8+530+8,y+(int)lineO, makecol(c/2.0,c,c));}*/

            int pixel=((int)ty*32+(int)tx)*3+(hmt*32*32*3);
            red=All_Textures2[pixel+0]*shade;
            green=All_Textures2[pixel+1]*shade;
            blue=All_Textures2[pixel+2]*shade;
           rectfill(buffer,r*8,y+(int)lineO,r*8+8,y+(int)lineO, makecol(red,green,blue));

            ty+=ty_step;
        }

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

        }*/


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

void drawSky(BITMAP * buffer)
{
    for(int y=0;y<40;y++)
    {
        for(int x=0;x<120;x++)
        {

            int xo=(int)pa*4-x;if(xo<0){xo+=120;} xo=xo%120;
            int pixel=(y*32+xo)*3;
            int red=sky[pixel+0];
            int green=sky[pixel+1];
            int blue=sky[pixel+2];
            rectfill(buffer,x*8,y*8,x*8+8,y*8, makecol(red,green,blue));
        }
    }
}

void drawSprite(BITMAP*buffer)
{
    int x,y,s;

    //enemy attack
    int spx=(int)sp[3].x>>6,          spy=(int)sp[3].y>>6;          //normal grid position
    int spx_add=((int)sp[3].x+15)>>6, spy_add=((int)sp[3].y+15)>>6; //normal grid position plus     offset
    int spx_sub=((int)sp[3].x-15)>>6, spy_sub=((int)sp[3].y-15)>>6; //normal grid position subtract offset
    if(sp[3].x>px && map[spy*8+spx_sub]==0){ sp[3].x-=0.04;}
    if(sp[3].x<px && map[spy*8+spx_add]==0){ sp[3].x+=0.04;}
    if(sp[3].y>py && map[spy_sub*8+spx]==0){ sp[3].y-=0.04;}
    if(sp[3].y<py && map[spy_add*8+spx]==0){ sp[3].y+=0.04;}

    for(s=0;s<4;s++)
    {
        float sx=sp[s].x-px; //temp float variables
        float sy=sp[s].y-py;
        float sz=sp[s].z;

        float CS=cos(degToRad(pa)), SN=sin(degToRad(pa)); //rotate around origin
        float a=sy*CS+sx*SN;
        float b=sx*CS-sy*SN;
        sx=a; sy=b;

        sx=(sx*108.0/sy)+(120/2); //convert to screen x,y
        sy=(sz*108.0/sy)+( 80/2);

        int scale=32*80/b;   //scale sprite based on distance
        if(scale<0){ scale=0;} if(scale>120){ scale=120;}

        //texture
        float t_x=0, t_y=31, t_x_step=31.5/(float)scale, t_y_step=32.0/(float)scale;

        for(x=sx-scale/2;x<sx+scale/2;x++)
        {
            t_y=31;
            for(y=0;y<scale;y++)
            {
                if(sp[s].state==1 && x>0 && x<120 && b<depth[x])
                {
                    int pixel=((int)t_y*32+(int)t_x)*3+(sp[s].map*32*32*3);
                    int red   =All_Textures2[pixel+0];
                    int green =All_Textures2[pixel+1];
                    int blue  =All_Textures2[pixel+2];
                    if(red!=255, green!=0, blue!=255) //dont draw if purple
                    {
                        rectfill(buffer,x*8,sy*8-y*8,(x*8)+8,sy*8-y*8, makecol(red,green,blue)); //draw point
                    }
                    t_y-=t_y_step; if(t_y<0){ t_y=0;}
                }
            }
            t_x+=t_x_step;
        }
    }
}


int mouseTurnX()
{
    int mouseX=mouse_x;
    rest(6);
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


void drawPlayer(BITMAP *buffer)
{
    circlefill(buffer,(int)px,(int)py,5, makecol(255,0,0));
    line(buffer,(int)px,(int)py,(int)px+5*(int)pdx,(int)py+5*(int)pdy, makecol(0,0,255));
    line(buffer,(int)px,(int)py,(int)px+5*(int)pdx2,(int)py+5*(int)pdy2, makecol(255,0,255));
}

void buttons(float sense)
{

    int xo; if(pdx<0){xo=-20;}else{xo=20;}
    int yo; if(pdy<0){yo=-20;}else{yo=20;}
    int ipx=(int)(px/64.0), ipx_add_xo=(int)(((int)px+xo)/64), ipx_subb_xo=((int)px-xo)/64;
    int ipy=(int)(py/64.0), ipy_add_yo=((int)py+yo)/64, ipy_subb_yo=((int)py-yo)/64;

    int xo3; if(pdx2<0){xo3=-20;}else{xo3=20;}
    int yo3; if(pdy2<0){yo3=-20;}else{yo3=20;}
    int ipx3=(int)(px/64.0), ipx_add_xo3=(int)(((int)px+xo3)/64), ipx_subb_xo3=((int)px-xo3)/64;
    int ipy3=(int)(py/64.0), ipy_add_yo3=((int)py+yo3)/64, ipy_subb_yo3=((int)py-yo3)/64;


    if(key[KEY_W]){
        if(key[KEY_R]){runningvalue=2;}else{runningvalue=1;}
        if(map[ipy*mapX+ipx_add_xo]==0){px+=(float)runningvalue*pdx;}
        if(map[ipy_add_yo*mapX+ipx]==0){py+=(float)runningvalue*pdy;}
    }
    if(key[KEY_S]){
        if(key[KEY_R]){runningvalue=2;}else{runningvalue=1;}
        if(map[ipy*mapX+ipx_subb_xo]==0){px-=(float)runningvalue*pdx;}
        if(map[ipy_subb_yo*mapX+ipx]==0){py-=(float)runningvalue*pdy;}
    }
    if(mouseTurnX()==1){ pa+=sense; if(pa>2*(float)M_PI){pa-=2*(float )M_PI;} pdx=cosf(pa)*5; pdy=sinf(pa)*5; pdx2=cosf(pa+(float )(M_PI/2))*5;  pdy2=sinf(pa+(float )(M_PI/2))*5; }
    if(mouseTurnX()==2){ pa-=sense; if(pa<0){pa+=2*(float )M_PI;} pdx=cosf(pa)*5; pdy=sinf(pa)*5; pdx2=cosf(pa+(float )(M_PI/2))*5;  pdy2=sinf(pa+(float )(M_PI/2))*5; }

    if(key[KEY_D]){if(map[ipy3*mapX+ipx_add_xo3]==0){px+=pdx2;}
                   if(map[ipy_add_yo3*mapX+ipx3]==0){py+=pdy2;}}
    if(key[KEY_A]){if(map[ipy3*mapX+ipx_subb_xo3]==0){px-=pdx2;}
                   if(map[ipy_subb_yo3*mapX+ipx3]==0){py-=pdy2;}}

    if(key[KEY_E])
    {
        int xo2; if(pdx<0){xo2=-25;}else{xo2=25;}
        int yo2; if(pdy<0){yo2=-25;}else{yo2=25;}
        int ipx2=(int)(px/64.0), ipx_add_xo2=(int)(((int)px+xo2)/64);
        int ipy2=(int)(py/64.0), ipy_add_yo2=((int)py+yo2)/64;
        if(map[ipy_add_yo2*mapX+ipx_add_xo2]==4){map[ipy_add_yo2*mapX+ipx_add_xo2]=0;}

    }
}

int main() {

    initAllegro();
    BITMAP *buffer= create_bitmap(SCREEN_W,SCREEN_H);
    px=150;
    py=400;
    pa=0;
    pdx=cosf(pa)*5; pdy=sinf(pa)*5;

    sp[0].type=1; sp[0].state=1; sp[0].map=0; sp[0].x=(int)1.5*64; sp[0].y=(int)5*64; sp[0].z=0;
    while(!key[KEY_ESC])
    {
        clear_bitmap(buffer);
        //drawMap2D(buffer);
        drawSky(buffer);
        drawRays3D(buffer);
        //drawPlayer(buffer);
        drawSprite(buffer);
        buttons(0.25f);
        blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        rest(6);
    }
    allegro_exit();
    return 0;
}
END_OF_MAIN()
