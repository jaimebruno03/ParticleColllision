#include "ParticleType.h"
using namespace std;

//Inicializamos

ParticleType::ParticleType( std::string fName_,double fMass_,int fCharge_) : fMass(fMass_), fName(fName_), fCharge(fCharge_){} //constructor

//Métodos

void ParticleType::Print() const{
	
	cout<<"Particle type: " <<fName<<endl;

	cout<<"Mass:" <<fMass<<endl;
	
	cout<<"Charge:" <<fCharge<<endl;
}

double ParticleType::GetfMass() const{
	return fMass;}
	
 std::string ParticleType::GetfName() const{
	return fName;}
	
 int ParticleType::GetfCharge() const{
	return fCharge;}

 double ParticleType::GetWidth() const{
	return 0;}

	

