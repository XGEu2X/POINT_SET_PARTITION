#pragma once

#include <cmath>

namespace Evolutive {
	template <class Settler>
	class LpNorm {
	public:
		LpNorm() :p(DEFAULT_P) {}
		LpNorm(const double _p):p(_p){}
		
		double operator()(const Settler& s) const {
			double result = 0;
			size_t dim = s.dimension();
			for (size_t c1 = 0; c1 < dim; ++c1) {
				result += s[c1] * s[c1];
			}
			return pow(result,(1/p));
		}

	private:
	public:
		inline static const double DEFAULT_P = 2;
	private:
		const double p;
	};
	template<class Settler>
	class FirstCoordinate {
	public:
		FirstCoordinate() {}
		double operator()(const Settler& s) const { return s[0]; }
	private:
	public:
	private:
	};
}