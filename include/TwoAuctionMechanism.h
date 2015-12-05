/// ----------------------------------------*- mode: C++; -*--
/// @file TwoAuctionMechanism.h
/// This file defines functions used for executing the two auction mechanism.
/// ----------------------------------------------------------
/// $Id: TwoAuctionMechanism.h 4118 2015-11-23 14:33:00Z amarentes $
/// $HeadURL: https://./include/TwoAuctionMechanism.h $
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


#ifndef TWO_AUCTION_MECHANISM_H
#define TWO_AUCTION_MECHANISM_H

#include "stdincpp.h"
#include <cmath>        // std::abs

namespace auction {


/**
 * Define methods to execute the two auction mechanism.
 */
class TwoAuctionMechanism {

  public:
	
	/*! \short constructor for the class
	 */
	TwoAuctionMechanism();
	
	/*! \short destructor for the class
	 */
	~TwoAuctionMechanism();
	
  // protected:

  // private:

    /*!
     * \short   Calculates Function F_i(i,p) Defined as:
     * 			  f_i(i,p) = ((p+1)!)^{2} / (p+1+i)! * (p+2-i)!

        \arg \c i          i element.
        \arg \c p          p number total of elements.
    */
	double calculateFi(int i, int p);

    /*!
     * \short   Calculates Function G(p) Defined as:
     * 			  G(p) = ((p+1)!)^{2} / (2p+3)!

        \arg \c p          p number total of elements.
    */
	double calculateG( int p );

    /*!
     * \short   Calculates Function I(p) between [0,b] defined as:
     * 			  I(p) = \int_{0}_{b} (y(b + 1 -y)/b)^p f(y) dy
     * 			  	   = ( b - \sum{i=1}^{p+1}f_i(p) b^{i} - g(p)b^{p+2})*(1/(p+1))

        \arg \c b 		Maximum value that the independent variable y might take
    */
	double calculateUniformI(int p, double b);

    /*!
     * \short   Calculates Function I(p) between [0,y] defined as:
     * 			  I(p) = \int_{0}_{y} (y(b + 1 -y)/b)^p f(y) dy

        \arg   \c p		Number of IID variables to include in the maximum disribution.
        	   \c b 	Maximum value that the independent variable y might take
        	   \c y		Integration limit.

    */
	double calculateUniformBoundedI(int p, double b, double y);


    /*!
     * \short   Calculates the combinatory C(n,r)

        \arg   \c n		Total number of elements to choose from
        	   \c r 	number of elements to choose

    */
	long long C(int n, int r);


    /*!
     * \short   Calculates the Function D(n,k,j) defined as:
     * 			  D(n,k,j) = n*C^{n-k}_{j}*C^{n-1}_{k-1}

        \arg   \c n		Total number to choose from.
        	   \c k 	Number of object to subtract from n
        	   \c j		Nuber of elements of choose fron n-k.

    */
	double calculateD(int n, int k, int j);

    /*!
     * \short   Calculates the expected value of the k order statistic
     * 			of a sample with n random variables IID is defined by:
     *
     * 		E[Z_{n}^{k}(b)] = \sum_{j=0}^{n-k} (-1)^{j}*D(n,k,j)*I(k+j-1)

        \arg   \c n		Total number of users.
        	   \c k 	Number of objects to assign
        	   \c j		iterator over the number of users that stay in the auction.

    */
	double calculateExpectedValueK(int n, int k, double b,
									std::map<int,double> &Dvalues);

    /*!
     * \short   Calculates the expected value conditioned on a particular bid
     * 			of the k order statistic of a sample with n random variables IID is defined by:
     *
     * 		E[Z_{n}^{k}(y)] = \sum_{j=0}^{n-k} (-1)^{j}*D(n,k,j)*I(k+j-1, y)

        \arg   \c n		Total number of users.
        	   \c k 	Number of objects to assign
        	   \c j		iterator over the number of users that stay in the auction.

    */
	double calculateExpectedBoundedValueK(int n, int k, double b, double bid,
											std::map<int,double> &Dvalues);

    /*!
     * \short   Calculates the conditioned probability of winning with a particular bid
     * 			of the k order statistic of a sample with n random variables IID is defined by:
     *
     * 		Y[Z_{n}^{k}(y)] = \sum_{j=0}^{n-k} (-1)^{j}*D(n,k,j)*(w^{k+j}(b + 1 -w)^k+j)/((k+j)*b^{k+j})

        \arg   \c n		Total number of users.
        	   \c k 	Number of objects to assign
        	   \c j		iterator over the number of users that stay in the auction.

    */
	double calculateWinProbability(int n, int k, double b, double bid,
									std::map<int,double> &Dvalues);

    /*!
     * \short   Calculates the expected payoff when a user choose to stay
     * 			in the high budget auction and there is only one unit to auction.
     *
		\arg   \c n		Total number of users.
		\arg   \c b 	Maximum value that a user can pay for the unit
		\arg   \c bid   Proposed bid from the user.
		\arg   \c q 	Probability that a user decides to compete in the low budget auction.
    */
	double expectedProfitHStrategy(int n, double b, double bid, double q);

