#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspctrl.h>
#include "glib2d.h"


PSP_MODULE_INFO("game-test", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);


/stops the game.
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

auto main() -> int {
    
    setupcallbacks();

    //player sprite
    g2dTexture* ric = g2dTexLoad("ricardo.png",G2D_SWIZZLE);
    int w = (ric == NULL ? 10 : ric->w),
    h = (ric == NULL ? 10 : ric->h);

    //movement under here
    SceCtrlData ctrldata;
    while(1) {
            
            sceCtrlReadBufferPositive(&ctrldata, 1);

                 

                if (ctrldata.Buttons & PSP_CTRL_UP) {
                    //pspDebugScreenPrintf("up is pressed \n");
                    if (!input && y > 12.5){
                        y-=15;
                        score-=5;
                        input = true;
                    }
                    else {
   
                    }  
                    
                }

                else if (ctrldata.Buttons & PSP_CTRL_DOWN) {
                    //pspDebugScreenPrintf("down is pressed \n");
                    if (!input && y < 259.5){
                        y+=15;
                        score-=5;
                        input = true;
                    }
                    else {

                    } 
                    
                }

                else if (ctrldata.Buttons & PSP_CTRL_RIGHT) {
                    //pspDebugScreenPrintf("right is pressed \n");
                    if (!input && x < 467.5) {
                        x+=15;
                        score-=5;
                        input = true;
                     }
                     else {

                     }

                }

                else if (ctrldata.Buttons & PSP_CTRL_LEFT) {
                    //pspDebugScreenPrintf("left is pressed \n");
                    if (!input && x > 12.5){
                        x-=15;
                        score-=5;
                        input = true;
                    }

                    else {

                    }
                     
                    
                }
                else if (ctrldata.Buttons & PSP_CTRL_RTRIGGER && ctrldata.Buttons & PSP_CTRL_SELECT) {
                    //muur collision aan en uit zetten
                    if (!input && wallc) {
                        wallc = false;
                        input = true;
                    }
                    else if (!input && !wallc) {
                        wallc = true;
                        input = true;
                    } 
                    else {
            
                    }

                }
                else if (ctrldata.Buttons & PSP_CTRL_LTRIGGER && ctrldata.Buttons & PSP_CTRL_SELECT) {
                    //finish collision aan en uit zetten
                    if (!input && finishc) {
                        finishc = false;
                        input = true;
                        
                    }
                    else if (!input && !finishc) {
                        finishc = true;
                        input = true;
                        
                    } 
                    else {
            
                    }

                }


                
                else {
                    //als je niks indruk word hier input false. zodat je de knoppen moet klikken en niet in houden
                    input = false;
                }
                
                //draw stuff
                g2dClear(BLACK);

                drawwalls();
                if (!collected) {
                    drawcoin();
                }

                g2dBeginRects(ric);
                if (ric == NULL) {
                    g2dSetColor(RED);
                }
                g2dSetCoordMode(G2D_UP_LEFT);
                g2dSetAlpha(255);
                g2dSetScaleWH(w,h);
                g2dSetCoordXY(x,y);
                g2dSetRotation(0);
                g2dAdd();
                g2dEnd();
               
                
  
                g2dFlip(G2D_VSYNC);
        
                score-=1;

                    
                    
            
    }
    
}
