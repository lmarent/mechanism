#include <sys/types.h>
#include <time.h>     
#include <iostream>
#include <openssl/rand.h>
#include <map>
#include <cmath>
#include <stdio.h>
#include <inttypes.h>
#include "config.h"
#include "stdincpp.h"
#include "ProcError.h"
#include "MiscProcModule.h"
#include "TwoAuctionMechanism.h"
#include "FieldValue.h"

const int MOD_INIT_REQUIRED_PARAMS = 1;

// Variables given as parameters.
uint32_t lastId;
ipap_field_container g_ipap_fields;

/*! auction = 0 if the auction corresponds to low budget 
 * 			= 1 if the auction corresponds to high budget 
 */
float getResourceAvailability( auction::configParam_t *params, int auction )
{
 
#ifdef DEBUG
	 cout << "Starting getResourceAvailability - auction type:" << auction <<  endl;
#endif
	
	// Check the parameter auction type.
	if ((auction < 0) || (auction > 1)){
		throw auction::ProcError(AUM_PROC_PARAMETER_ERROR, 
					"two auction init module - auction type requested is wrong");
	}
	
     float bandwidth = 0;
     int numparams = 0;
     
     while (params[0].name != NULL) {

		
		// in all the application we establish the rates and 
		// burst parameters in bytes
		if (auction == 0){		        
			cout << "in auction param name:" << params[0].name << endl; 
			if (!strcmp(params[0].name, "bandwidth01")) {
				bandwidth = (float) parseFloat( params[0].value );
				numparams++;
			}
		} else {
			if (!strcmp(params[0].name, "bandwidth02")) {
				bandwidth = (float) parseFloat( params[0].value );
				numparams++;
			}
		}		
        params++;
     }
     
     if (numparams == 0)
		throw auction::ProcError(AUM_PROC_PARAMETER_ERROR, 
					"two auction init module - not enought parameters");
	
	if (bandwidth <= 0)
		throw auction::ProcError(AUM_PROC_BANDWIDTH_AVAILABLE_ERROR, 
					"two auction init module - The given bandwidth parameter is incorrect");

#ifdef DEBUG
	cout << "Ending getResourceAvailability - Bandwidth:" << bandwidth << endl;
#endif
	
	return bandwidth;
     
}


double getReservePrice( auction::configParam_t *params, int auction )
{
     double price = 0;
     int numparams = 0;
     
#ifdef DEBUG
     cout << "Starting getReservePrice - auction:" << auction << endl;
#endif

	// Check the parameter auction.
	if ((auction < 0) || (auction > 1)){
		throw auction::ProcError(AUM_PROC_PARAMETER_ERROR, 
					"two auction init module - auction requested is wrong");
	}
    
    while (params[0].name != NULL) {
		// in all the application we establish the rates and 
		// burst parameters in bytes
		if (auction == 0){		        				
			if (!strcmp(params[0].name, "reserveprice01")) {
				price = (double) parseDouble( params[0].value );
				numparams++;
			}
		} else {
			if (!strcmp(params[0].name, "reserveprice02")) {
				price = (double) parseDouble( params[0].value );
				numparams++;
			}
		}
        params++;
    }
     
    if (numparams == 0)
		throw auction::ProcError(AUM_PROC_PARAMETER_ERROR, 
					"two auction init module - not enought parameters");
	
	if (price < 0)
		throw auction::ProcError(AUM_PRICE_RESERVE_ERROR, 
					"two auction init module - The given reserve price is incorrect");
	
#ifdef DEBUG
	cout << "Ending getReservePrice" << price << endl;
#endif
		
	return price;
     
}

