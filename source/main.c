/*			-==========================-
			|		  TicTacToe 	   |
			-==========================-

main.c

Author : Minishlink
Created : May 2009
Latest modified : 09/06/09 (Day/Month/Year)

This is crappy to group all the functions here, but well, it's a small game...
It was first coded for MLlib 1.0, which is way not the same as the next releases; that's why the code is crappy too. :p

Twitter : http://twitter.com/Minishlink
Website : http://minishlink.dev-fr.org and http://louislagrange.free.fr
MLlib Website : http://louislagrange.free.fr/MLlib 							*/

#include <MLlib.h>

#include "common.h"

static MODPlay mod;
ML_Sprite fond, font, bg_retro, bg_compo, cursor[2], spriteCroixRond[2];

int main(int argc, char **argv) 
{	ML_Init();
	ML_SplashScreen();
	
	init();
	//compo();
	//retro();
	menu();
	    	
	return 0;
}

void menu()
{
	bool exit = 0;
	
	if(!ML_IsPlayingMOD()) ML_PlayMODFromBuffer(&mod, music_mod);
	
	while(1)
	{
		if(Wiimote[0].Newpress.Home) { exit = true; } 
		else if(Wiimote[0].Held.A && Wiimote[0].Held.B) jeu();
		
		ML_SetSpriteScale(&font, 5, 5);
		ML_SimpleText(&font, 160, 50, "TicTacToe");
		ML_SetSpriteScale(&font, 2, 2);
		ML_SimpleText(&font, 300, 90, "by Minishlink");
		
		ML_SetSpriteScale(&font, 2.5, 2.5);
		if(Wiimote[0].Held.A) ML_SimpleText(&font, 105, 190, "Press /A\\ + B to play !");	
		else if(Wiimote[0].Held.B) ML_SimpleText(&font, 105, 190, "Press A + /B\\ to play !");	
		else ML_SimpleText(&font, 125, 190, "Press A + B to play !");	
		
		ML_SimpleText(&font, 190, 320, "Instructions :");
		
		ML_SetSpriteScale(&font, 1.5, 1.5);
		ML_Text(&font, 20, 360,  "- Point the Wiimote to the screen and press A.\n\n- Press B to reset the grid, scores will be saved.\n\n- Press Home if you want to reset scores or quit.\n\n- You can play with 1 or 2 Wiimotes.");
 		
		if(exit)
			if(ML_FadeOut()) ML_Exit();
		
		ML_Refresh();
	}	
}

