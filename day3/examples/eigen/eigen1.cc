#include <Eigen/Dense>
#include <iostream>
using namespace Eigen;
using namespace std;
int main()
{
    MatrixXd m = MatrixXd::Random(3, 3);
    m = (m + MatrixXd::Constant(3, 3, 1.2)) * 50;
    cout << "m =" << "\n" << m << "\n";
    VectorXd v(3);
    v << 1, 2, 3;
    cout << "m * v =\n" 
         << m * v << "\n";
}