double getMaximumValue( auction::configParam_t *params, int auction )
{
     double maximumValue = 0;
     int numparams = 0;
     
#ifdef DEBUG
     cout << "Starting getMaximumValue - auction:" << auction << endl;
#endif

	// Check the parameter auction.
	if ((auction < 0) || (auction > 1)){
		throw auction::ProcError(AUM_PROC_PARAMETER_ERROR, 
					"two auction init module - auction requested is wrong");
	}
    
    while (params[0].name != NULL) {
		// in all the application we establish the rates and 
		// burst parameters in bytes
		if (auction == 0){		        				
			if (!strcmp(params[0].name, "maxvalue01")) {
				maximumValue = (double) parseDouble( params[0].value );
				numparams++;
			}
		} else {
			if (!strcmp(params[0].name, "maxvalue02")) {
				maximumValue = (double) parseDouble( params[0].value );
				numparams++;
			}
		}
        params++;
    }
     
    if (numparams == 0)
		throw auction::ProcError(AUM_PROC_PARAMETER_ERROR, 
					"two auction init module - not enought parameters");
	
	if (maximumValue < 0)
		throw auction::ProcError(AUM_PRICE_RESERVE_ERROR, 
					"two auction init module - The given reserve price is incorrect");
	
#ifdef DEBUG
	cout << "Ending getMaximumValue" << maximumValue << endl;
#endif
		
	return maximumValue;
     
}

time_t getTime( auction::configParam_t *params, string name )
{
     time_t tim = 0;
     int numparams = 0;
     
#ifdef DEBUG
     cout << "get time - field:" << name << endl;
#endif
     
     while (params[0].name != NULL) {
						
        if (!strcmp(params[0].name, name.c_str())) {
			tim = (time_t) parseTime(params[0].value); 
			numparams++;
		}
        params++;
     }
     
     if (numparams == 0)
		throw auction::ProcError(AUM_PROC_PARAMETER_ERROR, 
					"two auction init module - not enought parameters");
	
	if (tim == 0)
		throw auction::ProcError(AUM_DATETIME_NOT_DEFINED_ERROR, 
					"two auction init module - The given time is incorrect");
	
#ifdef DEBUG
	cout << "get time" << tim << endl;
#endif
		
	return tim;
     
}


void auction::initModule( auction::configParam_t *params )
{

	cout <<  "two auction module: start init module" << endl;
	int numparams = 0;
	
	// Bring fields defined for ipap_messages;
	g_ipap_fields.initialize_forward();
    g_ipap_fields.initialize_reverse();
	
	cout << "two auction module: end init module" << endl;

}

void auction::destroyModule( auction::configParam_t *params )
{
#ifdef DEBUG
	fprintf( stdout, "two auction module: start destroy module \n");
#endif


#ifdef DEBUG
	fprintf( stdout, "two auction module: end destroy module \n");
#endif

}


string makeKey(string auctionSet, string auctionName, 
				  string bidSet, string bidName)
{
	return auctionSet + "|" + auctionName + "|" + bidSet + "|" + bidName;
}

string getBidName(string allocationKey)
{
	cout << "start getBidName" << endl;
	
	std::size_t found = allocationKey.find_last_of("|");
	string bidName = allocationKey.substr(found+1);
	
	cout << "ending getBidName:" << bidName << endl;
	return bidName;
}

