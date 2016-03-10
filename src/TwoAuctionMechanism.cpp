/// ----------------------------------------*- mode: C++; -*--
/// @file TwoAuctionMechanism.cpp
/// This file implements the functions used
///           for executing the two auction mechanism.
/// ----------------------------------------------------------
/// $Id: TwoAuctionMechanism.cpp 2558 2015-11-23 11:23:00 amarentes $
/// $HeadURL: https://./src/TwoAuctionMechanism.cpp $
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


#include "TwoAuctionMechanism.h"
#include "Error.h"

using namespace auction;

TwoAuctionMechanism::TwoAuctionMechanism()
{

}

TwoAuctionMechanism::~TwoAuctionMechanism()
{

}

double TwoAuctionMechanism::calculateFi(int i, int p)
{
	// we check that the number i be in the interval [1,p+1]
	
	if ((i < 1) || (i > p+1)){
		throw Error("Given parameter i must be in the interval [1,p+1]");
	}
	
	double val_return = 0;
	double one = 1.0;
	
	if (i == 1){
		val_return = (one / (p + 2));
	}
	else { 
		val_return = (one / (p + 2));
		double num = p + 1;
		double dem = p + 3;
		
		for (int index = 2; index <= i; ++index)
		{
			val_return = val_return * (num / dem );
			num = num - 1;
			dem = dem + 1;
		} 
	}
	
	return val_return;
}


double TwoAuctionMechanism::calculateFiPrime(int p, int i)
{
	// we check that the number i be in the interval [1,p]
	
	if ((i < 1) || (i > p)){
		throw Error("Given parameter i must be in the interval [1,p]");
	}
	
	double val_return = 0;
	double one = 1.0;
	
	if (i == 1){
		val_return = (one / (p + 1));
	}
	else { 
		val_return = (one / (p + 1));
		double num = p;
		double dem = p + 2;
		
		for (int index = 2; index <= i; ++index)
		{
			val_return = val_return * (num / dem );
			num = num - 1;
			dem = dem + 1;
		} 
	}
	
	return val_return;
}

double TwoAuctionMechanism::calculateG( int p )
{
	double val_return = 0;
	val_return = calculateFi(p+1, p);
	val_return = (val_return / ( (2*p) + 3));
	
	return val_return;
}

double TwoAuctionMechanism::calculateGPrime( int p )
{
	double val_return = 0;
	val_return = calculateFiPrime(p, p);
	val_return = (val_return / ( (2*p) + 1));
	
	return val_return;
}

double 
TwoAuctionMechanism::calculateUniformI(int p, double b)
{
	
	// Verify that parameters are in the correct domain.
	
	if ( p < 0 ){
		throw Error("Given parameter p must be greater or equal to zero");
	}
	
	if ((b > 1) || (b < 0)){
		throw Error("Given parameter p must be in range [0,1]");
	}
	
	double valI = 0;
	
	for (int index = 1; index <= p+1; index++ )
	{
		double fip = calculateFi(index, p);
		double temp = fip * pow (b, index);
		valI = valI + temp;
	}
	
	double gp = calculateG(p) * pow (b, p+2);
	
	valI = valI + gp;
	
	valI = (b - valI );

	valI = valI / (p+1);
	
	return valI;
}

double 
TwoAuctionMechanism::calculateE(int p, double b, double c)
{
	// Verify that parameters are in the correct domain.
	
	if ( p < 0 ){
		throw Error("Given parameter p must be greater or equal to zero");
	}
	
	if ((b > 1) || (b < 0)){
		throw Error("Given parameter b must be in range [0,1]");
	}

	if ((c > 1) || (c < 0)){
		throw Error("Given parameter c must be in range [0,1]");
	}
	
	double valE = 0;
	
	for (int index = 1; index <= p; index++ )
	{
		double fiprime = calculateFiPrime(p, index);
		int index2 = p + index;
		int index3 = p - index + 1;
		double tempUpper = pow(c, index2) * pow(2-c,index3);
		double tempLower = pow(b, index2) * pow(2-b,index3);
				
		valE = valE + fiprime*(tempUpper-tempLower);
	}
	
	int index4 = (2*p) + 1;
	double gp = calculateGPrime(p) * ( pow(c, index4) - pow(b, index4));
	
	valE = valE + gp;
					
	return valE;
}

