#include <PointSet.hpp>
#include <RandomGenerators.hpp>

#include <iostream>
using namespace std;
using Vector = std::vector<double>;
int main() {
	Geometry::CirclePointSet RG(40, 1);
	Geometry::PointSet SET = RG.born();
	cout << SET.to_string() << endl;
	cout << "------------------------" << endl;
	cout << SET.perturbed(0.0001).to_string() << endl;
}