auction::BiddingObject *
createAllocation( auction::fieldDefList_t *fieldDefs, auction::fieldValList_t *fieldVals,
				  string auctionSet, string auctionName, string bidSet, string bidName, string sessionId, 
				  time_t start, time_t stop, float quantity, double price )
{										  		
#ifdef DEBUG
	fprintf( stdout, "two auction module: start create allocation \n");
#endif

	uint64_t timeUint64;
	
	auction::elementList_t elements;
    auction::optionList_t options;

	auction::fieldList_t elementFields;
	string elementName = "key_1";
	
	// The set for the allocation is the same as the initial bid.
	string allocset = bidSet;
	
	// Create the id given.
	uint32_t lid = getId();
	string allocname = uint32ToString(lid);
	cout << "before calling refidobject" << endl;
	// Insert reference bidding object
	ipap_field fRef = g_ipap_fields.get_field(0, IPAP_FT_REFIDBIDDINGOBJECT);	
	
	fillField(fieldDefs, fieldVals, 0, IPAP_FT_REFIDBIDDINGOBJECT, bidName, &elementFields);

	// Insert quantity
	ipap_field fQuantity = g_ipap_fields.get_field(0, IPAP_FT_QUANTITY);	
	ipap_value_field fVQuantity = fQuantity.get_ipap_value_field( quantity );
	string squantity = fQuantity.writeValue(fVQuantity);
	fillField(fieldDefs, fieldVals, 0, IPAP_FT_QUANTITY, squantity, &elementFields);

#ifdef DEBUG
	cout << "two auction module: start create allocation after quantity" << std::endl;
#endif

	// Insert Unit Value
	ipap_field fvalue = g_ipap_fields.get_field(0, IPAP_FT_UNITVALUE);	
	ipap_value_field fVValue = fvalue.get_ipap_value_field( price );
	string svalue = fvalue.writeValue(fVValue);
	fillField(fieldDefs, fieldVals, 0, IPAP_FT_UNITVALUE, svalue, &elementFields);

#ifdef DEBUG
	cout << "two auction module: start create allocation after unitvalue " << std::endl;
#endif

	string recordId = "Unique";
	fillField(fieldDefs, fieldVals, 0, IPAP_FT_IDRECORD, recordId, &elementFields);
		
	elements[elementName] = elementFields;
	
	// construct the interval with the allocation, based on start datetime 
	// and interval for the requesting auction

	auction::fieldList_t optionFields;

	// Insert start
	ipap_field fStart = g_ipap_fields.get_field(0, IPAP_FT_STARTSECONDS);	
	timeUint64 = *reinterpret_cast<uint64_t*>(&start);
	ipap_value_field fVStart = fStart.get_ipap_value_field( timeUint64 );
	string sstart = fStart.writeValue(fVStart);
	fillField(fieldDefs, fieldVals, 0, IPAP_FT_STARTSECONDS, sstart, &optionFields);

#ifdef DEBUG
	cout << "two auction module: start create allocation after startSeconds" << std::endl;
#endif
	
	// Insert stop
	ipap_field fStop = g_ipap_fields.get_field(0, IPAP_FT_ENDSECONDS);
	timeUint64 = *reinterpret_cast<uint64_t*>(&stop);	
	ipap_value_field fVStop = fStop.get_ipap_value_field( timeUint64 );
	string sstop = fStop.writeValue(fVStop);
	fillField(fieldDefs, fieldVals, 0, IPAP_FT_ENDSECONDS, sstop, &optionFields);

#ifdef DEBUG
	cout << "two auction module: start create allocation after endSeconds" << std::endl;
#endif		

	fillField(fieldDefs, fieldVals, 0, IPAP_FT_IDRECORD, recordId, &optionFields);
		
	options.push_back(pair<string, auction::fieldList_t>(elementName, optionFields));
	
    auction::BiddingObject *alloc = new auction::BiddingObject(auctionSet, auctionName, 
										allocset, allocname, IPAP_ALLOCATION, elements, options);

	// All objects must be inherit the session from the bid.
	alloc->setSession(sessionId);
	
#ifdef DEBUG
	cout << "two auction module: ending create allocation" << std::endl;
#endif	

	return alloc;
}

double getAllocationQuantity(auction::fieldValList_t *fieldVals, auction::BiddingObject *allocation)
{
#ifdef DEBUG
	fprintf( stdout, "two auction module: starting getAllocationQuantity \n");
#endif	
	
	float temp_qty = 0; 
	auction::elementList_t *elements = allocation->getElements();
		
	// there is only one element. 
	auction::fieldListIter_t field_iter;
	auction::field_t field;
	for (field_iter = (elements->begin()->second).begin(); 
				field_iter != (elements->begin()->second).end(); ++field_iter )
	{				
		if ((field_iter->name).compare("quantity") == 0 ){
			field = *field_iter; 
			temp_qty = parseFloat( ((field.value)[0]).getValue());
			break;
		}
	}

#ifdef DEBUG
	fprintf( stdout, "two auction module: ending getAllocationQuantity \n");
#endif	
	
	return temp_qty;

}

