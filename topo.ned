// Generated NED file for the TicToc9 simulation.
// This file outlines the network configuration using Tic9 and Toc9 modules.

import ned.IdealChannel;

simple Tic9
{
    parameters:
        @display("i=block/routing");
    gates:
        input in[];
        output out[];
        input in_c[];
        output out_c[];
}

simple Toc9
{
    parameters:
        @display("i=block/process");
    gates:
        input in[];
        output out[];
}

network Network
{
    @display("bgb=555,405");
    submodules:
        tic0: Tic9 { @display("i=,cyan;p=58,238"); }
        tic1: Tic9 { @display("i=,cyan;p=278,238"); }
        tic2: Tic9 { @display("i=,cyan;p=498,238"); }
        tic3: Tic9 { @display("i=,cyan;p=718,238"); }
        toc0: Toc9 { @display("i=,gold;p=81,100"); }
        toc1: Toc9 { @display("i=,gold;p=154,100"); }
        toc2: Toc9 { @display("i=,gold;p=227,100"); }
        toc3: Toc9 { @display("i=,gold;p=300,100"); }

    connections:
       tic0.out++ --> {  delay = 200ms; } --> toc0.in++;
       toc0.out++ --> {  delay = 200ms; } --> tic0.in++;
       tic0.out++ --> {  delay = 200ms; } --> toc1.in++;
       toc1.out++ --> {  delay = 200ms; } --> tic0.in++;
       tic0.out++ --> {  delay = 200ms; } --> toc2.in++;
       toc2.out++ --> {  delay = 200ms; } --> tic0.in++;
       tic0.out++ --> {  delay = 200ms; } --> toc3.in++;
       toc3.out++ --> {  delay = 200ms; } --> tic0.in++;
       tic1.out++ --> {  delay = 200ms; } --> toc0.in++;
       toc0.out++ --> {  delay = 200ms; } --> tic1.in++;
       tic1.out++ --> {  delay = 200ms; } --> toc1.in++;
       toc1.out++ --> {  delay = 200ms; } --> tic1.in++;
       tic1.out++ --> {  delay = 200ms; } --> toc2.in++;
       toc2.out++ --> {  delay = 200ms; } --> tic1.in++;
       tic1.out++ --> {  delay = 200ms; } --> toc3.in++;
       toc3.out++ --> {  delay = 200ms; } --> tic1.in++;
       tic2.out++ --> {  delay = 200ms; } --> toc0.in++;
       toc0.out++ --> {  delay = 200ms; } --> tic2.in++;
       tic2.out++ --> {  delay = 200ms; } --> toc1.in++;
       toc1.out++ --> {  delay = 200ms; } --> tic2.in++;
       tic2.out++ --> {  delay = 200ms; } --> toc2.in++;
       toc2.out++ --> {  delay = 200ms; } --> tic2.in++;
       tic2.out++ --> {  delay = 200ms; } --> toc3.in++;
       toc3.out++ --> {  delay = 200ms; } --> tic2.in++;
       tic3.out++ --> {  delay = 200ms; } --> toc0.in++;
       toc0.out++ --> {  delay = 200ms; } --> tic3.in++;
       tic3.out++ --> {  delay = 200ms; } --> toc1.in++;
       toc1.out++ --> {  delay = 200ms; } --> tic3.in++;
       tic3.out++ --> {  delay = 200ms; } --> toc2.in++;
       toc2.out++ --> {  delay = 200ms; } --> tic3.in++;
       tic3.out++ --> {  delay = 200ms; } --> toc3.in++;
       toc3.out++ --> {  delay = 200ms; } --> tic3.in++;
       tic0.out_c++ --> {  delay = 200ms; } --> tic1.in_c++;
       tic1.out_c++ --> {  delay = 200ms; } --> tic0.in_c++;
       tic0.out_c++ --> {  delay = 200ms; } --> tic2.in_c++;
       tic2.out_c++ --> {  delay = 200ms; } --> tic0.in_c++;
       tic0.out_c++ --> {  delay = 200ms; } --> tic3.in_c++;
       tic3.out_c++ --> {  delay = 200ms; } --> tic0.in_c++;
       tic1.out_c++ --> {  delay = 200ms; } --> tic2.in_c++;
       tic2.out_c++ --> {  delay = 200ms; } --> tic1.in_c++;
       tic1.out_c++ --> {  delay = 200ms; } --> tic3.in_c++;
       tic3.out_c++ --> {  delay = 200ms; } --> tic1.in_c++;
       tic2.out_c++ --> {  delay = 200ms; } --> tic3.in_c++;
       tic3.out_c++ --> {  delay = 200ms; } --> tic2.in_c++;
}