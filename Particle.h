#ifndef PARTICLE_H
#define PARTICLE_H

#include "ParticleType.h"
#include "ResonanceType.h"

#include <string>


class Particle {
public:
  Particle();
  Particle(std::string  fName, double Px = 0, double Py = 0, double Pz = 0);

  int GetIndex() const;

  static void AddParticleType(std::string  fName, double fMass, int fCharge, double fWdith = 0);
  static void AddResonanceType(std::string  fName, double fMass, int fCharge, double fWidth);

  void SetParticle(int &index);
  void SetParticle(std::string  fName); //overload

  static void PrintArray();
  void PrintParticle();

  double GetXImpulse() const;
  double GetYImpulse() const;
  double GetZImpulse() const;
  double GetMass() const;
  double GetCharge() const;
  double GetEnergy() const;

  double InvMass(Particle & p);

  void SetP(double px,double py,double pz);
  
  int Decay2body(Particle &dau1,Particle &dau2) const;

private:
  void Boost(double bx, double by, double bz);
  static int FindParticle(std::string  fName);
  static const int fMaxNumParticleType = 10;
  static ParticleType* fParticleType[fMaxNumParticleType]; 
                                        
  static int fNParticleType; 
  int fIParticle = 0; 
  double Px_ = 0;
  double Py_ = 0;
  double Pz_ = 0;
};

#endif // PARTICLE_H