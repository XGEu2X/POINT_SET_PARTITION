#include "PointSetPartition.h"

#include <iostream>
#include "stdio.h"

using namespace std;

int main() {
	size_t n, t;
	PointSet P;
	
	cout << "Inserte la cantidad de puntos: ";
	cin >> n;
	cout << "Inserte los puntos en el formato \"x y\":" << endl;
	for (size_t c1 = 0; c1 < n; ++c1) {
		double x, y;
		scanf("%lf %lf", &x, &y);
		P.push_back(Point(std::vector({ x,y })));
	}
	cout << "Inserte t: ";
	cin >> t;

	Qualifier f(t);

	cout << f(P, true) << endl;

	cout << P.to_string(PointSet::TO_STRING_GEOGEBRA) << endl;

	return 0;
}