double TwoAuctionMechanism::FunctionP(int p, double b, double c)
{
	double Fy = 0.0;
	double valReturn = 0.0;
		
	if (c > b){
		Fy = (2*c) - b - pow(c,2);
		Fy = Fy /(1-b);
	} else {
		Fy = c;
	}
	
	valReturn = pow(Fy,p+1);
	valReturn = valReturn * c;
	
	return valReturn;
}

double TwoAuctionMechanism::FunctionO(int p, double val)
{
	double val_return = 0;

	if ( p < 0 ){
		throw Error("Given parameter p must be greater or equal to zero");
	}
	
	if ((val > 1) || (val < 0)){
		throw Error("Given parameter val must be in range [0,1]");
	}

	val_return = pow ( val, p); 
	val_return = val_return / p;
	
	return val_return;
}

double TwoAuctionMechanism::FunctionFy(double b, double c)
{
	double Fy = (2*c) - b - pow(c,2);
	Fy = Fy /(1-b);
	
	return Fy;
	
}

double TwoAuctionMechanism::Functiongy(double b, double c)
{
	double val_return = (2-(2*c));
	val_return = val_return /(1-b);
	return val_return;
}

double TwoAuctionMechanism::functiongDerivate(double b)
{
	double val_return = -2.0 / (1-b);
	return val_return;
} 

double TwoAuctionMechanism::FunctionY0(int p, double b, double c)
{
	double val_return = pow(FunctionFy(b, c), p+1);
	
	return val_return;
}

double TwoAuctionMechanism::Derivate1y(int p, double b, double c)
{
	return (p+1)*pow(FunctionFy(b,c), p) * Functiongy(b,c);

}

double TwoAuctionMechanism::Derivate2y(int p, double b, double c)
{
	double val1 = (p+1);
	val1 = val1 * pow(FunctionFy(b,c), p-1);
	val1 = val1 * p;
	val1 = val1 * pow(Functiongy(b,c), 2);
	
	double val2 = (p+1);
	val2 = val2 * pow(FunctionFy(b,c), p);
	val2 = val2 * functiongDerivate(b);
	
	return val1 + val2;
}

double TwoAuctionMechanism::Derivate3y(int p, double b, double c)
{
	double val1 = (p+1);
	val1 = val1 * pow(FunctionFy(b,c), p-2);
	val1 = val1 * p;
	val1 = val1 * pow(Functiongy(b,c), 3);
	val1 = val1 * (p-1);
	
	double val2 = 3*(p+1);
	val2 = val2 * pow(FunctionFy(b,c), p-1);
	val2 = val2 * p;
	val2 = val2 * Functiongy(b,c);
	val2 = val2 * functiongDerivate(b);
	
	return val1 + val2;
}

double TwoAuctionMechanism::Derivate4y(int p, double b, double c)
{
    double val1 = (p+1)*p;
    val1 = val1 * pow(FunctionFy(b,c), p-3);
    val1 = val1 * (p-1);
    val1 = val1 * pow(Functiongy(b,c), 4);
    val1 = val1 * (p-2);
    
    double val2 = 6*(p+1);
    val2 = val2 * pow(FunctionFy(b,c), p-2);
    val2 = val2 * p; 
	val2 = val2 * pow(Functiongy(b,c), 2);
	val2 = val2 * (p-1);
	val2 = val2 * functiongDerivate(b);
	
	double val3 = 3*(p+1);
	val3 = val3 * pow(FunctionFy(b,c), p-1);
	val3 = val3 * p;
	val3 = val3 * pow(functiongDerivate(b),2);
    
    return val1 + val2 + val3;
}

double TwoAuctionMechanism::Derivate5y(int p, double b, double c)
{

    double val1 = (p+1)*(p);
    val1 = val1 * pow(FunctionFy(b,c), p-4);
    val1 = val1 * (p-1);
    val1 = val1 * pow(Functiongy(b,c), 5);
    val1 = val1 * (p-2)*(p-3);
    
    double val2 = 10*(p+1)*(p);
    val2 = val2 * pow(FunctionFy(b,c), p-3);
    val2 = val2 * (p-1);
	val2 = val2 * pow(Functiongy(b,c), 3);
	val2 = val2 * (p-2);
	val2 = val2 * functiongDerivate(b);
	
	double val3 = 15*(p+1);
	val3 = val3 * pow(FunctionFy(b,c), p-2);
	val3 = val3 * p;
	val3 = val3 * Functiongy(b,c);
	val3 = val3 * (p-1);
	val3 = val3 * pow(functiongDerivate(b),2);
    
    return val1 + val2 + val3;

}

