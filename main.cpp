#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspctrl.h>
#include "glib2d.h"

float x = 12.5, y = 136;
bool input = false; 


PSP_MODULE_INFO("game-test", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);


//stops the game.
//this is just code that works, so dont change this. (upcoming 3 functions)
int exit_callback(int arg1, int arg2, void *common) {
    sceKernelExitGame();
    return 0;
}


int callbackthread(SceSize args, void *argp) {
    int cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
    sceKernelRegisterExitCallback(cbid);

    sceKernelSleepThreadCB();
    return 0;
}


void setupcallbacks () {
    int thid = sceKernelCreateThread("update_thread", callbackthread, 0x11, 0xfa0, 0, NULL);
    if (thid >= 0) {
        sceKernelStartThread(thid, 0, NULL);
    }
}
//wall variables
int muurtop[8] = {47, 151, 0, 157, 0, 266, 6, 161};
int muurleft[8] = {45, 0, 0, 0, 6, 6, 474, 474};
int muurwidth[8] = {6, 43, 6, 6, 479, 479, 6, 6};
int muurheight[8] = {68, 6, 116, 115, 6, 6, 105, 161};

int drawwalls() {
    //draw the walls    
    for (int j = 0; j < 8; j++) {
        g2dBeginRects(NULL); // No texture
        g2dSetColor(WHITE);
        g2dSetScaleWH(muurwidth[j],muurheight[j]);
        g2dSetCoordXY(muurleft[j],muurtop[j]);
        g2dAdd();
        g2dEnd();
    
    }

    return 0;
}

int drawstuff() {
    //draw stuff
    g2dClear(BLACK);

    drawwalls();       

    g2dBeginRects(ric);
    if (ric == NULL) {
        g2dSetColor(RED);
    }
    g2dSetCoordMode(G2D_CENTER);
    g2dSetAlpha(255);
    g2dSetScaleWH(w,h);
    g2dSetCoordXY(x,y);
    g2dSetRotation(0);
    g2dAdd();
    g2dEnd();
               
    g2dFlip(G2D_VSYNC);
    
}

int collision() {
    //0.1 difference so only collision on overlap
        float playertop = y - 12.4;
        float playerbottom = y + 12.4;
        float playerleft = x - 12.4;
        float playerright = x + 12.4;

        for (int i = 0; i < 8; i++) {

            int muur_top = muurtop[i];
            int muur_bottom = muurtop[i] + muurheight[i];
            int muur_left = muurleft[i];
            int muur_right = muurleft[i] + muurwidth[i];

            if (playertop > muur_bottom || playerright < muur_left || playerbottom < muur_top || playerleft > muur_right) {

            }
            else {
                //collision
                x = xoud;
                y = youd;
                
            }

        }
    drawstuff();
}



auto main() -> int {
    
    setupcallbacks();

    //player sprite
    g2dTexture* ric = g2dTexLoad("ricardo.png",G2D_SWIZZLE);
    int w = (ric == NULL ? 10 : ric->w),
    h = (ric == NULL ? 10 : ric->h);

    //movement under here
    SceCtrlData ctrldata;
    while(true) {
            
            sceCtrlReadBufferPositive(&ctrldata, 1);

                float xoud = x;
                float youd = y;
        

                if (ctrldata.Buttons & PSP_CTRL_UP) { 
                    y--;
                }

                else if (ctrldata.Buttons & PSP_CTRL_DOWN) {
                    y++;
                }

                else if (ctrldata.Buttons & PSP_CTRL_RIGHT) {                  
                        x++;
                }

                else if (ctrldata.Buttons & PSP_CTRL_LEFT) {                   
                        x--; 
                }
                
                
                else {
                    //als je niks indruk word hier input false. zodat je de knoppen moet klikken en niet in houden
                    input = false;
                }
        
                collision();
              
    }
    
}
