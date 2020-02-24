#include "../PointSetPartition.h"
#include "AutoSearch.h"

using namespace std::chrono;
using namespace Geometry;
using namespace Evolutive;
using namespace std;

using diffEvo = DiffEvo<vector<Circle::pointSet>, CirclePointSet, Qualifier>;

int main() {
	/* Parameters List
		Algorithm (1 = RandomSearch, 2 = DifferentialEvolution)
		--General
		n := Amount of points
		t := two times the number of points in the small quarters
		r := radius of circle. The circle where we are generating the random points
		--DiffEvo
		PopSize
		Cm
		Cp
		RandomSettlers
		Iterations		
		--Qualifier
		Method (
			1 = Minimize Number of Partitions, 
			2 = 1 + Minimize Distance Between Partitions,
			3 = 1 + Minimize Distance Between Middle Points of Partitions
		)
	*/

	size_t n, t;
	double r;
	size_t popSize, randSettlers;
	double Cm, Cp;
	unsigned int iterations, method, alg;

	cin >> alg;
	cin >> n;
	cin >> t;
	cin >> r;
	if (alg == 2) {
		cin >> popSize;
		cin >> Cm;
		cin >> Cp;
		cin >> randSettlers;
	}
	cin >> iterations;
	cin >> method;
	
	double minValue = 5;

	Qualifier f(t, method);
	if (alg == 1) {
		CirclePointSet RG(n, r);
		
		auto start = high_resolution_clock::now();
	
		for (size_t c1 = 0; c1 < iterations; ++c1) {
			Circle::pointSet Set = RG.born();
			for (size_t c1 = 0; c1 < n; ++c1) {
				Set.set_value(f(Set));
			}
			double value = Set.get_value();
			if (value < minValue) {
				auto stop = high_resolution_clock::now();
				auto durationM = duration_cast<minutes>(stop - start);
				auto durationS = duration_cast<seconds>(stop - start);

				minValue = value;

				Set.sort_by_coordinate(1);
				cout << "Points" << endl << Set.to_string(Circle::pointSet::TO_STRING_SAGE) << endl;
				cout << "Partitions" << endl << f(Set, true) << endl;
				cout << "Duration: " << durationM.count() << " Minutes " << durationS.count() % 60 << " Seconds" << endl << endl;
			}
		}

	}
	if (alg == 2) {
		Qualifier f(t, method);
		CirclePointSet RG(n, r);
		vector<Circle::pointSet> Population = RG.born(popSize);
		diffEvo DE(Cp, Cm, diffEvo::SORT_DESCENDING);

		auto start = high_resolution_clock::now();

		for (size_t c1 = 0; c1 < popSize; ++c1) {
			Population[c1].set_value(f(Population[c1]));
		}

		for (size_t c1 = 0; c1 < iterations; ++c1) {
			DE.evolve(Population, RG, f, 1, randSettlers);
			double value = Population[popSize - 1].get_value();
			if (value < minValue) {
				auto stop = high_resolution_clock::now();
				auto durationM = duration_cast<minutes>(stop - start);
				auto durationS = duration_cast<seconds>(stop - start);

				minValue = value;
				Geometry::PointSet p = Population[popSize - 1];
				p.sort_by_coordinate(1);
				cout << "Points" << endl << p.to_string(Circle::pointSet::TO_STRING_SAGE) << endl;
				cout << "Partitions" << endl << f(p, true) << endl;
				cout << "Duration: " << durationM.count() << " Minutes " << durationS.count()%60 << " Seconds" << endl << endl;
			}
		}
	}

	return 0;
}