double TwoAuctionMechanism::Derivate6y(int p, double b, double c)
{
    double val1 = (p+1)*(p);
    val1 = val1 * pow(FunctionFy(b,c), p-5);
    val1 = val1 *(p-1)*(p-2);
    val1 = val1 * pow(Functiongy(b,c), 6);
    val1 = val1 *(p-3)*(p-4);
    
    double val2 = 15*(p+1)*(p);
    val2 = val2 * pow(FunctionFy(b,c), p-4);
    val2 = val2 *(p-1)*(p-2);
	val2 = val2 * pow(Functiongy(b,c), 4);
	val2 = val2 * (p-3);
	val2 = val2 * functiongDerivate(b);
	
	double val3 = 45*(p+1)*(p);
	val3 = val3 * pow(FunctionFy(b,c), p-3);
	val3 = val3 * (p-1);
	val3 = val3 * pow(Functiongy(b,c), 2);
	val3 = val3 * (p-2);
	val3 = val3 * pow(functiongDerivate(b),2);

	double val4 = 15*(p+1)*(p);
	val4 = val4 * pow(FunctionFy(b,c), p-2);
	val4 = val4 * (p-1);
	val4 = val4 * pow(functiongDerivate(b),3);
    
    return val1 + val2 + val3 + val4;

}

double TwoAuctionMechanism::calculateStep(int p, double b, double c, double tolerance)
{
	double nplusone = 7.0;
	double val = Derivate6y(p,b,c);
	double fact6 = 720.0;
	val = abs(val);
	val = (fact6 * nplusone) / val;
	val = val * tolerance;
	val = pow( val, 1.0 / nplusone );
	
	return val;
}

void 
TwoAuctionMechanism::CalculateEvaluationPointsNumericalV(int p, double b, double start, 
						double end, double tolerance, set<double> *points)
{
	
	double center = (start + end) / 2.0;
	double h = calculateStep(p, b, center, tolerance);
	
	// cout << "center:" << center << "h:" << h << endl;
	
	if ((center - h) < start ){
		points->insert(end);
		points->insert(start);
	} else { 
		// we have to divide the interval, because h is small.
		double startInt = center - h;
		double endInt = center + h;
		points->insert(startInt);
		points->insert(endInt);
		CalculateEvaluationPointsNumericalV(p,b,start, startInt, tolerance, points);
		CalculateEvaluationPointsNumericalV(p,b,endInt, end, tolerance, points);
	}	
}

double TwoAuctionMechanism::AproximateV(int p, double b, double middle, double value)
{
	double val0 = FunctionY0(p, b, middle);
	val0 = val0 / 1.0;
	val0 = val0 * (value - middle);
	
	double val1 = Derivate1y(p, b, middle);
	val1 = val1 / 2.0;
	val1 = val1 * pow((value - middle),2.0);
	
	double val2 = Derivate2y(p, b, middle);
	val2 = val2 / 6.0;
	val2 = val2 * pow(value - middle, 3.0);

	double val3 = Derivate3y(p, b, middle);
	val3 = val3 / 24.0;
	val3 = val3 * pow(value - middle, 4.0);

	double val4 = Derivate4y(p, b, middle);
	val4 = val4 / 120.0;
	val4 = val4 * pow(value - middle, 5.0);

	double val5 = Derivate5y(p, b, middle);
	val5 = val5 / 720.0;
	val5 = val5 * pow(value - middle, 6.0);

	double val6 = Derivate6y(p, b, middle);
	val6 = val6 / 5040.0;
	val6 = val6 * pow(value - middle, 7.0);

	return val0 + val1 + val2 + val3 + val4 + val5 + val6;
}

