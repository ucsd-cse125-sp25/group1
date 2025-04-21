#pragma once
#include <iostream>
#include <stdexcept>
#include<sstream>

#define OGL3D_ERROR(message)\
{\
std::stringstream m;\
m<<"OGL3D Error: " << message<<std::endl;\
throw std::runtime_error(m.str());\
}

#define OGL3D_WARNING(message)\
std::wclog << "OGL3D Warning: " << message<< std::endl;

#define OGL3D_INFO(message)\
std::wclog << "OGL3D Info: " << message<< std::endl;