void jeu()
{
	bool tour = 0, newGame = 1;
	int i, j;
	
	int damier[3][3] = {{BLANK}};
	
	int cursorX, cursorY;
	u8 won = 0, times = 0, scorePlayerOne = 0, scorePlayerTwo = 0, wiimote = 0;
	
	while(1)
	{
		if(Wiimote[0].Released.Home) { menu(); } 
		else if(Wiimote[0].Newpress.B) newGame = 1;
		
		cursorX = cursor[tour].x;
		cursorY = cursor[tour].y;
		
		ML_DrawSprite(&fond);
		ML_SetSpriteScale(&font, 5, 5);
		ML_SimpleText(&font, 160, 50, "TicTacToe");
		
		ML_SetSpriteScale(&font, 2, 2);
		ML_Text(&font, 250, 100, "Player : %d", tour+1);		
		ML_Text(&font, 260, 420, "Times : %d", times);
		
		ML_SetSpriteScale(&font, 1.5, 1.5);
		ML_SimpleText(&font, 50, 180, "Player 1 :");
		ML_SimpleText(&font, 480, 180, "Player 2 :");
		
		ML_SetSpriteScale(&font, 8, 16);
		ML_Text(&font, 85, 270, "%d", scorePlayerOne);
		ML_Text(&font, 530, 270, "%d", scorePlayerTwo);
		
		// Draw 1st line
		if(damier[0][0] != BLANK) //== CROIX || damier[0][0] == ROND)
			ML_DrawSpriteXY(&spriteCroixRond[damier[0][0]], (fond.x+SIZE_BORDER), (fond.y+SIZE_BORDER));			
		
		if(damier[1][0] != BLANK) //== CROIX || damier[1][0] == ROND)
			ML_DrawSpriteXY(&spriteCroixRond[damier[1][0]], (fond.x+(SIZE_BORDER*2+SIZE_BLOC)), (fond.y+SIZE_BORDER));
		
		if(damier[2][0] != BLANK) //== CROIX || damier[2][0] == ROND)
			ML_DrawSpriteXY(&spriteCroixRond[damier[2][0]], (fond.x+(SIZE_BORDER*3+SIZE_BLOC*2)), (fond.y+SIZE_BORDER));
		
		// Draw 2nd line
		if(damier[0][1] != BLANK) //== CROIX || damier[0][1] == ROND)
			ML_DrawSpriteXY(&spriteCroixRond[damier[0][1]], (fond.x+SIZE_BORDER), (fond.y+(SIZE_BORDER*2+SIZE_BLOC)));
			
		if(damier[1][1] != BLANK) //== CROIX || damier[1][1] == ROND)
			ML_DrawSpriteXY(&spriteCroixRond[damier[1][1]], (fond.x+(SIZE_BORDER*2+SIZE_BLOC)), (fond.y+(SIZE_BORDER*2+SIZE_BLOC)));
			
		if(damier[2][1] != BLANK) //== CROIX || damier[2][1] == ROND)
			ML_DrawSpriteXY(&spriteCroixRond[damier[2][1]], (fond.x+(SIZE_BORDER*3+SIZE_BLOC*2)), (fond.y+(SIZE_BORDER*2+SIZE_BLOC)));
			
		// Draw 3rd line
		if(damier[0][2] != BLANK) //== CROIX || damier[0][2] == ROND)
			ML_DrawSpriteXY(&spriteCroixRond[damier[0][2]], (fond.x+SIZE_BORDER), (fond.y+(SIZE_BORDER*3+SIZE_BLOC*2)));
			
		if(damier[1][2] != BLANK) //== CROIX || damier[1][2] == ROND)
			ML_DrawSpriteXY(&spriteCroixRond[damier[1][2]], (fond.x+(SIZE_BORDER*2+SIZE_BLOC)), (fond.y+(SIZE_BORDER*3+SIZE_BLOC*2)));
			
		if(damier[2][2] != BLANK) //== CROIX || damier[2][2] == ROND)
			ML_DrawSpriteXY(&spriteCroixRond[damier[2][2]], (fond.x+(SIZE_BORDER*3+SIZE_BLOC*2)), (fond.y+(SIZE_BORDER*3+SIZE_BLOC*2)));
		
		// "Collisions"
		if(Wiimote[wiimote].Newpress.A && !won)
		{	
			// 1st line		
			if (cursorX <= fond.x+(SIZE_BORDER+SIZE_BLOC) && cursorX >= fond.x+SIZE_BORDER &&
				cursorY <= fond.y+(SIZE_BORDER+SIZE_BLOC) && cursorY >= fond.y+SIZE_BORDER &&
				(damier[0][0] == BLANK))
			{
				damier[0][0] = tour;
				tour^=1;
				times++;
			}
				
			else if (cursorX <= fond.x+(SIZE_BORDER*2+SIZE_BLOC*2) && cursorX >= fond.x+(SIZE_BORDER*2+SIZE_BLOC) &&
					 cursorY <= fond.y+(SIZE_BORDER+SIZE_BLOC) && cursorY >= fond.y+SIZE_BORDER &&
					 (damier[1][0] == BLANK))
			{
				damier[1][0] = tour;
				tour^=1;
				times++;
			}
			
			else if (cursorX <= fond.x+(SIZE_BORDER*3+SIZE_BLOC*3) && cursorX >= fond.x+(SIZE_BORDER*3+SIZE_BLOC*2) &&
					 cursorY <= fond.y+(SIZE_BORDER+SIZE_BLOC) && cursorY >= fond.y+SIZE_BORDER &&
					 (damier[2][0] == BLANK))
			{
				damier[2][0] = tour;
				tour^=1;
				times++;
			}
			
			// 2nd line
			else if (cursorX <= fond.x+(SIZE_BORDER+SIZE_BLOC) && cursorX >= fond.x+SIZE_BORDER &&
					 cursorY <= fond.y+(SIZE_BORDER*3+SIZE_BLOC*2) && cursorY >= fond.y+(SIZE_BORDER*2+SIZE_BLOC) &&
					 (damier[0][1] == BLANK))
			{
				damier[0][1] = tour;
				tour^=1;
				times++;
			}
			
			else if (cursorX <= fond.x+(SIZE_BORDER*2+SIZE_BLOC*2) && cursorX >= fond.x+(SIZE_BORDER*2+SIZE_BLOC) &&
					 cursorY <= fond.y+(SIZE_BORDER*3+SIZE_BLOC*2) && cursorY >= fond.y+(SIZE_BORDER*2+SIZE_BLOC) &&
					 (damier[1][1] == BLANK))
			{
				damier[1][1] = tour;
				tour^=1;
				times++;
			}
			
			else if (cursorX <= fond.x+(SIZE_BORDER*3+SIZE_BLOC*3) && cursorX >= fond.x+(SIZE_BORDER*3+SIZE_BLOC*2) &&
					 cursorY <= fond.y+(SIZE_BORDER*3+SIZE_BLOC*2) && cursorY >= fond.y+(SIZE_BORDER*2+SIZE_BLOC) &&
					 (damier[2][1] == BLANK))
			{
				damier[2][1] = tour;
				tour^=1;
				times++;
			}
			
			// 3rd line
			else if (cursorX <= fond.x+(SIZE_BORDER+SIZE_BLOC) && cursorX >= fond.x+SIZE_BORDER &&
					 cursorY <= fond.y+(SIZE_BORDER*3+SIZE_BLOC*3) && cursorY >= fond.y+(SIZE_BORDER*3+SIZE_BLOC*2) &&
					 (damier[0][2] == BLANK))
			{
				damier[0][2] = tour;
				tour^=1;
				times++;
			}
			
			else if (cursorX <= fond.x+(SIZE_BORDER*2+SIZE_BLOC*2) && cursorX >= fond.x+(SIZE_BORDER*2+SIZE_BLOC) &&
					 cursorY <= fond.y+(SIZE_BORDER*3+SIZE_BLOC*3) && cursorY >= fond.y+(SIZE_BORDER*3+SIZE_BLOC*2) &&
					 (damier[1][2] == BLANK))
			{
				damier[1][2] = tour;
				tour^=1;
				times++;
			}
			
			else if (cursorX <= fond.x+(SIZE_BORDER*3+SIZE_BLOC*3) && cursorX >= fond.x+(SIZE_BORDER*3+SIZE_BLOC*2) &&
					 cursorY <= fond.y+(SIZE_BORDER*3+SIZE_BLOC*3) && cursorY >= fond.y+(SIZE_BORDER*3+SIZE_BLOC*2) &&
					 (damier[2][2] == BLANK))
			{
				damier[2][2] = tour;
				tour^=1;
				times++;
			}
		}
		
		// Detect if won
		if(times >= 5 && !won)
		{
			if ((damier[0][0] == damier[1][0] && damier[0][0] == damier[2][0] && damier[0][0] != BLANK && damier[1][0] != BLANK && damier[2][0] != BLANK) || 
				(damier[0][1] == damier[1][1] && damier[0][1] == damier[2][1] && damier[0][1] != BLANK && damier[1][1] != BLANK && damier[2][1] != BLANK) ||
				(damier[0][2] == damier[1][2] && damier[0][2] == damier[2][2] && damier[0][2] != BLANK && damier[1][2] != BLANK && damier[2][2] != BLANK) || 
				(damier[0][0] == damier[0][1] && damier[0][0] == damier[0][2] && damier[0][0] != BLANK && damier[0][1] != BLANK && damier[0][2] != BLANK) ||
				(damier[1][0] == damier[1][1] && damier[1][0] == damier[1][2] && damier[1][0] != BLANK && damier[1][1] != BLANK && damier[1][2] != BLANK) || 
				(damier[2][0] == damier[2][1] && damier[2][0] == damier[2][2] && damier[2][0] != BLANK && damier[2][1] != BLANK && damier[2][2] != BLANK) ||
				(damier[0][0] == damier[1][1] && damier[0][0] == damier[2][2] && damier[0][0] != BLANK && damier[1][1] != BLANK && damier[2][2] != BLANK) || 
				(damier[2][0] == damier[1][1] && damier[2][0] == damier[0][2] && damier[2][0] != BLANK && damier[1][1] != BLANK && damier[0][2] != BLANK)  )
			won = 1;
		}
		
		if(won == 1) 
		{
			if(tour == 0) scorePlayerTwo++; // inverser les deux car ça change plus haut
			else scorePlayerOne++;
			
			won = 2;
		}	
		
		if(newGame)
		{
			for(i = 0; i < 3; i++)
				for(j = 0; j < 3; j++)
					damier[i][j] = BLANK;	
			
			if(scorePlayerOne < scorePlayerTwo) tour = 0;
			else if(scorePlayerOne > scorePlayerTwo) tour = 1;
			
			newGame = 0;	
			won = 0;
		}	
		
		if(tour == 0) { wiimote = 0; ML_SetSpriteAlpha(&cursor[C_2], 150); ML_SetSpriteAlpha(&cursor[C_1], 255); }
		else {
			if(Wiimote[1].Enabled) wiimote = 1; 
			else wiimote = 0;
			
			ML_SetSpriteAlpha(&cursor[C_1], 150);
			ML_SetSpriteAlpha(&cursor[C_2], 255);
		}
	
		if(Wiimote[1].Enabled) 
		{
			ML_Cursor(&cursor[C_1], 0);
			ML_Cursor(&cursor[C_2], 1);
		} else
			ML_Cursor(&cursor[tour], 0);
		
		//Easter egg which deserves to strictly nothing
		if((Wiimote[0].Held.One && ML_IsCollisionEx(&cursor[C_1], &fond)) || (Wiimote[1].Held.Two && ML_IsCollisionEx(&cursor[C_2], &fond)))
			fond.visible = 0;
		else fond.visible = 1;
		
		ML_Refresh();
	}		
}

