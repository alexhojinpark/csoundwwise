// CsoundWrapper.cpp
#include "CsoundWrapper.h"
#include <cstdio>

CsoundWrapper::CsoundWrapper() {
    csound = new Csound();
    initialized = false;
}

CsoundWrapper::~CsoundWrapper() {
    if (initialized) csound->Stop();
    delete csound;
}

bool CsoundWrapper::load(const char* csdFile) {
    if (csound->Compile(csdFile) == 0) {
        csound->Start();
        initialized = true;
        return true;
    }
    else {
        printf("[CsoundWrapper] Failed to compile csd file: %s\n", csdFile);
    }
    return false;
}

int CsoundWrapper::getKsmps() const {
    if (!initialized) return 0;
    return csound->GetKsmps();
}

bool CsoundWrapper::performBlock(float* output, int numFrames) {
    if (!initialized) {
        printf("[CsoundWrapper] performBlock called but not initialized!\n");
        return false;
    }

    int ksmps = csound->GetKsmps();
    if (numFrames != ksmps) {
        printf("[CsoundWrapper] Warning: numFrames (%d) != ksmps (%d)\n", numFrames, ksmps);
    }

    // Get pointers to spout
    double* spout = csound->GetSpout();

    // Perform block
    int ret = csound->PerformKsmps();
    if (ret != 0) {
        printf("[CsoundWrapper] PerformKsmps returned error %d\n", ret);
        return false;
    }

    for (int i = 0; i < ksmps && i < numFrames; ++i) {
        output[i] = static_cast<float>(spout[i]);
    }

    return true;
}