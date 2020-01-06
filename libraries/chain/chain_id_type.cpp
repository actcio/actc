/**
 *  @file
 *  @copyright defined in actc/LICENSE.txt
 */

#include <actc/chain/chain_id_type.hpp>
#include <actc/chain/exceptions.hpp>

namespace actc { namespace chain {

   void chain_id_type::reflector_verify()const {
      actc_ASSERT( *reinterpret_cast<const fc::sha256*>(this) != fc::sha256(), chain_id_type_exception, "chain_id_type cannot be zero" );
   }

} }  // namespace actc::chain

namespace fc {

   void to_variant(const actc::chain::chain_id_type& cid, fc::variant& v) {
      to_variant( static_cast<const fc::sha256&>(cid), v);
   }

   void from_variant(const fc::variant& v, actc::chain::chain_id_type& cid) {
      from_variant( v, static_cast<fc::sha256&>(cid) );
   }

} // fc
