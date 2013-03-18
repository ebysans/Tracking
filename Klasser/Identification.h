#ifndef _IDENTIFICATION_H_
#define _IDENTIFICATION_H_

#include "frame.h"
#include <list>
#include <cmath>
#include <queue>

namespace Identification
{

	//////////     Module     ///////////
	/////////////////////////////////////

	class Identifier
	{
	public:
		Identifier() {uniqueIDPool = 1;}
		void identify(std::list<Frame> & frames);

	private:
		int uniqueIDPool;
		int newID() {return uniqueIDPool++;}
	};


	class ProbabilityContainer
	{
	public:
		int index;
		int probableId;
		float probability;
		ProbabilityContainer(int index, int probableId, float probability) : index(index),probableId(probableId),probability(probability) {}
		bool operator<(const ProbabilityContainer & pc) { return probability < pc.probability; }
	};

	struct Condition
	{
		int indexValue;
		Condition(int indexValue) : indexValue(indexValue) {}
		bool operator() (const ProbabilityContainer& pc) { return pc.index == indexValue; }
	};


	////////// TEST GENERATION ///////////
	//////////////////////////////////////

	void generate_testdata(std::list<Frame> & frameList);

};

#endif