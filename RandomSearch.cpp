#include "PointSetPartition.h"

#include <iostream>

using namespace std;

int main()
{
	//Parameters
	int t, n, iterations;

	cout << "Inserta la cantidad de puntos: ";
	cin >> n;
	cout << "Inserta t: ";
	cin >> t;
	cout << "Inserta el limite de iteraciones: ";
	cin >> iterations;
	
	Geometry::Circle RG;
	Qualifier f(t);

	PointSet S = RG.born(n);
	int min_value = f(S);
	cout << "Value: " << min_value << " Tries: " << 0 << endl;
	if (min_value < 5) {
		S.sort_by_coordinate(1);
		cout << S.to_string(PointSet::TO_STRING_SAGE) << endl;
		f(S, true);
	}

	for (size_t c1 = 1; c1 < iterations; ++c1) {
		PointSet C = RG.born(n);
		int CValue = f(C);
		if (CValue < min_value) {
			min_value = CValue;
			cout << "Value: " << min_value << " Tries: " << c1 << endl;
			S = C;
			if (min_value < 5) {
				S.sort_by_coordinate(1);
				cout << S.to_string(PointSet::TO_STRING_SAGE) << endl;
				f(S, true);
			}
		}
	}
	return 0;
}
