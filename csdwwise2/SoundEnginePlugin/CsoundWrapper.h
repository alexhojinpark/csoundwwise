// CsoundWrapper.h
#pragma once
#include <C:/Program Files/Csound6_x64/include/csound/csound.hpp>
//#include <csound.hpp>
class CsoundWrapper {
public:
    CsoundWrapper();
    ~CsoundWrapper();

    bool load(const char* csdFile);
    bool performBlock(float* outputBuffer, int numFrames);
    int getKsmps() const;

private:
    Csound* csound;
    bool initialized;
};
