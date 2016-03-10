/// ----------------------------------------*- mode: C++; -*--
/// @file TwoAuctionMechanismGeneralized.cpp
/// This file implements the functions used for executing the two auction mechanism.
/// When NH and NL tend to infinity.
/// ----------------------------------------------------------
/// $Id: TwoAuctionMechanismGeneralized.cpp 2558 2016-03-08 11:25:00 amarentes $
/// $HeadURL: https://./src/TwoAuctionMechanismGeneralized.cpp $
// ===========================================================
//
// Copyright (C) 2012-2016, all rights reserved by
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

#include "TwoAuctionMechanismGeneralized.h"
#include "Error.h"
#include <algorithm>
#include <ctype.h>
#include <iostream>
#include <cmath>


namespace auction
{

const string QUADRATURE_FILES = DEF_SYSCONFDIR "/quadrature";

}

using namespace auction;

TwoAuctionMechanismGeneralized::TwoAuctionMechanismGeneralized()
{

}

TwoAuctionMechanismGeneralized::~TwoAuctionMechanismGeneralized()
{

}

string TwoAuctionMechanismGeneralized::removeSpaces(string input)
{
  int length = input.length();
  for (int i = 0; i < length; i++) {
     if(input[i] == ' ')
     {
        input.erase(i, 1);
         length--;
         i--;
     }
  }
  return input;
}

vector<double> TwoAuctionMechanismGeneralized::hermquad(quadrature_type_t type)
{
	vector<double> vect_return;
	
	if (type == QUADRATURE_ABSCISSAE){


		vect_return.push_back(5.38748089001123286199e+00);
		vect_return.push_back(4.60368244955074427298e+00);
		vect_return.push_back(3.94476404011562521040e+00);
		vect_return.push_back(3.34785456738321632688e+00);
		vect_return.push_back(2.78880605842813048055e+00);
		vect_return.push_back(2.25497400208927552311e+00);
		vect_return.push_back(1.73853771211658620678e+00);
		vect_return.push_back(1.23407621539532300786e+00);
		vect_return.push_back(7.37473728545394358719e-01);
		vect_return.push_back(2.45340708300901249903e-01);
		vect_return.push_back(-2.45340708300901249903e-01);
		vect_return.push_back(-7.37473728545394358719e-01);
		vect_return.push_back(-1.23407621539532300786e+00);
		vect_return.push_back(-1.73853771211658620678e+00);
		vect_return.push_back(-2.25497400208927552311e+00);
		vect_return.push_back(-2.78880605842813048055e+00);
		vect_return.push_back(-3.34785456738321632688e+00);
		vect_return.push_back(-3.94476404011562521040e+00);
		vect_return.push_back(-4.60368244955074427298e+00);
		vect_return.push_back(-5.38748089001123286199e+00);
 
	}

	if (type == QUADRATURE_WEIGHTS){

		vect_return.push_back(2.22939364553415129254e-13);
		vect_return.push_back(4.39934099227318055366e-10);
		vect_return.push_back(1.08606937076928169398e-07);
		vect_return.push_back(7.80255647853206369398e-06);
		vect_return.push_back(2.28338636016353967260e-04);
		vect_return.push_back(3.24377334223786183217e-03);
		vect_return.push_back(2.48105208874636108814e-02);
		vect_return.push_back(1.09017206020023320014e-01);
		vect_return.push_back(2.86675505362834129720e-01);
		vect_return.push_back(4.62243669600610089640e-01);
		vect_return.push_back(4.62243669600610089640e-01);
		vect_return.push_back(2.86675505362834129720e-01);
		vect_return.push_back(1.09017206020023320014e-01);
		vect_return.push_back(2.48105208874636108814e-02);
		vect_return.push_back(3.24377334223786183217e-03);
		vect_return.push_back(2.28338636016353967260e-04);
		vect_return.push_back(7.80255647853206369398e-06);
		vect_return.push_back(1.08606937076928169398e-07);
		vect_return.push_back(4.39934099227318055366e-10);
		vect_return.push_back(2.22939364553415129254e-13);
	}
	
	return vect_return;
}

