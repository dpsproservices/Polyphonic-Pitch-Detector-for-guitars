
/* 
 * File:   cComplex.h
 * Author: luciamarock
 *
 * Created on 5 novembre 2016, 15.28
 */

#ifndef CCOMPLEX_H
#define CCOMPLEX_H

#include "common_type.h"

class cComplex {
private:
    //Real and imaginary part
    cFloat m_re;
    cFloat m_im;
    //Static
    static const cFloat dgrad;
public:
    //Constant imaginary unity
    static const cComplex i;
    static const cComplex j;
public:
    //Default constructor
    cComplex() : 
        m_re(0.0), 
        m_im(0.0) 
    {
        
    }
        
    //Real-Imaginary constructor
    cComplex(cFloat re, cFloat im) : 
        m_re(re), 
        m_im(im) 
    {
        
    }
    
    //Real Constructor
    cComplex(cFloat val) : 
        m_re(val), 
        m_im(0.0) 
    {
        
    }
    
    //Copy Constructor
    cComplex(const cComplex& orig) :
        m_re(orig.m_re), 
        m_im(orig.m_im) 
    {
        
    }
    
    //polar constructor
    static cComplex polar(cFloat magnitude, cFloat phase)
    {
        return cComplex(magnitude*cos(phase), magnitude*sin(phase));
    }
    
    //unity constructor
    static cComplex unity(cFloat phase)
    {
        return cComplex(cos(phase), sin(phase));
    }

    //Assignment Operator
    cComplex& operator=(const cFloat val) {
        m_re = val;
        m_im = 0.0;
        return *this;
    }
    cComplex& operator=(const cComplex& rhs) {
        m_re = rhs.m_re;
        m_im = rhs.m_im;
        return *this;
    }
    
    //Basic access
    cFloat re() const {
        return m_re;
    }
    void setRe(cFloat re) {
        m_re = re;
    }

    cFloat im() const {
        return m_im;
    }
    void setIm(cFloat im) {
        m_im = im;
    }

    //Conjugate number
    cComplex conjugate() const {
        return cComplex(m_re, -m_im);
    }

    //Norm
    cFloat norm() const {
        return m_re*m_re + m_im*m_im;
    }
    
    //Magnitude
    cFloat magnitude() { 
        return sqrt(m_re*m_re + m_im*m_im); 
    }
    
    //Phase
    cFloat phase() {
       return atan2(m_im,m_re); 
    }
    
    //Angle
    cFloat angle() { 
        return dgrad*atan2(m_im,m_re); 
    }

    //Arithmetic operations
    cComplex operator+(const cComplex& rhs) const {
        return cComplex(m_re + rhs.m_re, m_im + rhs.m_im);
    }

    cComplex operator-(const cComplex& rhs) const {
        return cComplex(m_re - rhs.m_re, m_im - rhs.m_im);
    }

    cComplex operator*(const cComplex& rhs) const {
        return cComplex(m_re * rhs.m_re - m_im * rhs.m_im,
                m_re * rhs.m_im + m_im * rhs.m_re);
    }

    cComplex operator/(const cComplex& rhs) const {
        cFloat denominator = rhs.m_re * rhs.m_re + rhs.m_im * rhs.m_im;
        return cComplex((m_re * rhs.m_re + m_im * rhs.m_im) / denominator,
                        (m_im * rhs.m_re - m_re * rhs.m_im) / denominator);
    }

    cComplex& operator+=(const cComplex& rhs) {
        m_re += rhs.m_re;
        m_im += rhs.m_im;
        return *this;
    }

    cComplex& operator-=(const cComplex& rhs) {
        m_re -= rhs.m_re;
        m_im -= rhs.m_im;
        return *this;
    }

    cComplex& operator*=(const cComplex& rhs) {
        const cFloat temp = m_re;
        m_re = m_re * rhs.m_re - m_im * rhs.m_im;
        m_im = m_im * rhs.m_re + temp * rhs.m_im;
        return *this;
    }

    cComplex& operator/=(const cComplex& rhs) {
        cFloat denominator = rhs.m_re * rhs.m_re + rhs.m_im * rhs.m_im;
        cFloat temp = m_re;
        m_re = (m_re * rhs.m_re + m_im * rhs.m_im) / denominator;
        m_im = (m_im * rhs.m_re - temp * rhs.m_im) / denominator;
        return *this;
    }

    cComplex& operator++() {
        ++m_re;
        return *this;
    }

    cComplex operator++(int) {
        cComplex temp(*this);
        ++m_re;
        return temp;
    }

    cComplex& operator--() {
        --m_re;
        return *this;
    }

    cComplex operator--(int) {
        cComplex temp(*this);
        --m_re;
        return temp;
    }

    cComplex operator+(const cFloat val) const {
        return cComplex(m_re + val, m_im);
    }

    cComplex operator-(const cFloat val) const {
        return cComplex(m_re - val, m_im);
    }

    cComplex operator*(const cFloat val) const {
        return cComplex(m_re * val, m_im * val);
    }

    cComplex operator/(const cFloat val) const {
        return cComplex(m_re / val, m_im / val);
    }

    cComplex& operator+=(const cFloat val) {
        m_re += val;
        return *this;
    }

    cComplex& operator-=(const cFloat val) {
        m_re -= val;
        return *this;
    }

    cComplex& operator*=(const cFloat val) {
        m_re *= val;
        m_im *= val;
        return *this;
    }

    cComplex& operator/=(const cFloat val) {
        m_re /= val;
        m_im /= val;
        return *this;
    }

    friend cComplex operator+(const cFloat left, const cComplex& right) {
        return cComplex(left + right.m_re, right.m_im);
    }

    friend cComplex operator-(const cFloat left, const cComplex& right) {
        return cComplex(left - right.m_re, -right.m_im);
    }

    friend cComplex operator*(const cFloat left, const cComplex& right) {
        return cComplex(left * right.m_re, left * right.m_im);
    }

    friend cComplex operator/(const cFloat left, const cComplex& right) {
        cFloat denominator = right.m_re * right.m_re + right.m_im * right.m_im;
        return cComplex(left * right.m_re / denominator,
                       -left * right.m_im / denominator);
    }

    //Boolean operators
    bool operator==(const cComplex &rhs) const {
        return (m_re == rhs.m_re) && (m_im == rhs.m_im);
    }

    bool operator!=(const cComplex &rhs) const {
        return (m_re != rhs.m_re) || (m_im != rhs.m_im);
    }

    bool operator==(const cFloat val) const {
        return (m_re == val) && (m_im == 0.0);
    }

    bool operator!=(const cFloat val) const {
        return (m_re != val) || (m_im != 0.0);
    }

    friend bool operator==(const cFloat left, const cComplex& right) {
        return (left == right.m_re) && (right.m_im == 0.0);
    }

    friend bool operator!=(const cFloat left, const cComplex& right) {
        return (left != right.m_re) || (right.m_im != 0.0);
    }
    
    //special function
    static cComplex exp(cComplex z)
    {
        return ::exp(z.re())*cComplex(cos(z.im()), sin(z.im()));
    }
};

#endif /* CCOMPLEX_H */

