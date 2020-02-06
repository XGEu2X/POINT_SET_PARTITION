#pragma once

#include <vector>
#include <string>

class Point {
public:
	Point() :V(DEFAULT_DIM) {}
	Point(const size_t dim) :V(dim) {}
	Point(const std::vector<double>& _V) :V(_V) {}

	inline typename std::vector<double>::iterator begin() { return V.begin(); }
	inline typename std::vector<double>::const_iterator begin() const { return V.begin(); }
	inline typename std::vector<double>::iterator end() { return V.end(); }
	inline typename std::vector<double>::const_iterator end() const { return V.end(); }
	inline typename std::vector<double>::value_type& operator[](const size_t i) { return V[i]; }
	inline typename std::vector<double>::value_type operator[](const size_t i) const { return V[i]; }

	double norm2() const {
		double result = 0;
		for (double d : V) result += d * d;
		return result;
	}
	inline double norm() const { return sqrt(norm2()); }
	Point normalized2() const { 
		size_t dim = V.size();
		Point result(dim);
		for (size_t c1 = 0; c1 < dim; ++c1) { result[c1] = (1 / norm2()) * V[c1]; }
		return result;
	}
	Point normalized() const {
		size_t dim = V.size();
		Point result(dim);
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
	const static size_t DEFAULT_DIM = 2;
private:
	std::vector<double> V;
};

Point operator +(const Point& p1, const Point& p2) {
	size_t dim = p1.dimension();
	Point result(dim);
	for (size_t c1 = 0; c1 < dim; ++c1) result[c1] = p1[c1] + p2[c1];
	return result;
}
Point operator *(const double d, const Point& p) {
	size_t dim = p.dimension();
	Point result(dim);
	for (size_t c1 = 0; c1 < dim; ++c1) result[c1] = d * p[c1];
	return result;
}
Point operator -(const Point& p1, const Point& p2) { return p1 + (-1) * p2; }