vector<double> TwoAuctionMechanismGeneralized::gaussQuadrature0Inf(int n, quadrature_type_t type)
{
	vector<double> val_return;

    if (type == QUADRATURE_ABSCISSAE){

		if (n==2){
						
			val_return.push_back(0.300193931060839);
			val_return.push_back(1.25242104533372);
		}
		
		if (n==3){

			val_return.push_back(0.190554149798192);
			val_return.push_back(0.848251867544577);
			val_return.push_back(1.79977657841573);
			
		}

		if (n==4){

			val_return.push_back(0.133776446996068);
			val_return.push_back(0.624324690187190);
			val_return.push_back(1.34253782564499);
			val_return.push_back(2.26266447701036);
		
		}

		if (n==5){

			val_return.push_back(0.100242151968216);
			val_return.push_back(0.482813966046201);
			val_return.push_back(1.06094982152572);
			val_return.push_back(1.77972941852026);
			val_return.push_back(2.66976035608766);
			
		}
		
		if (n==6){

			val_return.push_back(0.0786006594130979);
			val_return.push_back(0.386739410270631);
			val_return.push_back(0.866429471682044);
			val_return.push_back(1.46569804966352);
			val_return.push_back(2.17270779693900);
			val_return.push_back(3.03682016932287);
					
		}

	}	
	if (type == QUADRATURE_WEIGHTS){

		if (n==2){
			val_return.push_back(0.640529179684379);
			val_return.push_back(0.245697745768379);
			
		}
		
		if (n==3){
			val_return.push_back(0.446029770466658);
			val_return.push_back(0.396468266998335);
			val_return.push_back(0.0437288879877644);

		}

		if (n==4){
			val_return.push_back(0.325302999756919);
			val_return.push_back(0.421107101852062);
			val_return.push_back(0.133442500357520);
			val_return.push_back(0.00637432348625728);
		
		}

		if (n==5){
			val_return.push_back(0.248406152028443);
			val_return.push_back(0.392331066652399);
			val_return.push_back(0.211418193076057);
			val_return.push_back(0.0332466603513439);    
			val_return.push_back(0.000824853344515628);
			
		}
		
		if (n==6){
			val_return.push_back(0.196849675488598);
			val_return.push_back(0.349154201525395);
			val_return.push_back(0.257259520584421);
			val_return.push_back(0.0760131375840057); 
			val_return.push_back(0.00685191862513596);
			val_return.push_back(0.0000984716452019267);
					
		}		
	}
	
	return val_return;

}

void
TwoAuctionMechanismGeneralized::split( vector<string> & theStringVector,  /* Altered/returned value */
									   const  string  & theString,
									   const  string  & theDelimiter)
{

    size_t  start = 0, end = 0;

    while ( end != string::npos)
    {
        end = theString.find( theDelimiter, start);

        // If at end, use length=maxLength.  Else use length=end-start.
        theStringVector.push_back( theString.substr( start,
                       (end == string::npos) ? string::npos : end - start));

        // If at end, use start=maxSize.  Else use start=end+delimiter.
        start = (   ( end > (string::npos - theDelimiter.size()) )
                  ?  string::npos  :  end + theDelimiter.size());
    }
}

/**
 val = loadQuadrature()

 load the quadrature weigths and abscissae for n an k.

 Arguments:
  n     -- number of samples
  k     -- order statistics

 Return Values:
  The expected abscissae and weights for bl and 1.
*/

