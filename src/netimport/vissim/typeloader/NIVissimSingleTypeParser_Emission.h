/****************************************************************************/
// Eclipse SUMO, Simulation of Urban MObility; see https://eclipse.org/sumo
// Copyright (C) 2001-2018 German Aerospace Center (DLR) and others.
// This program and the accompanying materials
// are made available under the terms of the Eclipse Public License v2.0
// which accompanies this distribution, and is available at
// http://www.eclipse.org/legal/epl-v20.html
// SPDX-License-Identifier: EPL-2.0
/****************************************************************************/
/// @file    NIVissimSingleTypeParser_Emission.h
/// @author  Daniel Krajzewicz
/// @date    Wed, 30 Apr 2003
/// @version $Id$
///
//
/****************************************************************************/
#ifndef NIVissimSingleTypeParser_Emission_h
#define NIVissimSingleTypeParser_Emission_h


// ===========================================================================
// included modules
// ===========================================================================
#include <config.h>

#include <iostream>
#include "../NIImporter_Vissim.h"


// ===========================================================================
// class definitions
// ===========================================================================
/**
 * @class NIVissimSingleTypeParser_Emission
 *
 */
class NIVissimSingleTypeParser_Emission :
    public NIImporter_Vissim::VissimSingleTypeParser {
public:
    /// Constructor
    NIVissimSingleTypeParser_Emission(NIImporter_Vissim& parent);

    /// Destructor
    ~NIVissimSingleTypeParser_Emission();

    /// Parses the data type from the given stream
    bool parse(std::istream& from);

};


#endif

/****************************************************************************/

