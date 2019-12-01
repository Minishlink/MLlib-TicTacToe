/*			-==========================-
			|		  TicTacToe 	   |
			-==========================-

main.c

Author : Minishlink
Created : May 2009
Latest modified : 09/06/09 (Day/Month/Year)

Twitter : http://twitter.com/Minishlink
Website : http://minishlink.dev-fr.org and http://louislagrange.free.fr
MLlib Website : http://louislagrange.free.fr/MLlib 							*/

#ifndef _COMMON_H
#define _COMMON_H

#include <MLlib.h>
#include "main.h"

#include "font_png.h"
#include "croix_png.h"
#include "rond_png.h"
#include "fond_png.h"
#include "cursor1_png.h"
#include "cursor2_png.h"
#include "bg_retro_png.h"
#include "bg_compo_png.h"

#include "music_mod.h"

#define SIZE_BORDER	16
#define SIZE_BLOC	64
#define SIZE_CURSOR 96

enum { 
	C_1 = 0,
	C_2
};

#define CROIX	0
#define ROND	1
#define BLANK	2

#endif

