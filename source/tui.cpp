#include <tui.h>
#include <3ds.h>


TUI::TUI(){
    gfxInitDefault();
    PrintConsole* Console = consoleInit(GFX_TOP, NULL); 
}

int TUI::Loop(){

    while (aptMainLoop())
	{
		//Scan all the inputs. This should be done once for each frame
		hidScanInput();

		//hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
		u32 kDown = hidKeysDown();

		if (kDown & KEY_START) break; // break in order to return to hbmenu

		// Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();

		//Wait for VBlank
		gspWaitForVBlank();
	}
    gfxExit();
    return 0;
}

Menu::Menu(){
    
}
