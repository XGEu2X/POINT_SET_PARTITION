#pragma once

#include <vector>

#include "Probability-Headers/Probability.hpp"

namespace Evolutive {
	template <class Population, class Descriptor, class Qualifier>
	class DiffEvo {
	public:
		using Settler = typename Population::settler_type;

		DiffEvo(double _Cp = 1, double _Cm = 0.2) :Cp(_Cp), Cm(_Cm) {}

		void evolve(Population& P, const Descriptor& D, const Qualifier& f, const unsigned int steps = 1, size_t randomSettlers = 0) const {
			size_t popSize = P.size(), settlerDim = P[0].dimension();
			if (randomSettlers > P.size())randomSettlers = P.size();
			
			for (unsigned int c1 = 0; c1 < steps; ++c1) {
				for (size_t c2 = 0; c2 < popSize; ++c2) {
					Settler x = P[c2];
					std::vector<Settler> L = choose_mutators(c2, P);
					Settler s = L[0] + Cp * (L[2] - L[1]);
					s = mutate(x, s, random_int(0, (int)settlerDim));
					s = D.project(s);
					s.set_value(f(s));
					if (s.get_value() > x.get_value())P[c2] = s;
				}

				P.sort_by_value();
				if (randomSettlers > 0) {
					for (size_t c2 = 0; c2 < randomSettlers; ++c2) {
						P[c2] = D.born();
						P[c2].set_value(f(P[c2]));
					}
					P.sort_by_value();
				}
				
			}
		}
	private:
		std::vector<Settler> choose_mutators(const size_t i, const Population& P) const {
			std::vector<Settler> result;

			int y, w, z;
			do { y = random_int(0, (int)P.size()); } while (i == y);
			result.push_back(P[y]);
			do { w = random_int(0, (int)P.size()); } while (i == w && w == y);
			result.push_back(P[w]);
			do { z = random_int(0, (int)P.size()); } while (i == z && z == y && z == w);
			result.push_back(P[z]);

			return result;
		}
		Settler mutate(const Settler& x, const Settler& y, const size_t fixed) const {
			Settler result = x;
			size_t dim = result.dimension();
			for (size_t c1 = 0; c1 < dim; ++c1) {
				if (c1 == fixed)continue;
				if (probability_of_true(Cm))result[c1] = y[c1];
			}
			return result;
		}
	public:
	private:
		double Cp, Cm;
	};
}