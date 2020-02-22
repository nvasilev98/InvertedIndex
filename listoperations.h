
#ifndef LISTOPERATIONS_H
#define LISTOPERATIONS_H


#include<iostream>
#include<list>


using set = std::list<int>;


void insertIntoSet(set& ls, int num)
{
	auto it = ls.cbegin();
	for (it; it != ls.cend() && num > *it; ++it)
	{
	}
	ls.insert(it, num);
}


set operator+(const set& set1, const set& set2)
{
	if (set1.empty())
	{
		return set2;
	}

	if (set2.empty())
	{
		return set1;
	}

	set result;
	auto it1 = set1.cbegin(), it2 = set2.cbegin();
	while (it1 != set1.cend() && it2 != set2.cend())
	{
		if (*it1 == *it2)
		{
			result.push_back(*it1);
			++it1;
			++it2;
		}
		else if (*it1 < *it2)
		{
			result.push_back(*it1);
			++it1;
		}
		else
		{
			result.push_back(*it2);
			++it2;
		}
	}

	for (; it1 != set1.cend(); ++it1)
	{
		result.push_back(*it1);
	}

	for (; it2 != set2.cend(); ++it2)
	{
		result.push_back(*it2);
	}

	return result;
}


set operator*(const set& set1, const set& set2)
{
	if (set1.empty() || set2.empty())
	{
		return {};
	}
	set result;
	auto it1 = set1.cbegin(), it2 = set2.cbegin();
	while (it1 != set1.cend() && it2 != set2.cend())
	{
		if (*it1 == *it2)
		{
			result.push_back(*it1);
			++it1;
			++it2;
		}
		else if (*it1 < *it2)
		{
			++it1;
		}
		else
		{
			++it2;
		}
	}

	return result;
}


set operator-(const set& set1, const set& set2)
{
	if (set1.empty())
	{
		return {};
	}

	if (set2.empty())
	{
		return set1;
	}
	set result;
	auto it1 = set1.cbegin(), it2 = set2.cbegin();
	while (it1 != set1.cend() && it2 != set2.cend())
	{
		if (*it1 == *it2)
		{
			++it1;
			++it2;
		}
		else if (*it1 < *it2)
		{
			result.push_back(*it1);
			++it1;
		}
		else
		{
			++it2;
		}
	}

	for (; it1 != set1.cend(); ++it1)
	{
		result.push_back(*it1);
	}

	return result;
}




#endif // !LISTOPERATIONS.H

