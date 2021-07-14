// created by Ryan Puhalovich - http://github.com/rpuhalovich
// simple biquad written by me for practice - using the Transposed Canonical Form

#pragma once

#include <fxobjects.h>

struct Coefficient {
    Coefficient& operator=(const Coefficient& coeffs) {
        if (this == &coeffs) return *this;
        this->a0 = coeffs.a0;
        this->a1 = coeffs.a1;
        this->a2 = coeffs.a2;
        this->b1 = coeffs.b1;
        this->b2 = coeffs.b2;
        this->c0 = coeffs.c0;
        this->d0 = coeffs.d0;
        return *this;
    }

    double a0 = 0.0f;
    double a1 = 0.0f;
    double a2 = 0.0f;
    double b1 = 0.0f;
    double b2 = 0.0f;
    double c0 = 0.0f;
    double d0 = 0.0f;
};

struct StateReg {
    double x_z1 = 0.0f;
    double x_z2 = 0.0f;
    double y_z1 = 0.0f;
    double y_z2 = 0.0f;
};

class SimpleBiquad : public IAudioSignalProcessor {
public:
    virtual bool reset(double _sampleRate);
    virtual double processAudioSample(double xn);
    virtual bool canProcessAudioFrame();

    void setCoeffs(Coefficient coeffs);
    void clearCoeffs();
private:
    Coefficient coeffs;
    StateReg regs;
    double sampleRate = 44100.0f;
};
