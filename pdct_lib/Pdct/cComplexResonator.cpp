/* 
 * File:   cComplexResonator.cpp
 * Author: luciamarock
 * 
 * Created on 11 novembre 2016, 21.56
 */

#include "cComplexResonator.h"

cComplexResonator::cComplexResonator():
       m_b0(1.0, 0.0),
       m_a1(0.0, 0.0),
       m_out(0.0, 0.0) 
{
    
}

cComplexResonator::cComplexResonator(const cComplexResonator& orig):
       m_b0(1.0, 0.0),
       m_a1(orig.m_a1),
       m_out(orig.m_out)
{
    
}

cComplexResonator::~cComplexResonator() 
{
    
}

