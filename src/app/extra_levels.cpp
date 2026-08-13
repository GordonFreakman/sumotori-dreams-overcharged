#include "boundary.h"

#include "types.h"

extern char g_gameMenuLabels[5][7][24];

extern char *g_builtinLevelScripts[];

extern SumoS32 g_gameArenaPageRowCount;
extern SumoS32 g_gameArenaPageChainLinks;
extern void (*g_gameModFilePickerRequest)();

static const char s_extraLevelScript6[] =
    "startpos=vec(0,180,250);pos=startpos;angle=0;dir=vec(0,0,-1);addbox(vec(40,1,20),pos-dir*20,0,1);i=0; re"
    "peat(55){i=i+0.28;addbox(vec(40,1,2),pos+dir*2,0,1);dir=dir*vec(1,-1,1);turnto(dir+vec(0,-0.01,0));dir=d"
    "ir*vec(1,-1,1);pos=pos+dir*4;dir=normalize(vec(0,-1+cos(i)*0.8,-1));}man(vec(10,4,2)+startpos,vec(-1.2,0"
    ",-0.7),2);man(vec(-10,4,3)+startpos,vec(1.2,0,-0.2),3);man(vec(10,4,-8)+startpos,vec(-1.2,0,-0.7),2);man"
    "(vec(-10,4,-9)+startpos,vec(1.2,0,-0.2),3);";

static const char s_extraLevelScript7[] =
    "h=14;i=0;repeat(h){l = (h-i+1)*6;addbox( vec(l,3,l),vec(0,i*6-7+200,0),0,1);i=i+1;}l = (h+1)*6-6;addbox("
    "vec(5,100,5),vec(l,100,0-l),3,1);addbox(vec(5,100,5),vec(l,100,l),3,1);addbox(vec(5,100,5),vec(0-l,100,0"
    "-l),3,1);addbox(vec(5,100,5),vec(0-l,100,l),3,1); i=-18;l = (h-i+1)*6;addbox( vec(l,3,l),vec(0,i*6-7+200"
    ",0),4,1);man(vec(7,h*6-7+200,-7),vec(-2,0,1),3); man(vec(-7,h*6-7+200,7),vec(2,0,-1),2);man(vec(-7,h*6-7"
    "+200,-7),vec(1,0,2),1); man(vec(7,h*6-7+200,7),vec(-1,0,-2),0);";

extern "C" int SumoTraceFracture(int id, float x, float y, float z, float b) {
  SDL_Log("[TRACE] fracture id=%d pos=(%.2f,%.2f,%.2f) breakability=%.2f", id,
          x, y, z, b);
  return 0;
}

void SumoInstallExtraLevels() {
  g_builtinLevelScripts[6] = (char *)s_extraLevelScript6;
  g_builtinLevelScripts[7] = (char *)s_extraLevelScript7;

  SDL_strlcpy(g_gameMenuLabels[4][2], "bad trip",
              sizeof(g_gameMenuLabels[4][2]));
  SDL_strlcpy(g_gameMenuLabels[4][3], "top rooster",
              sizeof(g_gameMenuLabels[4][3]));
  SDL_strlcpy(g_gameMenuLabels[4][4], "load mod file",
              sizeof(g_gameMenuLabels[4][4]));
  g_gameMenuLabels[4][5][0] = '\0';

  g_gameModFilePickerRequest = SumoRequestModFilePicker;

  g_gameArenaPageRowCount = 5;
  g_gameArenaPageChainLinks = 2;
}
