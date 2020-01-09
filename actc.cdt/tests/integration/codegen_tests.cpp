#include <boost/test/unit_test.hpp>
#include <actc/testing/tester.hpp>
#include <actc/chain/abi_serializer.hpp>

#include <Runtime/Runtime.h>

#include <fc/variant_object.hpp>

#include <contracts.hpp>

using namespace actc;
using namespace actc::testing;
using namespace actc::chain;
using namespace actc::testing;
using namespace fc;

using mvo = fc::mutable_variant_object;

BOOST_AUTO_TEST_SUITE(codegen_tests)

BOOST_FIXTURE_TEST_CASE( simple_tests, tester ) try {
   create_accounts( { N(test), N(actc.token), N(someone), N(other) } );
   produce_block();

   set_code( N(actc.token), contracts::transfer_wasm() );
   set_abi(  N(actc.token),  contracts::transfer_abi().data() );

   set_code( N(someone), contracts::transfer_wasm() );
   set_abi(  N(someone),  contracts::transfer_abi().data() );

   set_code( N(test), contracts::simple_wasm() );
   set_abi( N(test),  contracts::simple_abi().data() );

   set_code( N(other), contracts::simple_wasm() );
   set_abi( N(other),  contracts::simple_abi().data() );

   produce_blocks();
   push_action(N(test), N(test1), N(test), 
         mvo()
         ("nm", "bucky"));

   BOOST_CHECK_THROW(push_action(N(test), N(test1), N(test), mvo()("nm", "notbucky")), 
         fc::exception);

   push_action(N(test), N(test2), N(test), 
         mvo()
         ("arg0", 33)
         ("arg1", "some string"));
   BOOST_CHECK_THROW(push_action(N(test), N(test2), N(test), mvo() ("arg0", 30)("arg1", "some string")), fc::exception);
   BOOST_CHECK_THROW(push_action(N(test), N(test2), N(test), mvo() ("arg0", 33)("arg1", "not some string")), fc::exception);

   set_abi( N(test),  contracts::simple_wrong_abi().data() );
   produce_blocks();
  
   BOOST_CHECK_THROW(push_action(N(test), N(test3), N(test), mvo() ("arg0", 33) ("arg1", "some string")), fc::exception);

   set_abi( N(test),  contracts::simple_abi().data() );
   produce_blocks();

   push_action(N(test), N(test4), N(test), mvo() ("to", "someone"));
   push_action(N(test), N(test5), N(test), mvo() ("to", "someone"));
   push_action(N(test), N(testa), N(test), mvo() ("to", "someone"));
   BOOST_CHECK_THROW(push_action(N(test), N(testb), N(test), mvo() ("to", "someone")), fc::exception);

   // test that the pre_dispatch will short circuit dispatching if false
   push_action(N(test), N(testc), N(test), mvo() ("nm", "bucky"));
   BOOST_CHECK_THROW(push_action(N(test), N(testc), N(test), mvo() ("nm", "someone")), fc::exception);
   push_action(N(test), N(testc), N(test), mvo() ("nm", "quit"));

} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( simple_actc_tests, tester ) try {
   set_code( N(actc), contracts::simple_wasm() );
   set_abi( N(actc),  contracts::simple_wrong_abi().data() );
   produce_blocks();
   push_action(N(actc), N(test1), N(actc),
         mvo()
         ("nm", "bucky"));

   BOOST_CHECK_THROW(push_action(N(actc), N(test1), N(actc), mvo()("nm", "notbucky")),
         fc::exception);

   push_action(N(actc), N(test2), N(actc),
         mvo()
         ("arg0", 33)
         ("arg1", "some string"));
   BOOST_CHECK_THROW(push_action(N(actc), N(test2), N(actc), mvo() ("arg0", 30)("arg1", "some string")), fc::exception);
   BOOST_CHECK_THROW(push_action(N(actc), N(test2), N(actc), mvo() ("arg0", 33)("arg1", "not some string")), fc::exception);
   
   push_action(N(actc), N(test3), N(actc),
         mvo()
         ("arg0", 33)
         ("arg1", "some string"));

} FC_LOG_AND_RETHROW() }