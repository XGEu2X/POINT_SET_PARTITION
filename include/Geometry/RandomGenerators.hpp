#pragma once

#include "PointSet.hpp"
#include "Probability/Probability.hpp"

const double Pi = 3.14159265358979323846;

namespace Geometry {

	class HyperCube {
	public:
		using point = Point<double>;
		using pointSet = PointSet<point>;

		HyperCube() : L(point::DEFAULT_DIM), H(point::DEFAULT_DIM, DEFAULT_HIGH_LIM) {}
		HyperCube(const std::vector<double>& _L, const std::vector<double>& _H) : L(_L), H(_H) {}
		point born() const {
			size_t dim = H.size();
			point result(dim);
			for (size_t c1 = 0; c1 < dim; ++c1) { result[c1] = random_real(L[c1], H[c1]); }
			return result;
		}
		pointSet born(const size_t i) const {
			pointSet result;
			for (size_t c1 = 0; c1 < i; ++c1) { result.push_back(born()); }
			return result;
		}
		point project(const point& p) const {
			size_t dim = p.dimension();
			point result(dim);
			for (size_t c1 = 0; c1 < dim; ++c1) {
				if (result[c1] < L[c1])result[c1] = L[c1];
				if (result[c1] > H[c1])result[c1] = L[c1];
			}
			return result;
		}
	private:
	public:
		inline static const double DEFAULT_HIGH_LIM = 5;
	private:
		std::vector<double> L, H;
	};

	class Circle {
	public:

		using point = Point<double>;
		using pointSet = PointSet<point>;

		Circle(const double _r = DEFAULT_RADIUS) :r(_r) {}
		point born() const {
			Point result(2);
			double radius = r * sqrt(random_real(double(0), double(1)));
			double theta = random_real(double(0), 2 * Pi);
			result[0] = radius * cos(theta);
			result[1] = radius * sin(theta);
			return result;
		}
		pointSet born(const size_t i) const {
			pointSet result;
			for (size_t c1 = 0; c1 < i; ++c1) { result.push_back(born()); }
			return result;
		}
		point project( const point& p) const { 
			point result = p;
			if (result.norm() >= r)result = (r-DBL_EPSILON) * p.normalized();
			return result;
		}
	private:
	public:
		inline const static double DEFAULT_RADIUS = 1;
	private:
		double r;
	};
}