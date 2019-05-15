#ifndef HEIGHT_GENERATOR
#define HEIGHT_GENERATOR
#include <random>
#include <chrono>
#include <iostream>
#include <cmath>
using namespace std;

/**
\file HeightGenerator.hpp
\brief Header file for HeightGenerator.cpp

\author Christopher Arausa
\version Final
\date 05/14/2019
*/

/**
\class HeightGenerator
\brief the height generator class is responsible for generating smooth noise to use for generating heightmaps
*/
class HeightGenerator {
  private:
    float amplitude; ///< Amplitude of the generator
    int octaves; ///< Number of loops to apply smoothing
    float roughness; ///< How rough do we want it
    mt19937_64 random_generator; ///< Random generator for reasons
    unsigned int seed; ///< The seed we're using .
  public:
    HeightGenerator();
    ~HeightGenerator();
    float generateHeight(int x, int y);
    float getNoise(int x, int z);
    float getSmoothNoise(int x, int z);
    float getInterpolatedNoise(float x, float z);
    float interpolate(float a, float b, float blend);

    //Setters and getters for the generator.
    unsigned int getSeed();
    float getAmplitude();
    float getOctaves();
    float getRoughness();
    void setAmplitude(float amp);
    void setOctaves(float o);
    void setRoughness(float r);
    void setSeed(unsigned int s);
};

#endif