void retro()
{	
	int i = -200;
	
	while(i < 1200)
	{
		if(Wiimote[0].Released.Plus) i = 1200;
		
		if(i < 1198)
		{
			ML_DrawSprite(&bg_retro);
		
			if(i >= 0)
			{
				if(i%40 < 20) 
				{
					ML_SetSpriteScale(&font, 10, 20);
					ML_SimpleText(&font, 70, 110, "WARNING");
				}
		
				ML_SetSpriteScale(&font, 2, 2);
				if(i > 240) ML_Text(&font, 40, 240, "This is a RETRO game:\nIt can give you some headaches\naccording to:\n   - its GRAPHICS\n   - its MUSIC!");	
				else ML_Text(&font, 40, 480-i, "This is a RETRO game:\nIt can give you some headaches\naccording to:\n   - its GRAPHICS\n   - its MUSIC!");	
			
				if(i > 240) ML_SimpleText(&font, 380, 300, "(LOL)");
			
				ML_SetSpriteScale(&font, 1.5, 1.5);
				ML_SimpleText(&font, 30, 430, "Press (+) to skip.");			
			}
		}
	
		i++;
		ML_Refresh();
	}
}

void compo()
{	
	ML_DrawSprite(&bg_compo);
	ML_Refresh();
	
	sleep(5);
		
	ML_Refresh();
}

void init()
{	
	ML_InitMOD(&mod);
	
	ML_SetNumberOfPads(2, 0);
	
	ML_SetBackgroundColor(GX_COLOR_WHITE);
	ML_LoadSpriteFromBuffer(&font, font_png, 0, 0);
	ML_InitTile(&font, 8, 8);
	ML_SetSpriteScale(&font, 2, 2);
	ML_LoadSpriteFromBuffer(&bg_compo, bg_compo_png, 0, 0);
	ML_LoadSpriteFromBuffer(&bg_retro, bg_retro_png, 0, 0);
	ML_LoadSpriteFromBuffer(&fond, fond_png, 640/2 - 128, 480/2 - 128);
	ML_LoadSpriteFromBuffer(&spriteCroixRond[CROIX], croix_png, 0, 0);
	ML_LoadSpriteFromBuffer(&spriteCroixRond[ROND], rond_png, 0, 0);
	ML_LoadSpriteFromBuffer(&cursor[C_1], cursor1_png, 0, 0);
	ML_LoadSpriteFromBuffer(&cursor[C_2], cursor2_png, 0, 0);
}

