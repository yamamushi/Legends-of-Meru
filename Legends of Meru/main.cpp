//
//  main.cpp
//  Legends of Meru
//
//  Created by Jonathan Rumion on 10/13/13.
//  Copyright (c) 2013 The ASCII Project. All rights reserved.
//

#include "libtcod.hpp"
#include <locale>

int main()
{
    
    // initialize the libtcod root console and set the font
    const char *font="../data/fonts/font.png";
    setlocale(LC_ALL, "en_US.UTF-8");
    TCODConsole::setCustomFont(font, TCOD_FONT_LAYOUT_ASCII_INROW | TCOD_FONT_TYPE_GREYSCALE, 32, 2048);
    TCODConsole::initRoot(80,45,"The ASCII Project",false,TCOD_RENDERER_SDL);
    /*   TCODConsole::mapAsciiCodesToFont(0, 65535, 0, 0);
     TCODConsole::mapAsciiCodeToFont(179, 17, 298);
     TCODConsole::mapAsciiCodeToFont(180, 3, 299);
     TCODConsole::mapAsciiCodeToFont(191, 23, 298);
     TCODConsole::mapAsciiCodeToFont(192, 26, 298);
     TCODConsole::mapAsciiCodeToFont(195, 0, 299);
     TCODConsole::mapAsciiCodeToFont(196, 16, 298);
     TCODConsole::mapAsciiCodeToFont(217, 29, 298);
     TCODConsole::mapAsciiCodeToFont(218, 20, 298); */
    // draw to TCODConsole::root
    //TCODConsole::root->setDefaultForeground(TCODColor::white);
    //TCODConsole::root->setDefaultBackground(TCODColor(0, 0, 0));
    int c = 0;
    while(c < 2048) {
        for(int y = 0; y < 45; y++) {
            for(int x = 0; x < 80; x++) {
                if(x % 3 == 0 || y % 5 == 0)
                    TCODConsole::root->putCharEx(x, y, c, TCODColor::green, TCODColor::black);
                else if(x % 2 == 0 || y % 3 == 0 )
                    TCODConsole::root->putCharEx(x, y, c, TCODColor::blue, TCODColor::black);
                else if(x % 5 == 0 || y % 2 == 0)
                    TCODConsole::root->putCharEx(x, y, c, TCODColor::red, TCODColor::black);
                ++c; // increment character number
            }
        }
    }
    
    TCODConsole::flush();
    TCODConsole::waitForKeypress(true);
    
}
