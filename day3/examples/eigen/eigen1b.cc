#include <Eigen/Dense>
#include <iostream>
using namespace Eigen;
using namespace std;
int main()
{
    Matrix3d m = Matrix3d::Random();
    m = (m + Matrix3d::Constant(1.2)) * 50;
    cout << "m =" << "\n" << m << "\n";
    Vector3d v(1, 2, 3);

    cout << "m * v =" << "\n"
         << m * v << "\n";
}
