#include "../PointSetPartition.h"
#include "AutoSearch.h"

using namespace std::chrono;
using namespace Geometry;
using namespace Evolutive;
using namespace std;

using diffEvo = DiffEvo<vector<Circle::pointSet>, CirclePointSet, Qualifier>;

int main(int argc, char* argv[]) {
	/* Parameters List
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
			1 = Random search
			2 = Minimize Number of Partitions,
			3 = 2 + Minimize Distance Between Partitions,
			4 = 3 + Minimize Distance Between Middle Points of Partitions
		)
	*/

	size_t n, t;
	double r;
	size_t popSize, randSettlers;
	double Cm, Cp;
	unsigned int iterations, method;

	std::istringstream ss_n(argv[1]);
	if (!(ss_n >> n))
	{
		std::cout << "Error with arguments" << std::endl;
		return 0;
	}
	
	std::istringstream ss_t(argv[2]);
	if (!(ss_t >> t))
	{
		std::cout << "Error with arguments" << std::endl;
		return 0;
	}

	std::istringstream ss_r(argv[3]);
	if (!(ss_r >> r))
	{
		std::cout << "Error with arguments" << std::endl;
		return 0;
	}

	std::istringstream ss_popSize(argv[4]);
	if (!(ss_popSize >> popSize))
	{
		std::cout << "Error with arguments" << std::endl;
		return 0;
	}

	std::istringstream ss_Cm(argv[5]);
	if (!(ss_Cm >> Cm))
	{
		std::cout << "Error with arguments" << std::endl;
		return 0;
	}

	std::istringstream ss_Cp(argv[6]);
	if (!(ss_Cp >> Cp))
	{
		std::cout << "Error with arguments" << std::endl;
		return 0;
	}

	std::istringstream ss_randSettlers(argv[7]);
	if (!(ss_randSettlers >> randSettlers))
	{
		std::cout << "Error with arguments" << std::endl;
		return 0;
	}

	std::istringstream ss_iterations(argv[8]);
	if (!(ss_iterations >> iterations))
	{
		std::cout << "Error with arguments" << std::endl;
		return 0;
	}

	std::istringstream ss_method(argv[9]);
	if (!(ss_method >> method))
	{
		std::cout << "Error with arguments" << std::endl;
		return 0;
	}


	double minValue = 5;

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
			cout << "Duration: " << durationM.count() << " Minutes " << durationS.count() % 60 << " Seconds" << endl << endl;
		}
	}

	return 0;
}