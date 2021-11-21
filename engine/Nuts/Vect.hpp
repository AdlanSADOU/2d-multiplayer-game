/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** Vect
*/

#pragma once

namespace nuts
{
    /**
     * @brief Utility struct for manipulating 2-dimensional vectors.
     * Coordinates represented by int values.
     */
    typedef struct
    {
        int x;
        int y;
    } Vector2i;

    /**
     * @brief Utility struct for manipulating 2-dimensional vectors.
     * Coordinates represented by unsigned int values.
     */
    typedef struct
    {
        unsigned int x;
        unsigned int y;
    } Vector2u;

    /**
     * @brief Utility struct for manipulating 2-dimensional vectors.
     * Coordinates represented by float values.
     */
    typedef struct
    {
        float x;
        float y;
    } Vector2f;

    /**
     * @brief Utility struct for manipulating 3-dimensional vectors.
     * Coordinates represented by int values.
     */
    typedef struct
    {
        int x;
        int y;
        int z;
    } Vector3i;

    /**
     * @brief Utility struct for manipulating 3-dimensional vectors.
     * Coordinates represented by float values.
     */
    typedef struct
    {
        float x;
        float y;
        float z;
    } Vector3f;
}