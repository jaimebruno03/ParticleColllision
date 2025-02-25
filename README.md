# Simulating Particle Collisions with C++ and ROOT

This project simulates elementary particle collisions using C++ and ROOT. The main goal is to generate and analyze collision events through Monte Carlo methods, focusing on extracting the resonance signal of the K∗ particle. ROOT framework need to be installed

- Simulates 105 collision events, generating around 120 particles per event.
- Includes different particle types: π+, π−, K+, K−, P+, P−, K∗.
- Implements three main C++ classes:

    ParticleType → Defines stable particles (name, mass, charge).

    ResonanceType → Extends ParticleType for unstable resonances, adding width.

    Particle → Describes individual particles, including momentum components.

- Uses ROOT histograms for data visualization and statistical analysis.

# Code Structure

📌 ParticleType.h / .cxx → Defines stable particles.

📌 ResonanceType.h / .cxx → Defines unstable resonances.

📌 Particle.h / .cxx → Handles particle properties and decays.

📌 main.cxx → Executes Monte Carlo event generation and fills histograms.

📌 analysis.cxx → Performs statistical analysis and visualization of results.


# Compilation

g++ main.cxx Particle.cxx ParticleType.cxx ResonanceType.cxx -o simulation 

g++ analysis.cxx -o analysis 

# Running the Simulation

./simulation

./analysis

# Authors

Jaime Bruno
Marta Aznar



Angular and momentum distributions.

Invariant mass distributions for πK pairs, identifying the K∗ resonance.

Statistical fits are applied to validate results.

