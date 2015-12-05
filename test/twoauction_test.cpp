/*
 * Test the two auction module.
 *
 * $Id: twoauction_test.cpp 2015-11-30 14:47:00 amarentes $
 * $HeadURL: https://./test/twoauction_test.cpp $
 */
#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include "BiddingObject.h"
#include "FieldValue.h"
#include "FieldValParser.h"
#include "FieldDefParser.h"
#include "BiddingObjectFileParser.h"
#include "BiddingObjectManager.h"
#include "ModuleLoader.h"
#include "Module.h"
#include "ConstantsAum.h"
#include "ProcModule.h" 


using namespace auction;

class twoauction_Test : public CppUnit::TestFixture {

	CPPUNIT_TEST_SUITE( twoauction_Test );

    CPPUNIT_TEST( test );
	CPPUNIT_TEST_SUITE_END();

  public:
	void setUp();
	void tearDown();
	void test();

    //! filter definitions
    fieldDefList_t fieldDefs;

    //! filter values
    fieldValList_t fieldVals;
    
    //! module pointer
    ModuleLoader *loader;
    ProcModule *procmod = NULL;
    Module *mod = NULL; 
    
    BiddingObjectManager *manager = NULL;
    biddingObjectDB_t *bids = NULL;
    ConfigManager *conf= NULL;
    string moduleName;
    
};

CPPUNIT_TEST_SUITE_REGISTRATION( twoauction_Test );

