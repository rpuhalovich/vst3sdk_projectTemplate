// created by Ryan Puhalovich - http://github.com/rpuhalovich
// relies on a biquad object to do the calculations - this object
// just calculates the coeffs of a biquad

#pragma once

#include <fxobjects.h>
#include "SimpleBiquad.hpp"

#define DEQUALS_PRECISION 0.00001

enum class FilterType {
    LPF2,
    HPF2,
    BPF,
    BSF,
    LSF,
    HSF,
    PEQ,
    OFF
};

// changable parameters of the filter
struct FilterParameters {
    FilterParameters& operator=(const FilterParameters& params) {
        if (this == &params) return *this;
        fc = params.fc;
        Q = params.Q;
        boost = params.boost;
        type = params.type;
        return *this;
    }
    FilterType type = FilterType::LPF2;
    double fc = 100.0f; // cut off frequency
    double Q = 0.707f;
    double boost = 0.0f;
};

class Filter : public IAudioSignalProcessor {
public:
    virtual bool reset(double _sampleRate);
    virtual double processAudioSample(double xn); // this is not where the coeffs are to be calculated
    virtual bool canProcessAudioFrame();

    FilterParameters getParameters();

    // sets the parameters and also calcs the new coeffs resulting from parameter changes
    void setParameters(const FilterParameters& parameters);
private:
    Coefficient coeffs;
    SimpleBiquad biquad;
    FilterParameters params;
    double sampleRate = 44100.0f;

    // returns true if coeffs were calculated
    bool calculateCoeffs();
};
