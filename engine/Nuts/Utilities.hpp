/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** Utilities.hpp
*/

#pragma once

#include <iostream>

#define COUT(textStream) (std::cout << "$> " << textStream)

#if defined(_DEBUG)
#define DEBUG_LOG(textStream) (std::cout << " " << textStream)
#else
#define DCOUT(textStream) (0)
#endif // _DEBUG