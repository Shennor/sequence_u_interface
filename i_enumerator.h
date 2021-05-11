#pragma once

template <typename T>
struct IEnumerator
{
	virtual bool MoveNext() = 0;
	virtual T GetCurrent() = 0;
	virtual void Reset() = 0;
};

template <typename T>
struct IEnumerable
{
	virtual IEnumerator<T>* GetEnumerator() = 0;
};