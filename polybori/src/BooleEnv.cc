// -*- c++ -*-
//*****************************************************************************
/** @file BooleEnv.cc
 *
 * @author Alexander Dreyer
 * @date 2006-03-06
 *
 * This file implements the class BooleEnv, which hold global structures.
 * a polynomial ring over Booleans. 
 *
 * @par Copyright:
 *   (c) 2007 by The PolyBoRi Team
 *
 * @internal 
 * @version \$Id$
 *
 * @par History:
 * @verbatim
 * $Log$
 * Revision 1.1  2007/12/13 15:53:49  dreyer
 * CHANGE: Ordering in BoolePolyRing again; BooleEnv manages active ring
 *
 * @endverbatim
**/
//*****************************************************************************


// load header file
# include "BooleEnv.h"
# include "BoolePolyRing.h"
#include "OrderedManager.h"

BEGIN_NAMESPACE_PBORI



// Note, direct access via friends, to  active_ring.pOrder and pMgt, because
// inline doesn't work up to now, because os the undefined type issue.



BooleEnv::block_iterator 
BooleEnv::blockBegin() {

  return active_ring.pOrder->blockBegin();
}

BooleEnv::block_iterator
BooleEnv::blockEnd() {

  return active_ring.pOrder->blockEnd();
}

void BooleEnv::appendBlock(idx_type idx) {

  active_ring.pOrder->appendBlock(idx);
}

void BooleEnv::clearBlocks() {

  active_ring.pOrder->clearBlocks();
}



BooleEnv::idx_type
BooleEnv::lastBlockStart() {
  return active_ring.lastBlockStart();
}




BooleEnv::manager_type& BooleEnv::manager() {
  return ring().manager(); }
BooleEnv::order_type& BooleEnv::ordering() { 
  return  ring().ordering(); }

BooleEnv::ring_type BooleEnv::active_ring;


  /// Get empty decision diagram
BooleEnv::dd_type BooleEnv::zero() { return ring().zero(); }

  /// Get decision diagram with all variables negated
BooleEnv::dd_type BooleEnv::one() { return ring().one(); }

  /// Get number of ring variables the of active ring
BooleEnv::size_type BooleEnv::nVariables() { 
  return manager().nVariables(); 
}





  /// Set name of variable with index idx
void 
BooleEnv::setVariableName(idx_type idx, vartext_type varname) {
  manager().setVariableName(idx, varname);
}

  /// Get name of variable with index idx
BooleEnv::vartext_type 
BooleEnv::getVariableName(idx_type idx){
  return manager().getVariableName(idx);
}


  /// Change order of current ring
void 
BooleEnv::changeOrdering(ordercode_type code) {
    ring().changeOrdering(code);
}




  /// Get numerical code for current ordering
BooleEnv::ordercode_type BooleEnv::getOrderCode() { 
  return ordering().getOrderCode();
}

  /// Get numerical code for current base ordering 
  /// (the same for non-block orderings)
BooleEnv::ordercode_type BooleEnv::getBaseOrderCode() { 
  return ordering().getBaseOrderCode(); 
}


void
BooleEnv::printInfo() {

  return ring().printInfo();
}



  /// Access idx-th variable of the active ring
BooleEnv::dd_type BooleEnv::variable(idx_type idx) { 
  return manager().variable(idx); 
} 


  /// Access idx-th variable
BooleEnv::dd_type BooleEnv::persistentVariable(idx_type idx) {
    return manager().persistentVariable(idx); 
  }


void BooleEnv::set(ring_type& theRing) { active_ring = theRing; }


END_NAMESPACE_PBORI