void 
TwoAuctionMechanismGeneralized::LoadQuadrature(int n, int k, quadrature_type_t type, quadrature_limit_type_t limit_type, vector<double> &result)
{

    std::fstream fs;
    string filename;
    ostringstream ss; 
    
    if ( type == QUADRATURE_WEIGHTS){
		ss << QUADRATURE_FILES << "/Weight_NH_" << n << "_K_" << k;
		filename = ss.str();
	}

    if ( type == QUADRATURE_ABSCISSAE){
		ss << QUADRATURE_FILES << "/Abscissae_NH_" << n << "_K_" << k;
		filename = ss.str();
	}
		
	if (filename.size() > 0){
	
		fs.open(filename.c_str(), std::fstream::in);
		
		if (limit_type == QUADRATURE_LOWER_LIMIT){
			vector<string> w0b;
			string tline_0b;
			std::getline(fs, tline_0b);
			split(w0b, tline_0b,string(","));
			for (size_t k=0; k < w0b.size(); k++){
			   w0b[k] = removeSpaces(w0b[k]);
			   if ( !w0b[k].empty()){
					result.push_back(atof(w0b[k].c_str()));
			   }
			}
		}
		else
		{
			vector<string> w01;
			string tline_0b, tline_01; 
			std::getline(fs, tline_0b);
			std::getline(fs, tline_01);
			
			split(w01, tline_01,string(","));
			for (size_t k=0;  k < w01.size(); k++){
				w01[k] = removeSpaces(w01[k]);
				if ( !w01[k].empty()){
					result.push_back(atof(w01[k].c_str())); 
				}
			}
		}
		
		fs.close();
	}
}

 
/**
  FH_inverse(bl, point)

  Calculates the inverse of the min probability function for the H auction.

 Arguments:
	bl - maximum value in the L auction.
	Points - a vector with the points to calculate the inverse

 Return Values:
	the inverse.
*/
double TwoAuctionMechanismGeneralized::FhInverse(double bl, double point)
{
	

	double y = 1 - point;
	double x = 1 - sqrt(pow((1-bl),2) * y);
	
	return x;

}

/**
X = fH(bl, point)

 Calculates the density function of the min probability function for the H auction.

 Arguments:
  bl - maximum value in the L auction. 
  points - the point to calculate the density function

 Return Values:
	X - density for a point.
*/
double TwoAuctionMechanismGeneralized::fH(double bl, double point)
{

	double tmp = pow(1-bl,2);
	double x1 = 2 - (2*point);
	double x = x1/tmp;
	
	return x;
}

/**
 X = fL(Bl, Points)

 Calculates the density function of the min probability function for the L auction.

 Arguments:
  Bl - maximum value 
  Points - a vector with the points to calculate the density function

 Return Values:
  X - A column vector containing the density.
*/
double TwoAuctionMechanismGeneralized::fL(double bl, double point)
{
	double val_return;
	
	val_return = (bl + 1) - (2*point);
	val_return = val_return/bl;
	
	return val_return;	
}
/**
 Calculates the inverse of the min probability function for the L auction.

 Arguments:
  Bl - maximum value 
  Points - a vector with the points to calculate the inverse

 Return Values:
  X - inverse of FL.
*/
double TwoAuctionMechanismGeneralized::FLInverse(double bl, double point)
{

	double y = 4*point*bl;
	double x = (1+bl); 
	x = x - sqrt(pow(1+bl,2) - y);
	x = x / 2;

	return x;
}

double TwoAuctionMechanismGeneralized::FLAcum(double bl, double point)
{
	double val;
	
	val = (point*bl) + point - (pow(point,2)); 
	val = val / bl;
	
	return val;
} 

double TwoAuctionMechanismGeneralized::ProbWithoutReplacement(double N, double C)
{    
    double prob = 0;
    
    for (int j=0; j <= C-1; j++){
        prob = prob + (1/(N-j));
    }
    
    return prob;
	
}

/**
	N_Users(Points)

 Calculates the number of users for the normal points.

 Arguments:
	NH  -- Maximum number of users
	q   -- probability of a user going to the L auction.
	Points - a vector with the points to calculate the number of users

 Return Values:
	N - A vector containing the number of users.
*/
vector<int> TwoAuctionMechanismGeneralized::N_Users(int NH, double q, vector<double> points)
{
	vector<double> mean;
	vector<double> desv;
	vector<int> N;
	
	double meanTmp, desvTmp;

	for (size_t i=0; i < points.size(); i++){
		meanTmp = NH*(1-q);
		mean.push_back(meanTmp);
		desvTmp = sqrt(2*NH*q*(1-q));
		desv.push_back(desvTmp);
		N.push_back( ceil( meanTmp - (points[i]*desvTmp)));
	}
	
	
	for (size_t i=0; i < N.size(); i++){
		if (N[i] < 0){
			N[i] = 0;
		} else if ( N[i] > NH ){
			N[i] = NH;
		}
	}
	
	return N;
}


