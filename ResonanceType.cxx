#include "ResonanceType.h"

ResonanceType::ResonanceType( std::string  fName_, double fMass_,int fCharge_, double fWidth_): ParticleType(fName_, fMass_, fCharge_), fWidth(fWidth_) {}

double ResonanceType::GetWidth() const { return fWidth; }

void ResonanceType::Print() const {
  ParticleType::Print();
  std::cout << "Particle width " << fWidth << '\n';
}
