#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <3ds.h>
#include <http.h>
#include <curl/curl.h>
#include <tinyxml2.h>
#include <tui.h>

int main(int argc, char **argv)
{	
	TUI app;
	//Initialize console on top screen. Using NULL as the second argument tells the console library to use the internal console structure as current one    
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
	
	app.Loop();
	return 0;
}

