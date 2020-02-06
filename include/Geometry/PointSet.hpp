#pragma once

#include "Point.hpp"

#include <algorithm>

namespace Geometry{
	template <typename point = Point<double> >
	class PointSet {
	public:
		using Transposition = std::pair<size_t, size_t>;
		using Diff = std::pair<double, Transposition>;
		using DiffList = std::vector<Diff>;

		//Evolutive Algorithms compatibility
		using settler_type = point;

		PointSet() :S(0) {}

		inline typename std::vector<point>::iterator begin() { return S.begin(); }
		inline typename std::vector<point>::const_iterator begin() const { return S.begin(); }
		inline typename std::vector<point>::iterator end() { return S.end(); }
		inline typename std::vector<point>::const_iterator end() const { return S.end(); }
		inline typename std::vector<point>::value_type& operator[](const size_t i) { return S[i]; }
		inline typename std::vector<point>::value_type operator[](const size_t i) const { return S[i]; }

		std::string to_string() const {
			std::string result = "";
			for (const point& p : S) {
				result += p.to_string() + "\n";
			}
			return result;
		}
		size_t size() const { return S.size(); }

		inline void push_back(const point& p) { S.push_back(p); }

		void sort_by_coordinate(const size_t i, const unsigned int orderType = ORDER_ASCENDENT) {
			std::sort(S.begin(), S.end(), 
				[i, orderType](const point& p1, const point& p2){
					bool result = false;
					if (orderType == ORDER_ASCENDENT) { result = p1[i] < p2[i]; }
					if (orderType == ORDER_DESCENDENT) { result = p1[i] > p2[i]; }
					return result;
				}
			);
		}
		std::vector<point> sorted_by_coordinate(const size_t i, const unsigned int orderType = ORDER_ASCENDENT) const {
			std::vector<point> result = S;
			std::sort(result.begin(), result.end(),
				[i, orderType](const point& p1, const point& p2) {
					bool result = false;
					if (orderType == ORDER_ASCENDENT) { result = p1[i] < p2[i]; }
					if (orderType == ORDER_DESCENDENT) { result = p1[i] > p2[i]; }
					return result;
				}
			);
			return result;
		}
		void sort_by_value(const unsigned int orderType = ORDER_ASCENDENT) {
			std::sort(S.begin(), S.end(), [orderType](const point& p1, const point& p2) {
				bool result = false;
				if (orderType == ORDER_ASCENDENT) { result = p1.get_value() < p2.get_value(); }
				if (orderType == ORDER_DESCENDENT) { result = p1.get_value() > p2.get_value(); }
				return result;
			});
		}

		DiffList get_diff_list() const {
			DiffList result;
			for (size_t c1 = 0; c1 < S.size() - 1; ++c1) {
				for (size_t c2 = c1 + 1; c2 < S.size(); ++c2) {
					size_t a = c1, b = c2;
					double x = ((S[c2] - S[c1]).normalized())[0];
					Transposition tr(a, b); Diff d(x, tr);
					result.push_back(d);
				}
			}
			return result;
		}

	private:
	public:
		inline static const unsigned int ORDER_ASCENDENT = 1;
		inline static const unsigned int ORDER_DESCENDENT = 2;
	private:
		std::vector<point> S;
	};
}