/* header files should come here */

#ifndef CRK4_HH__
#define CRK4_HH__

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
#include <cmath>

class CRK4
{
private:
	static const int P=10000;
	double T[P], X1[P], X2[P], Energy[P];
	double omega0, omega, gam, a0, omega02, omega2, dt;
	int iNt;

	public:
		CRK4(){} // constructor
		~CRK4(){} // destructor

		void InitVal(double _omega0, double _omega, double _gam, double _a0);

		void getResult(double* rT, double* rX1, double* rX2, double* rE);

		double f1(const double &t, const double &x1, const double &x2){
			return x2;
		}

		double f2(const double &t, const double &x1, const double &x2){
			return -(omega02+2.0*a0*cos(omega*t))*sin(x1)-gam*x2;
		}

		void RK(const double& Ti , const double& Tf, const double& X10,
		const double& X20, const int & Nt);

		void RKSTEP(double& t, double& x1, double& x2, const double& dt);
}; 
#endif
