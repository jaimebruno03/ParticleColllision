Description

This project simulates elementary particle collisions using C++ and ROOT. The main goal is to generate and analyze collision events through Monte Carlo methods, focusing on extracting the resonance signal of the K∗ particle.

Features

Simulates 105 collision events, generating around 120 particles per event.

Includes different particle types: π+, π−, K+, K−, P+, P−, K∗.

Uses TRandom functions from ROOT for random number generation.

Implements three main C++ classes:

ParticleType (defines stable particles: name, mass, charge).

ResonanceType (extends ParticleType for unstable resonances, adding width).

Particle (describes individual particles, including momentum components).

Generates and analyzes kinematic distributions (momentum, angles, invariant mass).

Uses ROOT histograms for data visualization and statistical analysis.

Code Structure

ParticleType.h / .cxx - Defines stable particles.

ResonanceType.h / .cxx - Defines unstable resonances.

Particle.h / .cxx - Handles particle properties and decays.

main.cxx - Executes Monte Carlo event generation and fills histograms.

analysis.cxx - Performs statistical analysis and visualization of results.

Installation & Compilation

Prerequisites

ROOT framework installed (installation guide).

C++ compiler (e.g., g++).

Compilation

# Compile the simulation code
 g++ main.cxx Particle.cxx ParticleType.cxx ResonanceType.cxx -o simulation `root-config --cflags --glibs`

# Compile the analysis script
 g++ analysis.cxx -o analysis `root-config --cflags --glibs`

Running the Simulation

# Run the Monte Carlo simulation
./simulation

# Run the analysis on generated data
./analysis

Results

The program generates ROOT histograms showing:

Particle type distributions.

Angular and momentum distributions.

Invariant mass distributions for πK pairs, identifying the K∗ resonance.

Statistical fits are applied to validate results.