double TwoAuctionMechanism::CalculateNumericalV(int p, double b, double c, double tolerance)
{
	std::set<double> points;
	std::set<double>::iterator it;
	double start = 0;
	double end = 0;
	double val = 0;
	
	CalculateEvaluationPointsNumericalV(p, b, b, c, tolerance, &points);
	
	if (points.size() < 2){
		throw Error("undetermined error");
	} else {
		it = points.begin();
		start = *it;
		it++;
		end = *it;
		for ( ; it != points.end(); ){	
			// calculate the value for start and end.
			double middle = (end + start)/ 2.0;
			double valend = AproximateV(p, b, middle, end);
			double valstart = AproximateV(p, b, middle, start);
			val = val + valend - valstart;
			
			// cout << "start:" << start << ":val:" << valstart << ":end:" << end <<  ":val:" << valend << endl;
			
			start = end;
			it++;
			if ( it != points.end() ){
				end = *it;
			} else {
				break;
			}
		}
	}
	
	return val;
}
double TwoAuctionMechanism::FunctionQ(int p, double b, double c)
{

	if ( p < 0 ){
		throw Error("Given parameter p must be greater or equal to zero");
	}
	
	if ((b > 1) || (b < 0)){
		throw Error("Given parameter b must be in range [0,1]");
	}

	if ((c > 1) || (c < 0)){
		throw Error("Given parameter c must be in range [0,1]");
	}

	if ( c < b ){
		throw Error("Given parameter c must be less than b");
	}
	
	double val_return = 0;
	double negativeb = (b*-1) / (1-b);
		
	double valK0 = pow(negativeb,p)*(c-b);
		
	for ( int k=1; k<=p; k++){
		
		double valK = calculateE(k, b, c);		
		
		//cout << "K:" << k << ":b:" << b << ":c:" << c << ":E(k, b, c):" << valK << endl;
		for (int i = 0; i < p-k; i++){
			valK = valK * ((p-i)*(negativeb)) / (p-k-i);
		}

		// cout << "k:" << k << ":valK:" << valK << endl;

		valK = valK / pow (1-b,k);
		val_return = val_return + valK;
		//cout << "k:" << k << ":valK:" << valK << ":ValReturn:" << val_return << endl;
	}
	
	//cout << "val_return:" << val_return << "valK0:" << valK0 << endl;
		
	val_return = val_return + valK0;
	
	//cout << "val_return:" << val_return << endl;

			
	return val_return;
}

double TwoAuctionMechanism::FunctionV(int p, double b, double c)
{	
	double val_return = 0;
	double tolerance =  0.00000001;
	
	if ( p >= 15 ) {
		val_return = CalculateNumericalV(p, b, c, tolerance);
	} else {	
		val_return = FunctionQ(p, b, c);
	}	
	return  val_return;
}

double TwoAuctionMechanism::calculateUniformIPrime(int p, double b, double c)
{
	double valReturn = 0;

	if ( p < 0 ){
		throw Error("Given parameter p must be greater or equal to zero");
	}
	
	if ((b > 1) || (b < 0)){
		throw Error("Given parameter b must be in range [0,1]");
	}

	if ((c > 1) || (c < 0)){
		throw Error("Given parameter c must be in range [0,1]");
	}
	
	valReturn = FunctionP(p,b,c);
		
	if (c > b){

		valReturn = valReturn - FunctionO(p+2,b);		
		valReturn = valReturn - FunctionV(p+1,b,c);
				
	} else {
				
		valReturn = valReturn - FunctionO(p+2,c);
	}	

	valReturn = valReturn / (p+1);
	
	return valReturn;
}

double TwoAuctionMechanism::calculateUniformBoundedI(int p, double b, double y)
{
	// Verify that parameters are in the correct domain.

	if ( p < 0 ){
		throw Error("Given parameter p must be greater than or equal to zero");
	}

	if ((b > 1) || (b < 0)){
		throw Error("Given parameter p must be in range [0,1]");
	}

	if ( y < 0 ){
		throw Error("Given parameter y must be greater than or equal to zero");
	}

	if ( y > b ){
		throw Error("Given parameter y must be less than parameter b");
	}


	double valI = 0;

	for (int index = 1; index <= p+1; index++ )
	{
		double fip = calculateFi(index, p);
		double temp = fip * pow ((b+1-y), p+2-index);
		temp = temp *pow(y,index);
		valI = valI + temp;
	}


	double gp = calculateG(p) * pow (y, p+2);

	valI = valI + gp;
	valI = (y * pow((b+1-y), p+1) - valI );
	valI = valI*pow(y/b,p+1);
	valI = valI / (p+1);
	
	//std::cout << "calculateUniformBoundedI " << " p:" << p << " b:" << b << " y:" << y << valI << std::endl;
	
	return valI;
}

