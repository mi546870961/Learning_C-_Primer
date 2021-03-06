#ifndef QUERYRESULT_H
#define QUERYRESULT_H

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <memory>
#include "12_32_StrBlob.h"

class QueryResult
{
friend std::ostream &print(std::ostream &, const QueryResult &);
public:
	using line_no = std::vector<std::string>::size_type;
	QueryResult();
	QueryResult(std::string s,
				std::shared_ptr<std::set<line_no>> l,
				StrBlob c):
		sought(s), lines(l), content(c) { }
private:
	std::string sought;
	std::shared_ptr<std::set<line_no>> lines;
	StrBlob content;
};

std::ostream &print(std::ostream &, const QueryResult &);

#endif