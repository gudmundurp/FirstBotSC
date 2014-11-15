#pragma once

#include <type_traits>
#include <cinttypes>
#include <map>
#include <functional>

template<class ElementType>
class DisjointSet
{
public:
	typedef std::function<int(ElementType&)> IndexFunction;

	DisjointSet(const IndexFunction&);
	virtual ~DisjointSet();

	/**
	 * Finds the representative element for the disjoint set containing element.
	 */
	const ElementType& Find(const ElementType& element);

	/**
	 * Joins the disjoint sets containing element1 and element2
	 */
	const ElementType& Union(const ElementType& element1, const ElementType& element2);

	/**
	 * Moves element to its own disjoint set.
	 */
	void Isolate(const ElementType& element);

private:
	IndexFunction fp_index;
	std::map<ElementType, ElementType> m_sets;
};
