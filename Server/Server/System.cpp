#include "System.h"
#include "geometry.h"
#include "random.h"

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace geom;
using namespace random;
using namespace std;

System::System() {
	objects.push_back({});
	objects.back().pos = { 100, 100 };
	objects.back().team = "biba";

	objects.push_back({});
	objects.back().pos = { 500, 500 };
	objects.back().team = "boba";
}

System::~System() {
}
