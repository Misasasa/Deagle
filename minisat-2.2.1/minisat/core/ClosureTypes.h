// __SZH_ADD_BEGIN__
#ifndef CLOSURETYPES_H
#define CLOSURETYPES_H

#include <iostream>
#include <vector>
#include <bitset>
#include <set>

#include "../../minisat/mtl/Vec.h"
#include "../../minisat/mtl/Heap.h"
#include "../../minisat/mtl/Alg.h"
#include "../../minisat/core/SolverTypes.h"
#include "../../minisat/mtl/Sort.h"
#include "../../minisat/core/GraphTypes.h"

namespace Minisat
{

struct closure_nodet;

struct closure_edget
{
    int from;
	int to;
	edge_kindt kind;
    literal_vector reason;

    //closure_edget() : from(-1), to(-1), kind(OCLT_NA), reason(literal_vector()) {}
	closure_edget(int _from = -1, int _to = -1, edge_kindt _kind = OCLT_NA) : from(_from), to(_to), kind(_kind), reason(literal_vector()) {}
	closure_edget(int _from, int _to, edge_kindt _kind, literal_vector& _reason) : from(_from), to(_to), kind(_kind), reason(_reason) {}
	//bool operator<(const closure_edget& right) const;
	bool operator==(const closure_edget& right) const;
	//bool operator!=(const closure_edget& right) const;
};

struct closure_nodet
{
    std::string name;
    int address;

    bool is_write;
    bool is_read;
    //some special nodes are neither write nor read

	std::vector<closure_edget> out;
	std::vector<closure_edget> in;
	std::vector<int> out_bitset;

	//for writes only
	bool guard_lighted;
    Lit guard;


	std::vector<closure_edget> in_rf;
	std::vector<closure_edget> out_rf;

	//about atomic
	int atomic_parent;
	std::set<int> atomic_items; //only for representative
	std::set<int> atomic_reads; //from atomic_items
	std::set<int> atomic_writes; //from atomic_items
	std::set<int> atomic_in;
	std::set<int> atomic_out;

	closure_nodet(std::string _name, int _address, int id);

	//dangerous edges are saved here, visited or unvisited
	std::vector<int> dangerous_out;
	std::vector<int> dangerous_in;

	int location; //for sort EPO properly
};

}
#endif // CLOSURETYPES_H
// __SZH_ADD_END__