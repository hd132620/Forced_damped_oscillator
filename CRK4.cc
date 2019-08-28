#include "./CRK4.hh"

void CRK4::InitVal(double _omega0, double _omega, double _gam, double
_a0){
	std::cout << " *Init "<< std::endl;
	omega0 = _omega0; omega = _omega;
	gam = _gam; a0 =_a0;
	omega02 = omega0*omega0;
	omega2 = omega*omega;
}

void CRK4::getResult(double* rT, double* rX1, double* rX2, double* rE){
std::cout << "iNt : " << iNt << std::endl;
	for(int i=0; i<iNt; i++){
		rT[i] = T[i];
		rX1[i] = X1[i];
		rX2[i] = X2[i];
		rE[i] = 0.5*X2[i]*X2[i] + omega02*(1.0-cos(X1[i]));
	}
}

void CRK4::RK(const double& Ti , const double& Tf, const double& X10,
const double& X20, const int& Nt){
	double TS,X1S,X2S; //time and X1,X2 at given step
	int    i;
	iNt = Nt;
	dt     = (Tf-Ti)/(Nt-1);
	T [0]  = Ti;
	X1[0]  = X10;
	X2[0]  = X20;
	TS     = Ti;
	X1S    = X10;
	X2S    = X20;
	for(i=1;i<Nt;i++){
		RKSTEP(TS,X1S,X2S,dt);
		T [i] = TS;
		X1[i] = X1S;
		X2[i] = X2S;
	}
}
void CRK4::RKSTEP ( double& t, double& x1, double& x2, const double& dt ) {
	double k11 , k12 , k13 , k14 , k21 , k22 , k23 , k24 ;
	double h , h2 , h6 ;

	h = dt; // h =dt
	h2 = 0.5* h; // h2=h/2
	h6 = h / 6.0; // h6=h/6
	k11= f1(t , x1 , x2);
	k21= f2(t , x1 , x2);
	k12= f1(t+h2 , x1+h2 * k11 , x2+h2 * k21);
	k22= f2(t+h2 , x1+h2 * k11 , x2+h2 * k21);
	k13= f1(t+h2 , x1+h2 * k12 , x2+h2 * k22);
	k23= f2(t+h2 , x1+h2 * k12 , x2+h2 * k22);
	k14= f1(t+h , x1+h * k13 , x2+h * k23);
	k24= f2(t+h , x1+h * k13 , x2+h * k23);
	t = t + h;
	x1 = x1 + h6 * ( k11 + 2.0*( k12+k13 ) + k14 );
	x2 = x2 + h6 * ( k21 + 2.0*( k22+k23 ) + k24 );
}
