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
	//if (min_value < 3) {
		f(S, true);
		cout << "Value: " << min_value << endl;
		S.sort_by_coordinate(1);
		cout << S.to_string(PointSet::TO_STRING_GEOGEBRA) << endl;
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
				S.sort_by_coordinate(1);
				cout << S.to_string(PointSet::TO_STRING_GEOGEBRA) << endl;
			//}
		}
	}
	return 0;
}
