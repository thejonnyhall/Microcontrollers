#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <cab202_graphics.h>
#include <cab202_sprites.h>
#include <cab202_timers.h>

// ADD INCLUDES HERE

// Configuration
#define DELAY (10) /* Millisecond delay between game updates */

#define HERO_WIDTH (5) /* Basically says if you see HERO_WIDTH replace it with (5)
#define HERO_HEIGHT (5)
#define ZOMBIE_WIDTH (5)
#define ZOMBIE_HEIGHT (5)

// Game state.
bool game_over = false; /* Set this to true when game is over */
bool update_screen = true; /* Set to false to prevent screen update. */

static char * hero_image =
/**/	"H   H"
/**/	"H   H"
/**/	"HHHHH"
/**/	"H   H"
/**/	"H   H";

static char * zombie_image =
/**/	"ZZZZZ"
/**/	"   Z "
/**/	"  Z  "
/**/	" Z   "
/**/	"ZZZZZ";

static char * msg_image =
/**/	"Goodbye and Thanks for playing ZombieDash Jr. by Jonny Hall"
/**/	"            Press any key to exit...            ";

// (c) Declare a sprite_id called hero.

// (m) Declare a sprite_id called zombie.

// Setup game.
void setup(void) {
	// Useful variables.
	int w = screen_width(), wh = HERO_WIDTH, wz = ZOMBIE_WIDTH;
	int h = screen_height(), hh = HERO_HEIGHT, hz = ZOMBIE_HEIGHT;

	// (a) Draw the border (setup).
	draw_line(0, 0, w - 1, 0, '*');
	draw_line(0, h-1, w - 1, h-1, '*');
	draw_line(0, 0, 0, h-1, '*');
	draw_line(0, 0, 0, h-1 '*');


	// Keep the next line intact.
	show_screen();

	// (d) Set up the hero at the centre of the screen.

	// (e) Draw the hero.

	// Keep the next line intact.
	show_screen();

	// (n)	Set up the zombie at a random location on the screen.

	// (o) Draw the zombie.

	// (p) Set the zombie in motion.

	// Keep the next line intact.
	show_screen();
}

// Play one turn of game.
void process(void) {
	int w = screen_width(), wh = HERO_WIDTH, wz = ZOMBIE_WIDTH;
	int h = screen_height(), hh = HERO_HEIGHT, hz = ZOMBIE_HEIGHT;

	// (f) Get a character code from standard input without waiting.
	
	// (y) Test for end of game.

	// (g)	Get the current screen coordinates of the hero in integer variables 
	//		by rounding the actual coordinates.

	// (h) Move hero left according to specification.

	// (i) Move hero right according to specification.

	// (j) Move hero up according to specification.

	// (k) Move hero down according to specification.

	// (q.a) Test to move the zombie if key is 'z' or ERROR.
		// (r) Zombie takes one step.

		// (s) Get screen location of zombie.

		// (t) Get the displacement vector of the zombie.

		// (u) Test to see if the zombie hit the left or right border.

		// (v) Test to see if the zombie hit the top or bottom border.

		// (w) Test to see if the zombie needs to step back and change direction.

	// (q.b) End else-if test to move the zombie if key is 'z' or negative.

	// Leave next line intact
	clear_screen();

	// (b) Draw the border (process).

	// (l)	Draw the hero.

	// (x)	Draw the zombie.
}

// Clean up game
void cleanup(void) {
	// STATEMENTS
}

// Program entry point.
int main(void) {
	setup_screen();

	auto_save_screen(true);

	setup();
	show_screen();

	while ( !game_over ) {
		process();

		if ( update_screen ) {
			show_screen();
		}

		timer_pause(DELAY);
	}

	cleanup();

	return 0;
}