double TwoAuctionMechanism::calculateD(double init, int n, int k, int j)
{
	
	// Verify the parameters
	if (n <= 0){
		throw Error("Given parameter n must be greater than zero");
	}

	if (k < 0){
		throw Error("Given parameter k must be greater than or equal to zero");
	}

	if (k > n){
		throw Error("Given parameter k must be less than or equal to n");
	}

	if (j < 0){
		throw Error("Given parameter j must be greater than or equal to zero");
	}

	if (j > (n-k)){
		throw Error("Given parameter j must be less than or equal to n-k");
	}

	double val_return = init;
	
	int t = n-k-j+1;  // This is always greater or equal than zero.
	
	// calculates the maximum of (n-t,k-1,j)
	int max = n-t;
	if (max <= k-1){
		max = k-1;
	}
	if (max <= j){
		max = j;
	}
	
	// creates the index for the three number to multiply
	int indexk;
	if ((k-1) == 0){
		indexk = 1;
	} else {
		indexk = k-1;
	}

	int indexj;
	if (j == 0){
		indexj = 1;
	} else {
		indexj = j;
	}

	int indexn = n;
	
	for (int index = 0; index <= max; index++ ){
		val_return = val_return * indexn / (indexk*indexj);
		
		if (indexk > 1){ indexk--; }
		if (indexj > 1){ indexj--; }
		if (indexn > t){
			indexn--;
		} else {
			indexn = 1;
		}
	}
	return val_return;
}

double TwoAuctionMechanism::calculateExpectedValueK(int n, int k, double b)
{
	//Verify the parameters given.
	if (n <= 0){
		throw Error("Given parameter n must be greater than zero");
	}

	if (k < 0){
		throw Error("Given parameter k must be greater than or equal to zero");
	}

	if (k > n){
		throw Error("Given parameter k must be less than or equal to n");
	}

	if ((b > 1) || (b < 0)){
		throw Error("Given parameter b must be in range [0,1]");
	}


	double expectedVal = 0;
	
	for (int j=0; j <= (n-k); j++ ){
		int p = 0;
		double i_p = 0;
		p = k+j-1;
		i_p = calculateUniformI(p,b);
		i_p = calculateD(i_p, n, k, j);
		expectedVal = expectedVal + i_p*pow(-1,j);
		
		//std::cout << "expected j:" << j << " p:" << p << " D:" << (iter->second) << " i_p:" << i_p << " val:" << expectedVal << std::endl;
	}
	
	return expectedVal;
}

double TwoAuctionMechanism::calculateExpectedBoundedValueK(int n, int k, double b, double bid, std::map<int,double> &Dvalues)
{
	//std::cout << "calculateExpectedBoundedValueK:" << " n:" << n << " k:" << k << " b:" << b << " bid:" << bid << std::endl; 
	
	//Verify the parameters given.
	if (n <= 0){
		throw Error("Given parameter n must be greater than zero");
	}

	if (k < 0){
		throw Error("Given parameter k must be greater than or equal to zero");
	}

	if (k > n){
		throw Error("Given parameter k:%d must be less than or equal to n:%d", k, n);
	}

	if ((b > 1) || (b < 0)){
		throw Error("Given parameter b must be in range [0,1]");
	}

	if (bid < 0){
		throw Error("Parameter bid must be greater than zero");
	}

	if (bid > b){
		throw Error("Parameter bid must be less than or equal to parameter b");
	}

	double acumExpectedVal = 0;

	for (int j=0; j <= (n-k); j++ ){

		int p = k+j-1;
		double i_p = calculateUniformBoundedI(p,b, bid);
		i_p = calculateD(i_p, n, k, j);
		double expectedVal = i_p*pow(-1,j);
		std::cout << "expectedVal:" << expectedVal << std::endl; 
		acumExpectedVal = acumExpectedVal + expectedVal;
	}
	
	//std::cout << "calculateExpectedBoundedValueK:" << " out:" << acumExpectedVal << std::endl; 
	
	return acumExpectedVal;
}

