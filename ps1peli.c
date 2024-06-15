// Loading basic PS1 libraries
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libetc.h>
#include <stdlib.h>
#include <stdio.h>

#define OT_LENGTH	12				// OT precision/size
#define OT_ENTRIES	1<<OT_LENGTH
#define MAX_PRIMS	16384			// Primitive area size

// Screen resolution
#define SCREENXRES	320
#define SCREENYRES	240

// Calculate center of screen
#define CENTERX		SCREENXRES/2
#define CENTERY		SCREENYRES/2

// Stuff for display and rendering
DISPENV 	disp;
DRAWENV 	draw;
RECT		ClearRect	={ 0, 0, SCREENXRES, SCREENYRES };

u_long		myOT[2][OT_ENTRIES];	// Ordering table (contains pointers to primitives)
u_long		myPrims[2][MAX_PRIMS];	// Primitive list (can contain various primitive types)
u_long		*myPrimPtr=0;			// Next primitive pointer
int		ActivePage=0;	

// Spinning cursor
static char 		pos=0;
static char		cur_frame=0;
char 			cursor[4]={'/','-','\\','i'};

int main();
void Init();
void sp_cursor();

int main() {
	
	DR_MODE 	dr_prim;
	TILE		tl_prim;
	
	long	i, p, t, OTz, OTc, Flag, nclip;
	int		NumPrims;
	
	int		r, g, b;
	int frame = 20;

	Init();

	FntLoad(960, 256);
	FntOpen(0, 0, SCREENXRES, SCREENYRES, 0, 512);

	SetTile(&tl_prim);
	SetDrawMode(&dr_prim, 0, 0, GetTPage(0, 0, 0, 0), 0);
	SetSemiTrans(&tl_prim, 1);
	MargePrim(&dr_prim, &tl_prim);

	setRGB0(&tl_prim, 128, 128, 128);
	setXY0(&tl_prim, 120, 120);
	setWH (&tl_prim, 64, 64);
	
	while (1) {

		// Toggle buffer index
		ActivePage = (ActivePage + 1) & 1;

		// Clear the current OT
		ClearOTagR(&myOT[ActivePage][0], OT_ENTRIES);

		sp_cursor();
		// FntPrint("\n\n             %c TILE Test %c", cursor[pos], cursor[pos]);
		
		AddPrim(&myOT[ActivePage][OTc], &dr_prim);

		// Prepare to switch buffers
		SetDefDispEnv(&disp, 0, 256*ActivePage, SCREENXRES, SCREENYRES);
		SetDefDrawEnv(&draw, 0, 256*(1-ActivePage), SCREENXRES, SCREENYRES);

		// Wait for all drawing to finish and wait for VSync
		while(DrawSync(1));
		VSync(0);
		
		if (PadRead(0) & PADRright) r++;
		if (PadRead(0) & PADRup) g++;
		if (PadRead(0) & PADRdown) b++;
		
		if (PadRead(0) & PADL1) r--;
		if (PadRead(0) & PADL2) g--;
		if (PadRead(0) & PADR1) b--;

		if (frame == 20) {
					FntPrint("\n\n\
     /\\\n\
    /  \\\n\
   /    \\\n\
  /------\\\n\
 /        \\\n\
/----------\\\n\
I  GameJam I\n\
I          I\n\
I          I                O   \n\
I          I               /I\\ \n\
I          I                I   \n\
I          I               / \\ \n\
I----------I\n");
		}

		if (frame == 19) {
					FntPrint("\n\n\
     /\\\n\
    /  \\\n\
   /    \\\n\
  /------\\\n\
 /        \\\n\
/----------\\\n\
I  GameJam I\n\
I          I\n\
I          I               O   \n\
I          I              /I\\ \n\
I          I               I   \n\
I          I              / \\ \n\
I----------I\n");
		}

		if (frame == 18) {
					FntPrint("\n\n\
     /\\\n\
    /  \\\n\
   /    \\\n\
  /------\\\n\
 /        \\\n\
/----------\\\n\
I  GameJam I\n\
I          I\n\
I          I              O   \n\
I          I             /I\\ \n\
I          I              I   \n\
I          I             / \\ \n\
I----------I\n");
		}

		if (frame == 17) {
					FntPrint("\n\n\
     /\\\n\
    /  \\\n\
   /    \\\n\
  /------\\\n\
 /        \\\n\
/----------\\\n\
I  GameJam I\n\
I          I\n\
I          I             O   \n\
I          I            /I\\ \n\
I          I             I   \n\
I          I            / \\ \n\
I----------I\n");
		}

		if (frame == 16) {
					FntPrint("\n\n\
     /\\\n\
    /  \\\n\
   /    \\\n\
  /------\\\n\
 /        \\\n\
/----------\\\n\
I  GameJam I\n\
I          I\n\
I          I            O   \n\
I          I           /I\\ \n\
I          I            I   \n\
I          I           / \\ \n\
I----------I\n");
		}

				if (frame == 15) {
					FntPrint("\n\n\
     /\\\n\
    /  \\\n\
   /    \\\n\
  /------\\\n\
 /        \\\n\
/----------\\\n\
I  GameJam I\n\
I          I\n\
I          I           O   \n\
I          I          /I\\ \n\
I          I           I   \n\
I          I          / \\ \n\
I----------I\n");
		}

		if (frame == 14) {
					FntPrint("\n\n\
     /\\\n\
    /  \\\n\
   /    \\\n\
  /------\\\n\
 /        \\\n\
/----------\\\n\
I  GameJam I\n\
I          I\n\
I          I          O   \n\
I          I         /I\\ \n\
I          I          I   \n\
I          I         / \\ \n\
I----------I\n");
		}

		if (frame == 13) {
					FntPrint("\n\n\
     /\\\n\
    /  \\\n\
   /    \\\n\
  /------\\\n\
 /        \\\n\
/----------\\\n\
I  GameJam I\n\
I          I\n\
I          I         O   \n\
I          I        /I\\ \n\
I          I         I   \n\
I          I        / \\ \n\
I----------I\n");
		}

		if (frame == 12) {
					FntPrint("\n\n\
     /\\\n\
    /  \\\n\
   /    \\\n\
  /------\\\n\
 /        \\\n\
/----------\\\n\
I  GameJam I\n\
I          I\n\
I          I        O   \n\
I          I       /I\\ \n\
I          I        I   \n\
I          I       / \\ \n\
I----------I\n");
		}

		if (frame == 11) {
					FntPrint("\n\n\
     /\\\n\
    /  \\\n\
   /    \\\n\
  /------\\\n\
 /        \\\n\
/----------\\\n\
I  GameJam I\n\
I          I\n\
I          I       O   \n\
I          I      /I\\ \n\
I          I       I   \n\
I          I      / \\ \n\
I----------I\n");
		}

				if (frame == 10) {
					FntPrint("\n\n\
     /\\\n\
    /  \\\n\
   /    \\\n\
  /------\\\n\
 /        \\\n\
/----------\\\n\
I  GameJam I\n\
I          I\n\
I          I      O   \n\
I          I     /I\\ \n\
I          I      I   \n\
I          I     / \\ \n\
I----------I\n");
		}

		if (frame == 9) {
					FntPrint("\n\n\
     /\\\n\
    /  \\\n\
   /    \\\n\
  /------\\\n\
 /        \\\n\
/----------\\\n\
I  GameJam I\n\
I          I\n\
I          I     O   \n\
I          I    /I\\ \n\
I          I     I   \n\
I          I    / \\ \n\
I----------I\n");
		}

		if (frame == 8) {
					FntPrint("\n\n\
     /\\\n\
    /  \\\n\
   /    \\\n\
  /------\\\n\
 /        \\\n\
/----------\\\n\
I  GameJam I\n\
I          I\n\
I          I    O   \n\
I          I   /I\\ \n\
I          I    I   \n\
I          I   / \\ \n\
I----------I\n");
		}

		if (frame == 7) {
					FntPrint("\n\n\
     /\\\n\
    /  \\\n\
   /    \\\n\
  /------\\\n\
 /        \\\n\
/----------\\\n\
I  GameJam I\n\
I          I\n\
I          I   O   \n\
I          I  /I\\ \n\
I          I   I   \n\
I          I  / \\ \n\
I----------I\n");
		}

		if (frame == 6) {
					FntPrint("\n\n\
     /\\\n\
    /  \\\n\
   /    \\\n\
  /------\\\n\
 /        \\\n\
/----------\\\n\
I  GameJam I\n\
I          I\n\
I          I  O   \n\
I          I /I\\ \n\
I          I  I   \n\
I          I / \\ \n\
I----------I\n");
		}

		if (frame == 5) {
					FntPrint("\n\n\
     /\\\n\
    /  \\\n\
   /    \\\n\
  /------\\\n\
 /        \\\n\
/----------\\\n\
I  GameJam I\n\
I          I\n\
I          I O   \n\
I          I/I\\ \n\
I          I I   \n\
I          I/ \\ \n\
I----------I\n");
		}

		if (frame == 4) {
					FntPrint("\n\n\
     /\\\n\
    /  \\\n\
   /    \\\n\
  /------\\\n\
 /        \\\n\
/----------\\\n\
I  GameJam I\n\
I          I\n\
I   \\O/    I\n\
I    I     I\n\
I    I     I\n\
I   / \\    I\n\
I----------I\n");
		}




		if (PadRead(0) & PADLleft) {
			// frame-- if frame is greater than 4
			if (frame > 4) {
				frame--;
			}
		}

		if (PadRead(0) & PADLright) {
			// frame-- if frame is greater than 4
			if (frame < 20) {
				frame++;
			}
		}
		
		// Switch display buffers
		PutDispEnv(&disp);
		PutDrawEnv(&draw);
		
		// Clear the drawing buffer before drawing the next frame
		ClearRect.y = 256*(1-ActivePage);
		ClearImage(&ClearRect, 0, 0, 0);
		
		// Begin drawing the new frame
		DrawOTag(&myOT[ActivePage][OT_ENTRIES-1]);
		FntFlush(0);
		
		SetDispMask(1);

	}

}

void Init() {
	
	// Reset the GPU and initialize the controller
	ResetGraph(0);
	PadInit(0);
	SetVideoMode(0);
	
	// Init font system
	FntLoad(960, 0);
	FntOpen(0, 0, SCREENXRES, SCREENYRES, 0, 512);
	
	// Initialize and setup the GTE
	InitGeom();
	SetGeomOffset(CENTERX, CENTERY);
	SetGeomScreen(CENTERX);
	
	
	// Set the display and draw environments
	SetDefDispEnv(&disp, 0, 0, SCREENXRES, SCREENYRES);
	SetDefDrawEnv(&draw, 0, 256, SCREENXRES, SCREENYRES);
	
	
	// Set the new display/drawing environments
	VSync(0);
	PutDispEnv(&disp);
	PutDrawEnv(&draw);
	ClearImage(&ClearRect, 0, 0, 0);
	
}

void sp_cursor() {
	cur_frame++;
	if (cur_frame >= 8) {
		cur_frame = 0;
		pos = (pos+1) % 4;
	}
}