    /*!
     * \short   Calculates the expected payoff when a user choose to stay
     * 			in the high budget auction and there is more than one unit to auction.
     *
		\arg   \c n		Total number of users.
		\arg   \c k		Total number of units to auction.
		\arg   \c b 	Maximum value that a user can pay for any unit
		\arg   \c rph 	reserved price to pay.
		\arg   \c bid   Proposed bid from the user.
		\arg   \c q 	Probability that a user decides to compete in the low budget auction.
    */
	double expectedProfitHStrategyWithUnits(int n, int k, double b, double rp, double bid, double q);

    /*!
     * \short   Calculates the expected payoff when a high budget user
     * 			choose the strategy L(low budget auction) and there is
     * 			more than one unit to auction.
     *
		\arg   \c nh	Total number of high budget users.
		\arg   \c nl	Total number of low budget users.
		\arg   \c bh	Maximum value that a high budget user can pay for any unit
		\arg   \c bl	Maximum value that a low budget user can pay for any unit
		\arg   \c bid   Proposed bid from the user.
		\arg   \c q 	Probability that a user decides to compete in the low budget auction.
    */
	double expectedProfitLStrategy(int nh, int nl, double bh, double bl, double bid, double q);

	/*!
     * \short   Calculates the payoff when a high budget user choose
     * 			the strategy L(low budget auction), the number of high budget 
     * 			users going into the low budget auction is nh, and there are
     * 			kl units to auction (nh<kl).
     *
		\arg   \c nh	Total number of high budget users going into the low budget auction.
		\arg   \c nl	Total number of low budget users.
		\arg   \c kl	Total number of units to auction.
		\arg   \c bl	Maximum value that a user can pay being a low budget user.
		\arg   \c rpl	Reserved price for the low budget auction.
		\arg   \c bid	user's bid .
	*/
	double expectedProfitLStrategyEnoughQuantities(int nh, int nl, int kl, double bl, double rlp, double bid );
	
	/*!
     * \short   Calculates the payoff when a high budget user choose
     * 			the strategy L(low budget auction), the number of high budget 
     * 			users going into the low budget auction is nh, and there are
     * 			kl units to auction (nh>=kl).
     *
		\arg   \c nh	Total number of high budget users going into the low budget auction.
		\arg   \c nl	Total number of low budget users.
		\arg   \c kl	Total number of units to auction.
		\arg   \c bl	Maximum value that a user can pay being a low budget user.
		\arg   \c bid	user's bid .
	*/	
	double expectedProfitLStrategyNotEnoughQuantities(int nh, int nl, int kl, double bl, double bid);

    /*!
     * \short   Calculates the expected payoff when a high budget user choose
     * 			the strategy L(low budget auction) and there is
     * 			more than one unit to auction.
     *
		\arg   \c nh	Total number of high budget users.
		\arg   \c nl	Total number of low budget users.
		\arg   \c bh	Maximum value that a high budget user can pay for any unit
		\arg   \c bl	Maximum value that a low budget user can pay for any unit
		\arg   \c kh	Units in the high budget auction
		\arg   \c kl	Units in the low budget auction
		\arg   \c rph	reseve price for the high budget auction
		\arg   \c rpl	reseve price for the low budget auction
		\arg   \c bid   Proposed bid from the user.
		\arg   \c q 	Probability that a user decides to compete in the low budget auction.
    */
	double expectedProfitLStrategyWithUnits(int nh, int nl, double bh, double bl,
											int kh, int kl, double rph, double rpl, 
											double bid, double q);

    /*!
     * \short   Calculates the difference between the H strategy and the L strategy
     *
		\arg   \c nh	Total number of high budget users.
		\arg   \c nl	Total number of low budget users.
		\arg   \c bh	Maximum value that a high budget user can pay for any unit
		\arg   \c bl	Maximum value that a low budget user can pay for any unit
		\arg   \c bid   Proposed bid from the user.
		\arg   \c q 	Probability that a user decides to compete in the low budget auction.
    */
	double functionF(int nh, int nl, double bh, double bl, double bid, double q);
	
    /*!
     * \short   Calculates the difference between the H strategy and the L strategy when it is using quantities.
     *
		\arg   \c nh	Total number of high budget users.
		\arg   \c nl	Total number of low budget users.
		\arg   \c bh	Maximum value that a high budget user can pay for any unit
		\arg   \c bl	Maximum value that a low budget user can pay for any unit
		\arg   \c kh	Number of units in the high budget auction.
		\arg   \c kl	Number of units in the low budget auction.
		\arg   \c rph	reseve price for the high budget auction
		\arg   \c rpl	reseve price for the low budget auction
		\arg   \c bid   Proposed bid from the user.
		\arg   \c q 	Probability that a user decides to compete in the low budget auction.
    */
	double functionFWithUnits(int nh, int nl, double bh, double bl, int kh, int kl, double rph, double rpl, double bid, double q);


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
	double zeros(int nh, int nl, double bh, double bl, double bid, double a, double b, double macheps, double t);

	/* \short  Auxiliary function to calculate zeros of a function
	 */
	double zerosWithUnits(int nh, int nl, double bh, double bl, double kh, double kl, 
							double rph, double rpl, double bid, double a, double b, double macheps, double t);


};


} // namespace auction

#endif // TWO_AUCTION_MECHANISM_H
