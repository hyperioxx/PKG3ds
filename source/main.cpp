#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <3ds.h>
#include <http.h>
#include <curl/curl.h>
#include <tinyxml2.h>

int main(int argc, char **argv)
{	
	gfxInitDefault();   
	httpcInit(0); // Buffer size when POST/PUT.

	//Initialize console on top screen. Using NULL as the second argument tells the console library to use the internal console structure as current one
	consoleInit(GFX_TOP, NULL);    
	u8* result = http_download("https://archive.org/download/nintendo-3ds-complete-collection/nintendo-3ds-complete-collection_files.xml");
	tinyxml2::XMLDocument doc;

	int err = doc.Parse((char *)result, strlen((const char *)result));

	if (err != tinyxml2::XML_SUCCESS){
        printf("Error parsing XML\n");
	}
	
	tinyxml2::XMLElement* parent = doc.FirstChildElement("files");
	for(tinyxml2::XMLElement* child = parent->FirstChildElement(); child != NULL; child = child->NextSiblingElement()){
		const char *item = child->Attribute("name");
		printf("%s\n", item);
	}
	
	// Main loop
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

