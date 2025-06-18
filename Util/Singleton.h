#pragma once

template <typename T>
class Singleton abstract
{
public:
	virtual ~Singleton() = default;

	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;
	Singleton& operator=(const Singleton&&) = delete;

protected:
	Singleton() = default;

public:
	static T* GetInstance() 
	{
		static T instance;

		return &instance;
	}
};