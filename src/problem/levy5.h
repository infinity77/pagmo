/*****************************************************************************
 *   Copyright (C) 2004-2009 The PaGMO development team,                     *
 *   Advanced Concepts Team (ACT), European Space Agency (ESA)               *
 *   http://apps.sourceforge.net/mediawiki/pagmo                             *
 *   http://apps.sourceforge.net/mediawiki/pagmo/index.php?title=Developers  *
 *   http://apps.sourceforge.net/mediawiki/pagmo/index.php?title=Credits     *
 *   act@esa.int                                                             *
 *                                                                           *
 *   This program is free software; you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation; either version 2 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with this program; if not, write to the                           *
 *   Free Software Foundation, Inc.,                                         *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.               *
 *****************************************************************************/

#ifndef PAGMO_PROBLEM_LEVY5_H
#define PAGMO_PROBLEM_LEVY5_H

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/version.hpp>
#include <string>

#include "../types.h"
#include "base.h"

namespace pagmo{ namespace problem {

/// The Levy5 problem.
/**
 *
 * This is a box-constrained continuous single-objecive problem.
 * The objective function is the generalised n-dimensional Levy5 function. This, in two dimensions,
 * can be written as:
 *
 * \f[
 * 	F(x,y) = \sum_{i=1}^5 i\cos[(i-1)x + i]\sum_{j=1}^5 j\cos[(j+1)x + j] +
	(x+1.42513)^2 + (y+0.00832)^2, x,y \in \left[ -100,100 \right].
 * \f]
 *
 * The global minimum in two dimension is in \f$x=-1.30685, y=-1.424845\f$, where \f$ F = -176.1375 \f$. The function
 * is here implemented as fully scalable so that it can be instantiated in any dimension.
 *
 * @see http://arxiv.org/pdf/physics/0402085
 *
 * @author Dario Izzo (dario.izzo@esa.int)
 */

class __PAGMO_VISIBLE levy5 : public base
{
	public:
		levy5(int);
		base_ptr clone() const;
		std::string get_name() const;
	protected:
		void objfun_impl(fitness_vector &, const decision_vector &) const;
	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive &ar, const unsigned int /*version*/){
			ar & boost::serialization::base_object<base>(*this);
		}
};

template<class Archive>
inline void save_construct_data( Archive & ar, const levy5 *t, const unsigned int /*file_version*/) {
    // save data required to construct instance
	int n;
	n = t->get_dimension();
    ar << n;
}

template<class Archive>
inline void load_construct_data( Archive & ar, levy5 *t, const unsigned int /*file_version*/) {
    // retrieve data from archive required to construct new instance
    int n;
    ar >> n;
    // invoke inplace constructor to initialize instance of my_class
    ::new(t)levy5(n);
}

}} //namespaces

#endif // PAGMO_PROBLEM_LEVY_H
