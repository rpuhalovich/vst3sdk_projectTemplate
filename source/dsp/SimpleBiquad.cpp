// created by Ryan Puhalovich - http://github.com/rpuhalovich

#include "SimpleBiquad.hpp"

bool SimpleBiquad::reset(double _sampleRate) {
    SimpleBiquad::sampleRate = _sampleRate; // doesn't get used though
    return true; // success
}

double SimpleBiquad::processAudioSample(double xn) {
    // --- 1)  form output y(n) = a0*x(n) + a1*x(n-1) + a2*x(n-2) - b1*y(n-1) - b2*y(n-2)
    double yn = coeffs.a0 * xn + coeffs.a1 * regs.x_z1 + coeffs.a2 * regs.x_z2 -
                coeffs.b1 * regs.y_z1 - coeffs.b2 * regs.y_z2;

    // --- 2) underflow check
    checkFloatUnderflow(yn);

    // --- 3) update states
    regs.x_z2 = regs.x_z1;
    regs.x_z1 = xn;

    regs.y_z2 = regs.y_z1;
    regs.y_z1 = yn;

    // --- return value
    return yn;
}

bool SimpleBiquad::canProcessAudioFrame() { return false; }

void SimpleBiquad::setCoeffs(Coefficient coeffs) {
    this->coeffs = coeffs;
}

void SimpleBiquad::clearCoeffs() {
    this->coeffs.a0 = 0.0;
    this->coeffs.a1 = 0.0;
    this->coeffs.a2 = 0.0;
    this->coeffs.b1 = 0.0;
    this->coeffs.b2 = 0.0;
    this->coeffs.c0 = 0.0;
    this->coeffs.d0 = 0.0;
}