/**
 * 
 calculates the polinomial:
    1/3 - 1/2bl + bl^3/6 - ((1-Q)yadj + QPL)(1/2 - bl + bl^2/2)
  Parameters
   bl      -- Mininum budget for rich people 
   sigma   -- standard deviation for the limiting normal variable
   nu      -- mean for the limiting normal variable
   y       -- variable value
   Q       -- probability given for the auction.
   PL      -- reserved price of the L auction.

*/
double TwoAuctionMechanismGeneralized::p11star(double bl, double sigma, double nu, double y, double Q, double PL)
{
    
    double yajst, val1, val2, val;
    
    yajst = ((sqrt(2.0)*sigma*y) + nu);
    val1 = (1.0/3.0) - (bl/2.0) + (pow(bl,3.0)/6.0); 
    val2 = ((1.0 - Q)*yajst) + (Q*PL);
    val2 = val2*((1.0/2.0) - bl + (pow(bl,2.0)/2.0));
    val = val1 - val2;
    
    return val;
}

/**
 * 

calculates the polinomial:
   1/6 - bl^2/2 + bl^3/3 - ((1-Q)yajust + QPL)(1/2 - bl + bl^2/2)
  Parameters
   bl      -- Mininum budget for rich people 
   sigma   -- standard deviation for the limiting normal variable
   nu      -- mean for the limiting normal variable
   y       -- variable value
   Q       -- probability given for the auction.
   PL      -- reserved price of the L auction.
*/
double TwoAuctionMechanismGeneralized::p21star(double bl, double sigma, double nu, double y, double Q, double PL)
{
	
	double yajust, val1, val2, val;
    
    yajust = (sqrt(2.0)*sigma*y + nu);
    val1 = (1.0/6.0) - (pow(bl,2.0)/2.0) + (pow(bl,3.0)/3.0);
    val2 = ((1.0-Q)*yajust) + (Q*PL);
    val2 = val2*(1.0/2.0 - bl + (pow(bl,2.0)/2.0));
    val = val1 - val2;
    
    return val;
    
}

/**
 * 
Calculates the polinomial:
   1/3 - 1/2yadj + yadj^3/6 - ((1-Q)yadj + QPL)(1/2 - yadj + yadj^2/2)
  Parameters
   bl      -- Mininum budget for rich people 
   sigma   -- standard deviation for the limiting normal variable
   nu      -- mean for the limiting normal variable
   y       -- variable value
   Q       -- probability given for the auction.
   PL      -- reserved price of the L auction.
*/
double TwoAuctionMechanismGeneralized::p12star(double sigma, double nu, double y, double Q, double PL)
{
    
    double yajst, val1, val2, val;
    
    yajst = (sqrt(2.0)*sigma*y + nu);
    val1 = (1.0/3.0) - ((1.0/2.0)*yajst) + (pow(yajst,3.0)/6.0);
    val2 = ((1.0 - Q)*yajst) + (Q*PL);
    val2 = val2*((1.0/2.0) - yajst + (pow(yajst,2.0)/2.0));
    
    val = val1 - val2;
    return val;
}

/**
 calculates the polinomial:
   1/6 - yadj^2/2+ yadj^3/3 - ((1-Q)yadj + QPL)(1/2 -yadj + yadj^/2)
  Parameters
   bl      -- Mininum budget for rich people 
   sigma   -- standard deviation for the limiting normal variable
   nu      -- mean for the limiting normal variable
   y       -- variable value
   Q       -- probability given for the auction.
   PL      -- reserved price of the L auction.
*/

double TwoAuctionMechanismGeneralized::p22star(double sigma, double nu, double y, double Q, double PL)
{
	double yadj, value1, value2, val;
	
    yadj = (sqrt(2.0)*sigma*y) + nu;
    value1 = (1.0/6.0) - (pow(yadj,2.0)/2.0) + (pow(yadj,3.0)/3.0);
    value2 = ((1.0 - Q)*yadj) + (Q*PL);
    value2 = value2*((1.0/2.0) - yadj + (pow(yadj,2.0)/2.0));
    
    val = value1 - value2;
    
    return val;
}

/** 
 *  expectedPayoffHStrategyKUnitsMechanism 
    expected profit for strategy (h,\beta_h) with k units.

    Parameters:

 */ 