double 
TwoAuctionMechanism::calculateExpectedBoundedValueKPrime(int n, int k, double b, double bid)
{

	std::cout << "calculateExpectedBoundedValueKPrime:" << " n:" << n << " k:" << k << " b:" << b << " bid:" << bid << std::endl; 
	
	//Verify the parameters given.
	if (n <= 0){
		throw Error("Given parameter n must be greater than zero");
	}

	if (k < 0){
		throw Error("Given parameter k must be greater than or equal to zero");
	}

	if (k > n){
		throw Error("Given parameter k:%d must be less than or equal to n:%d", k, n);
	}

	if ((b > 1) || (b < 0)){
		throw Error("Given parameter b must be in range [0,1]");
	}

	if (bid < 0){
		throw Error("Parameter bid must be greater than zero");
	}

	double acumExpectedVal = 0;

	for (int j=0; j <= (n-k); j++ ){
				
		int p = k+j-1;
		double q_p = calculateUniformIPrime(p, b, bid);
		double expectedVal = calculateD(q_p, n, k, j);
		expectedVal = expectedVal * pow(-1,j);
		std::cout << "j:" << j << ":p:" << p << ":calculateIntegralPrime:" 
				<< q_p << ":expectedVal:" << expectedVal << std::endl; 
		
		acumExpectedVal = acumExpectedVal + expectedVal;
	}
	
	//std::cout << "calculateExpectedBoundedValueK:" << acumExpectedVal << std::endl; 
	
	return acumExpectedVal;
	
}


double TwoAuctionMechanism::calculateWinProbability(int n, int k, double b, double bid, std::map<int,double> &Dvalues)
{
	
	//std::cout << "calculateWinProbability " << "n:" << n << " k:" << k << " b:" << b << " bid:" << bid << std::endl;
	
	double probabilityVal = 0;
	for (int j=0; j <= (n-k); j++ ){

		double probi = (bid*(b+1-bid))/b;
		probi = pow(probi,k+j) / (k+j);
		probi = calculateD(probi, n, k, j);
		probabilityVal = probabilityVal + (probi*pow(-1,j));
	}
	
	//std::cout << "output calculateWinProbability " << probabilityVal << std::endl;
	
	return probabilityVal;
}

double TwoAuctionMechanism::calculateWinProbabilityPrime(int n, int k, double b, double bid)
{
	double Fy = 0.0;
	double minusFy = 0.0;
	double intern = 1.0;
	double acum = 0.0; 
	double valReturn = 0.0;
		
	if (bid > b){
		Fy = (2*bid) - b - pow(bid,2);
		Fy = Fy /(1-b);
		minusFy = 1.0 - Fy;
	} else {
		Fy = bid;
		minusFy = 1.0 - Fy;
	}
			
	for (int j=0; j <= (n-k); j++ ){
		intern = 1.0;
		for ( int s = 1; s <= j; s++){
			
			double tmp = (k+s-1);
			tmp = tmp / s;
			intern = intern * tmp*(minusFy);
		}
				
		acum = acum + intern;
	}
		
	valReturn = acum * pow(Fy,k);

	return valReturn;
}

long long TwoAuctionMechanism::C(int n, int r)
{
    std::vector< std::vector<long long> > C(2, std::vector<long long> (r + 1, 0));

    for (int i = 0; i <= n; i++)
    {
        for (int k = 0; k <= r && k <= i; k++)
        {
            if (k == 0 || k == i)
                C[i & 1][k] = 1;
            else
                C[i & 1][k] = (C[(i - 1) & 1][k - 1] + C[(i - 1) & 1][k]);
        }
    }
    return C[n & 1][r];
}

double TwoAuctionMechanism::expectedProfitHStrategy(int n, double b, double bid, double q)
{
	// Calculates the expected value for a unique object as a function of q
	double sumProfit = 0;
	double profit = 0;
	for ( int k = 0; k < n; k++ ){
		int numPeople = n-k;

		std::map<int, double> Dvalues;

		double winProb = calculateWinProbabilityPrime(numPeople, numPeople, b, bid);
		double expecVal = calculateExpectedBoundedValueKPrime(numPeople, numPeople, b, bid);
		double initProb = pow(q,k)*pow(1-q,n-k)*C(n, std::min(k,n-k));
		profit = initProb*winProb*bid - initProb*expecVal;
		sumProfit = sumProfit + profit;
		//std::cout << "K:" << k << ":WinProb:" << winProb << ":ExpecVal:" << 
		//		expecVal << ":initProb:" << initProb << ":profit:" << profit << ":sumProfit" << sumProfit << std::endl;
	}

	return sumProfit;
}

