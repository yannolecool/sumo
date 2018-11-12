/****************************************************************************/
// Eclipse SUMO, Simulation of Urban MObility; see https://eclipse.org/sumo
// Copyright (C) 2001-2018 German Aerospace Center (DLR) and others.
// This program and the accompanying materials
// are made available under the terms of the Eclipse Public License v2.0
// which accompanies this distribution, and is available at
// http://www.eclipse.org/legal/epl-v20.html
// SPDX-License-Identifier: EPL-2.0
/****************************************************************************/
/// @file    MSCFModel_KraussX.cpp
/// @author  Tobias Mayer
/// @author  Daniel Krajzewicz
/// @author  Jakob Erdmann
/// @author  Michael Behrisch
/// @author  Laura Bieker
/// @date    Mon, 04 Aug 2009
/// @version $Id$
///
// Krauss car-following model, changing accel and speed by slope
/****************************************************************************/


// ===========================================================================
// included modules
// ===========================================================================
#include <config.h>

#include <microsim/lcmodels/MSAbstractLaneChangeModel.h>
#include <microsim/MSVehicle.h>
#include <microsim/MSNet.h>
#include "MSCFModel_KraussX.h"


#define OVERBRAKING_THRESHOLD -3

// ===========================================================================
// method definitions
// ===========================================================================
MSCFModel_KraussX::MSCFModel_KraussX(const MSVehicleType* vtype):
    MSCFModel_Krauss(vtype),
    myTmp1(vtype->getParameter().getCFParam(SUMO_ATTR_TMP1, 0.0)),
    myTmp2(vtype->getParameter().getCFParam(SUMO_ATTR_TMP2, 0.0)) {
}


MSCFModel_KraussX::~MSCFModel_KraussX() {}


MSCFModel*
MSCFModel_KraussX::duplicate(const MSVehicleType* vtype) const {
    return new MSCFModel_KraussX(vtype);
}


double
MSCFModel_KraussX::patchSpeedBeforeLC(const MSVehicle* veh, double vMin, double vMax) const {
    return dawdleX(veh->getSpeed(), vMin, vMax, veh->getRNG());
}


double
MSCFModel_KraussX::dawdleX(double vOld, double vMin, double vMax, std::mt19937* rng) const {
    double speed = vMax;
    if (!MSGlobals::gSemiImplicitEulerUpdate) {
        // in case of the ballistic update, negative speeds indicate
        // a desired stop before the completion of the next timestep.
        // We do not allow dawdling to overwrite this indication
        if (speed < 0) {
            return speed;
        }
    }
    // extra slow to start
    if (vOld < myAccel) {
        speed -= ACCEL2SPEED(myTmp1 * myAccel);
    }
    const double random = RandHelper::rand(rng);
    speed -= ACCEL2SPEED(myDawdle * myAccel * random);
    // overbraking
    if (vOld > vMax) {
        speed -= ACCEL2SPEED(myTmp2 * myAccel * random);
        //std::cout << " vMin=" << vMin << " vMax=" << vMax << "speed=" << speed << " d1=" << ACCEL2SPEED(myDawdle * myAccel * random) << " d2=" << ACCEL2SPEED(myTmp2 * myAccel * random) << " unexpectedDecel=" << (speed < vMin) << "\n";
        if (MSGlobals::gSemiImplicitEulerUpdate) {
            speed = MAX2(0.0, speed);
        }
    }
    speed = MAX2(vMin, speed);
    return speed;
}



/****************************************************************************/
