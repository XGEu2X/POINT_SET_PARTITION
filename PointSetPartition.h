#include <RandomGenerators.hpp>

using Point = Geometry::Point<double>;
using PointSet = Geometry::PointSet<Point>;

using Transposition = PointSet::Transposition;
using Diff = PointSet::Diff;
using DiffList = PointSet::DiffList;

using Sequence = std::pair<double, std::vector<size_t>>;
using SequenceList = std::vector<Sequence>;

class doubleVsSeq {
public:
	doubleVsSeq() {}
	bool operator ()(const double d, const Sequence& s) { return d < s.first; }
	bool operator ()(const Sequence& s, const double d) { return d > s.first; }
};

class Qualifier {
public:


	Qualifier(const size_t _t, const unsigned int _method = METHOD_DEFAULT) :t(_t), method(_method) {}
	double operator()(PointSet& p, const bool printFlag = false) const {
		double result = 0;
		
		//Structures to be used by the methods
		std::vector<std::pair<Geometry::Point<double>, Geometry::Point<double>>> Borders;

		p.sort_by_coordinate(1);

		DiffList DL = p.get_diff_list();
		std::sort(DL.begin(), DL.end(),
			[](const Diff& d1, const Diff& d2) {
				return d1.first > d2.first;
			}
		);

		std::vector<size_t> firstSeq; for (size_t c1 = 0; c1 < p.size(); ++c1) { firstSeq.push_back(c1); }
		SequenceList SL;
		for (size_t c1 = 0; c1 < DL.size(); ++c1) {
			apply_transp(firstSeq, DL[c1].second);
			SL.push_back(std::pair(1 - DL[c1].first, firstSeq));
		}
		for (size_t c1 = 0; c1 < DL.size(); ++c1) {
			std::vector<size_t> reversed(firstSeq.size());
			std::reverse_copy(SL[c1].second.begin(), SL[c1].second.end(), reversed.begin());
			double reversedX = SL[c1].first + 2;
			SL.push_back(std::pair(reversedX, reversed));
		}

		SequenceList HS = SL, TS = SL;
		for (size_t c1 = 0; c1 < SL.size(); ++c1) {
			std::vector<size_t>::const_iterator begin = SL[c1].second.begin();
			//Half
			std::vector<size_t> H(begin, begin + p.size() / 2);
			std::sort(H.begin(), H.end());
			HS[c1].second = H;
			//T
			std::vector<size_t> T(begin, begin + t);
			std::sort(T.begin(), T.end());
			TS[c1].second = T;
		}

		SequenceList::iterator it1 = HS.begin(), it2;
		while (it1 != HS.end() - 1) {
			it2 = it1 + 1;
			if (!has_difference(it1, it2)) {
				HS.erase(it2);
			}
			else {
				++it1;
			}
		}
		if (!has_difference(HS.end() - 1, HS.begin()))HS.erase(HS.begin());

		it1 = TS.begin(), it2;
		while (it1 != TS.end() - 1) {
			it2 = it1 + 1;
			if (!has_difference(it1, it2)) {
				TS.erase(it2);
			}
			else {
				++it1;
			}
		}
		if (!has_difference(TS.end() - 1, TS.begin()))TS.erase(TS.begin());


		size_t n = HS.size();
		for (size_t c1 = 0; c1 < n; ++c1) {
			size_t next = (c1 + 1) % n;
			double x1 = ort(HS[c1].first), x2 = ort(HS[next].first);
			SequenceList::iterator lower = std::upper_bound(TS.begin(), TS.end(), x1, doubleVsSeq());
			if (lower == TS.begin())lower = TS.end() - 1;
			else --lower;
			SequenceList::iterator upper = std::lower_bound(TS.begin(), TS.end(), x2, doubleVsSeq());
			if (upper == TS.begin())upper = TS.end();

			while (lower != upper) {
				if (is_valid_partition(HS[c1].second, lower->second)) {


					//DEPENDS ON THE METHOD USED
					if (method != METHOD_DEFAULT) {
						Borders.push_back(
							std::pair< Geometry::Point<double>, Geometry::Point<double>>(
								decrypt(HS[c1].first), 
								decrypt(HS[next].first)
							)
						);
					}

					++result;
					if (printFlag) {
						std::cout << "p1=[";
						for (size_t i = 0; i < HS[c1].second.size(); ++i){
							std::cout << HS[c1].second[i];
							if(i < HS[c1].second.size()-1)
								std::cout << ",";
						}
						std::cout << "]" << std::endl;
						std::cout << "p2=[";
						for (size_t i = 0; i < lower->second.size(); ++i){
							std::cout << lower->second[i];
							if(i < lower->second.size() - 1 )
								std::cout << ",";
						}
						std::cout << "]" << std::endl << "dibujo(p,p1,p2)" << std::endl;
					}
				}
				++lower; if ((lower == upper))break;
				if (lower == TS.end())lower = TS.begin(); if ((lower == upper))break;
			}
		}

		//DEPENDS ON THE METHOD USED
		if (method == METHOD_PLUS_DIFFERENCE) {
			double minDiff = 0.999;
			size_t size = Borders.size();
			for (size_t c1 = 0; c1 < size; ++c1) {
				size_t next = (c1 + 1) % size;
				double diff = 1 - Borders[c1].second * Borders[next].first;
				diff /= 2;
				if (diff < minDiff)minDiff = diff;
			}
			result += minDiff;
		}
		if (method == METHOD_MIDDLE_DIFFERENCE) {
			double minDiff = 0.999;
			size_t size = Borders.size();
			for (size_t c1 = 0; c1 < size; ++c1) {
				size_t next = (c1 + 1) % size;
				Geometry::Point<double> m1 = (1/ (Borders[c1].first + Borders[c1].second).norm()) * Borders[c1].first + Borders[c1].second;
				Geometry::Point<double> m2 = (1/ (Borders[next].first + Borders[next].second).norm())*Borders[next].first + Borders[next].second;
				double diff = 1 - m1 * m2;
				diff /= 2;
				if (diff < minDiff)minDiff = diff;
			}
			result += minDiff;
		}
		if (method == METHOD_RANGE_SIZE) {
			double minDiff = 0.999;
			size_t size = Borders.size();
			for (size_t c1 = 0; c1 < size; ++c1) {
				double diff = 1 - Borders[c1].second * Borders[c1].first;
				diff /= 2;
				if (diff < minDiff)minDiff = diff;
			}
			result += minDiff;
		}
		//

		return result;
	}
private:
	void apply_transp(std::vector<size_t>& P, const Transposition& tr) const {
		for (size_t c1 = 0; c1 < P.size(); ++c1) {
			if (P[c1] == tr.first) {
				P[c1] = tr.second;
				P[c1 + 1] = tr.first;
				break;
			}
		}
	}
	bool is_valid_partition(const std::vector<size_t>& p1, const std::vector<size_t>& p2) const {
		bool result = false;
		std::vector<size_t> P1 = p1, P2 = p2;
		//std::sort(P1.begin(), P1.end()); std::sort(P2.begin(), P2.end());
		std::vector<size_t> V(p1.size() + p2.size());
		std::vector<size_t>::iterator it = std::set_intersection(P1.begin(), P1.end(), P2.begin(), P2.end(), V.begin());
		V.resize(it - V.begin());
		if (V.size() == t / 2) result = true;
		return result;
	}
	bool has_difference(const SequenceList::const_iterator& it1, const SequenceList::const_iterator& it2) const {
		std::vector<size_t> V(it1->second.size());
		std::vector<size_t>::iterator it = std::set_intersection(
			it1->second.begin(),
			it1->second.end(),
			it2->second.begin(),
			it2->second.end(),
			V.begin()
		);
		V.resize(it - V.begin());
		return V.size() != it1->second.size();
	}
	double ort(const double d) const {
		double result = d;
		if (d >= 0 && d < 2) {
			result = 1 - result;
			result = -1 * sqrt(1 - result * result);
			if (d >= 0 && d < 1) {
				result = 1 - result;
			}
			else {
				result = 3 + result;
			}
		}
		else {
			result = result - 3;
			result = sqrt(1 - result * result);
			if (d >= 2 && d < 3) {
				result = 3 + result;
			}
			else {
				result = 1 - result;
			}
		}
		return result;
	}
	Geometry::Point<double> decrypt(const double d) const {
		double x, y;
		if (d < 2) {
			x = 1 - d;
			y = sqrt(1 - x * x);
		}
		else {
			x = d - 3;
			y = sqrt(1 - x * x);
			y *= -1;
		}
		std::vector<double> vec({ x,y });
		Geometry::Point<double> res(vec);
		return res;
	}
public:
	inline static unsigned int METHOD_DEFAULT = 1;
	inline static unsigned int METHOD_PLUS_DIFFERENCE = 2;
	inline static unsigned int METHOD_MIDDLE_DIFFERENCE = 3;
	inline static unsigned int METHOD_RANGE_SIZE = 4;

private:
	const size_t t;
	const unsigned int method;
};