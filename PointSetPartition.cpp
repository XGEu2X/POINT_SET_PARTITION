#include <RandomGenerators.hpp>

#include <iostream>

using Transposition = PointSet::Transposition;
using Diff = PointSet::Diff;
using DiffList = PointSet::DiffList;

using Sequence = std::pair<double, std::vector<size_t>>;
using SequenceList = std::vector<Sequence>;

class doubleVsSeq{
public:
	doubleVsSeq() {}
	bool operator ()(const double d, const Sequence& s) { return d < s.first; }
	bool operator ()(const Sequence& s, const double d) { return d > s.first; }
};

class Qualifier {
public:
	

	Qualifier(const size_t _t):t(_t){}
	unsigned int operator()(PointSet& p, const bool printFlag = false) {
		unsigned int result = 0;

		p.sort_by_coordinate(1);

		DiffList DL = p.get_diff_list();
		std::sort(DL.begin(), DL.end(), 
			[](const Diff& d1, const Diff& d2) {
				return d1.first > d2.first;
			}
		); 
		
		/*
		for (size_t c1 = 0; c1 < DL.size(); ++c1) {
			std::cout << DL[c1].first << "--> (" << DL[c1].second.first << " " << DL[c1].second.second << ")" << std::endl;
		}
		*/

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

		/*
		for (size_t c1 = 0; c1 < SL.size(); ++c1) {
			std::cout << SL[c1].first << " ";
			for (size_t c2 = 0; c2 < firstSeq.size(); ++c2) {
				std::cout << SL[c1].second[c2] << " ";
			}
			std::cout << std::endl;
		}
		*/
		
		SequenceList HS = SL, TS = SL;
		for (size_t c1 = 0; c1 < SL.size(); ++c1) {
			std::vector<size_t>::const_iterator begin = SL[c1].second.begin();
			//Half
			std::vector<size_t> H(begin, begin + p.size()/2);
			std::sort(H.begin(), H.end());
			HS[c1].second = H;
			//T
			std::vector<size_t> T(begin, begin + t);
			std::sort(T.begin(), T.end());
			TS[c1].second = T; 
		}

		SequenceList::iterator it1 = HS.begin(), it2;
		while (it1 != HS.end()-1) {
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
			//if (x1 > 4) { x1 = x1 - 4; } if (x2 > 4) { x2 = x2 - 4; }
			SequenceList::iterator lower = std::upper_bound(TS.begin(), TS.end(), x1, doubleVsSeq());
			if (lower == TS.begin())lower = TS.end() - 1;
			else --lower;
			SequenceList::iterator upper = std::lower_bound(TS.begin(), TS.end(), x2, doubleVsSeq());
			if (upper == TS.begin())upper = TS.end();
			
			while (lower != upper) {
				if (is_valid_partition(HS[c1].second, lower->second)) { 
					++result; 
					if(printFlag){
						for (size_t i = 0; i < HS[c1].second.size(); ++i)std::cout << HS[c1].second[i] << " ";
						std::cout << std::endl;
						for (size_t i = 0; i < lower->second.size(); ++i)std::cout << lower->second[i] << " ";
						std::cout << std::endl;
						std::cout << std::endl;
					}
				}
				++lower; if ((lower == upper))break;
				if (lower == TS.end())lower = TS.begin(); if ((lower == upper))break;
			}
		}

		return result;
	}
private:
	void apply_transp(std::vector<size_t>& P, const Transposition& tr) {
		for (size_t c1 = 0; c1 < P.size(); ++c1) {
			if (P[c1] == tr.first) {
				P[c1] = tr.second;
				P[c1 + 1] = tr.first;
				break;
			}
		}
	}
	bool is_valid_partition(const std::vector<size_t>& p1, const std::vector<size_t>& p2) {
		std::vector<size_t> P1 = p1, P2 = p2;
		//std::sort(P1.begin(), P1.end()); std::sort(P2.begin(), P2.end());
		std::vector<size_t> V(p1.size() + p2.size());
		std::vector<size_t>::iterator it = std::set_intersection(P1.begin(), P1.end(), P2.begin(), P2.end(), V.begin());
		V.resize(it - V.begin());
		if (V.size() == t / 2) {
			
			return true;
		}
		return false;
	}
	bool has_difference(const SequenceList::const_iterator& it1, const SequenceList::const_iterator& it2) {
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
	double ort(const double d) {
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
public:
private:
	const size_t t;
};

using namespace std;

int main()
{

	//Parameters
	int t = 8, n = 40, iterations = 1000000;
	
	Circle RG;
	Qualifier f(t);

	PointSet S = RG.born(n);
	int min_value = f(S);
	//if (min_value < 3) {
		f(S, true);
		cout << "Value: " << min_value << endl;
		S.sorted_by_coordinate(1);
		cout << S.to_string();
	//}

	for (size_t c1 = 0; c1 < iterations; ++c1) {
		PointSet C = RG.born(n);
		int CValue = f(C);
		if (CValue < min_value) {
			min_value = CValue;
			S = C;
			//if (min_value < 3) {
				f(S, true);
				cout << "Value: " << min_value << endl;
				S.sorted_by_coordinate(1);
				cout << S.to_string();
			//}
		}
	}

/*
	HyperCube RG;
	Qualifier f(4);

	PointSet S;
S.push_back(Point(vector<double>({-0.593354,-0.702197})));
S.push_back(Point(vector<double>({-0.300290,-0.519713})));
S.push_back(Point(vector<double>({0.481180,-0.411768})));
S.push_back(Point(vector<double>({0.859043,-0.198779})));
S.push_back(Point(vector<double>({-0.123778,-0.178035})));
S.push_back(Point(vector<double>({0.891238,-0.069544})));
S.push_back(Point(vector<double>({-0.301237,-0.048465})));
S.push_back(Point(vector<double>({0.986272,0.153452})));
S.push_back(Point(vector<double>({-0.524309,0.315818})));
S.push_back(Point(vector<double>({-0.765601,0.344159})));

	cout << "Value: " << f(S, true) << endl;*/
	return 0;
}
