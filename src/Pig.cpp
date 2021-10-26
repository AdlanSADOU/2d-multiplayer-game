/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** Pig
*/

#include "Pig.hpp"

Pig::Pig()
{
    this->size = 1;
}

Pig::Pig(int size)
{
    this->size = size;
}

Pig::~Pig()
{

}

int Pig::GetPigSize()
{
    return (size);
}