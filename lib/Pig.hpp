/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** Pig
*/

#ifndef PIG_HPP_
#define PIG_HPP_

class Pig {
    public:
        Pig();
        Pig(int size);
        ~Pig();
        int GetPigSize();

    protected:
    private:
        int size;
};

#endif /* !PIG_HPP_ */
