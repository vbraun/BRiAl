// -*- c++ -*-
//*****************************************************************************
/** @file BlockDegLexOrder.cc
 *
 * @author Alexander Dreyer
 * @date 2006-05-18
 *
 * Defining Degree-lexicographical ordering.
 *
 * @par Copyright:
 *   (c) 2007 by
 *   Dep. of Mathematics, Kaiserslautern University of Technology and @n
 *   Fraunhofer Institute for Industrial Mathematics (ITWM)
 *   D-67663 Kaiserslautern, Germany
 *
 * @internal 
 * @version \$Id$
 *
 * @par History:
 * @verbatim
 * $Log$
 * Revision 1.1  2007/03/21 08:55:09  dreyer
 * ADD: first version of block_dlex running
 *
 * @endverbatim
**/
//*****************************************************************************

// include  definitions


#include "BlockDegLexOrder.h"

#include "pbori_algo.h"
#include "PBoRiOutIter.h"
#include "CIdxPath.h"


#include "CDelayedTermIter.h"

// get internal routines
#include "pbori_routines.h"

#include "CDegLexIter.h"


#include "CDegreeCache.h"

#include "BooleSet.h"

BEGIN_NAMESPACE_PBORI



// Comparison of monomials
BlockDegLexOrder::comp_type
BlockDegLexOrder::compare(const monom_type& lhs, const monom_type& rhs) const {
  
  PBORI_TRACE_FUNC( 
    "BlockDegLexOrder::compare(const monom_type&, const monom_type&) const)" );

  return block_dlex_compare(lhs.begin(), lhs.end(),
                            rhs.begin(), rhs.end(),
                            blockBegin(), blockEnd(),
                            idx_comparer_type() );
}

// Comparison of monomials
BlockDegLexOrder::comp_type
BlockDegLexOrder::compare(const exp_type& lhs, const exp_type& rhs) const {
  
  PBORI_TRACE_FUNC( 
    "BlockDegLexOrder::compare(const exp_type&, const exp_type&) const)" );

  return block_dlex_compare(lhs.begin(), lhs.end(),
                            rhs.begin(), rhs.end(),
                            blockBegin(), blockEnd(),
                            idx_comparer_type() );

}

// Comparison of monomials
BlockDegLexOrder::comp_type
BlockDegLexOrder::compare(idx_type lhs, idx_type rhs) const {
  
  PBORI_TRACE_FUNC( 
    "BlockDegLexOrder::compare(monom_type, monom_type) const)" );

  return generic_compare_3way(lhs, rhs, idx_comparer_type());
}

// Extraction of leading term
BlockDegLexOrder::monom_type 
BlockDegLexOrder::lead(const poly_type& poly) const {

  PBORI_TRACE_FUNC( "BlockDegLexOrder::lead(const poly_type&) const)" );

  CBlockDegreeCache<> blockDegCache(poly.diagram().manager());

  CCacheManagement<CCacheTypes::block_dlex_lead> cache_mgr(poly.diagram().manager());


  return monom(  dd_block_degree_lead(cache_mgr, blockDegCache, 
                                      poly.navigation(), 
                                      m_indices.begin(),
                                      BooleSet(), 
                                      descending_property()) );

}

// Extraction of leading term
BlockDegLexOrder::monom_type 
BlockDegLexOrder::lead(const poly_type& poly, size_type bound) const {

  PBORI_TRACE_FUNC( "BlockDegLexOrder::lead(const poly_type&, size_type) const)" );

  return lead(poly);
}


// maybe common template here
// Extraction of leading exponent
BlockDegLexOrder::exp_type 
BlockDegLexOrder::leadExp(const poly_type& poly) const {

  PBORI_TRACE_FUNC( "BlockDegLexOrder::leadexp(const poly_type&) const)" );

  return exp_type(lead(poly).exp());
}

// maybe common template here
// Extraction of leading exponent
BlockDegLexOrder::exp_type 
BlockDegLexOrder::leadExp(const poly_type& poly, size_type bound) const {

  PBORI_TRACE_FUNC( "BlockDegLexOrder::leadexp(const poly_type&, size_type) const)");
  return leadExp(poly);
}


// Initialize iterator corresponding to leading term
BlockDegLexOrder::iterator
BlockDegLexOrder::leadIterator(const poly_type& poly) const {

  PBORI_TRACE_FUNC( "BlockDegLexOrder::leadIterator(const poly_type& poly) const" );

  return iterator();//generic_iteration<self, iterator>().leadIterator(poly);  
}

// Initialize iterator corresponding to leading term
BlockDegLexOrder::indirect_iterator
BlockDegLexOrder::leadIteratorBegin(const poly_type& poly) const {

  PBORI_TRACE_FUNC( "BlockDegLexOrder::leadIteratorBegin(const poly_type& poly) const" );

  //  return generic_iteration<self, iterator>().leadIterator(poly);
  typedef CGenericCore<self, poly_type, delayed_iterator, monom_type, delayed_iterator>
    iterator_core; 
  typedef CAbstractIterCore<COrderBase::delayed_iterator, monom_type> base_core;
  typedef PBORI_SHARED_PTR(base_core) core_pointer;
  return indirect_iterator(core_pointer(new iterator_core(poly)));
}

BlockDegLexOrder::indirect_iterator
BlockDegLexOrder::leadIteratorEnd() const {

  PBORI_TRACE_FUNC( "BlockDegLexOrder::leadIteratorEnd() const" );

  typedef CGenericCore<self, poly_type, delayed_iterator, monom_type, delayed_iterator>
    iterator_core; 
  typedef CAbstractIterCore<delayed_iterator, monom_type> base_core;
  typedef PBORI_SHARED_PTR(base_core) core_pointer;
  return indirect_iterator(core_pointer(new iterator_core()));
}

// Initialize iterator corresponding to leading term
BlockDegLexOrder::indirect_exp_iterator
BlockDegLexOrder::leadExpIteratorBegin(const poly_type& poly) const {

  PBORI_TRACE_FUNC( "BlockDegLexOrder::leadExpIteratorBegin(const poly_type& poly) const" );

  //  return generic_iteration<self, iterator>().leadIterator(poly);
  typedef CGenericCore<self, poly_type, delayed_iterator, exp_type, delayed_iterator>
    iterator_core; 
  typedef CAbstractIterCore<COrderBase::delayed_iterator, exp_type> base_core;
  typedef PBORI_SHARED_PTR(base_core) core_pointer;
  return indirect_exp_iterator(core_pointer(new iterator_core(poly)));
}

BlockDegLexOrder::indirect_exp_iterator
BlockDegLexOrder::leadExpIteratorEnd() const {

  PBORI_TRACE_FUNC( "BlockDegLexOrder::leadExpIteratorEnd() const" );

  typedef CGenericCore<self, poly_type, delayed_iterator, exp_type, delayed_iterator>
    iterator_core; 
  typedef CAbstractIterCore<delayed_iterator, exp_type> base_core;
  typedef PBORI_SHARED_PTR(base_core) core_pointer;
  return indirect_exp_iterator(core_pointer(new iterator_core()));
}

// Find next term (after iter) in polynomial according to current order
BlockDegLexOrder::iterator
BlockDegLexOrder::incrementIterator(iterator iter, const poly_type& poly) const {

  PBORI_TRACE_FUNC(
    "BlockDegLexOrder::incrementIterator(iterator, const poly_type&) const" );

 return iterator();//generic_iteration<self, iterator>().incrementIterator(iter, poly);
}

END_NAMESPACE_PBORI