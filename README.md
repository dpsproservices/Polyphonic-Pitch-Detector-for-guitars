# README #

This is a pitch detection application for Linux based on complex resonators and optimized for Guitar Input. Theory of complex resonators are described in the article: "A Computationally Efficient Method for Polyphonic Pitch Estimation" [Ruohua Zhou,  Joshua D. Reiss,  Marco Mattavelli,  and Giorgio Zoia ]. 

This is the C++ version of the MatLab algorithm presented in --> http://luciama.altervista.org/otherworks.html  (Polyphonic Pitch Detector for guitars)

The system is still under development in order to implement frequency domain effects like the ones briefly showed at: http://lushmaroon.altervista.org/my-project.html?cb=1495296000881


# HOW to build
$cd pdct
$mkdir build
$cd build
$cmake ..
$make


#How to run
cd build
./pdct
