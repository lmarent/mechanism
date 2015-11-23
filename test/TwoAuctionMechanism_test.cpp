#include <string.h>
#include <math.h>       /* pow */
#include <stdexcept>      // std::invalid_argument
#include <map>
#include <CPPUNIT_ASSERT.h>
#include <sstream>      // std::ostringstream
#include <iostream>       // std::cerr
#include <cmath>        // std::abs
#include <vector>

using namespace auction;

class TwoAuctionMechanismTest : CppUnit::TestFixture {

	CPPUNIT_TEST_SUITE( TwoAuctionMechanismTest );
	CPPUNIT_TEST( testFunctions );
	CPPUNIT_TEST_SUITE_END();

  public:
	void setUp();
	void tearDown();
	void testFunctions();
}

CPPUNIT_TEST_SUITE_REGISTRATION( TwoAuctionMechanismTest );

void TwoAuctionMechanismTest::setUp() 
{
	
	
}

void TwoAuctionMechanismTest::tearDown() 
{
	
	
}


int TwoAuctionMechanismTest::testFunctions()
{
	// Parameters 
	double b = 0.6;  ///! Maximum value that all budget user can pay.
	int p = 10;
	
	try {

		// Tests for CalculateFi function.
		CPPUNIT_ASSERT(calculateFi(1, 10) >= 0.0833332);
		CPPUNIT_ASSERT(calculateFi(1, 10) <= 0.0833334);
		CPPUNIT_ASSERT(calculateFi(2, 10) >= 0.0705127);
		CPPUNIT_ASSERT(calculateFi(2, 10) <= 0.0705129);
		CPPUNIT_ASSERT(calculateFi(3, 10) >= 0.0503662);
		CPPUNIT_ASSERT(calculateFi(3, 10) <= 0.0503664);

		// Tests for calculateG function
		CPPUNIT_ASSERT(calculateG(10) >= 0.000000061);
		CPPUNIT_ASSERT(calculateG(10) <= 0.000000062);

		// Test for calculateI function
		CPPUNIT_ASSERT(calculateI(p, b) >= 0.0462077);
		CPPUNIT_ASSERT(calculateI(p, b) <= 0.0462079);

		// Test for calculateD function
		CPPUNIT_ASSERT(calculateD( 10, 5, 2 ) == 12600 );
		CPPUNIT_ASSERT(calculateD( 40,10,2) ==  3687323296800);

		int n2 =10;
		int k = 6;

		std::map<int, double> Dvalues;

		// Calculate the values D for j \in [0,n-k]
		for (int j=0; j <= (n2-k); j++ ){
			Dvalues[j] = calculateD(n2,k,j);
		}

		CPPUNIT_ASSERT (calculateExpectedValueK( n2, k, b, Dvalues) >= 0.24638);
		CPPUNIT_ASSERT (calculateExpectedValueK( n2, k, b, Dvalues) <= 0.24640);
		double bid = 0.5;
		CPPUNIT_ASSERT ( calculateWinProbability(n2, k, b, bid, Dvalues) >= 0.999291);
		CPPUNIT_ASSERT ( calculateWinProbability(n2, k, b, bid, Dvalues) <= 0.999293);

		std::cout << calculateBoundedI(p, b, bid) << std::endl;

		int nh = 10;
		int nl = 30;
		double bh = 0.6;
		double bl = 0.4;
		double bidF =0.5;
		double a = 0.1;
		double b = 0.9;
		double macheps = 0.000001;
		double t = 0.000001;

		/*
		for ( double q = 0.1; q <= 0.9; q = q + 0.1){
			std::cout << "q:"<< q << "High:" <<
			expectedProfitHStrategy(nh, bh, bidF, q) << "Low:" <<
			expectedProfitLStrategy( nh, nl, bh, bl, bidF, q) << std::endl;
		}

		for ( double q = 0.1; q <= 0.9; q = q + 0.1){
			std::cout << "q:"<< q << "functionF:" <<
			functionF(nh, nl, bh, bl, bidF, q) << std::endl;
		}
		*/
		double qStart = zeros(nh, nl, bh, bl, bidF, a, b, macheps, t);

		double q = 0.22605;
		std::cout << "q:"<< q << "functionF:" <<
		functionF(nh, nl, bh, bl, bidF, q) << std::endl;

		std::cout << "qStart:" << qStart << std::endl;




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
	} catch (std::invalid_argument &e){
		std::cout << "Invalid argument: " << e.what() << '\n';
	}
	return 0;
}
