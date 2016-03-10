/// ----------------------------------------*- mode: C++; -*--
/// @file TwoAuctionMechanismGeneralized.h
/// This file defines functions used for executing the generalized two auction mechanism.
/// ----------------------------------------------------------
/// $Id: TwoAuctionMechanism.h 4118 2016-03-08 13:51:00Z amarentes $
/// $HeadURL: https://./include/TwoAuctionMechanismGeneralized.h $
// ===========================================================
//
// Copyright (C) 2012-2014, all rights reserved by
// - System and Computing Engineering, Universidad de los Andes
//
// More information and contact:
// https://www.uniandes.edu.co/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; version 2 of the License
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//
// ===========================================================


#ifndef TWO_AUCTION_MECHANISM_GENERALIZED_H
#define TWO_AUCTION_MECHANISM_GENERALIZED_H

#include "config.h"
#include "stdincpp.h"
#include <cmath>        // std::abs

typedef enum 
{
    INVALID = -1,
    QUADRATURE_WEIGHTS = 0, 
    QUADRATURE_ABSCISSAE
} quadrature_type_t;

typedef enum 
{
    QUADRATURE_LOWER_LIMIT = 0, 
    QUADRATURE_UPPER_LIMIT
} quadrature_limit_type_t;

extern const string QUADRATURE_FILES;

namespace auction {


/**
 * Define methods to execute the two auction mechanism.
 */
class TwoAuctionMechanismGeneralized {

  public:
	
	/*! \short constructor for the class
	 */
	TwoAuctionMechanismGeneralized();
	
	/*! \short destructor for the class
	 */
	~TwoAuctionMechanismGeneralized();
	
	string removeSpaces(string input);
	
	/*! \short gives the abscissae and weights of the hermite quadrature of 20 points.
	 */
	vector<double> hermquad(quadrature_type_t type);
	
	void
	split( vector<string> & theStringVector,  /* Altered/returned value */
		   const  string  & theString,
		   const  string  & theDelimiter);
	
	/** \short load the quadrature weigths and abscissae for n an k.

		@param  n     -- number of samples
		@param  k     -- order statistics

		Return Values:
			The expected abscissae and weights for bl and 1.
	*/
	void 
	LoadQuadrature(int n, int k, quadrature_type_t type, quadrature_limit_type_t limit_type, vector<double> &result);
	
	vector<double> gaussQuadrature0Inf(int n, quadrature_type_t type);
	/**

		\short Calculates the inverse of the min probability function for the H auction.

		@param bl - maximum value in the L auction.
		@param Points - a vector with the points to calculate the inverse

 		@return the inverse.
	*/
	double FhInverse(double bl, double point);


	/**
		\short Calculates the density function of the min probability function for the H auction.
		
		@param bl - maximum value in the L auction. 
		@param points - the point to calculate the density function

		@return density for a point.
	*/
	double fH(double bl, double point);
	
	
	double FLAcum(double bl, double point);
	
	double fL(double bl, double point);
	
	double FLInverse(double bl, double point);
	
	double ProbWithoutReplacement(double N, double C);
	
	/**
		\short Calculates the number of users for the normal points.

		@param NH  -- Maximum number of users
		@param q   -- probability of a user going to the L auction.
		@param Points - a vector with the points to calculate the number of users

		@return N - A vector containing the number of users.
	*/
	vector<int> N_Users(int NH, double q, vector<double> points);

	/**
	* 
		\short calculates the polinomial:
			1/3 - 1/2bl + bl^3/6 - ((1-Q)yadj + QPL)(1/2 - bl + bl^2/2)
  
		@param bl      -- Mininum budget for rich people 
		@param sigma   -- standard deviation for the limiting normal variable
		@param nu      -- mean for the limiting normal variable
		@param y       -- variable value
		@param Q       -- probability given for the auction.
		@param PL      -- reserved price of the L auction.

	*/
	double p11star(double bl, double sigma, double nu, double y, double Q, double PL);	
	
	
	/**
	* \short  calculates the polinomial:
		1/6 - bl^2/2 + bl^3/3 - ((1-Q)yajust + QPL)(1/2 - bl + bl^2/2)
  
	@param bl     -- Mininum budget for rich people 
	@param sigma  -- standard deviation for the limiting normal variable
	@param nu     -- mean for the limiting normal variable
	@param y       -- variable value
	@param Q       -- probability given for the auction.
	@param PL      -- reserved price of the L auction.
	*/
	double p21star(double bl, double sigma, double nu, double y, double Q, double PL);
	
