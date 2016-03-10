/*
 * Test the TwoAuctionMechanismGeneralized class.
 *
 * $Id: TwoAuctionMechanismGeneralized.cpp 1730 2015-11-23 21:30:00  $
 * $HeadURL: https://./test/TwoAuctionMechanismGeneralized.cpp $
 */

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include "Error.h"
#include "TwoAuctionMechanismGeneralized.h"

using namespace auction;

class TwoAuctionMechanismGeneralizedTest : public CppUnit::TestFixture  {

	CPPUNIT_TEST_SUITE( TwoAuctionMechanismGeneralizedTest );
	CPPUNIT_TEST( testFunctions );
	CPPUNIT_TEST_SUITE_END();

  public:
	void setUp();
	void tearDown();
	void testFunctions();

};

CPPUNIT_TEST_SUITE_REGISTRATION( TwoAuctionMechanismGeneralizedTest );

void TwoAuctionMechanismGeneralizedTest::setUp() 
{

}

void TwoAuctionMechanismGeneralizedTest::tearDown() 
{

}


void TwoAuctionMechanismGeneralizedTest::testFunctions()
{
	// Parameters 
	double bl = 0.5;
	
	try {

		TwoAuctionMechanismGeneralized *mechanism = new TwoAuctionMechanismGeneralized();
		
		vector<double> weights = mechanism->hermquad(QUADRATURE_WEIGHTS);
		CPPUNIT_ASSERT(weights.size() == 20);
		CPPUNIT_ASSERT(weights[6] == 2.48105208874636108814e-02);
		
		vector<double> abscissae = mechanism->hermquad(QUADRATURE_ABSCISSAE);
		CPPUNIT_ASSERT(abscissae.size() == 20);
		CPPUNIT_ASSERT(abscissae[6] == 1.73853771211658620678e+00);
		
		vector<double> weights0Inf = mechanism->gaussQuadrature0Inf(2,QUADRATURE_WEIGHTS);
		CPPUNIT_ASSERT(weights0Inf.size() == 2);

		vector<double> abscissae0Inf = mechanism->gaussQuadrature0Inf(4,QUADRATURE_ABSCISSAE);
		CPPUNIT_ASSERT(abscissae0Inf.size() == 4);
		
		string theString = "1, 2, 3, 4, ";
		vector<string> splitted; 
		string delimiter = ",";
		mechanism->split(splitted, theString, delimiter);
		CPPUNIT_ASSERT(splitted.size() == 5);
		CPPUNIT_ASSERT(splitted[0] == "1");
		CPPUNIT_ASSERT(splitted[1] == " 2");
		CPPUNIT_ASSERT(splitted[2] == " 3");
		CPPUNIT_ASSERT(splitted[3] == " 4");
		
		vector<double> abscissae0b;
		mechanism->LoadQuadrature(30, 8, QUADRATURE_ABSCISSAE, QUADRATURE_LOWER_LIMIT, abscissae0b);
		CPPUNIT_ASSERT( abscissae0b[1] == 0.54542464); 

		vector<double> weight01;
		mechanism->LoadQuadrature(30, 8, QUADRATURE_WEIGHTS, QUADRATURE_UPPER_LIMIT, weight01);
		CPPUNIT_ASSERT( weight01[2] == 0.13344364); 

		double point1 = 0.55;
		double point2 = 0.8;
		double point3 = 0.9;
				
		CPPUNIT_ASSERT( round(mechanism->FhInverse(bl, point1)*10000000) == 6645898);
		CPPUNIT_ASSERT( round(mechanism->FhInverse(bl, point2)*10000000) == 7763932);
		CPPUNIT_ASSERT( round(mechanism->FhInverse(bl, point3)*10000000) == 8418861);
		
		CPPUNIT_ASSERT( round(mechanism->fH(bl, point1)*10000000) == 36000000);
		CPPUNIT_ASSERT( round(mechanism->fH(bl, point2)*10000000) == 16000000);
		CPPUNIT_ASSERT( round(mechanism->fH(bl, point3)*10000000) == 8000000);
				
		point1 = 0.1;
		point2 = 0.25;
		point3 = 0.4;
		
		CPPUNIT_ASSERT( round(mechanism->FLAcum(bl, point1)*10000000) == 2800000);
		CPPUNIT_ASSERT( round(mechanism->FLAcum(bl, point2)*10000000) == 6250000);
		CPPUNIT_ASSERT( round(mechanism->FLAcum(bl, point3)*10000000) == 8800000);
		
		CPPUNIT_ASSERT( round(mechanism->fL(bl, point1)*100000) == 260000);
		CPPUNIT_ASSERT( round(mechanism->fL(bl, point2)*100000) == 200000);
		CPPUNIT_ASSERT( round(mechanism->fL(bl, point3)*100000) == 140000);
																					
		CPPUNIT_ASSERT( round(mechanism->FLInverse(bl, point1)*1000000000) == 34108947);
		CPPUNIT_ASSERT( round(mechanism->FLInverse(bl, point2)*1000000000) == 88562172);
		CPPUNIT_ASSERT( round(mechanism->FLInverse(bl, point3)*1000000000) == 147920271);
				
		CPPUNIT_ASSERT( round(mechanism->ProbWithoutReplacement(50, 10)*10000000) == 2206623);
		
		vector<int> N = mechanism->N_Users(70, 0.1, abscissae);
		CPPUNIT_ASSERT( N[0] == 44);
		CPPUNIT_ASSERT( N[19] == 70);

		vector<int> N2 = mechanism->N_Users(40, 0.7, abscissae);
		CPPUNIT_ASSERT( N2[0] == 0);
		CPPUNIT_ASSERT( N2[19] == 35);
		
		double sigma = 0.026746974;
		double nu = 0.598390336;
		double y = 0.23;
		double Q = 0.25;
		double PL = 0.15;
		CPPUNIT_ASSERT( round(mechanism->p11star(bl, sigma, nu, y, Q, PL)*1000000000) == 42564451);
		CPPUNIT_ASSERT( round(mechanism->p21star(bl, sigma, nu, y, Q, PL)*1000000000) == 21731118);
		CPPUNIT_ASSERT( round(mechanism->p12star( sigma, nu, y, Q, PL)*1000000000) == 29039463);
		CPPUNIT_ASSERT( round(mechanism->p22star( sigma, nu, y, Q, PL)*1000000000) == 18930025);
		
		int NH = 70;
		int CH = 20;
		double q = 0.3;
		double PH = 0.5;
		cout << setprecision(30);

		CPPUNIT_ASSERT( round(mechanism->expectedPayoffHStrategyKUnitsMechanism(
						weights, abscissae, NH, CH, q , bl, PH, Q, PL)*1000000000) == 101597608);
		
		int CL = 20;
		int NL = 70;
		CPPUNIT_ASSERT( round(mechanism->expectedPayoffLStrategyKUnits(
						weights, abscissae, NH, NL, q , bl, CL, PL)*1000000000) == 100885949);
								
		CPPUNIT_ASSERT( round(mechanism->gstar(NH, NL, CH, CL, PH, PL, bl, Q, q)*1000000000) == 711659);  
		
		double bh = 1.0;
		double macheps = 0.01;
		double t = 0.000001;
		double a =0.1;
		double b= 0.8;
		
		CPPUNIT_ASSERT( round(mechanism->zerosWithUnits(NH, NL, bh, bl, CH, CL, 
							PH, PL, Q, a, b, macheps, t)*1000000000) == 304363617);
		
		mechanism->zeroin(NH, NL, bh, bl, CH, CL, PH, PL, Q,  &a, &b);
		
		cout << "zeroin:" << a << endl;

		
	} catch (Error &e){
		std::cout << "Invalid argument: " << e.getError() << std::endl;
		throw e;
	}
}
