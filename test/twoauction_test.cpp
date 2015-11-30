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
    Module *module = NULL;
    
};

CPPUNIT_TEST_SUITE_REGISTRATION( twoauction_Test );

void twoauction_Test::setUp() 
{

	try
	{
		
		biddingObjectDB_t *bids = new biddingObjectDB_t();
		
		BiddingObject *ptrBid;
		
		int domain = 1;
		const string fieldname = DEF_SYSCONFDIR "/fielddef.xml";
		const string fieldValuename = DEF_SYSCONFDIR "/fieldval.xml";		
		manager = new BiddingObjectManager(domain, fieldname, fieldValuename);

		// Parse the bidding objects in file example_bids1.xml, it allocates the memory.
		string filename = "../../etc/example_bids1.xml";
		biddingObjectDB_t *new_bids = manager->parseBiddingObjects(filename);	
		CPPUNIT_ASSERT( new_bids->size() == 1 );
		ptrBid = new BiddingObject(*((*new_bids)[0]));
		bids->push_back(ptrBid);
        saveDelete(new_bids);
        saveDelete(manager);
		
		// Parse the bidding objects in file example_bids2.xml, it allocates the memory.
		int domain = 2;
		const string fieldname = DEF_SYSCONFDIR "/fielddef.xml";
		const string fieldValuename = DEF_SYSCONFDIR "/fieldval.xml";		
		manager = new BiddingObjectManager(domain, fieldname, fieldValuename);

		string filename = "../../etc/example_bids2.xml";
		biddingObjectDB_t *new_bids = manager->parseBiddingObjects(filename);	
		CPPUNIT_ASSERT( new_bids->size() == 1 );
		ptrBid = new BiddingObject(*((*new_bids)[0]));
		bids->push_back(ptrBid);
        saveDelete(new_bids);
        saveDelete(manager);

		// Parse the bidding objects in file example_bids3.xml, it allocates the memory.
		int domain = 3;
		const string fieldname = DEF_SYSCONFDIR "/fielddef.xml";
		const string fieldValuename = DEF_SYSCONFDIR "/fieldval.xml";		
		manager = new BiddingObjectManager(domain, fieldname, fieldValuename);

		string filename = "../../etc/example_bids3.xml";
		biddingObjectDB_t *new_bids = manager->parseBiddingObjects(filename);	
		CPPUNIT_ASSERT( new_bids->size() == 1 );
		ptrBid = new BiddingObject(*((*new_bids)[0]));
        saveDelete(new_bids);
        saveDelete(manager);		
		
		// Parse the bidding objects in file example_bids4.xml, it allocates the memory.
		int domain = 4;
		const string fieldname = DEF_SYSCONFDIR "/fielddef.xml";
		const string fieldValuename = DEF_SYSCONFDIR "/fieldval.xml";		
		manager = new BiddingObjectManager(domain, fieldname, fieldValuename);

		string filename = "../../etc/example_bids4.xml";
		biddingObjectDB_t *new_bids = manager->parseBiddingObjects(filename);	
		CPPUNIT_ASSERT( new_bids->size() == 1 );
		ptrBid = new BiddingObject(*((*new_bids)[0]));
		bids->push_back(ptrBid);
        saveDelete(new_bids);		
        saveDelete(manager);		

		// Parse the bidding objects in file example_bids5.xml, it allocates the memory.
		int domain = 5;
		const string fieldname = DEF_SYSCONFDIR "/fielddef.xml";
		const string fieldValuename = DEF_SYSCONFDIR "/fieldval.xml";		
		manager = new BiddingObjectManager(domain, fieldname, fieldValuename);

		string filename = "../../etc/example_bids5.xml";
		biddingObjectDB_t *new_bids = manager->parseBiddingObjects(filename);	
		CPPUNIT_ASSERT( new_bids->size() == 1 );
		ptrBid = new BiddingObject(*((*new_bids)[0]));
		bids->push_back(ptrBid);
        saveDelete(new_bids);		
        saveDelete(manager);		

		// Parse the bidding objects in file example_bids6.xml, it allocates the memory.
		int domain = 6;
		const string fieldname = DEF_SYSCONFDIR "/fielddef.xml";
		const string fieldValuename = DEF_SYSCONFDIR "/fieldval.xml";		
		manager = new BiddingObjectManager(domain, fieldname, fieldValuename);

		string filename = "../../etc/example_bids6.xml";
		biddingObjectDB_t *new_bids = manager->parseBiddingObjects(filename);	
		CPPUNIT_ASSERT( new_bids->size() == 1 );
		ptrBid = new BiddingObject(*((*new_bids)[0]));
		bids->push_back(ptrBid);
        saveDelete(new_bids);		
        saveDelete(manager);

		// Parse the bidding objects in file example_bids7.xml, it allocates the memory.
		int domain = 7;
		const string fieldname = DEF_SYSCONFDIR "/fielddef.xml";
		const string fieldValuename = DEF_SYSCONFDIR "/fieldval.xml";		
		manager = new BiddingObjectManager(domain, fieldname, fieldValuename);

		string filename = "../../etc/example_bids7.xml";
		biddingObjectDB_t *new_bids = manager->parseBiddingObjects(filename);	
		CPPUNIT_ASSERT( new_bids->size() == 1 );
		ptrBid = new BiddingObject(*((*new_bids)[0]));
		bids->push_back(ptrBid);
        saveDelete(new_bids);		
        saveDelete(manager);

		// Parse the bidding objects in file example_bids8.xml, it allocates the memory.
		int domain = 8;
		const string fieldname = DEF_SYSCONFDIR "/fielddef.xml";
		const string fieldValuename = DEF_SYSCONFDIR "/fieldval.xml";		
		manager = new BiddingObjectManager(domain, fieldname, fieldValuename);

		string filename = "../../etc/example_bids8.xml";
		biddingObjectDB_t *new_bids = manager->parseBiddingObjects(filename);	
		CPPUNIT_ASSERT( new_bids->size() == 1 );
		ptrBid = new BiddingObject(*((*new_bids)[0]));
		bids->push_back(ptrBid);
        saveDelete(new_bids);		
        saveDelete(manager);

		// Parse the bidding objects in file example_bids9.xml, it allocates the memory.
		int domain = 9;
		const string fieldname = DEF_SYSCONFDIR "/fielddef.xml";
		const string fieldValuename = DEF_SYSCONFDIR "/fieldval.xml";		
		manager = new BiddingObjectManager(domain, fieldname, fieldValuename);

		string filename = "../../etc/example_bids9.xml";
		biddingObjectDB_t *new_bids = manager->parseBiddingObjects(filename);	
		CPPUNIT_ASSERT( new_bids->size() == 1 );
		ptrBid = new BiddingObject(*((*new_bids)[0]));
		bids->push_back(ptrBid);
        saveDelete(new_bids);		
        saveDelete(manager);

		// Parse the bidding objects in file example_bids10.xml, it allocates the memory.
		int domain = 10;
		const string fieldname = DEF_SYSCONFDIR "/fielddef.xml";
		const string fieldValuename = DEF_SYSCONFDIR "/fieldval.xml";		
		manager = new BiddingObjectManager(domain, fieldname, fieldValuename);

		string filename = "../../etc/example_bids10.xml";
		biddingObjectDB_t *new_bids = manager->parseBiddingObjects(filename);	
		CPPUNIT_ASSERT( new_bids->size() == 1 );
		ptrBid = new BiddingObject(*((*new_bids)[0]));
		bids->push_back(ptrBid);
        saveDelete(new_bids);	
        saveDelete(manager);
		
		// Load the module
		string libname, path, ext, filename;
		libHandle_t libhandle = NULL;
    
		if (libname.empty()) {
			return NULL;
		}
    
        path = "../../src/.lib/";
		libname = "libtwoauction.so";
        // use '.so' as postfix if it is not yet there
        if (libname.substr(libname.size()-3,3) != ".so") {
            ext = ".so";
        }
	
        // construct filename of module including path and extension
        filename = path + libname + ext;
	
        // try to load the library module
        libhandle = dlopen(filename.c_str(), RTLD_LAZY);
        if (!libhandle) {

			fprintf(stderr, "%s\n", dlerror());
		}
        
        if (libhandle == NULL) {
            // try to load without .so extension (cater for libtool bug)
            filename = path + libname;
            
            libhandle = dlopen(filename.c_str(), RTLD_LAZY);
            if (libhandle == NULL) {
                throw Error("cannot load module '%s': %s", 
                            libname.c_str(), (char *) dlerror());
            }
        }
        
        // dlopen succeeded, now check what module we have there 
        // everything went fine up to now -> create new module info entry
        {
            int magic = fetchMagic(libhandle);

            
            if (magic == PROC_MAGIC) {
                module = new ProcModule(conf, libname, filename, libhandle, group);
            } else {
                throw Error("unsupported module type (unknown magic number)");
            }
        }
	
        module->link();             // increase sue counter in this module

		// Finally, we create the bidding object manager required to execute the auction.
		int domain = 11;
		const string fieldname = DEF_SYSCONFDIR "/fielddef.xml";
		const string fieldValuename = DEF_SYSCONFDIR "/fieldval.xml";		
		manager = new BiddingObjectManager(domain, fieldname, fieldValuename);

	}
	catch(Error &e){
		std::cout << "Error:" << e.getError() << std::endl << std::flush;

        if (module) {
            saveDelete(module);
        }
        if (libhandle) {
            dlclose(libhandle);
        }
        throw e;
	}
}

void twoauction_Test::tearDown() 
{
	if (module != NULL){
		module->unlink();
		saveDelete(module);
	}
	
	if (manager != NULL){
		saveDelete(manager);
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
	
	actProcess.getAPI()->execute(manager->getFieldDefs(),
								 manager->getFieldVals(),
								 actProcess.getParams(), 
								 auctionSet, auctionName,
								 start, stop, bids, &ptr );
	
}
