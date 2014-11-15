#include "DisjointSet.h"
#include "catch.hpp"

template<class ElementType>
DisjointSet<ElementType>::DisjointSet(const IndexFunction& index)
	: fp_index(index)
{
}

template<class ElementType>
DisjointSet<ElementType>::~DisjointSet()
{
}

template<class ElementType>
const ElementType& DisjointSet<ElementType>::
Find(const ElementType& element)
{
	if (!m_sets.count(element)) {
		m_sets[element] = element;
	}
	return m_sets[element];
}

template<class ElementType>
const ElementType& DisjointSet<ElementType>::
Union(const ElementType& element1, const ElementType& element2)
{
	ElementType rep1 = m_sets[element1];
	ElementType rep2 = m_sets[element2];

	for (std::map<ElementType, ElementType>::value_type& keyVal : m_sets) {
		if (keyVal.second == rep1) {
			keyVal.second = rep2;
		}
	}

	return rep2;
}

template<class ElementType>
void DisjointSet<ElementType>::
Isolate(const ElementType& element)
{
}

TEST_CASE("Finding a member in empty disjointset returns that member") {
	DisjointSet<int> d([](int val) { return val; });
	auto x = d.Find(3);
	REQUIRE(x == 3);
}

TEST_CASE("Union of elements returns representative, which is the same for both") {
	DisjointSet<int> d([](int val) { return val; });
	d.Find(3);
	d.Find(4);
	int newRepresentative = d.Union(3, 4);
	REQUIRE(d.Find(3) == d.Find(4));
	REQUIRE(((newRepresentative == 3) || (newRepresentative == 4)));
}

TEST_CASE("Create union of 3 elements.") {
	DisjointSet<int> d([](int val) { return val; });
	d.Find(1);
	d.Find(2);
	d.Find(3);
	d.Union(1, 2);
	int rep = d.Union(1, 3);
	REQUIRE(rep == d.Find(1));
	REQUIRE(rep == d.Find(2));
	REQUIRE(rep == d.Find(3));
}

TEST_CASE("Create union of 3 elements different way around.") {
	DisjointSet<int> d([](int val) { return val; });
	d.Find(1);
	d.Find(2);
	d.Find(3);
	d.Union(1, 2);
	int rep = d.Union(2, 3);
	REQUIRE(rep == d.Find(1));
	REQUIRE(rep == d.Find(2));
	REQUIRE(rep == d.Find(3));
}

TEST_CASE("UnionsAreSplittable") {
	DisjointSet<int> d([](int val) { return val; });
	d.Find(1);
	d.Find(2);
	d.Find(3);
	d.Union(1, 2);
	int rep = d.Union(2, 3);
	REQUIRE(rep == d.Find(1));
	REQUIRE(rep == d.Find(2));
	REQUIRE(rep == d.Find(3));
	d.Isolate(2);

	REQUIRE(d.Find(1) == d.Find(3));
	REQUIRE(2 == d.Find(2));
	REQUIRE(2 != d.Find(1));
}

//uint32_t
//index(const ElementType& element)
//{
//	static std::set<ElementType, uint32_t> elements;
//	if (!elements.count(element)) {
//		elements[element] = elements.size();
//	}
//	return elements[element];
//}


