#include "PointSetPartition.h"

#include <DifferentialEvolution.hpp>

#include <iostream>

using namespace std;
using namespace Geometry;

int main() {
	//Parameters
	size_t t, n;
	unsigned int iterations;

	cout << "Inserta la cantidad de puntos: ";
	cin >> n;
	cout << "Inserta t: ";
	cin >> t;
	cout << "Inserta el limite de iteraciones (x100): ";
	cin >> iterations;

	CirclePointSet RG(n);
	Qualifier f(t, Qualifier::METHOD_RANGE_SIZE);

	size_t popSize = 40;
	vector< Circle::pointSet >S = RG.born(popSize);
	Evolutive::DiffEvo<vector<Circle::pointSet>, CirclePointSet, Qualifier> DE(1,0.2,2);

	for (size_t c1 = 0; c1 < S.size(); ++c1) {
		S[c1].set_value(f(S[c1]));
	}
	f(S[popSize - 1], true);
	cout << "Value: " << S[popSize - 1].get_value() << endl;
	S[popSize - 1].sort_by_coordinate(1);
	cout << S[popSize - 1].to_string(Circle::pointSet::TO_STRING_SAGE) << endl;
	double min_value = S[popSize - 1].get_value();

	for (size_t c1 = 0; c1 < iterations; ++c1) {
		DE.evolve(S, RG, f, 1, popSize / 10);
		if (S[popSize - 1].get_value() < min_value) {
			min_value = S[popSize - 1].get_value();
			if (min_value < 5) {
				S[popSize - 1].sort_by_coordinate(1);
				cout << S[popSize-1].to_string(Circle::pointSet::TO_STRING_SAGE) << endl;
				f(S[popSize - 1], true);
			}
			cout << "Value: " << min_value << endl;
		}
	}
}