double getBidPrice(auction::BiddingObject *bid)
{
	
	double unitPrice = -1;
	auction::elementList_t *elems = bid->getElements();
				
	auction::elementListIter_t elem_iter;
	for ( elem_iter = elems->begin(); elem_iter != elems->end(); ++elem_iter )
	{
		unitPrice = getDoubleField(&(elem_iter->second), "unitprice");
		break;
	}
	
	return unitPrice;
	
}

void separateBids(auction::biddingObjectDB_t *bids,double bl, double bh, 
					auction::biddingObjectDB_t *bids_low, auction::biddingObjectDB_t *bids_high)
{

#ifdef DEBUG
	cout << "Starting separateBids" << endl;
#endif

	auction::biddingObjectDB_t::iterator iter;
	for (iter = bids->begin();iter != bids->end(); ++iter){
		auction::BiddingObject *bid = *iter;
		double price = getBidPrice(bid);
		
		if (price >= 0){
			if (price >bl){
				bids_high->push_back(bid);
			}	
			else{ 
				bids_low->push_back(bid);
			}
		}
	}

#ifdef DEBUG
	cout << "Ending separateBids" << endl;
#endif		

}

void changeAllocationPrice(auction::fieldValList_t *fieldVals, 
									auction::BiddingObject *allocation, double price)
{

#ifdef DEBUG
	cout << "two auction module: starting changeAllocationPrice" << endl;
#endif

	auction::elementList_t *elements = allocation->getElements();
	
	// there is only one element. 
	auction::fieldListIter_t field_iter;
	auction::field_t field;
	for (field_iter = (elements->begin()->second).begin(); 
				field_iter != (elements->begin()->second).end(); ++field_iter )
	{
		if ((field_iter->name).compare("unitprice") == 0){
			// Delete the field. 
			field = *field_iter; 
			string fvalue = doubleToString(price);
			field_iter->value[0] = auction::FieldValue(field_iter->type, fvalue);
			break;
		}
	}
	if ( field.name.empty()){
		throw auction::ProcError("Field quantity was not included in the allocation");
	}

#ifdef DEBUG
	cout << "two auction module: ending changeAllocationPrice" << endl;
#endif	


}

void addQuantityAllocation(auction::fieldValList_t *fieldVals, 
									auction::BiddingObject *allocation, float quantity)
{

#ifdef DEBUG
	cout << "two auction module: starting add quantity allocation" << endl;
#endif

	auction::elementList_t *elements = allocation->getElements();
	
	// there is only one element. 
	auction::fieldListIter_t field_iter;
	auction::field_t field;
	for (field_iter = (elements->begin()->second).begin(); 
				field_iter != (elements->begin()->second).end(); ++field_iter )
	{
		if ((field_iter->name).compare("quantity") == 0){
			// Delete the field. 
			field = *field_iter; 
			float temp_qty = parseFloat( ((field.value)[0]).getValue());
			temp_qty += quantity;
			string fvalue = floatToString(temp_qty);
			field_iter->value[0] = auction::FieldValue(field_iter->type, fvalue);
			break;
		}
	}
	
	if ( field.name.empty()){
		throw auction::ProcError("Field quantity was not included in the allocation");
	}

#ifdef DEBUG
	cout << "two auction module: ending add quantity allocation" << endl;
#endif	
	
}

int calculateRequestedQuantities(auction::biddingObjectDB_t *bids)
{

#ifdef DEBUG
	cout << "two auction module: starting calculateRequestedQuantities" << endl;
#endif	
	
	int sumQuantity = 0;
	
	auction::biddingObjectDBIter_t bid_iter; 
	for (bid_iter = bids->begin(); bid_iter != bids->end(); ++bid_iter){
		auction::BiddingObject * bid = *bid_iter;
		auction::elementList_t *elems = bid->getElements();
		auction::elementListIter_t elem_iter;
		
		for ( elem_iter = elems->begin(); elem_iter != elems->end(); ++elem_iter )
		{
			int quantity = floor(getDoubleField(&(elem_iter->second), "quantity"));
			sumQuantity = sumQuantity + quantity;
		}
	}

#ifdef DEBUG
	cout << "two auction module: ending calculateRequestedQuantities" << sumQuantity << endl;
#endif
	
	return sumQuantity;
}