double TwoAuctionMechanismGeneralized::expectedPayoffHStrategyKUnitsMechanism(vector<double> weights, vector<double> abscissae, 
					int NH, int CH, double q , double bl, double PH, double Q, double PL)
{
	int n = 6;
	vector<double> weights0inf = gaussQuadrature0Inf(n, QUADRATURE_WEIGHTS );
	vector<double> abscissae0inf = gaussQuadrature0Inf(n, QUADRATURE_ABSCISSAE );

    // calculates the number of people in the H Auction for every point. 
    vector<int> Nusers = N_Users(NH,q,abscissae);
    
    // calculates kn,p, nu, sigma (the statistical order to find).
    int index = 0;
    double value = 0.0;
    double acum5 = 0.0;
    double pi = 4.0*atan(1.0);
    
    vector<int> N, K, ind;
    vector<double> p, yo, fyo, nu, sigma;
    int nTmp, kTmp;
    double pTmp, yoTmp, fyoTmp, sigmaTmp, tmp, tmp2;
        
    for (size_t j=0 ; j < Nusers.size(); j++)
    {
        if ( Nusers[j] > CH ){
			nTmp = Nusers[j];
			kTmp = Nusers[j] - CH;
			pTmp = static_cast<double>(kTmp) / static_cast<double>(nTmp);
			yoTmp = FhInverse(bl, pTmp);
			fyoTmp = fH(bl,yoTmp);
			sigmaTmp = sqrt(((pTmp*(1-pTmp))/ (Nusers[j]*pow(fyoTmp,2))));
			
						 	
            N.push_back(nTmp);
            K.push_back(kTmp);
            p.push_back(pTmp);
            yo.push_back(yoTmp);
            fyo.push_back(fyoTmp);
            nu.push_back(yoTmp);
            sigma.push_back(sigmaTmp);
                        
            ind.push_back(j);
            index = index + 1;
        } else {
            tmp = (1.0-pow(bl,2.0)) / (2.0*(1.0-bl));
            tmp = tmp - ((1.0-Q)*PH) - (Q*PL);
            tmp = tmp * weights[j];
            acum5 = acum5 + tmp;
        }
    }
        
    acum5 = acum5 / sqrt(pi);
     
     
    if (index >= 1){
        for (size_t j=0 ; j < K.size(); j++){

            vector<double> weights0bl;
            LoadQuadrature(N[j],K[j], QUADRATURE_WEIGHTS, QUADRATURE_LOWER_LIMIT, weights0bl );
            
            vector<double> abscissae0bl;
            LoadQuadrature(N[j],K[j], QUADRATURE_ABSCISSAE, QUADRATURE_LOWER_LIMIT, abscissae0bl );
            
            vector<double> weights01; 
            LoadQuadrature(N[j],K[j], QUADRATURE_WEIGHTS, QUADRATURE_UPPER_LIMIT, weights01);
            
            vector<double> abscissae01;
            LoadQuadrature(N[j],K[j], QUADRATURE_ABSCISSAE, QUADRATURE_UPPER_LIMIT, abscissae01);

            double acum1a = 0.0;
            double acum1b = 0.0;
            for (size_t l=0 ; l < weights0inf.size(); l++){
                tmp = p11star(bl, sigma[j], nu[j], abscissae0inf[l], Q, PL);
                acum1a = acum1a + (weights0inf[l] * tmp);
                tmp2 = p21star(bl, sigma[j], nu[j], abscissae0inf[l], Q, PL);
                acum1b = acum1b + (weights0inf[l] * tmp2);
            }
                        
            double acum2a = 0.0;
            double acum2b = 0.0;
            for (size_t l=0; l < weights0bl.size(); l++){
                tmp = p11star(bl, sigma[j], nu[j], abscissae0bl[l], Q, PL);
                acum2a = acum2a + (weights0bl[l] * tmp);
                tmp = p21star(bl, sigma[j], nu[j], abscissae0bl[l], Q, PL);
                acum2b = acum2b + (weights0bl[l] * tmp);
            }
            
            double acum3a = 0.0;
            double acum3b = 0.0;
            for (size_t l=0; l < weights0bl.size(); l++){
                tmp = p12star(sigma[j], nu[j], abscissae0bl[l], Q, PL);
                acum3a = acum3a + (weights0bl[l] * tmp);
                tmp = p22star(sigma[j], nu[j], abscissae0bl[l], Q, PL);
                acum3b = acum3b + (weights0bl[l] * tmp);
            }

            double acum4a = 0.0;
            double acum4b = 0.0;
            for (size_t l=0; l < weights01.size(); l++){
                tmp = p12star(sigma[j], nu[j], abscissae01[l], Q, PL);
                acum4a = acum4a + (weights01[l] * tmp);
                tmp = p22star(sigma[j], nu[j], abscissae01[l], Q, PL);
                acum4b = acum4b + (weights01[l] * tmp);
            }
            
            double totacuma = (acum1a  - acum2a) + acum3a + acum4a;
            double totacumb = (acum1b  - acum2b) + acum3b + acum4b;

            value = value + (weights[ind[j]]*(totacuma+totacumb));
        }
    }
        
    value = value / pow(sqrt(pi),2);
    value = value / pow(1-bl,2);
    
    value = value + acum5;

	return value;
}

