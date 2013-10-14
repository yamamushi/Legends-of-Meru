//
//  main.cpp
//  Legends of Meru
//
//  Created by Jonathan Rumion on 10/13/13.
//  Copyright (c) 2013 The ASCII Project. All rights reserved.
//

#include "libtcod.hpp"
#include "ActionScheduler.h"
#include "ConcurrentQueue.h"
#include <locale>
#include <thread>
#include <iostream>
#include <vector>
#include <random>


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
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(32, 10000);
    int c = 0;
    while(c < 2048) {
        for(int y = 0; y < 45; y++) {
            for(int x = 0; x < 80; x++) {
                
                int i =  distr(eng);
                    TCODConsole::root->putCharEx(x, y, i, TCODColor::green, TCODColor::black);
                ++c;
                
            }
        }
    }
    
    TCODConsole::flush();
    TCODConsole::waitForKeypress(true);

    TCODConsole::root->clear();
    TCODImage *pic = new TCODImage("../data/meru2.png");
    pic->scale(160,90);
    pic->blit2x(TCODConsole::root, 0, 0);
    TCODConsole::flush();
    TCODConsole::waitForKeypress(true);
    
    std::vector<std::thread> threads;
    
    ActionScheduler aScheduler;
    for(auto x = 0; x < 5; x++)
    {
        threads.push_back(std::thread([&aScheduler](){
            for(int i = 0; i < 100; ++i){
                aScheduler.write(i);
            
            }
        }));
    }
    
    for(auto& thread : threads){
        thread.join();
    }

    while(!aScheduler.is_empty())
        std::cout << aScheduler.read_next() << std::endl;



}