void twoauction_Test::setUp() 
{

	try
	{
		
		string filename;
		biddingObjectDB_t *new_bids = NULL;
		bids = new biddingObjectDB_t();
		moduleName = "libtwoauction";
		
		BiddingObject *ptrBid;
		
		int domain = 1;
		string fieldname = DEF_SYSCONFDIR "/auctionmanager/fielddef.xml";
		string fieldValuename = DEF_SYSCONFDIR "/auctionmanager/fieldval.xml";		
		manager = new BiddingObjectManager(domain, fieldname, fieldValuename, "");

		// Parse the bidding objects in file example_bids1.xml, it allocates the memory.
		filename = "../etc/example_bids1.xml";
		new_bids = manager->parseBiddingObjects(filename);	
		CPPUNIT_ASSERT( new_bids->size() == 1 );
		ptrBid = (*new_bids)[0];
		bids->push_back(ptrBid);
        saveDelete(new_bids);
        saveDelete(manager);
		
		// Parse the bidding objects in file example_bids2.xml, it allocates the memory.
		domain = 2;
		fieldname = DEF_SYSCONFDIR "/auctionmanager/fielddef.xml";
		fieldValuename = DEF_SYSCONFDIR "/auctionmanager/fieldval.xml";		
		manager = new BiddingObjectManager(domain, fieldname, fieldValuename, "");

		filename = "../etc/example_bids2.xml";
		new_bids = manager->parseBiddingObjects(filename);	
		CPPUNIT_ASSERT( new_bids->size() == 1 );
		ptrBid = new BiddingObject(*((*new_bids)[0]));
		bids->push_back(ptrBid);
        saveDelete(new_bids);
        saveDelete(manager);

		// Parse the bidding objects in file example_bids3.xml, it allocates the memory.
		domain = 3;
		fieldname = DEF_SYSCONFDIR "/auctionmanager/fielddef.xml";
		fieldValuename = DEF_SYSCONFDIR "/auctionmanager/fieldval.xml";		
		manager = new BiddingObjectManager(domain, fieldname, fieldValuename, "");

		filename = "../etc/example_bids3.xml";
		new_bids = manager->parseBiddingObjects(filename);	
		CPPUNIT_ASSERT( new_bids->size() == 1 );
		ptrBid = new BiddingObject(*((*new_bids)[0]));
 		bids->push_back(ptrBid);
        saveDelete(new_bids);
        saveDelete(manager);		
		
		// Parse the bidding objects in file example_bids4.xml, it allocates the memory.
		domain = 4;
		fieldname = DEF_SYSCONFDIR "/auctionmanager/fielddef.xml";
		fieldValuename = DEF_SYSCONFDIR "/auctionmanager/fieldval.xml";		
		manager = new BiddingObjectManager(domain, fieldname, fieldValuename, "");

		filename = "../etc/example_bids4.xml";
		new_bids = manager->parseBiddingObjects(filename);	
		CPPUNIT_ASSERT( new_bids->size() == 1 );
		ptrBid = new BiddingObject(*((*new_bids)[0]));
		bids->push_back(ptrBid);
        saveDelete(new_bids);		
        saveDelete(manager);		

		// Parse the bidding objects in file example_bids5.xml, it allocates the memory.
		domain = 5;
		fieldname = DEF_SYSCONFDIR "/auctionmanager/fielddef.xml";
		fieldValuename = DEF_SYSCONFDIR "/auctionmanager/fieldval.xml";		
		manager = new BiddingObjectManager(domain, fieldname, fieldValuename, "");

		filename = "../etc/example_bids5.xml";
		new_bids = manager->parseBiddingObjects(filename);	
		CPPUNIT_ASSERT( new_bids->size() == 1 );
		ptrBid = new BiddingObject(*((*new_bids)[0]));
		bids->push_back(ptrBid);
        saveDelete(new_bids);		
        saveDelete(manager);		

		// Parse the bidding objects in file example_bids6.xml, it allocates the memory.
		domain = 6;
		fieldname = DEF_SYSCONFDIR "/auctionmanager/fielddef.xml";
		fieldValuename = DEF_SYSCONFDIR "/auctionmanager/fieldval.xml";		
		manager = new BiddingObjectManager(domain, fieldname, fieldValuename, "");

		filename = "../etc/example_bids6.xml";
		new_bids = manager->parseBiddingObjects(filename);	
		CPPUNIT_ASSERT( new_bids->size() == 1 );
		ptrBid = new BiddingObject(*((*new_bids)[0]));
		bids->push_back(ptrBid);
        saveDelete(new_bids);		
        saveDelete(manager);

		// Parse the bidding objects in file example_bids7.xml, it allocates the memory.
		domain = 7;
		fieldname = DEF_SYSCONFDIR "/auctionmanager/fielddef.xml";
		fieldValuename = DEF_SYSCONFDIR "/auctionmanager/fieldval.xml";		
		manager = new BiddingObjectManager(domain, fieldname, fieldValuename, "");

		filename = "../etc/example_bids7.xml";
		new_bids = manager->parseBiddingObjects(filename);	
		CPPUNIT_ASSERT( new_bids->size() == 1 );
		ptrBid = new BiddingObject(*((*new_bids)[0]));
		bids->push_back(ptrBid);
        saveDelete(new_bids);		
        saveDelete(manager);

		// Parse the bidding objects in file example_bids8.xml, it allocates the memory.
		domain = 8;
		fieldname = DEF_SYSCONFDIR "/auctionmanager/fielddef.xml";
		fieldValuename = DEF_SYSCONFDIR "/auctionmanager/fieldval.xml";		
		manager = new BiddingObjectManager(domain, fieldname, fieldValuename, "");

		filename = "../etc/example_bids8.xml";
		new_bids = manager->parseBiddingObjects(filename);	
		CPPUNIT_ASSERT( new_bids->size() == 1 );
		ptrBid = new BiddingObject(*((*new_bids)[0]));
		bids->push_back(ptrBid);
        saveDelete(new_bids);		
        saveDelete(manager);

		// Parse the bidding objects in file example_bids9.xml, it allocates the memory.
		domain = 9;
		fieldname = DEF_SYSCONFDIR "/auctionmanager/fielddef.xml";
		fieldValuename = DEF_SYSCONFDIR "/auctionmanager/fieldval.xml";		
		manager = new BiddingObjectManager(domain, fieldname, fieldValuename, "");

		filename = "../etc/example_bids9.xml";
		new_bids = manager->parseBiddingObjects(filename);	
		CPPUNIT_ASSERT( new_bids->size() == 1 );
		ptrBid = new BiddingObject(*((*new_bids)[0]));
		bids->push_back(ptrBid);
        saveDelete(new_bids);		
        saveDelete(manager);

		// Parse the bidding objects in file example_bids10.xml, it allocates the memory.
		domain = 10;
		fieldname = DEF_SYSCONFDIR "/auctionmanager/fielddef.xml";
		fieldValuename = DEF_SYSCONFDIR "/auctionmanager/fieldval.xml";		
		manager = new BiddingObjectManager(domain, fieldname, fieldValuename, "");

		filename = "../etc/example_bids10.xml";
		new_bids = manager->parseBiddingObjects(filename);	
		CPPUNIT_ASSERT( new_bids->size() == 1 );
		ptrBid = new BiddingObject(*((*new_bids)[0]));
		bids->push_back(ptrBid);
        saveDelete(new_bids);	
        saveDelete(manager);
		
		// Load the configuration
        string configFileName =  DEF_SYSCONFDIR "/auctionmanager/netaum.conf.xml";

        conf = new ConfigManager(AUM_CONFIGFILE_DTD, configFileName, "");
		
		// Load the module
		string libname, path, ext;

		string moduleDir = DEF_LIBDIR;
		loader = new ModuleLoader(conf, moduleDir.c_str() /*module (lib) basedir*/,
                                  moduleName,/*modlist*/
                                  "Proc" /*channel name prefix*/,
                                  "AUM_PROCESSOR" /* Configuration group */);

		// Finally, we create the bidding object manager required to execute the auction.
		domain = 11;
		fieldname = DEF_SYSCONFDIR "/auctionmanager/fielddef.xml";
		fieldValuename = DEF_SYSCONFDIR "/auctionmanager/fieldval.xml";		
		manager = new BiddingObjectManager(domain, fieldname, fieldValuename, "");

	}
	catch(Error &e){
		std::cout << "Error:" << e.getError() << std::endl << std::flush;

        if (loader) {
            saveDelete(loader);
        }
        throw e;
	}
}