/**
 * 
 * % expectedPayoffLStrategyKUnits 
%    expected profit for strategy (l,bl) with k units.
%  Parameters:
%      NH   -- Number of users in the H auction.
%      q    -- Probability of going into the L auction.
%      bl   -- Maximum budget in the L auction.
%      CL   -- Number of units auctioneed in the L auction.
*/
double TwoAuctionMechanismGeneralized::expectedPayoffLStrategyKUnits(vector<double> weights, vector<double> abscissae, int NH, int NL, double q , double bl, int CL, double PL )
{
    
    double pi = 4.0*atan(1.0);
    vector<int> Nusers;
    vector<int> unitsForLUsers;
    
    // calculates the number of people in the H Auction for every point. 
    Nusers = N_Users(NH,q,abscissae);

    for (size_t k=0; k < Nusers.size(); k++){
        if ( CL >= (NH-Nusers[k])){
            unitsForLUsers.push_back( CL - (NH-Nusers[k]));
        } else{
            unitsForLUsers.push_back( 0 );
        }
    }
	vector<double> mean;
	
	
    for (size_t k=0;  k < Nusers.size(); k++)
    {
		int Kn = NL - unitsForLUsers[k];
		double pn = static_cast<double>(Kn)/static_cast<double>(NL);
		double mu = FLInverse(bl, pn);
		double fyo = fL(bl,mu);
		double mu2 = (Kn - (NL*pn)) / (NL*fyo);
		mean.push_back(mu + mu2); // This value is the expected value of YL
	}
	
    // Calculates the probability of winning the units between high budget
    // users
    vector<double> prob;
    double ExpecNL;
    
    for (size_t k=0; k < Nusers.size(); k++){
          ExpecNL = ceil((1.0 - FLAcum(bl, PL))*NL);
          double probTmp = ProbWithoutReplacement(ExpecNL + NH-Nusers[k] + 1 , CL); 
          prob.push_back( probTmp );
    }
      
    double acum = 0.0;
    for (size_t k=0; k < Nusers.size(); k++){
        double tmp = 1.0/3.0 - (bl/2.0) + (pow(bl,3.0)/6.0) ;
        tmp = tmp - (mean[k]*(1.0/2.0 -bl + (pow(bl,2.0)/2.0) ));
        tmp = tmp*prob[k];
        acum = acum + (tmp*weights[k]);
    }  
    
    double acum2 = 0.0;
    for (size_t k=0; k < Nusers.size(); k++){
        double tmp = 1.0/6.0 - (pow(bl,2.0)/2.0) + (pow(bl,3.0)/3.0) ;
        tmp = tmp - (mean[k]*(1.0/2.0 -bl + (pow(bl,2.0)/2.0) ));
        tmp = tmp*prob[k];
        acum2 = acum2 + (tmp*weights[k]);
    }  
                
    double value = (acum + acum2)/(pow(1.0-bl,2.0));
    value = value/sqrt(pi);
    	
	return value;
} 

