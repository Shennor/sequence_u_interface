#pragma once
#include "sequence.h"

template<typename T>
class MathVector
{
private:
	Sequence<T>* sequence_;
public:

	// Constructors

	MathVector();
	MathVector(const MathVector* other);
	MathVector(size_t dim);
	MathVector(Sequence<T> seq);
	MathVector(T* items, size_t count);

	// Operators

	size_t GetDim() const;
	T GetAxisProject(const size_t axis) const;
	T SetAxisProject(const size_t axis, const T& item);
	MathVector Sum(const MathVector& other) const;
	MathVector Multiply(const T item) const;
	T Norm();
	T ScalarProduct(const MathVector* other) const;

	// Overloading

	MathVector<T> operator+(MathVector<T> other);
	MathVector<T> operator*(const T item);
};
	
	// Realization

	template <typename T>
	MathVector<T>::MathVector()
	{
		sequence_ = new ArraySequence<T>();
	}

	template <typename T>
	MathVector<T>::MathVector(const MathVector* other)
	{
		sequence_ = new ArraySequence<T>(other->sequence_);
	}

	template <typename T>
	MathVector<T>::MathVector(size_t dim)
	{
		sequence_ = new ArraySequence<T>(dim);
	}
	
	template <typename T>
	MathVector<T>::MathVector(Sequence<T> seq)
	{
		sequence_ = new ArraySequence<T>(seq);
	}

	template <typename T>
	MathVector<T>::MathVector(T* items, size_t count)
	{
		sequence_ = new ArraySequence<T>(items, count);
	}

	template <typename T>
	size_t MathVector<T>::GetDim() const
	{
		return sequence_->GetCount();
	}

	template <typename T>
	T MathVector<T>::GetAxisProject(const size_t axis) const
	{
		try
		{
			return this->sequence_->Get(axis);
		}
		catch(std::exception e)
		{
			throw std::out_of_range("MathVector GetAxisProject: "
				+ std::string(e.what()));
		}
	}

	template <typename T>
	T MathVector<T>::SetAxisProject(const size_t axis, const T& item)
	{
		try
		{
			this->sequence_->Set(axis, item);
			return this->sequence_->Get(axis);
		}
		catch (std::exception& e)
		{
			throw std::out_of_range("MathVector SetAxisProject: "
				+ std::string(e.what()));
		}
	}
	
	template <typename T>
	MathVector<T> MathVector<T>::Sum(const MathVector& other) const
	{
		size_t min = this->GetDim();
		if (other.GetDim() < min)
		{
			min = other.GetDim();
		}
		
		MathVector<T> res = new MathVector<T>();

		for(size_t i = 0; i < min; ++i)
		{
			res.sequence_->Append(this->sequence_->Get(i) + other.sequence_->Get(i));
		}

		for(size_t i = min; i < this->GetDim(); ++i)
		{
			res.sequence_->Append(this->sequence_->Get(i));
		}
		
		for (size_t i = min; i < other.GetDim(); ++i)
		{
			res.sequence_->Append(other.sequence_->Get(i));
		}
		
		return res;
	}

	template <typename T>
	MathVector<T> MathVector<T>::Multiply(const T item) const
	{
		MathVector<T> res = this;
		for(size_t i = 0; i < this->GetDim(); ++i)
		{
			res.SetAxisProject(i, res.GetAxisProject(i)*item);
		}
		return res;
	}

	template <typename T>
	T MathVector<T>::Norm()
	{
		if(this->GetDim() == 0)
		{
			throw std::invalid_argument(
				"MathVector Norm: dimension is 0");
		}
		
		T sum = (this->GetAxisProject(0)) * (this->GetAxisProject(0));
		for(size_t i = 1; i < this->GetDim(); ++i)
		{
			sum += (this->GetAxisProject(i)) * (this->GetAxisProject(i));
		}

		return sqrt(sum);
	}

	template <typename T>
	T MathVector<T>::ScalarProduct(const MathVector* other) const
	{
		if(this->GetDim() != other->GetDim())
		{
			throw std::invalid_argument(
				"MathVector ScalarProduct: different dimensions");
		}
		if(this->GetDim() == 0)
		{
			throw std::invalid_argument("MathVector ScalarProduct:"
				" vectors dimension is 0");
		}
		
		T res = this->GetAxisProject(0) * other->GetAxisProject(0);
		for(size_t i = 1; i < this->GetDim(); ++i)
		{
			res += this->GetAxisProject(i) * other->GetAxisProject(i);
		}
		return res;
	}

	// Overloading

	template<typename T>	
	MathVector<T> MathVector<T>::operator+(MathVector<T> other)
	{
		return this->Sum(other);
	}

	template<typename T>
	MathVector<T> MathVector<T>::operator*(const T item)
	{
		return this->Multiply(&item);
	}