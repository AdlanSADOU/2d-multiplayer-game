/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** main
*/

#include <iostream>
#include <string> // required on windows for std::to_string(...)
#include "Pig.hpp"

int main(void)
{
    Pig peppa(10);
    std::cout << std::to_string(peppa.GetPigSize()) << std::endl;

    return (0);
}
