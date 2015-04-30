//
//  PlotDLA.cpp
//  DLA
//
//  Created by Henry Jackson on 30/04/2015.
//  Copyright (c) 2015 n/a. All rights reserved.
//

#include "PlotDLA.h"

/////////////////////////////////////////////////////////////////////////////////
//// PlotDLA functions //////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

void PlotDLA(DLA& dla, Plot& pl) {
    vector<Particle> particles = dla.getParticles();
    for (auto it = particles.begin(); it != particles.end(); ++it) {
        pl.drawLine( (*it).getLine(), Scalar(0,0,0) );
    }
}