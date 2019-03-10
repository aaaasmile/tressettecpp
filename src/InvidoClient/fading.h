
// fading.h

/* 
  Fading with alphablending
  (c) Patrick Kooman, 2002
  contact: patrick@2dgame-tutorial.com
*/

#include <stdio.h>
#include "SDL.h"

/* Fades the given surface in or out to the given screen within the given time */
void fade (SDL_Surface* p_surf_screen, SDL_Surface* p_surf_img, Uint32 ui_seconds, int i_fade_out, SDL_Renderer*  psdlRenderer) ;