/**
 Calculates the expected payoff difference between both strategies with
 mechanism

 Arguments:
  NH          -- Maximum number of users in the H auction 
  NL          -- Maximum number of users in the L auction 
  CH          -- Number of units to sell in the H auction 
  CL          -- Number of units to sell in the L auction 
  PH          -- Reserved price in the H auction          
  PL          -- Reserved price in the L auction          
  bl          -- Maximum budget in the L auction          
  Q           -- Probability of receving the PL price in the A auction
  q           -- Probability of a user going to the L auction.

 Return Values:
  The expected value.
*/
double TwoAuctionMechanismGeneralized::gstar(int NH, int NL, int CH, int CL, double PH, double PL, double bl, double Q, double q)
{
    
    double val1, val2, val;
    
    vector<double> Weights = hermquad( QUADRATURE_WEIGHTS);
    vector<double> Abscissae = hermquad( QUADRATURE_ABSCISSAE);
    
    val1 = expectedPayoffHStrategyKUnitsMechanism(Weights, Abscissae, NH, CH, q , bl, PH, Q, PL );
    val2 = expectedPayoffLStrategyKUnits(Weights, Abscissae, NH, NL, q , bl, CL, PL );
    
    val = val1 - val2;
	
	return val;
}



void 
TwoAuctionMechanismGeneralized::zeros_initialize(double *a, double *b, double *c, double *d, double *e, double *fa, double *fc )
{
	*c = *a;
	*fc = *fa;
	*e = *b - *a;
	*d = *b - *a ;
}

void TwoAuctionMechanismGeneralized::zeros_ext(double *a, double *b, double *c, double *fa, double *fb, double *fc)
{
	double bOld = *b;
	double cOld = *c;
	double fbOld = *fb;
	double fcOld = *fc;

	if (std::abs(fcOld) < std::abs(fbOld)){
		*a = bOld;
		*b = cOld;
		*c = bOld;
		*fa = fbOld;
		*fb = fcOld;
		*fc = fbOld;
	}
}


void TwoAuctionMechanismGeneralized::zeros_tol(double b, double c, double t, double macheps, double *tol, double *m)
{
	*tol = (2*macheps*std::abs(b)) + t;
	*m = 0.5*(c-b);
}


// This procedure returns a zero x of a function f in the given interval [a,b], to within a tolerance
// 6macheps |x| + 2t, where macheps is the relative machine precision and t is a positive tolerance. The procedure
// assumes that f(a) and f(b) have different signs.
double TwoAuctionMechanismGeneralized::zerosWithUnits(int nh, int nl, double bh, double bl, double kh, double kl, 
													  double rph, double rpl, double Q, double a,
													  double b, double macheps, double t)
{
	// cout << "starting zerosWithUnits - Parameters nh:" << nh << " nl:" << nl
	//	 << " bh:" << bh << " bl:" << bl << " kh:" << kh << " kl:" << kl
	//	 << " rph:" << rph << " rpl:" << rpl << " bid:" << bid 
	//	 << " a:" << a << " b:" << b << " macheps:" << macheps << " t:" << t << endl;

	// Define local variables to be used.
	double c,d,e,fa,fb,fc,tol,m,p,q,r,s;

	// Variables initialization
	fa = gstar(nh, nl, kh, kl, rph, rpl, bl, Q, a);
	fb = gstar(nh, nl, kh, kl, rph, rpl, bl, Q, b);

	// Check the precondition (fa.fb <= 0)
	if ((fa*fb) > 0){
		throw Error("The function evaluated in a and b does not have different sign");
	}

	zeros_initialize(&a, &b, &c, &d, &e, &fa, &fc );
	zeros_ext(&a, &b, &c, &fa, &fb, &fc);
	zeros_tol(b, c, t, macheps, &tol, &m);

	while ((std::abs(m) > tol) && (fb != 0)){

		//std::cout << "a:" << a << " fa:" << fa << " b:" << b << " fb:" << fb << " c:" << c << " fc:" << fc << "m:"<< m << std::endl;
		// Verify if a bisection is forced
		if ((std::abs(e) < tol) || (std::abs(fa) <= std::abs(fb))){
			d = m;
			e = m;
		} else {
			s = fb / fa;
			if (a == c){ // Linear interpolation
				p = 2*m*s;
				q = 1 - s;
			} else { // Inverse quadratic interpolation
				q = fa / fc;
				r = fb/fc;
				p = s*((2*m*q*(q-r)) - ((b-a)*(r-1)) );
				q = (q - 1)*(r - 1)*(s - 1);
			}
			if (p > 0){
				q = -1;
			} else {
				p = -p;
			}

			s = e;
			e = d;

			if (((2*p) < ((3*m*q) - (std::abs(tol*q)))) && (p < std::abs(0.5*s*q)) ){
				d = p/q;
			} else {
				d = m;
				e = m;
			}
		}

		a = b;
		fa = fb;
		if (std::abs(d) > tol){
			b = b + d;
		} else {
			if (m > 0) {
				b = b + tol;
			} else {
				b = b - tol;
			}
		}

		fb = gstar(nh, nl, kh, kl, rph, rpl, bl, Q, b);
		c = a;
		fc = fa;
		if ( (fb > 0) ){
			//std::cout << "initialize and exchange" << " a:" << a << " fa:" << fa << " b:" << b << " fb:" << fb <<  " c:" << c << " fc:" << fc << std::endl;
			zeros_initialize(&a, &b, &c, &d, &e, &fa, &fc );
			zeros_ext(&a, &b, &c, &fa, &fb, &fc);
			//std::cout << "after initialize and exchange" << " a:" << a << " fa:" << fa << " b:" << b << " fb:" << fb <<  " c:" << c << " fc:" << fc << std::endl;
			zeros_tol(b, c, t, macheps, &tol, &m);
		} else {
			//std::cout << "exchange" << " a:" << a << " fa:" << fa << " b:" << b << " fb:" << fb <<  " c:" << c << " fc:" << fc << std::endl;
			zeros_ext(&a, &b, &c, &fa, &fb, &fc);
			//std::cout << "after exchange" << " a:" << a << " fa:" << fa << " b:" << b << " fb:" << fb <<  " c:" << c << " fc:" << fc << std::endl;
			zeros_tol(b, c, t, macheps, &tol, &m);
		}
	}

	double zero = b;
	return zero;
}

