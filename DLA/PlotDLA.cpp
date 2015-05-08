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

void plotDLA(HLSlit& hl, Plot& pl) {
    vector<Particle> particles = hl.getParticles();
    for (auto it = particles.begin(); it != particles.end(); ++it) {
        pl.drawLine( (*it).getLine(), Scalar(0,0,0) );
    }
    
    vector<Loop> loops = hl.getOuterLoops();
    for (auto it = loops.begin(); it != loops.end(); ++it) {
        pl.drawLoop( (*it).getLoop(), Scalar(0,0,255));
    }

    pl.drawCircle(0.0, 1.0, Scalar(0,0,0));
}