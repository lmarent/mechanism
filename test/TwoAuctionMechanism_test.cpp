/*
 * Test the TwoAuctionMechanism class.
 *
 * $Id: TwoAuctionMechanism.cpp 1730 2015-11-23 21:30:00  $
 * $HeadURL: https://./test/TwoAuctionMechanism.cpp $
 */

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include "Error.h"
#include "TwoAuctionMechanism.h"

using namespace auction;

class TwoAuctionMechanismTest : public CppUnit::TestFixture  {

	CPPUNIT_TEST_SUITE( TwoAuctionMechanismTest );
	CPPUNIT_TEST( testFunctions );
	CPPUNIT_TEST_SUITE_END();

  public:
	void setUp();
	void tearDown();
	void testFunctions();

};

CPPUNIT_TEST_SUITE_REGISTRATION( TwoAuctionMechanismTest );

void TwoAuctionMechanismTest::setUp() 
{

}

void TwoAuctionMechanismTest::tearDown() 
{

}


void TwoAuctionMechanismTest::testFunctions()
{
	// Parameters 
	double b = 0.6;  ///! Maximum value that all budget user can pay.
	int p = 10;
	
	try {
		
		cout << "max double:" << std::numeric_limits<double>::max() << endl;
		
		TwoAuctionMechanism *test = new TwoAuctionMechanism();
		
		// Test for CalculateFi function.
		CPPUNIT_ASSERT(test->calculateFi(1, 10) >= 0.0833332);
		CPPUNIT_ASSERT(test->calculateFi(1, 10) <= 0.0833334);
		CPPUNIT_ASSERT(test->calculateFi(2, 10) >= 0.0705127);
		CPPUNIT_ASSERT(test->calculateFi(2, 10) <= 0.0705129);
		CPPUNIT_ASSERT(test->calculateFi(3, 10) >= 0.0503662);
		CPPUNIT_ASSERT(test->calculateFi(3, 10) <= 0.0503664);

		// Test for CalculateFiPrime function.
		CPPUNIT_ASSERT(test->calculateFiPrime(16, 3) >= 0.04127966);
		CPPUNIT_ASSERT(test->calculateFiPrime(16, 3) <= 0.04127968);
		CPPUNIT_ASSERT(test->calculateFiPrime(10, 2) >= 0.07575757);
		CPPUNIT_ASSERT(test->calculateFiPrime(10, 2) <= 0.07575758);
		CPPUNIT_ASSERT(test->calculateFiPrime(30, 5) >= 0.01688373);
		CPPUNIT_ASSERT(test->calculateFiPrime(30, 5) <= 0.01688374);
		CPPUNIT_ASSERT(test->calculateFiPrime(10, 10) >=  0.000005412);
		CPPUNIT_ASSERT(test->calculateFiPrime(10, 10) <=  0.000005414);
				
		CPPUNIT_ASSERT(test->calculateFiPrime(60, 30) >=  0.000000005 );
		CPPUNIT_ASSERT(test->calculateFiPrime(60, 30) <=  0.000000007 );
		

		// Test for calculateG function
		CPPUNIT_ASSERT(test->calculateG(10) >= 0.000000061);
		CPPUNIT_ASSERT(test->calculateG(10) <= 0.000000062);
				
		// Test for calculateGPrime function
		CPPUNIT_ASSERT(test->calculateGPrime(10) >=  0.0000002576);
		CPPUNIT_ASSERT(test->calculateGPrime(10) <=  0.0000002578);
		CPPUNIT_ASSERT(test->calculateGPrime(15) >=  0.0000000001);
		CPPUNIT_ASSERT(test->calculateGPrime(15) <=  0.0000000003);
		CPPUNIT_ASSERT(test->calculateGPrime(7) >=   0.0000194249);
		CPPUNIT_ASSERT(test->calculateGPrime(7) <=   0.0000194251);
		CPPUNIT_ASSERT(test->calculateGPrime(90) >=   0);
		
		cout << "C(76,15)" << test->C(74,15) << endl;
		
		/*
		for (int s = 1; s <= 300; s++){
			cout << "test->C(" << s << ", 0.5, 0.8):" << 
				test->calculateE(s, 0.5, 0.8) << endl;
		}
		*/
				
		CPPUNIT_ASSERT(test->calculateE(10, 0.5, 0.8) >= 0.0907831);
		CPPUNIT_ASSERT(test->calculateE(10, 0.5, 0.8) <= 0.0907833);
		CPPUNIT_ASSERT(test->calculateE(40, 0.5, 0.8) >= 0.00946037);
		CPPUNIT_ASSERT(test->calculateE(40, 0.5, 0.8) <= 0.00946039);
				
		// Test for FunctionQ
		/*
		cout << "test->FunctionFy(b, c):" << test->FunctionFy(0.5,0.55) << endl;
		cout << "test->Functiongy(b, c):" << test->Functiongy(0.5,0.55) << endl;
		cout << "test->functiongDerivate(b):" << test->functiongDerivate(0.5) << endl;
		cout << "test->Derivate1y(50,0.5,0.55):" << test->Derivate1y(100,0.5,0.55) << endl;
		cout << "test->Derivate2y(50,0.5,0.55):" << test->Derivate2y(100,0.5,0.55) << endl;
		cout << "test->Derivate3y(50,0.5,0.55):" << test->Derivate3y(100,0.5,0.55) << endl;
		cout << "test->Derivate4y(50,0.5,0.55):" << test->Derivate4y(100,0.5,0.55) << endl;
		cout << "test->Derivate5y(50,0.5,0.55):" << test->Derivate5y(100,0.5,0.55) << endl;
		cout << "test->Derivate6y(50,0.5,0.55):" << test->Derivate6y(100,0.5,0.55) << endl;
		
		cout << "calculateStep(15, 0.5, 1.0, 0.00000001):" << test->calculateStep(15, 0.5, 0.9, 0.00000001) << endl;
				
		cout << "test->CalculateNumericalV(15, 0.5, 1.0, 0.00000001)" << 
					test->CalculateNumericalV(13, 0.5, 0.9, 0.00000001) << endl;
		
		
		cout << "test C(60,30)"<< test->C(70,35) << endl;
			
		
		for (int s = 1; s <= 15; s++){
			cout << "test->FunctionV(" << s << ",0.5,0.9)" << test->FunctionV(s, 0.5, 0.9) << endl;
		}
			
		
		cout << "test->FunctionV("  << ",0.5,0.9)" << test->FunctionV(s, 0.5, 0.9) << endl;"
		*/
		
		// Test for FunctionO		
		CPPUNIT_ASSERT(test->FunctionO(12, 0.8) >= 0.00572661 );
		CPPUNIT_ASSERT(test->FunctionO(12, 0.8) <= 0.00572663 );
		
		//cout << "test FunctionP(10, 0.5, 0.8)" << test->FunctionP(10, 0.5, 0.8) << endl;
		
		// Test for FunctionP
		CPPUNIT_ASSERT(test->FunctionP(10, 0.5, 0.8) >= 0.31970 );
		CPPUNIT_ASSERT(test->FunctionP(10, 0.5, 0.8) <= 0.31972 );
				
		// Test for calculateIPrime function
		CPPUNIT_ASSERT(test->calculateUniformIPrime(10, 0.5, 0.8) >= 0.02637);
		CPPUNIT_ASSERT(test->calculateUniformIPrime(10, 0.5, 0.8) <= 0.02639);
										
		// Test for calculateI function
		CPPUNIT_ASSERT(test->calculateUniformI(p, b) >= 0.0462077);
		CPPUNIT_ASSERT(test->calculateUniformI(p, b) <= 0.0462079);

		double init = 0.000001;
		std::cout.setf( std::ios::fixed, std:: ios::floatfield );

		cout << "test->calculateUniformIPrime(100, 0.5, 0.8)" 
				<< test->calculateUniformIPrime(100, 0.5, 0.8) << endl;


		// Test for calculateD function
		CPPUNIT_ASSERT(test->calculateD( init, 10, 5, 2 ) >= 0.0125 );
		CPPUNIT_ASSERT(test->calculateD( init, 40,10,2) >=  3687323.2967);
		CPPUNIT_ASSERT(test->calculateD( init, 40,10,2) <=  3687323.2969);

		cout << "test calculateWinProbabilityPrime(30,6,0.5,0.5)" 
				<< test->calculateWinProbabilityPrime(30, 6, 0.5, 0.5) << endl;

				
		// Test for calculateWinProbabilityPrime function
		CPPUNIT_ASSERT(test->calculateWinProbabilityPrime(30, 6, 0.5, 0.5) >= 0.99982 );
		CPPUNIT_ASSERT(test->calculateWinProbabilityPrime(30, 6, 0.5, 0.5) <= 0.99984 );

		int n2 =75;
		int k = 16;
		
		std::map<int, double> Dvalues;
		// Calculate the values D for j \in [0,n-k]
		for (int j=0; j <= (n2-k); j++ ){
			Dvalues[j] = test->calculateD(init,n2,k,j);
			cout << ":n2:" << n2 << ":k:" << k << ":j:"  << j << ":Dvalue:" << Dvalues[j] << endl;
		}
		
		
		
		//CPPUNIT_ASSERT (test->calculateExpectedValueK( n2, k, b, Dvalues) >= 0.24638);
		// CPPUNIT_ASSERT (test->calculateExpectedValueK( n2, k, b, Dvalues) <= 0.24640);
		double bid = 0.5;
		//CPPUNIT_ASSERT ( test->calculateWinProbability(n2, k, b, bid, Dvalues) >= 0.999291);
		//CPPUNIT_ASSERT ( test->calculateWinProbability(n2, k, b, bid, Dvalues) <= 0.999293);
		
		n2 = 75;
		k = 16;
		b = 0.5;
		bid = 0.6;
		cout << "test->calculateExpectedBoundedValueKPrime( n2, k, b, bid, Dvalues)" << 
				test->calculateExpectedBoundedValueKPrime( n2, k, b, bid)	<< endl;
		//CPPUNIT_ASSERT (test->calculateExpectedBoundedValueKPrime( n2, k, b, bid, Dvalues) >= 0.388035);
		//CPPUNIT_ASSERT (test->calculateExpectedBoundedValueKPrime( n2, k, b, bid, Dvalues) <= 0.388037);
						
		CPPUNIT_ASSERT (test->calculateWinProbabilityPrime(n2,k,b,bid) >= 0.813344);
		CPPUNIT_ASSERT (test->calculateWinProbabilityPrime(n2,k,b,bid) <= 0.813346);
	
	
		for (int s= 1; s <= 100; s++){
			cout << "calculateUniformI s:" << s << ":val:" << test->calculateUniformI(s,0.5) << endl;
		}
		
		int nh = 10;
		int nl = 30;
		double bh = 0.5;
		double bl = 0.4;
		double bidF = 1.0;
		double a = 0.1;
		double b = 0.9;
		double macheps = 0.000001;
		double t = 0.000001;

		
		for ( double q = 0.1; q <= 0.9; q = q + 0.1){
			std::cout << "q:"<< q << ":High:" <<
			test->expectedProfitHStrategy(nh, bh, bidF, q) << ":Low:" <<
			test->expectedProfitLStrategy( nh, nl, bh, bl, bidF, q) << std::endl;
		}
	
		double qStar = test->zeros(nh, nl, bh, bl, bidF, a, b, macheps, t);

		double q = 0.22605;
		std::cout << "q:"<< q << "functionF:" <<
		test->functionF(nh, nl, bh, bl, bidF, q) << std::endl;

		std::cout << "qStar:" << qStar << std::endl;
				
		nh = 10;
		nl = 15;
		int kl = 6;
		double bidih = 0.4;
		
		CPPUNIT_ASSERT ( test->expectedProfitLStrategyNotEnoughQuantities(nh, nl, kl, bl, bidih)>= 0.0225276);
		CPPUNIT_ASSERT ( test->expectedProfitLStrategyNotEnoughQuantities(nh, nl, kl, bl, bidih)<= 0.0225278);
		
		
		// Test to check profit value with enough quantities.
		nh =15;
		nl = 15;
		kl = 6;
		bh = 1.0;
		int kh = 6;
		bl= 0.4;
		bid =0.6;
		double rpl = 0.3;
		double rph = 0.7;
		q = 0.5;
		
		double ghhacum = 0; 
		for (int j = 0; j < kl; j++){
			double ghh = test->expectedProfitLStrategyEnoughQuantities(j, nl, kl, bl, rpl, bid );
			ghhacum = ghhacum + ghh;
		}
		
		CPPUNIT_ASSERT ( ghhacum >= 2.07008 );
		CPPUNIT_ASSERT ( ghhacum <= 2.07009 );

		q = 0.2;
		for (bid = 0.5; bid <= bh ; bid=bid+ 0.01){
			for (q = 0.05; q<= 0.95; q=q+0.01){
				double expected = test->expectedProfitLStrategyWithUnits(nh, nl, bh, bl, kh, kl, rph, rpl, bid, q);
				std::cout << "q:" << q << " :bid:" << bid << " :expected L Strategy:" << expected << std::endl;
			}
		}
		
		
		for (bid = 0.5; bid <= 0.95 ; bid=bid+ 0.02){
			for (q = 0.05; q<= 0.95; q=q+0.01){
				double expected = test->expectedProfitHStrategyWithUnits(nh, kh, bh, bl, rph, bid, q);
				std::cout << "q:" << q << " :bid:" << bid << " :expected H Strategy:" << expected << std::endl;
			}
		}
		
		a = 0.1;
		b = 0.5;
		qStar = test->zerosWithUnits(nh, nl, bh, bl, 6, 6, 0.45, 0.3, bidF, a, b, macheps, t);
		std::cout << "qStar:" << qStar << std::endl;
				
		delete test;

		
		
	/*
	
	double expected = 0;
	for (k=0; k <= n; k++){
		// calculate the expected k value.
		expected = expected + calculateExpectedKvalue(n, k, b, Dvalues);
	}
	
	// calculates the probability.
	double probability = 0;
	for (k=0; k <= n; k++){
		calculateWinProbability(n, k, b, bid, Dvalues);
	}	
	*/	
	} catch (Error &e){
		std::cout << "Invalid argument: " << e.getError() << std::endl;
		throw e;
	}
}