double TwoAuctionMechanismGeneralized::tolx(double  x)
{
	return fabs(x)*1.0e-6+1.0e-6;
}


int TwoAuctionMechanismGeneralized::zeroin(int nh, int nl, double bh, double bl, double kh, double kl, double rph, double rpl, double Q,  double *x, double *y)
{
	int ext,extrapolate;
	double c,fc,b,fb,a,fa,d,fd,fdb,fda,w,mb,tol,m,p,q;

	b = *x;
	fb= gstar(nh, nl, kh, kl, rph, rpl, bl, Q, *x);
	a = *x = *y;
	fa= gstar(nh, nl, kh, kl, rph, rpl, bl, Q, *x);
	c=a;
	fc=fa;
	ext=0;
	extrapolate=1;
	while (extrapolate) {
		if (fabs(fc) < fabs(fb)) {
			if (c != a) {
				d=a;
				fd=fa;
			}
			a=b;
			fa=fb;
			b = *x =c;
			fb=fc;
			c=a;
			fc=fa;
		}
		tol=tolx(*x);
		m=(c+b)*0.5;
		mb=m-b;
		if (fabs(mb) > tol) {
			if (ext > 2)
				w=mb;
			else {
				if (mb == 0.0)
					tol=0.0;
				else
					if (mb < 0.0) tol = -tol;
				p=(b-a)*fb;
				if (ext <= 1)
					q=fa-fb;
				else {
					fdb=(fd-fb)/(d-b);
					fda=(fd-fa)/(d-a);
					p *= fda;
					q=fdb*fa-fda*fb;
				}
				if (p < 0.0) {
					p = -p;
					q = -q;
				}
				w=(p<FLT_MIN || p<=q*tol) ? tol : ((p<mb*q) ? p/q : mb);
			}
			d=a;
			fd=fa;
			a=b;
			fa=fb;
			*x = b += w;
			fb=gstar(nh, nl, kh, kl, rph, rpl, bl, Q, *x);
			if ((fc >= 0.0) ? (fb >= 0.0) : (fb <= 0.0)) {
				c=a;
				fc=fa;
				ext=0;
			} else
				ext = (w == mb) ? 0 : ext+1;
		} else
			break;
	}
	*y = c;
	return ((fc >= 0.0) ? (fb <= 0.0) : (fb >= 0.0));
}
