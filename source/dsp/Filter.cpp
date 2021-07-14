// created by Ryan Puhalovich - http://github.com/rpuhalovich
// see the .hpp file for detailed comments

#include "Filter.hpp"

bool Filter::reset(double _sampleRate) {
    sampleRate = _sampleRate;
    calculateCoeffs();
    return true; // success
}

double Filter::processAudioSample(double xn) {
    return coeffs.d0 * xn + coeffs.c0 * biquad.processAudioSample(xn);
}

bool Filter::canProcessAudioFrame() { return false; }

bool Filter::calculateCoeffs() {
    // clear coeff struct
    biquad.clearCoeffs();
    
    // set default pass-through
    coeffs.a0 = 1.0;
    coeffs.c0 = 1.0;
    coeffs.d0 = 0.0;
    
    if (params.type == FilterType::LPF2) {
        // calculate filter coeffs
        double theta_c = (2 * kPi * params.fc) / sampleRate;
        double d = 1 / params.Q;
        double betaNum = 1.0 - ((d / 2.0) * sin(theta_c));
        double betaDen = 1.0 + ((d / 2.0) * sin(theta_c));
        double beta = 0.5 * (betaNum / betaDen);
        double gamma = (0.5 + beta) * (cos(theta_c));
        double alpha = (0.5 + beta - gamma) / 2.0;
        
        // assign filter coeffs
        coeffs.a0 = alpha;
        coeffs.a1 = 2.0 * alpha;
        coeffs.a2 = alpha;
        coeffs.b1 = -2.0 * gamma;
        coeffs.b2 = 2.0 * beta;
        
        biquad.setCoeffs(coeffs);
        return true; // coeffs were calculated
    } else if (params.type == FilterType::HPF2) {
        double theta_c = (2 * kPi * params.fc) / sampleRate;
        double d = 1 / params.Q;
        double betaNum = 1.0 - ((d / 2.0) * sin(theta_c));
        double betaDen = 1.0 + ((d / 2.0) * sin(theta_c));
        double beta = 0.5 * (betaNum / betaDen);
        double gamma = (0.5 + beta) * (cos(theta_c));
        double alpha = (0.5 + beta + gamma) / 2.0;
        
        coeffs.a0 = alpha;
        coeffs.a1 = -2.0 * alpha;
        coeffs.a2 = alpha;
        coeffs.b1 = -2.0 * gamma;
        coeffs.b2 = 2.0 * beta;
        
        biquad.setCoeffs(coeffs);
        return true;
    } else if (params.type == FilterType::BPF) {
        double K = tan((kPi * params.fc) / sampleRate);
        double delta = K * K * params.Q + K + params.Q;
        
        coeffs.a0 = K / delta;
        coeffs.a1 = 0.0;
        coeffs.a2 = (-K) / delta;
        coeffs.b1 = ( 2.0 * params.Q * (K * K - 1.0) ) / delta;
        coeffs.b2 = ( (K * K * params.Q) - K + params.Q ) / delta;
        
        biquad.setCoeffs(coeffs);
        return true;
    } else if (params.type == FilterType::BSF) {
        double K = tan((kPi * params.fc) / sampleRate);
        double delta = K * K * params.Q + K + params.Q;
        
        double alpha = (params.Q * (K * K + 1.0) ) / delta;
        double beta = (2.0 * params.Q * (K * K - 1.0) ) / delta;
        
        coeffs.a0 = alpha;
        coeffs.a1 = beta;
        coeffs.a2 = alpha;
        coeffs.b1 = beta;
        coeffs.b2 = ( (K * K * params.Q) - K + params.Q ) / delta;
        
        biquad.setCoeffs(coeffs);
        return true;
    } else if (params.type == FilterType::LSF) {
        double theta = (2.0 * kPi * params.fc) / sampleRate;
        double mu = pow(10.0, params.boost / 20.0);
        double beta = 4.0 / (1.0 + mu);
        double delta = beta * tan(theta / 2.0);
        double gamma = (1.0 - delta) / (1.0 + delta);
        double alpha = (1.0 - gamma) / 2.0;
        
        coeffs.a0 = alpha;
        coeffs.a1 = alpha;
        coeffs.a2 = 0.0;
        coeffs.b1 = -(gamma);
        coeffs.c0 = mu - 1.0;
        coeffs.d0 = 1.0;
        
        biquad.setCoeffs(coeffs);
        return true;
    } else if (params.type == FilterType::HSF) {
        double theta = (2.0 * kPi * params.fc) / sampleRate;
        double mu = pow(10.0, params.boost / 20.0);
        double beta = (1.0 + mu) / 4;
        double delta = beta * tan(theta / 2.0);
        double gamma = (1.0 - delta) / (1.0 + delta);
        double alpha = (1.0 + gamma) / 2.0;
        
        coeffs.a0 = alpha;
        coeffs.a1 = -alpha;
        coeffs.a2 = 0.0;
        coeffs.b1 = -gamma;
        coeffs.b2 = 0.0;
        coeffs.c0 = mu - 1.0;
        coeffs.d0 = 1.0;
        
        biquad.setCoeffs(coeffs);
        return true;
    } else if (params.type == FilterType::PEQ) {
        double theta = (2.0 * kPi * params.fc) / sampleRate;
        double mu = pow(10.0, params.boost / 20.0);
        double zeta = 4.0 / (1.0 + mu);
        double betaNum = 1.0 - (zeta * tan(theta / (2 * params.Q)));
        double betaDen = 1.0 + (zeta * tan(theta / (2 * params.Q)));
        double beta = 0.5 * (betaNum / betaDen);
        double gamma = (0.5 + beta) * cos(theta);

        double alpha = 0.5 - beta;

        coeffs.a0 = alpha;
        coeffs.a1 = 0.0;
        coeffs.a2 = -alpha;
        coeffs.b1 = -2 * gamma;
        coeffs.b2 = 2 * beta;
        coeffs.c0 = mu - 1.0;
        coeffs.d0 = 1.0; 

        biquad.setCoeffs(coeffs);
        return true;
    }
    return false; // coeffs were not recalculated
}

FilterParameters Filter::getParameters() { return Filter::params; }

void Filter::setParameters(const FilterParameters& params) {
    // only set parameters if a parameter changes
    // float equality is actually okay here - we're comparing to if the parameter has changed at all
    if (this->params.boost != params.boost || this->params.fc != params.fc || this->params.Q != params.Q || this->params.type != params.type) {
        this->params = params;
    } else {
        return;
    }
    
    // don't allow 0 or (-) values for Q
    if (this->params.Q <= 0) { this->params.Q = 0.707; }
    calculateCoeffs();
}
