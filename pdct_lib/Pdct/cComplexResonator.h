
/* 
 * File:   cComplexResonator.h
 * Author: luciamarock
 *
 * Created on 11 novembre 2016, 21.56
 */

#ifndef CCOMPLEXRESONATOR_H
#define CCOMPLEXRESONATOR_H

#include "cComplex.h"


/* First order complex resonator */
class cComplexResonator {
private:
    cComplex m_b0;
    cComplex m_a1;
    cComplex m_out;
public:
    cComplexResonator();
    cComplexResonator(const cComplexResonator& orig);
    virtual ~cComplexResonator();
public:
    void setCoef_a1(cComplex coef)
    {
        m_a1 = coef;
    }
    cComplex getCoef_a1()
    {
        return m_a1;
    }
    void setCoef_b0(cComplex gain)
    {
        m_b0 = gain;
    }
    cComplex getCoef_b0()
    {
        return m_b0;
    }
    void reset()
    {
        m_out = cComplex(0.0, 0.0);
    }
    void tick(const cComplex* in, cComplex* out)
    {
        /* first order resonator */
        m_out = m_b0*(*in) + m_a1*m_out;
        *out = m_out;
    }
};

#endif /* CCOMPLEXRESONATOR_H */