double executeAuction(auction::fieldDefList_t *fieldDefs, auction::fieldValList_t *fieldVals, 
					string aset, string aname, time_t start, time_t stop, 
					auction::biddingObjectDB_t *bids, double qtyAvailable, 
					map<string,auction::BiddingObject *> &allocations)
{


	std::multimap<double, alloc_proc_t>  orderedBids;
	
	// Order Bids by elements.
	auction::biddingObjectDBIter_t bid_iter; 
	for (bid_iter = bids->begin(); bid_iter != bids->end(); ++bid_iter){
		auction::BiddingObject * bid = *bid_iter;
				
		auction::elementList_t *elems = bid->getElements();
				
		auction::elementListIter_t elem_iter;
		for ( elem_iter = elems->begin(); elem_iter != elems->end(); ++elem_iter )
		{
			double price = getDoubleField(&(elem_iter->second), "unitprice");
			double quantity = getDoubleField(&(elem_iter->second), "quantity");
			alloc_proc_t alloc;
		
			alloc.bidSet = bid->getBiddingObjectSet();
			alloc.bidName = bid->getBiddingObjectName();
			alloc.elementName = elem_iter->first;
			alloc.sessionId = bid->getSession();
			alloc.quantity = quantity;
			orderedBids.insert(make_pair(price,alloc));
		}
	}

	double sellPrice = 0;

#ifdef DEBUG	
	cout << "two auction module- qty available:" << qtyAvailable << endl;
#endif
	
	if ( orderedBids.size() > 0 ){
		std::multimap<double, alloc_proc_t>::iterator it = orderedBids.end();
		do
		{ 
			--it;
					
			if ( qtyAvailable < (it->second).quantity){
				(it->second).quantity = qtyAvailable;
				if (qtyAvailable > 0){
					sellPrice = it->first; 
					qtyAvailable = 0;
				 }
			}
			else{
				qtyAvailable = qtyAvailable - (it->second).quantity;
				sellPrice = it->first;
			}
			
		} while (it != orderedBids.begin());

#ifdef DEBUG	
	cout << "two auction module: after executing the auction" << (int) bids->size() << endl;
#endif
	
		map<string,auction::BiddingObject *>::iterator alloc_iter;
		
		// Creates allocations
		it = orderedBids.end();
		do
		{
			--it;
			
			if (allocations.find(makeKey(aset, 
				aname,(it->second).bidSet, (it->second).bidName )) != allocations.end()){
				alloc_iter = allocations.find(makeKey(aset, aname,
									(it->second).bidSet, (it->second).bidName ));
				addQuantityAllocation(fieldVals, alloc_iter->second, (it->second).quantity); 					
			}
			else{
				auction::BiddingObject *alloc = 
					createAllocation(fieldDefs, fieldVals, aset, aname, 
									  (it->second).bidSet, (it->second).bidName, (it->second).sessionId,
										start, stop, (it->second).quantity, sellPrice);
										
				allocations[makeKey(aset, aname,
									(it->second).bidSet, (it->second).bidName)] = alloc;
			}
			
		} while (it != orderedBids.begin());
	}
#ifdef DEBUG	
	cout << "two auction module: after create allocations" << (int) allocations.size() << endl;
#endif

	return sellPrice;
}

double getProbability()
{
	cout << "start getProbability:" << endl;
	
	unsigned int nbr;
	
	int ret = RAND_bytes((unsigned char *) &nbr, sizeof(nbr));
	
	assert( ret == 1 );
	
	unsigned long umin = numeric_limits<unsigned int>::min();
	unsigned long umax = numeric_limits<unsigned int>::max();
	
	double dumin = umin;
	double dumax = umax;
	double prob = nbr / (dumax - dumin);
	
	cout << "ending getProbability:" << prob << endl;
	
	return prob;
}

