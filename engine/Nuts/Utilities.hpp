/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** Utilities.hpp
*/

#pragma once
#define DLOG 0

#include <iostream>

#define COUT(textStream) (std::cout << "$> " << textStream)

#if (0)
#define DEBUG_LOG(textStream) (std::cout << " " << textStream)
#else
#define DEBUG_LOG(textStream) (0)
#endif // _DEBUG
