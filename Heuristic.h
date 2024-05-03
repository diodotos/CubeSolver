#pragma once

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>

#include "Cube2Pieces.h"

/* ----------------------------------------------------------------------------
 * This file contains the definition for the Heuristic class.
 * When we perform A* search, we use a heuristic to estimate the distance 
 * from the current state to the solved state. This heuristic is generated
 * by taking the maximum of the number of moves required to correctly 
 * permute and orient the corners of the 2x2x2 cube.
 * 
 * We precompute our heuristic and store it in a lookup table. This lookup
 * table is generated by performing a breadth first search on the 2x2x2 cube.
 *
 * Once we have our lookup tables, at program initialization we read the 
 * heuristics into a map. This map should not change for the program lifetime.
 * Hence the heuristic function is a static member function.
 * 
 * In the future this class should be extended to verify the integrity of the
 * lookup files before reading them into memory.
 * --------------------------------------------------------------------------
*/

class Heuristic
{
public:
	static void initOrientationLookup();
	static void initPermutationLookup();
	static void initPerfectLookup();

	virtual uint16_t heuristic(const Cube2Pieces& cube) const = 0;

//protected:
	static std::unordered_map<uint64_t, uint16_t> orientationLookup;
	static std::unordered_map<uint64_t, uint16_t> permutationLookup;
	static std::unordered_map<uint64_t, uint16_t> perfectLookup;

private:
	static void generateLookupTable(std::unordered_map<uint64_t, uint16_t>& lookup, uint32_t(Cube2Pieces::* hashFunction)() const);
	// Overload for 64 bit hash
	static void generateLookupTable(std::unordered_map<uint64_t, uint16_t>& lookup, uint64_t(Cube2Pieces::* hashFunction)() const);
	static void writeLookupToFile(const std::unordered_map<uint64_t, uint16_t>& lookup, const std::string& filename);
	static void readLookupFromFile(std::unordered_map<uint64_t, uint16_t>& lookup, const std::string& filename);

};

class PermutationHeuristic : public Heuristic
{
public:
	uint16_t heuristic(const Cube2Pieces& cube) const override;
};

class OrientationHeuristic : public Heuristic
{
public:
	uint16_t heuristic(const Cube2Pieces& cube) const override;
};

class DualHeuristic : public Heuristic
{
public:
	uint16_t heuristic(const Cube2Pieces& cube) const override;
};

class PerfectHeuristic : public Heuristic
{
public:
	uint16_t heuristic(const Cube2Pieces& cube) const override;
};