void ApplyMechanism(auction::fieldDefList_t *fieldDefs, auction::fieldValList_t *fieldVals,
					time_t start, time_t stop, map<string,auction::BiddingObject *> &allocations, 
					double price, double qStar)
{

	cout << "starting ApplyMechanism qStar:" << qStar << endl;

	map<string,auction::BiddingObject *>::iterator iter; 
	for (iter = allocations.begin(); iter != allocations.end(); ++iter){
		
		string bidName = getBidName(iter->first);
				
		auction::BiddingObject *alloc = iter->second;
		int quantity = floor(getAllocationQuantity(fieldVals, alloc)); 
		float unitsToPass = 0;
		for (int j = 0; j < quantity; j++){
			
			double prob = getProbability();
			
			if (prob <= qStar)  // pass a unit.
				unitsToPass = unitsToPass + 1;
		}
				
		if (unitsToPass > 0){
		
			if (unitsToPass < quantity){
				auction::BiddingObject * alloc2 = createAllocation( fieldDefs, fieldVals,
								alloc->getAuctionSet(), alloc->getAuctionName(), 
								alloc->getBiddingObjectSet(), bidName,
								alloc->getSession(), start, stop, unitsToPass, price );
				  
				float unitsToAdd = unitsToPass *-1;
				addQuantityAllocation(fieldVals, alloc, unitsToAdd);
				
				allocations[makeKey(alloc2->getAuctionSet(), alloc2->getAuctionName(),
								alloc2->getBiddingObjectSet(), alloc2->getBiddingObjectName())] = alloc2;
			} else {
				changeAllocationPrice(fieldVals, alloc, price);	
			}
		}
	}
	
	cout << "ending ApplyMechanism" << endl;
}

void auction::execute( auction::fieldDefList_t *fieldDefs, auction::fieldValList_t *fieldVals,  
					   auction::configParam_t *params, string aset, string aname, time_t start, 
					   time_t stop, auction::biddingObjectDB_t *bids, 
					   auction::biddingObjectDB_t **allocationdata )
{

#ifdef DEBUG
	cout << "two auction module: start execute" << (int) bids->size() << endl;
#endif

	float bandwidth_to_sell_low = getResourceAvailability( params, 0 );
	float bandwidth_to_sell_high = getResourceAvailability( params, 1 );
	double reserve_price_low = getReservePrice( params, 0 );	
	double reserve_price_high = getReservePrice( params, 1 );	
	double bl = getMaximumValue( params, 0 );	
	double bh = getMaximumValue( params, 1 );	
	
	auction::biddingObjectDB_t *bids_low = new auction::biddingObjectDB_t();
	auction::biddingObjectDB_t *bids_high = new auction::biddingObjectDB_t();
	
	// Order bids classifying them by whether they compete on the low and high auction.
	separateBids(bids,bl, bh, bids_low, bids_high);
	
	// Calculate the number of bids on both auctions.
	int nl = calculateRequestedQuantities(bids_low);
	int nh = calculateRequestedQuantities(bids_high);
	
	double qStar = 0;
	if ((nl > 0) && (nh > 0)){ 
	
		// Find the probability of changing from the high budget to low budget auction.
		TwoAuctionMechanism *mechanism = new TwoAuctionMechanism();
		double a = 0.01;
		double b = 0.5;
		double macheps = 0.000001;
		double t = 0.000001;
		double bidF = 0.6;
		qStar = mechanism->zerosWithUnits(nh, nl, bh, bl, bandwidth_to_sell_high, 
									  bandwidth_to_sell_low, reserve_price_high, 
									  reserve_price_low, bidF, a, b, macheps, t);
		
		delete mechanism;
	}
	
	// Execute auctions.
	map<string,auction::BiddingObject *> alloctions_low;
	double price_low = executeAuction( fieldDefs, fieldVals, aset, aname, start, stop, 
									  bids_low, bandwidth_to_sell_low, alloctions_low);
	
	cout << "after executeAuction low budget users" << endl;
	
	map<string,auction::BiddingObject *> alloctions_high;
	double price_high =	executeAuction( fieldDefs, fieldVals, aset, aname, start, stop, 
									 bids_high, bandwidth_to_sell_low, alloctions_high);
	
	cout << "after executeAuction high budget users" << endl;
	
	if (qStar > 0){
		// change bids from the high budget to low budget auction.
		ApplyMechanism( fieldDefs, fieldVals, start, stop, alloctions_high, price_low, qStar);
	}
		
	// Convert from the map to the final allocationDB result
	map<string,auction::BiddingObject *>::iterator alloc_iter;
	for ( alloc_iter = alloctions_low.begin(); 
				alloc_iter != alloctions_low.end(); ++alloc_iter )
	{
		(*allocationdata)->push_back(alloc_iter->second);
	}

	// Convert from the map to the final allocationDB result
	for ( alloc_iter = alloctions_high.begin(); 
				alloc_iter != alloctions_high.end(); ++alloc_iter )
	{
		(*allocationdata)->push_back(alloc_iter->second);
	}
	
	// Free the memory allocated to these two containers.
	delete bids_low;
	delete bids_high;
	
#ifdef DEBUG	
	cout << "two auction module: end execute" <<  endl;
#endif
}