	/**
	*  \short  Calculates the polinomial:
			1/3 - 1/2yadj + yadj^3/6 - ((1-Q)yadj + QPL)(1/2 - yadj + yadj^2/2)
	
		@param bl      -- Mininum budget for rich people 
		@param sigma   -- standard deviation for the limiting normal variable
		@param nu      -- mean for the limiting normal variable
		@param y       -- variable value
		@param Q       -- probability given for the auction.
		@param PL      -- reserved price of the L auction.
	*/
	double p12star(double sigma, double nu, double y, double Q, double PL);

	/**
		\short Calculates the polinomial:
			1/6 - yadj^2/2+ yadj^3/3 - ((1-Q)yadj + QPL)(1/2 -yadj + yadj^/2)
	
		@param bl      -- Mininum budget for rich people 
		@param sigma   -- standard deviation for the limiting normal variable
		@param nu      -- mean for the limiting normal variable
		@param y       -- variable value
		@param Q       -- probability given for the auction.
		@param PL      -- reserved price of the L auction.
	*/
	double p22star(double sigma, double nu, double y, double Q, double PL);

	/** 
	*  \short expectedPayoffHStrategyKUnitsMechanism 
		expected profit for strategy (h,\beta_h) with k units.

		@param 

	*/ 
	double expectedPayoffHStrategyKUnitsMechanism(vector<double> weights, vector<double> abscissae, 
					int NH, int CH, double q , double bl, double PH, double Q, double PL);
	

	/**
	* 
	* \short    expected profit for strategy (l,bl) with k units.

      @param NH   -- Number of users in the H auction.
      @param q    -- Probability of going into the L auction.
      @param bl   -- Maximum budget in the L auction.
      @param CL   -- Number of units auctioneed in the L auction.
	*/
	double expectedPayoffLStrategyKUnits(vector<double> weights, vector<double> abscissae, int NH, int NL, double q , double bl, int CL, double PL);
	
	/**
	  \short Calculates the expected payoff difference between both strategies with mechanism

	  @param NH          -- Maximum number of users in the H auction 
	  @param NL          -- Maximum number of users in the L auction 
	  @param CH          -- Number of units to sell in the H auction 
	  @param CL          -- Number of units to sell in the L auction 
	  @param PH          -- Reserved price in the H auction          
	  @param PL          -- Reserved price in the L auction          
	  @param bl          -- Maximum budget in the L auction          
	  @param Q           -- Probability of receving the PL price in the A auction
	  @param q           -- Probability of a user going to the L auction.

	Return Values:
		The expected value.
	*/
	double gstar(int NH, int NL, int CH, int CL, double PH, double PL, double bl, double Q, double q);
	
	/* \short  Auxiliary function to calculate zeros of a function,
	 * 		   initialize variables used
	 */
	void zeros_initialize(double *a, double *b, double *c, double *d, double *e, double *fa, double *fc );

	/* \short  Auxiliary function to calculate zeros of a function,
	 * 		   exchange the points defining the interval being analyzed
	 */
	void zeros_ext(double *a, double *b, double *c, double *fa, double *fb, double *fc);

	/* \short  Auxiliary function to calculate zeros of a function,
	 * 		   define the current tolerance obtained as a result of the interval.
	 */
	void zeros_tol(double b, double c, double t, double macheps, double *tol, double *m);

	/* \short  Auxiliary function to calculate zeros of a function
	 */
	double zerosWithUnits(int nh, int nl, double bh, double bl, double kh, double kl, 
							double rph, double rpl, double Q, double a, double b, double macheps, double t);


	int zeroin(int nh, int nl, double bh, double bl, double kh, double kl, double rph, double rpl, double Q,  double *x, double *y);
	
	double tolx(double  x);
	
};


} // namespace auction

#endif // TWO_AUCTION_MECHANISM_GENERALIZED_H
