//
//  PlotDLA.h
//  DLA
//
//  Created by Henry Jackson on 30/04/2015.
//  Copyright (c) 2015 n/a. All rights reserved.
//

#ifndef __DLA__PlotDLA__
#define __DLA__PlotDLA__

#include <stdio.h>

#include "HLSlit.h"
#include "Particle.h"
#include "Plot.h"

void plotDLA(HLSlit& hl, Plot& pl);

/*
class PlotDLA {
private:
    DLA* dla;
    Plot* pl;
    void plotLines();
public:
    PlotDLA(DLA* d, Plot* pl);
    void output(const char* filename);
    void show();
};
*/
#endif /* defined(__DLA__PlotDLA__) */
