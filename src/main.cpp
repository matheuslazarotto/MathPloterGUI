/** Function parser and ploter GUI 
 * 
 * The present code is a GUI application to 
 * set functions and plot them, converting 
 * the text from the interface to code usable 
 * mathematical functions. 
 * 
 * The graphical elements are made from the 
 * olcPixelGameEngine, while the convertion 
 * of string from the GUI to code functions 
 * are made by the Exprtk parser library.
 * 
 * External Python scripts are made to return 
 * the plot.
 * 
 *  
 * Credits:
 * This code is just an interface for the 
 * remarkable Exprtk function parser code, 
 * made by Arash Partow. The code, manual 
 * and files can be found at:
 * www.partow.net/programming/exprtk/
 *
 * Also, as mentioned, the graphical part is 
 * made with the educational, efficient and 
 * magnificent olcPixelGameEngine, provided 
 * by Javidx9. 
 * www.github.com/OneLoneCoder/olcPixelGameEngine
 *
 * In licenses/ folder the original license and 
 * readmes are found.
 * 
 * Install and Usage: type 'make' to compile
 * (it may take a few seconds and ~1.5GB of 
 *  RAM) and then type 'vblank_mode=0 ./func_ploter' 
 * to run this code.
 * 
 * Made by: M. Lazarotto (08/01/2021)
 **/

#include "FuncPloter.h"

int main()
{
	// Window settings
	cFuncPloter app;
	int32_t ScreenWidth  = 1240;
    int32_t ScreenHeight = 920;

	// Run
	if (app.Construct(ScreenWidth, ScreenHeight, 1, 1))
	{
		app.Start();
	}

	return 0;
}