double 
TwoAuctionMechanism::expectedProfitHStrategyWithUnits(int nh, int kh, double bh, double bl, double rp, double bid, double q)
{
	
	//std::cout << "expectedProfitHStrategyWithUnits nh:" << nh << " kh:" << kh << " bh:" << bh << std::endl;
	
	// Calculates the expected value for the k objects being auctioned as a function of q
	double sumProfit = 0;
	double profit = 0;
	
	// j is the index that indicates the number of people going to the low budget auction.
	for ( int j = 0; j <= nh; j++ ){
		
		int numPeople = nh-j;
		
		double initProb = pow(q,j)*pow(1-q,nh-j)*C(nh, std::min(j,nh-j));
		
		if ( numPeople <= kh ) {
			profit = initProb*(bid - rp);
		} 
		else {
			
			double winProb = calculateWinProbabilityPrime(numPeople, numPeople - kh, bl, bid);
			double expecVal = calculateExpectedBoundedValueKPrime(numPeople, numPeople - kh, bh, bid);
			
			//std::cout << "j:" << j << "WinProb:" << winProb << " ExpectedBoundedKValue:" << expecVal << std::endl;
		
			profit = initProb*((winProb*bid) - expecVal);
			
		}
		sumProfit = sumProfit + profit;
		//std::cout << "j:" << j << " initProb:" << initProb << " profit:" << profit << "sumProfit:" << sumProfit << std::endl;
	}

	return sumProfit;
}

double 
TwoAuctionMechanism::expectedProfitLStrategy(int nh, int nl, double bh, double bl, double bid, double q)
{
	double EYl = nl * calculateUniformI(nl-1, bl);

	double sumProfit = 0;
	for ( int k = 0; k < nh; k++ ){
		double initProb = pow(q,k)*pow(1-q,nh-k)*C(nh, std::min(k,nh-k));
		double profit = initProb * (bid - EYl) / (k+1);
		sumProfit = sumProfit + profit;
		// std::cout << "K:" << k << " initProb:" << initProb << " profit:" << profit << "sumProfit" << sumProfit << std::endl;
	}

	return sumProfit;
}


double 
TwoAuctionMechanism::expectedProfitLStrategyEnoughQuantities(int nh, int nl, int kl, double bl, double rpl, double bid )
{
	// Verify that parameters are correct.
	if (nh >= kl ){
		throw Error("The number of high budget users cannot exceed kl parameter");
	}
	
	if (nh < 0){
		throw Error("The number of high budget users must non negative");
	}

	if (nl <= 0){
		throw Error("The number of low budget users must be positive");
	}

	if (kl <= 0){
		throw Error("The number of units must be positive");
	}

	if ((bl < 0) || (bl > 1)){
		throw Error("The maximum value that low budget users can pay must lie in [0,1]");
	}

	if ((bid < 0) || (bid > 1)){
		throw Error("The bid must be in [0,1]");
	}

	if ((nl + nh) > kl ){
		
		// The auction should be executed.
		
		int orderk = nl-(kl-nh);
				
		return bid - calculateExpectedValueK(nl, orderk, bl);
		
	} else {
		//Not enough users, all users pay the reserved price.
		return bid - rpl;
	}
}

double
TwoAuctionMechanism::expectedProfitLStrategyNotEnoughQuantities(int nh, int nl, int kl, double bl, double bid)
{	
	
	// Verify that parameters are correct.
	if (nh <= 0){
		throw Error("The number nh:%d of high budget users must be positive", nh);
	}	

	if (kl <= 0){
		throw Error("The number kl:%d of unit being auctioneed must be positive", kl);
	}	
	
	if (nh < kl){
		throw Error("The number of high budget users:%d going to the low budget auction must be greater than Kl:%d", nh, kl);
	}	
	
	double val_return = 0;
	double dnh = nh;
	double dkl = kl;
		
	val_return = bid - (nl*calculateUniformI(nl-1,bl));
	val_return = val_return * (dkl/dnh);
	
	return val_return;
}

double 
TwoAuctionMechanism::expectedProfitLStrategyWithUnits(int nh, int nl, double bh, double bl, int kh, int kl, double rph, double rpl, double bid, double q)
{

	double sumProfit = 0;
	for ( int j = 0; j < nh; j++ ){
		double initProb = pow(q,j)*pow(1-q,nh-j)*C(nh, std::min(j,nh-j));
		double profit = 0;
		if (j < kl){ 
			profit = initProb * expectedProfitLStrategyEnoughQuantities(j, nl, kl, bl, rpl, bid );
		} else {
			profit = initProb * expectedProfitLStrategyNotEnoughQuantities(j, nl, kl, bl, bid);
		}	
		sumProfit = sumProfit + profit;
		// std::cout << "K:" << k << " initProb:" << initProb << " profit:" << profit << "sumProfit" << sumProfit << std::endl;
	}

	return sumProfit;
}

