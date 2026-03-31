#ifndef PSEUDO_RANDOM_NUMBERS_GENERATOR_FOR_GAME_H
#define PSEUDO_RANDOM_NUMBERS_GENERATOR_FOR_GAME_H

/**
 * @brief Pseudo-random numbers generator with some positive bound.
 * @param seed is some positive integer number;
 * @param bound is some bound of result's number;
 * @param offset is some deviation from result's segment;
 * 
 * All arguments is unsigned int.
 */
static int getRandomNumber(unsigned int seed, unsigned int bound, unsigned int offset) {
    seed = ((seed * 73129 + 95121) % bound + offset) % (bound - offset) + offset;
    return seed;
}

#endif // PSEUDO_RANDOM_NUMBERS_GENERATOR_FOR_GAME_H