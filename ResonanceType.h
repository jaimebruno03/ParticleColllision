#ifndef RESONANCETYPE_H
#define RESONANCETYPE_H

#include "ParticleType.h"

class ResonanceType : public ParticleType {

public:
ResonanceType(std::string  fName_, double fMass_, int fCharge_, double fWidth_);

double GetWidth() const override;

void Print() const override;

private:
const double fWidth;

};
#endif //RESONANCETYPE_H