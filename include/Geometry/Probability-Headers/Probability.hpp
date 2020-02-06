#pragma once

#include <ctime>
#include <random>

#include "pcg_random.hpp"
#include "pcg_extras.hpp"

#ifndef Probability_GUARD
#define Probability_GUARD

/**
* @brief Returns true with probability p and false with probability 1-p
* @return true or false according to probability p, which must be a number
* between 0 and 1.
*/
inline bool probability_of_true(double p)
{
	pcg_extras::seed_seq_from<std::random_device> seed_source;
	pcg64 randomEngine(seed_source);

	std::bernoulli_distribution d(p);
	return d(randomEngine);
}

/**
* @brief "I just wanted a random integer!
* @return A random integer in the range [from,thru), with uniform probability
* distribution
*/
template <class IntType = int>
IntType random_int(IntType from, IntType thru)
{
	pcg_extras::seed_seq_from<std::random_device> seed_source;
	pcg64 randomEngine(seed_source);

	std::uniform_int_distribution<IntType> d{};
	using parm_t = typename decltype(d)::param_type;
	return d(randomEngine, parm_t{ from, --thru });
}

/**
* @brief "I just wanted a random double!
* @return A random double number in the range [from,thru), with uniform
* probability distribution
*/
template <class FloatType = double>
FloatType random_real(FloatType from, FloatType upto)
{
	pcg_extras::seed_seq_from<std::random_device> seed_source;
	pcg64 randomEngine(seed_source);

	std::uniform_real_distribution<> d{};
	using parm_t = decltype(d)::param_type;
	return d(randomEngine, parm_t{ from, upto });
}

#endif