void twoauction_Test::tearDown() 
{
	if (loader != NULL){
		saveDelete(loader);
	}
	
	if (manager != NULL){
		saveDelete(manager);
	}
	
	if (conf != NULL){
		saveDelete(conf);
	}
	
	if (bids != NULL){
		saveDelete(bids);
	}
}


void twoauction_Test::test() 
{
	biddingObjectDB_t allocations;
	biddingObjectDB_t *ptr = &allocations;
	string auctionSet = "1";
	string auctionName = "1";
	time_t             start = time(NULL);
	time_t             stop = start + 100;
    string paramName;
    string paramValue;
	
	mod = loader->getModule(moduleName.c_str());
	procmod = dynamic_cast<ProcModule*>(mod);

	if (procmod != NULL){

		/* The following are the required parameters */

		configParam_t *params = new configParam_t[7];
		int i = 0;
	
		string paramName2 = "bandwidth01";
		string paramValue2 = "6";
		params[i].name = (char* ) paramName2.c_str();
		params[i].value = (char *) paramValue2.c_str();
		i++;
    	
		string paramName3 = "bandwidth02";
		string paramValue3 = "6";
		params[i].name = (char* ) paramName3.c_str();
		params[i].value = (char *) paramValue3.c_str();
		i++;

		string paramName4 = "reserveprice01";
		string paramValue4 = "0.3";
		params[i].name = (char* ) paramName4.c_str();
		params[i].value = (char *) paramValue4.c_str();
		i++;

		string paramName5 = "reserveprice02";
		string paramValue5 = "0.5";
		params[i].name = (char* ) paramName5.c_str();
		params[i].value = (char *) paramValue5.c_str();
		i++;

		string paramName6 = "maxvalue01";
		string paramValue6 = "0.5";
		params[i].name = (char* ) paramName6.c_str();
		params[i].value = (char *) paramValue6.c_str();
		i++;

		string paramName7 = "maxvalue02";
		string paramValue7 = "0.9";
		params[i].name = (char* ) paramName7.c_str();
		params[i].value = (char *) paramValue7.c_str();
		i++;
	
		params[i].name = NULL;
		params[i].value = NULL;
		
		procmod->getAPI()->execute(manager->getFieldDefs(),
								 manager->getFieldVals(),
								 params, 
								 auctionSet, auctionName,
								 start, stop, bids, &ptr );
		
		biddingObjectDBIter_t iter;
		for (iter = ptr->begin(); iter != ptr->end(); iter++){
			cout << "info:" << (*iter)->getInfo() << endl;
		}
	}
}
