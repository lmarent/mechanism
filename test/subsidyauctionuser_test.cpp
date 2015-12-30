/*
 * Test the subsidy auction user module.
 *
 * $Id: subsidyauctionuser_test.cpp 2015-12-30 11:36:00 amarentes $
 * $HeadURL: https://./test/subsidyauctionuser_test.cpp $
 */
#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include "BiddingObject.h"
#include "FieldValue.h"
#include "FieldValParser.h"
#include "FieldDefParser.h"
#include "AuctionManager.h"
#include "ModuleLoader.h"
#include "Module.h"
#include "ConstantsAum.h"
#include "ProcModule.h" 


using namespace auction;

class subsidyauctionuser_Test : public CppUnit::TestFixture {

	CPPUNIT_TEST_SUITE( subsidyauctionuser_Test );

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
    
    ConfigManager *conf= NULL;
    string moduleName;

	AuctionManager *auctionManagerPtr = NULL;

    auto_ptr<EventScheduler>  evnt;

    
};

CPPUNIT_TEST_SUITE_REGISTRATION( subsidyauctionuser_Test );

void subsidyauctionuser_Test::setUp() 
{

	const string filename = DEF_SYSCONFDIR "/auctionmanager/fielddef.xml";		
	const string fieldValuename = DEF_SYSCONFDIR "/auctionmanager/fieldval.xml";

	try
	{
		
		moduleName = "libsubsidyauctionuser";
				
		// Load the configuration
        string configFileName =  DEF_SYSCONFDIR "/auctionmanager/netagnt.conf.xml";
		string dtdfile = DEF_SYSCONFDIR "/auctionmanager/netagnt.conf.dtd";
        conf = new ConfigManager(dtdfile, configFileName, "");
		
		// Load the module
		string libname, path, ext;

		string moduleDir = DEF_LIBDIR;
		loader = new ModuleLoader(conf, moduleDir.c_str() /*module (lib) basedir*/,
                                  moduleName,/*modlist*/
                                  "Proc" /*channel name prefix*/,
                                  "AGENT_PROCESSOR" /* Configuration group */);

		int domain = 5;
		
		auctionManagerPtr = new AuctionManager(domain, filename, fieldValuename);
		auto_ptr<EventScheduler> _evnt(new EventScheduler());
        evnt = _evnt;


	}
	catch(Error &e){
		std::cout << "Error:" << e.getError() << std::endl << std::flush;

        if (loader) {
            saveDelete(loader);
        }
        
        if (auctionManagerPtr){
			saveDelete(auctionManagerPtr);
		}
		
        throw e;
	}
}

void subsidyauctionuser_Test::tearDown() 
{
	if (loader != NULL){
		saveDelete(loader);
	}
		
	if (conf != NULL){
		saveDelete(conf);
	}

	if (auctionManagerPtr != NULL){
		saveDelete(auctionManagerPtr);
	}
		
	evnt.reset();
	
}


void subsidyauctionuser_Test::test() 
{
	biddingObjectDB_t bids;
	biddingObjectDB_t *ptr = &bids;
	string auctionSet = "1";
	string auctionName = "1";
	time_t             start = time(NULL);
    string paramName;
    string paramValue;
	
	mod = loader->getModule(moduleName.c_str());
	procmod = dynamic_cast<ProcModule*>(mod);

	if (procmod != NULL){

		configParam_t *params = new configParam_t[2];
		int i = 0;
	
		string paramName2 = "domainid";
		string paramValue2 = "6";
		params[i].name = (char* ) paramName2.c_str();
		params[i].value = (char *) paramValue2.c_str();
		i++;
		
		params[i].name = NULL;
		params[i].value = NULL;
		
		procmod->getAPI()->reset( params );
		
		saveDelete(params);
		
		ipap_template_container *templates;
		
		const string filename = "../etc/subsidyauctiondef.xml";
		
		templates = new ipap_template_container();
		
		auctionDB_t * auctions = auctionManagerPtr->parseAuctions(filename, templates);
		
		saveDelete(templates);
				
		auction::fieldList_t fields;
	
		field_t field1;
		field_t field2;
		field_t field3;
		field_t field4;
		field_t field5;
		
	
		auction::fieldDefListIter_t iter; 
		iter = auctionManagerPtr->getFieldDefs()->find("quantity");
		if (iter != auctionManagerPtr->getFieldDefs()->end()){
			field1.name = iter->second.name;
			field1.len = iter->second.len;
			field1.type = iter->second.type;
			string fvalue1 = "2";
			field1.parseFieldValue(fvalue1);
		} else {
			throw Error("field quantity not found");
		}

		iter = auctionManagerPtr->getFieldDefs()->find("maxvalue");
		if (iter != auctionManagerPtr->getFieldDefs()->end()){
			field2.name = iter->second.name;
			field2.len = iter->second.len;
			field2.type = iter->second.type;
			string fvalue2 = "0.7";
			field2.parseFieldValue(fvalue2);
		} else {
			throw Error("field maxvalue not found");
		}
	
		iter = auctionManagerPtr->getFieldDefs()->find("unitbudget");
		if (iter != auctionManagerPtr->getFieldDefs()->end()){
			field3.name = iter->second.name;
			field3.len = iter->second.len;
			field3.type = iter->second.type;
			string fvalue3 = "0.61";
			field3.parseFieldValue(fvalue3);
		} else {
			throw Error("field unitbudget not found");
		}

		iter = auctionManagerPtr->getFieldDefs()->find("maxvalue01");
		if (iter != auctionManagerPtr->getFieldDefs()->end()){
			field4.name = iter->second.name;
			field4.len = iter->second.len;
			field4.type = iter->second.type;
			string fvalue4 = "0.5";
			field4.parseFieldValue(fvalue4);
		} else {
			throw Error("field maxvalue01 not found");
		}

		iter = auctionManagerPtr->getFieldDefs()->find("subsidy");
		if (iter != auctionManagerPtr->getFieldDefs()->end()){
			field5.name = iter->second.name;
			field5.len = iter->second.len;
			field5.type = iter->second.type;
			string fvalue5 = "1.2";
			field5.parseFieldValue(fvalue5);
		} else {
			throw Error("field subsidy not found");
		}

		fields.push_back(field1);
		fields.push_back(field2);
		fields.push_back(field3);
		fields.push_back(field4);
		fields.push_back(field5);
		
		
		time_t start = time(NULL);
		time_t end = start + 10;
		
		procmod->getAPI()->execute_user(auctionManagerPtr->getFieldDefs(),
										auctionManagerPtr->getFieldVals(),
										&fields, auctions, 
										start, end,
										&ptr );
		
		biddingObjectDBIter_t iter2;
		for (iter2 = ptr->begin(); iter2 != ptr->end(); iter2++){
			cout << "info:" << (*iter2)->getInfo() << endl;
		}
	}
}
