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
		
		TwoAuctionMechanism *test = new TwoAuctionMechanism();
		
		// Tests for CalculateFi function.
		CPPUNIT_ASSERT(test->calculateFi(1, 10) >= 0.0833332);
		CPPUNIT_ASSERT(test->calculateFi(1, 10) <= 0.0833334);
		CPPUNIT_ASSERT(test->calculateFi(2, 10) >= 0.0705127);
		CPPUNIT_ASSERT(test->calculateFi(2, 10) <= 0.0705129);
		CPPUNIT_ASSERT(test->calculateFi(3, 10) >= 0.0503662);
		CPPUNIT_ASSERT(test->calculateFi(3, 10) <= 0.0503664);

		// Tests for calculateG function
		CPPUNIT_ASSERT(test->calculateG(10) >= 0.000000061);
		CPPUNIT_ASSERT(test->calculateG(10) <= 0.000000062);

		// Test for calculateI function
		CPPUNIT_ASSERT(test->calculateUniformI(p, b) >= 0.0462077);
		CPPUNIT_ASSERT(test->calculateUniformI(p, b) <= 0.0462079);

		// Test for calculateD function
		CPPUNIT_ASSERT(test->calculateD( 10, 5, 2 ) == 12600 );
		CPPUNIT_ASSERT(test->calculateD( 40,10,2) ==  3687323296800);

		int n2 =10;
		int k = 6;

		std::map<int, double> Dvalues;

		// Calculate the values D for j \in [0,n-k]
		for (int j=0; j <= (n2-k); j++ ){
			Dvalues[j] = test->calculateD(n2,k,j);
		}

		CPPUNIT_ASSERT (test->calculateExpectedValueK( n2, k, b, Dvalues) >= 0.24638);
		CPPUNIT_ASSERT (test->calculateExpectedValueK( n2, k, b, Dvalues) <= 0.24640);
		double bid = 0.5;
		CPPUNIT_ASSERT ( test->calculateWinProbability(n2, k, b, bid, Dvalues) >= 0.999291);
		CPPUNIT_ASSERT ( test->calculateWinProbability(n2, k, b, bid, Dvalues) <= 0.999293);

		std::cout << test->calculateUniformBoundedI(p, b, bid) << std::endl;

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
		double qStar = test->zeros(nh, nl, bh, bl, bidF, a, b, macheps, t);

		double q = 0.22605;
		std::cout << "q:"<< q << "functionF:" <<
		test->functionF(nh, nl, bh, bl, bidF, q) << std::endl;

		std::cout << "qStar:" << qStar << std::endl;
		
		std::cout << "C(90,45):" << test->C(90,45) <<std::endl;
		
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
				double expected = test->expectedProfitHStrategyWithUnits(nh, kh, bh, rph, bid, q);
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
