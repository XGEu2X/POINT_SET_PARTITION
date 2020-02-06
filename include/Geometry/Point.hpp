#pragma once

#include <vector>
#include <string>

namespace Geometry {
	template <typename Scalar = double>
	class Point {
	public:
		Point() :V(DEFAULT_DIM), value(NO_VALUE) {}
		Point(const size_t dim) :V(dim), value(NO_VALUE) {}
		Point(const std::vector<Scalar>& _V) :V(_V), value(NO_VALUE) {}

		inline typename std::vector<Scalar>::iterator begin() { return V.begin(); }
		inline typename std::vector<Scalar>::const_iterator begin() const { return V.begin(); }
		inline typename std::vector<Scalar>::iterator end() { return V.end(); }
		inline typename std::vector<Scalar>::const_iterator end() const { return V.end(); }
		inline typename std::vector<Scalar>::value_type& operator[](const size_t i) { return V[i]; }
		inline typename std::vector<Scalar>::value_type operator[](const size_t i) const { return V[i]; }

		inline double get_value() const { return value; }
		inline void set_value(const double v) { value = v; }
		inline bool is_evaluated() const { return !(value == NO_VALUE); }

		Scalar norm2() const {
			double result = 0;
			for (Scalar d : V) result += d * d;
			return result;
		}
		inline double norm() const { return sqrt( (double)norm2() ); }
		Point<Scalar> normalized2() const {
			size_t dim = V.size();
			Point<Scalar> result(dim);
			for (size_t c1 = 0; c1 < dim; ++c1) { result[c1] = (1 / norm2()) * V[c1]; }
			return result;
		}
		Point<Scalar> normalized() const {
			size_t dim = V.size();
			Point<Scalar> result(dim);
			for (size_t c1 = 0; c1 < dim; ++c1) { result[c1] = (1 / norm()) * V[c1]; }
			return result;
		}
		inline size_t dimension() const { return V.size(); }

		std::string to_string() const {
			std::string result = "";
			for (size_t c1 = 0; c1 < V.size(); ++c1) {
				if (c1 == 0)result += "(";
				else result += ",";
				result += std::to_string(V[c1]);
			}
			result += ")";
			return result;
		}
	private:
	public:
		inline static const size_t DEFAULT_DIM = 2;
		inline static const double NO_VALUE = -1;
	private:
		std::vector<double> V;
		double value;
	};

	template <typename Scalar = double>
	Point<Scalar> operator +(const Point<Scalar>& p1, const Point<Scalar>& p2) {
		size_t dim = p1.dimension();
		Point<Scalar> result(dim);
		for (size_t c1 = 0; c1 < dim; ++c1) result[c1] = p1[c1] + p2[c1];
		return result;
	}
	template <typename Scalar = double>
	Point<Scalar> operator *(const double d, const Point<Scalar>& p) {
		size_t dim = p.dimension();
		Point<Scalar> result(dim);
		for (size_t c1 = 0; c1 < dim; ++c1) result[c1] = d * p[c1];
		return result;
	}
	template <typename Scalar = double>
	Point<Scalar> operator -(const Point<Scalar>& p1, const Point<Scalar>& p2) { return p1 + (-1) * p2; }
}