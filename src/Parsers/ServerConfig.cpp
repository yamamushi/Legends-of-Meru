/*
 
 ServerConfig.cpp
 Jonathan Rumion (Yamamushi)
 02-04-2013
 
 */


#include <iostream>
#include <fstream>
#include <exception>

#include <boost/program_options.hpp>
#include "ServerConfig.h"

namespace po = boost::program_options;


ServerConfigParser::ServerConfigParser(int argc_, const char** argv_){
    
    argc = argc_;
    argv = argv_;
    Parse();
    
}


void ServerConfigParser::Parse(){
    
    try {
        
        po::options_description desc("Allowed Options");
        desc.add_options()
        ("config,c", po::value<std::string>(&config_file)->default_value("server.conf"),"Configuration File")
        ("help,h", "Display this help text")
        ("version,v", "Display version number")
        ;
        
        po::options_description config("Config File Options");
        config.add_options()
        ("db_hostname", po::value<std::string>(&db_hostname)->default_value(""),"MySQL Server Hostname")
        ("db_port", po::value<int>(&db_port)->default_value(3306),"MySQL Server Port")
        ("db_username", po::value<std::string>(&db_username)->default_value(""),"MySQL Username")
        ("db_pass", po::value<std::string>(&db_pass)->default_value(""),"MySQL User Password")
        ("db_name", po::value<std::string>(&db_name)->default_value(""),"MySQL Database Name")
        ;
        
        po::options_description hidden("Hidden Options");
        hidden.add_options()
        ("data_dir", po::value<std::string>(&data_dir)->default_value("data/"),"Data Directory")
        ("server_port", po::value<int>(&server_port)->default_value(5250),"Server Listening Port")
        ;
        
        
        po::options_description config_file_options;
        config_file_options.add(config).add(hidden);
        
        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
        
        if(vm.count("help")){
            std::cout << desc << std::endl;
            std::cout << config << std::endl;
            exit(0);
        }
        if(vm.count("version")){
            std::cout << "The ASCII Project Server" << std::endl;
            exit(0);
        }
        
        std::ifstream ifs(config_file.c_str());
        if(!ifs){
            std::cout << "Could not open config file: " << config_file << std::endl;
            std::cout << "Usage: " << std::endl;
            std::cout << desc << std::endl;
            std::cout << config << std::endl;
            exit(0);
        }
        else {
            po::store(parse_config_file(ifs, config_file_options), vm);
            po::notify(vm);
        }
        
    }
    catch(std::exception& e){
        std::cerr << "error: " << e.what() << std::endl;
        exit(1);
    }
    catch(...){
        std::cerr << "Exception of unknown type!" << std::endl;
    }
    
}