#ifndef STRBLOB_H
#define STRBLOB_H

#include <iostream>
#include <string>
#include <vector>
#include <initializer_list>
#include <memory>

class StrBlob
{
public:
	friend class StrBlobPtr;
	friend class ConstStrBlobPtr;
	typedef std::vector<std::string>::size_type size_type;
	StrBlob();
	StrBlob(std::initializer_list<std::string> il);
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	void push_back(const std::string &t) { data->push_back(t); }
	void pop_back();
	std::string& front();
	const std::string& front() const;
	std::string& back();
	const std::string& back() const;
	StrBlobPtr begin();
	StrBlobPtr end();
	ConstStrBlobPtr cbegin() const;
	ConstStrBlobPtr cend() const;
private:
	std::shared_ptr<std::vector<std::string>> data;
	void check(size_type i, const std::string &msg) const;
};

class StrBlobPtr
{
public:
	friend bool eq(const StrBlobPtr &lhs, const StrBlobPtr &rhs);
	StrBlobPtr() : curr(0) {}
	StrBlobPtr(StrBlob &a, size_t sz = 0):
		wptr(a.data), curr(sz) {}
	std::string& deref() const;
	StrBlobPtr& incr();
private:
	std::shared_ptr<std::vector<std::string>>
		check(std::size_t, const std::string&) const;
	std::weak_ptr<std::vector<std::string>> wptr;
	std::size_t curr;
};

class ConstStrBlobPtr
{
public:
	friend bool eq(const StrBlobPtr &lhs, const StrBlobPtr &rhs);
	friend bool eq(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs);
	ConstStrBlobPtr() : curr(0) {}
	ConstStrBlobPtr(const StrBlob &a, size_t sz = 0):
		wptr(a.data), curr(sz) {}
	std::string& deref() const;
	ConstStrBlobPtr& incr();
private:
	std::shared_ptr<std::vector<std::string>>
		check(std::size_t, const std::string&) const;
	std::weak_ptr<std::vector<std::string>> wptr;
	std::size_t curr;
};

bool eq(const StrBlobPtr &lhs, const StrBlobPtr &rhs)
{ 
	auto l = lhs.wptr.lock();
	auto r = rhs.wptr.lock();
	if(l == r)
		return (!r || lhs.curr == rhs.curr);
	else
		return false;
}

bool eq(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs)
{ 
	auto l = lhs.wptr.lock();
	auto r = rhs.wptr.lock();
	if(l == r)
		return (!r || lhs.curr == rhs.curr);
	else
		return false;
}

#endif