void auction::execute_user( auction::fieldDefList_t *fieldDefs, auction::fieldValList_t *fieldVals, 
							auction::fieldList_t *requestparams, auction::auctionDB_t *auctions, 
							time_t start, time_t stop, auction::biddingObjectDB_t **biddata )
{
#ifdef DEBUG
	fprintf( stdout, "two auction module: start execute_user \n");
#endif
	// Nothing to do

#ifdef DEBUG
	fprintf( stdout, "two auction module: end execute_user \n");
#endif
	
}

void auction::destroy( auction::configParam_t *params )
{
#ifdef DEBUG
	fprintf( stdout, "two auction module: start destroy \n");
#endif

#ifdef DEBUG
	fprintf( stdout, "two auction module: end destroy \n");
#endif
}

void auction::reset( auction::configParam_t *params )
{
#ifdef DEBUG
	fprintf( stdout, "two auction module: start reset \n");
#endif

#ifdef DEBUG
	fprintf( stdout, "two auction module: end reset \n");
#endif
}

const char* auction::getModuleInfo( int i )
{
#ifdef DEBUG
	fprintf( stdout, "two auction module: start getModuleInfo \n");
#endif

    /* fprintf( stderr, "count : getModuleInfo(%d)\n",i ); */

    switch(i) {
    case auction::I_MODNAME:    return "Two Auction Module";
    case auction::I_ID:		    return "TwoAuction";
    case auction::I_VERSION:    return "0.1";
    case auction::I_CREATED:    return "2015/12/01";
    case auction::I_MODIFIED:   return "2015/12/01";
    case auction::I_BRIEF:      return "Auction process for spliting in low and high budget users";
    case auction::I_VERBOSE:    return "The auction calculates a probability q, so high budget users are priced as low budget users."; 
    case auction::I_HTMLDOCS:   return "http://www.uniandes.edu.co/... ";
    case auction::I_PARAMS:     return "None";
    case auction::I_RESULTS:    return "The set of assigments";
    case auction::I_AUTHOR:     return "Andres Marentes";
    case auction::I_AFFILI:     return "Universidad de los Andes, Colombia";
    case auction::I_EMAIL:      return "la.marentes455@uniandes.edu.co";
    case auction::I_HOMEPAGE:   return "http://homepage";
    default: return NULL;
    }

#ifdef DEBUG
	fprintf( stdout, "bas module: end getModuleInfo \n");
#endif
}

char* auction::getErrorMsg( int code )
{
#ifdef DEBUG
	fprintf( stdout, "bas module: start getErrorMsg \n");
#endif
	
	return NULL;

#ifdef DEBUG
	fprintf( stdout, "bas module: end getErrorMsg \n");
#endif
}
