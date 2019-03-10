

//main.cpp

#include "StdAfx.h"
#include <iostream>
#include "win_type_global.h"
//#include <stdio.h>
//#include <stdlib.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "AppGfx.h"
#include <string>
#include <direct.h>
#include "InvidoSettings.h"


////////////////////////////////////////
//       main
/*! Entry point to start the application
// \param int argc : 
// \param char *argv[] : 
*/
int main(int argc, char *argv[])
{

    
    AppGfx app;

    // app name and set the directory on installed application
    std::string strAppName;
    strAppName = argv[0];
    size_t iPos = strAppName.find_last_of('\\'); 
    size_t iLen = strAppName.length(); 
    std::string strDirname = strAppName.substr(0, iPos); 
    app.SetApplicationDir(strDirname);
    _chdir(strDirname.c_str() );

    try
    {
        // init application
        app.Init();
#ifdef _DEBUG
        if (argc == 2)
        {
            // use another port to connect with the gui net
            int iPortNum = 0;
            sscanf(argv[1], "%d", &iPortNum);
        }
#endif

        // uncomment this to start with the correct menu
	    app.MainLoop();
        // to be removed: goto play game
        //app.PlayGame();
        //app.ShowOptions();
        //app.PlayNetGame();
    }
    catch(Error::Init err)
    {
        // init error
#ifdef WIN32
        ::MessageBox(NULL, "Initialization Error, look on stderr.txt for more informations\nThe application is not correctly installed", "Application Error", MB_OK); 
#endif
        std::cerr << "Application initialization error: " << err.strErrMsg.c_str() << std::endl;   
        exit(EXIT_FAILURE);
    }
    
    
    
    return EXIT_SUCCESS;
}


