//
//  main.cpp
//  Meru-Server
//
//  Created by Jonathan Rumion on 10/13/13.
//  Copyright (c) 2013 The ASCII Project. All rights reserved.
//

#include <iostream>

#include "ServerConfig.h"

int main(int argc, const char *argv[])
{

    ServerConfigParser *serverConfig = new ServerConfigParser(argc, argv);
    
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
    
    
}

