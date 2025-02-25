#include <cmath>
#include <cstdlib> //for RAND_MAX
#include <iostream>

#include "Particle.h"

int constexpr c = 299792458; // m/s

Particle::Particle() = default;

Particle::Particle(std::string  fName, double Px, double Py, double Pz)
    : Px_(Px), Py_(Py), Pz_(Pz) {
  fIParticle = FindParticle(fName);
}

int Particle::fNParticleType = 0;
ParticleType *Particle::fParticleType[fMaxNumParticleType];

int Particle::FindParticle(std::string  fName) {
  int result = -1;
  for (int i = 0; i < fNParticleType; ++i) {
    auto name = fParticleType[i]->GetfName();
    if (name == fName) {
      result = i;
      // particle found
    } else {
    }
  }
  return result;
}

int Particle::GetIndex() const { return fIParticle; }

//////////////////////////////////////////////////
//              ADD PARTICLE TYPE              ///
/////////////////////////////////////////////////
void Particle::AddParticleType(std::string  fName, double fMass, int fCharge,
                               double fWidth) {

  if (FindParticle(fName) > fNParticleType) {
    std::cout << "Exceeded array capacity. Too many particle types.\n";
  }
  // adding particle identified by fName
  if (fWidth == 0) { // not a resonance
    fParticleType[fNParticleType] = new ParticleType(fName, fMass, fCharge);
    fNParticleType++;
  } else {
    fParticleType[fNParticleType] =
        new ResonanceType(fName, fMass, fCharge, fWidth);
    fNParticleType++;
  }

  std::cout << "Particle " << fName << " successfully added to the array.\n";
}

void Particle::SetParticle(int &index) {
  if (index < 0) {
    std::cout << "Invalid index value. Try with a positive number.\n";
  } else if (index < fNParticleType) {
    fIParticle = index; // particle index turns into the selected one, if chosen
                        // number is allowed
  } else {
    std::cout << "Invalid index value.\n";
  }
}

//Setting index particle by its name
void Particle::SetParticle(std::string  fName) {
  int index = FindParticle(fName);
  if (index < fNParticleType) {
    fIParticle = index;
  } else {
    std::cout << "Requested value is not in the array.\n";
  }
}

void Particle::PrintParticle() {
  int index = fIParticle;
  std::cout << "Printing particle " << fParticleType[fIParticle]->GetfName()
            << " information...\n";
  std::cout << "Position in the array = " << index << '\n';
  std::cout << "Impulse = "
            << "(" << Px_ << "," << Py_ << "," << Pz_ << ")\n\n";
}

void Particle::PrintArray() {
  for (int i = 0; i < fNParticleType; i++) {
    ParticleType *pt = fParticleType[i];
    std::string  name = fParticleType[i]->GetfName();
    std::cout << "Particle index = " << FindParticle(name) << '\n';
    pt->Print();
  }
}

double Particle::GetXImpulse() const { return Px_; }
double Particle::GetYImpulse() const { return Py_; }
double Particle::GetZImpulse() const { return Pz_; }
double Particle::GetMass() const {
  auto particle = *fParticleType[fIParticle];
  return particle.ParticleType::GetfMass();
}

double Particle::GetCharge() const {
  auto particle = *fParticleType[fIParticle];
  return particle.ParticleType::GetfCharge();
}

double Particle::GetEnergy() const {
  double pSquareModulus =
      std::pow(Px_, 2) + std::pow(Py_, 2) + std::pow(Pz_, 2);
  double pSquareMass = std::pow(GetMass(), 2);
  return std::sqrt(pSquareMass + pSquareModulus);
}

// invariant mass calculator
double Particle::InvMass(Particle &p) {
  double ImpulseSumSquared = std::pow(Px_ + p.GetXImpulse(), 2) +
                             std::pow(Py_ + p.GetYImpulse(), 2) +
                             std::pow(Pz_ + p.GetZImpulse(), 2);
  return std::sqrt(std::pow(GetEnergy() + p.GetEnergy(), 2) -
                   (ImpulseSumSquared));
}

void Particle::SetP(double px, double py, double pz) {
  Px_ = px;
  Py_ = py;
  Pz_ = pz;
}

int Particle::Decay2body(Particle &dau1, Particle &dau2) const {
  if (GetMass() == 0.0) {
    printf("Decayment cannot be preformed if mass is zero\n");
    return 1;
  }

  double massMot = GetMass();
  double massDau1 = dau1.GetMass();
  double massDau2 = dau2.GetMass();

  if (fIParticle > -1) { // add width effect

    // gaussian random numbers

    float x1, x2, w, y1, y2;

    double invnum = 1. / RAND_MAX;
    do {
      x1 = 2.0 * rand() * invnum - 1.0;
      x2 = 2.0 * rand() * invnum - 1.0;
      w = x1 * x1 + x2 * x2;
    } while (w >= 1.0);

    w = sqrt((-2.0 * log(w)) / w);
    y1 = x1 * w;
    y2 = x2 * w;

    massMot += fParticleType[fIParticle]->GetWidth() * y1;
  }

  if (massMot < massDau1 + massDau2) {
    printf("Decayment cannot be preformed because mass is too low in this "
           "channel\n");
    return 2;
  }

  double pout =
      sqrt(
          (massMot * massMot - (massDau1 + massDau2) * (massDau1 + massDau2)) *
          (massMot * massMot - (massDau1 - massDau2) * (massDau1 - massDau2))) /
      massMot * 0.5;

  double norm = 2 * M_PI / RAND_MAX;

  double phi = rand() * norm;
  double theta = rand() * norm * 0.5 - M_PI / 2.;
  dau1.SetP(pout * sin(theta) * cos(phi), pout * sin(theta) * sin(phi),
            pout * cos(theta));
  dau2.SetP(-pout * sin(theta) * cos(phi), -pout * sin(theta) * sin(phi),
            -pout * cos(theta));

  double energy =
      sqrt(Px_ * Px_ + Py_ * Py_ + Pz_ * Pz_ + massMot * massMot);

  double bx = Px_ / energy;
  double by = Py_ / energy;
  double bz = Pz_ / energy;

  dau1.Boost(bx, by, bz);
  dau2.Boost(bx, by, bz);

  return 0;
}

void Particle::Boost(double bx, double by, double bz) {

  double energy = GetEnergy();

  // Boost this Lorentz vector
  double b2 = bx * bx + by * by + bz * bz;
  double gamma = 1.0 / sqrt(1.0 - b2);
  double bp = bx * Px_ + by * Py_ + bz * Pz_;
  double gamma2 = b2 > 0 ? (gamma - 1.0) / b2 : 0.0;

  Px_ += gamma2 * bp * bx + gamma * bx * energy;
  Py_ += gamma2 * bp * by + gamma * by * energy;
  Pz_ += gamma2 * bp * bz + gamma * bz * energy;
}