double 
TwoAuctionMechanism::functionF(int nh, int nl, double bh, double bl, double bid, double q)
{
	 return expectedProfitHStrategy(nh, bh, bid, q) - expectedProfitLStrategy( nh, nl, bh, bl, bid, q);
}

double
TwoAuctionMechanism::functionFWithUnits(int nh, int nl, double bh, double bl, int kh, int kl, double rph, double rpl, double bid, double q)
{
	return expectedProfitHStrategyWithUnits(nh, kh, bh, bl, rph, bid, q) - 
	       expectedProfitLStrategyWithUnits(nh, nl, bh, bl, kh, kl, rph, rpl, bid, q);
}

void 
TwoAuctionMechanism::zeros_initialize(double *a, double *b, double *c, double *d, double *e, double *fa, double *fc )
{
	*c = *a;
	*fc = *fa;
	*e = *b - *a;
	*d = *b - *a ;
}

void TwoAuctionMechanism::zeros_ext(double *a, double *b, double *c, double *fa, double *fb, double *fc)
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

void TwoAuctionMechanism::zeros_tol(double b, double c, double t, double macheps, double *tol, double *m)
{
	*tol = (2*macheps*std::abs(b)) + t;
	*m = 0.5*(c-b);
}

// This procedure returns a zero x of a function f in the given interval [a,b], to within a tolerance
// 6macheps |x| + 2t, where macheps is the relative machine precision and t is a positive tolerance. The procedure
// assumes that f(a) and f(b) have different signs.
double TwoAuctionMechanism::zeros(int nh, int nl, double bh, double bl, double bid, double a, double b, double macheps, double t)
{
	// Define local variables to be used.
	double c,d,e,fa,fb,fc,tol,m,p,q,r,s;

	// Variables initialization
	fa = functionF(nh, nl, bh, bl, bid, a);
	fb = functionF(nh, nl, bh, bl, bid, b);

	// Check the precondition (fa.fb <= 0)
	if ((fa*fb) > 0){
		throw Error("The function evaluated in a and b does not have different sign");
	}

	zeros_initialize(&a, &b, &c, &d, &e, &fa, &fc );
	zeros_ext(&a, &b, &c, &fa, &fb, &fc);
	zeros_tol(b, c, t, macheps, &tol, &m);

	while ((std::abs(m) > tol) && (fb != 0)){

		//std::cout << "a:" << a << " fa:" << fa << " b:" << b << " fb:" << fb << " c:" << c << " fc:" << fc << std::endl;
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

		fb = functionF(nh, nl, bh, bl, bid, b);
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


// This procedure returns a zero x of a function f in the given interval [a,b], to within a tolerance
// 6macheps |x| + 2t, where macheps is the relative machine precision and t is a positive tolerance. The procedure
// assumes that f(a) and f(b) have different signs.
double TwoAuctionMechanism::zerosWithUnits(int nh, int nl, double bh, double bl, double kh, double kl, 
											double rph, double rpl, double bid, double a, 
											  double b, double macheps, double t)
{
	// cout << "starting zerosWithUnits - Parameters nh:" << nh << " nl:" << nl
	//	 << " bh:" << bh << " bl:" << bl << " kh:" << kh << " kl:" << kl
	//	 << " rph:" << rph << " rpl:" << rpl << " bid:" << bid 
	//	 << " a:" << a << " b:" << b << " macheps:" << macheps << " t:" << t << endl;

	// Define local variables to be used.
	double c,d,e,fa,fb,fc,tol,m,p,q,r,s;

	// Variables initialization
	fa = functionFWithUnits(nh, nl, bh, bl, kh, kl, rph, rpl, bid, a);
	fb = functionFWithUnits(nh, nl, bh, bl, kh, kl, rph, rpl, bid, b);

	// Check the precondition (fa.fb <= 0)
	if ((fa*fb) > 0){
		throw Error("The function evaluated in a and b does not have different sign");
	}

	zeros_initialize(&a, &b, &c, &d, &e, &fa, &fc );
	zeros_ext(&a, &b, &c, &fa, &fb, &fc);
	zeros_tol(b, c, t, macheps, &tol, &m);

	while ((std::abs(m) > tol) && (fb != 0)){

		//std::cout << "a:" << a << " fa:" << fa << " b:" << b << " fb:" << fb << " c:" << c << " fc:" << fc << std::endl;
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

		fb = functionFWithUnits(nh, nl, bh, bl, kh, kl, rph, rpl, bid, b);
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
