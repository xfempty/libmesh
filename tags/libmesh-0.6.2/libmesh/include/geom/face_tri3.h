// $Id: face_tri3.h,v 1.15 2007-10-21 20:48:41 benkirk Exp $

// The libMesh Finite Element Library.
// Copyright (C) 2002-2007  Benjamin S. Kirk, John W. Peterson
  
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
  
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
  
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA



#ifndef __tri3_h__
#define __tri3_h__


// C++ includes


// Local includes
#include "libmesh_common.h"
#include "face_tri.h"


// Forward declarations

/**
 * The \p Tri3 is an element in 2D composed of 3 nodes.
 * It is numbered like this:
 * \verbatim
 *   TRI3:  2      
 *          o      
 *         / \     
 *        /   \    
 *       /     \   
 *      /       \  
 *     /         \ 
 *    o-----------o
 *    0           1
 * \endverbatim
 */

// ------------------------------------------------------------
// Tri3 class definition
class Tri3 : public Tri
{
public:

  /**
   * Constructor.  By default this element has no parent.
   */
  Tri3 (Elem* p=NULL) :
    Tri(Tri3::n_nodes(), p) {}

  /**
   * Constructor.  Explicitly specifies the number of
   * nodes and neighbors for which storage will be allocated.
   */
  Tri3 (const unsigned int nn,
	const unsigned int ns,
	Elem* p) :
    Tri(nn, ns, p) {}

  /**
   * @returns \p TRI3
   */
  ElemType type () const { return TRI3; }

  /**
   * @returns 1
   */
  unsigned int n_sub_elem() const { return 1; }
  
  /**
   * @returns true iff the specified (local) node number is a vertex.
   */
  virtual bool is_vertex(const unsigned int i) const;

  /**
   * @returns true iff the specified (local) node number is an edge.
   */
  virtual bool is_edge(const unsigned int i) const;

  /**
   * @returns true iff the specified (local) node number is a face.
   */
  virtual bool is_face(const unsigned int i) const;
  
  /*
   * @returns true iff the specified (local) node number is on the
   * specified side
   */
  virtual bool is_node_on_side(const unsigned int n,
			       const unsigned int s) const;
  
  /*
   * @returns true iff the specified (local) node number is on the
   * specified edge (== is_node_on_side in 2D)
   */
  virtual bool is_node_on_edge(const unsigned int n,
			       const unsigned int e) const
  { return this->is_node_on_side(n,e); }
  
  /*
   * @returns true iff the element map is definitely affine within
   * numerical tolerances
   */
  virtual bool has_affine_map () const { return true; }

  /**
   * @returns FIRST
   */
  Order default_order() const { return FIRST; }

  AutoPtr<Elem> build_side (const unsigned int i,
			    bool proxy) const;

  virtual void connectivity(const unsigned int sf,
			    const IOPackage iop,
			    std::vector<unsigned int>& conn) const;

  /**
   * This maps the \f$ j^{th} \f$ node of the \f$ i^{th} \f$ side to
   * element node numbers.
   */
  static const unsigned int side_nodes_map[3][2];


  /**
   * An optimized method for computing the area of a 3-node triangle.
   */
  virtual Real volume () const;

  /**
   * Returns the minimum and maximum angles for the triangle
   * (in radians) in a std::pair.  The first entry in the pair
   * is the minimum angle, the second entry is the max angle.
   */
  std::pair<Real, Real> min_and_max_angle() const;
  
protected:

  
#ifdef ENABLE_AMR
  
  /**
   * Matrix used to create the elements children.
   */
  float embedding_matrix (const unsigned int i,
			  const unsigned int j,
			  const unsigned int k) const
  { return _embedding_matrix[i][j][k]; }

  /**
   * Matrix that computes new nodal locations/solution values
   * from current nodes/solution.
   */
  static const float _embedding_matrix[4][3][3];
  
#endif
    
};


#endif