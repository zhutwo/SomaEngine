#pragma once
#include "SomaStd.h"
#include <new>

class Helper
{
public:
	static void Print(std::string msg)
	{
		std::wstring wstr(msg.begin(), msg.end());
		MessageBox(NULL,
			wstr.c_str(),
			_T("Soma Debug"),
			NULL);
	}
	static void Ping()
	{
		MessageBox(NULL,
			_T("Ping!"),
			_T("Soma Debug"),
			NULL);
	}
};

class NonCopyable
{
public:
	NonCopyable() = default;
	NonCopyable(const NonCopyable&) = delete;
	NonCopyable& operator=(const NonCopyable&) = delete;

	NonCopyable(NonCopyable&&) = default;
	NonCopyable& operator=(NonCopyable&&) = default;
};

template <typename T>
T* GetSingleton()
{
	static T inst;
	return &inst;
}

template <class TDerived>
class Singleton
{
public:
	static TDerived& GetInst()
	{
		static TDerived inst{ token() };
		return inst;
	}
	//Non-copyable
	Singleton(const Singleton&) = delete;
	Singleton& operator =(const Singleton&) = delete;
protected:
	//Control construction
	struct token {};
	Singleton() {}
	//friend TDerived;
};

template <class BaseType, class SubType>
BaseType* GenericObjectCreationFunction(void) { return new SubType; }

template <class BaseClass, class IdType>
class GenericObjectFactory
{
	typedef BaseClass* (*ObjectCreationFunction)(void);
	std::map<IdType, ObjectCreationFunction> m_creationFunctions;

public:
	template <class SubClass>
	bool Register(IdType id)
	{
		auto findIt = m_creationFunctions.find(id);
		if (findIt == m_creationFunctions.end())
		{
			m_creationFunctions[id] = &GenericObjectCreationFunction<BaseClass, SubClass>;
			return true;
		}

		return false;
	}

	BaseClass* Create(IdType id)
	{
		auto findIt = m_creationFunctions.find(id);
		if (findIt != m_creationFunctions.end())
		{
			ObjectCreationFunction pFunc = findIt->second;
			return pFunc();
		}

		return NULL;
	}
};