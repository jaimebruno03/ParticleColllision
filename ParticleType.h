#ifndef PARTICLETYPE_H
#define PARTICLETYPE_H

#include "iostream"
#include "stdlib.h"

class ParticleType{
	
	private:
		
		//atributos 
		std::string fName;
		const double fMass;
		const int fCharge;
		
		
	public:
	
		ParticleType( std::string fName_,double fMass_,int fCharge_); //Constructor
		
		//Métodos
		virtual void Print() const; 

		
		double GetfMass() const;
		int GetfCharge() const;
		std::string GetfName() const;
		virtual double GetWidth() const;
		
};
#endif

	

	


		
		
		
		
	
	
	
