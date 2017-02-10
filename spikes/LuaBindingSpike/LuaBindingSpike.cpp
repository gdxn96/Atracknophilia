// LuaBindingSpike.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../../../RWMP3/MetaSystem/MetaSystem.h"
//#include "../../dependancies/LuaBridge/LuaBridge.h"
//#include "LuaBridge\LuaBridge.h"
#include "../../dependancies/lua52/lua.h"

#pragma region Apply
template<typename Ret>
void Apply(Ret(*fun) (), Variable ret, Variable* args, int argCount)
{
	Ret r = fun();
	ret = Variable(&r);
}

void Apply(void(*fun) (), Variable ret, Variable* args, int argCount)
{
	fun();
}

template<typename Ret, typename Arg0>
void Apply(Ret(*fun) (Arg0), Variable ret, Variable* args, int argCount)
{
	Ret r = fun(args[0].get<Arg0>());
	ret = Variable(&r);
}

template<typename Arg0>
void Apply(void(*fun) (Arg0), Variable ret, Variable* args, int argCount)
{
	fun(args[0].get<Arg0>());
}

template<typename Ret, typename Arg0, typename Arg1>
void Apply(Ret(*fun) (Arg0), Variable ret, Variable* args, int argCount)
{
	Ret r = fun(args[0].get<Arg0>(), args[1].get<Arg1>());
	ret = Variable(&r);
}

template<typename Arg0, typename Arg1>
void Apply(void(*fun) (Arg0), Variable ret, Variable* args, int argCount)
{
	fun(args[0].get<Arg0>(), args[1].get<Arg1>());
}

template<typename Ret, typename Arg0, typename Arg1, typename Arg2>
void Apply(Ret(*fun) (Arg0), Variable ret, Variable* args, int argCount)
{
	Ret r = fun(args[0].get<Arg0>(), args[1].get<Arg1>(), args[2].get<Arg2>());
	ret = Variable(&r);
}

template<typename Arg0, typename Arg1, typename Arg2>
void Apply(void(*fun) (Arg0), Variable ret, Variable* args, int argCount)
{
	fun(args[0].get<Arg0>(), args[1].get<Arg1>(), args[2].get<Arg2>());
}

template<typename Ret, typename Arg0, typename Arg1, typename Arg2, typename Arg3>
void Apply(Ret(*fun) (Arg0), Variable ret, Variable* args, int argCount)
{
	Ret r = fun(args[0].get<Arg0>(), args[1].get<Arg1>(), args[2].get<Arg2>(), args[3].get<Arg3>());
	ret = Variable(&r);
}

template<typename Arg0, typename Arg1, typename Arg2, typename Arg3>
void Apply(void(*fun) (Arg0), Variable ret, Variable* args, int argCount)
{
	fun(args[0].get<Arg0>(), args[1].get<Arg1>(), args[2].get<Arg2>(), args[3].get<Arg3>());
}

template<typename Ret, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
void Apply(Ret(*fun) (Arg0), Variable ret, Variable* args, int argCount)
{
	Ret r = fun(args[0].get<Arg0>(), args[1].get<Arg1>(), args[2].get<Arg2>(), args[3].get<Arg3>(), args[4].get<Arg4>());
	ret = Variable(&r);
}

template<typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
void Apply(void(*fun) (Arg0), Variable ret, Variable* args, int argCount)
{
	fun(args[0].get<Arg0>(), args[1].get<Arg1>(), args[2].get<Arg2>(), args[3].get<Arg3>(), args[4].get<Arg4>());
}

template<typename Ret, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
void Apply(Ret(*fun) (Arg0), Variable ret, Variable* args, int argCount)
{
	Ret r = fun(args[0].get<Arg0>(), args[1].get<Arg1>(), args[2].get<Arg2>(), args[3].get<Arg3>(), args[4].get<Arg4>(), args[5].get<Arg5>());
	ret = Variable(&r);
}

template<typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
void Apply(void(*fun) (Arg0), Variable ret, Variable* args, int argCount)
{
	fun(args[0].get<Arg0>(), args[1].get<Arg1>(), args[2].get<Arg2>(), args[3].get<Arg3>(), args[4].get<Arg4>(), args[5].get<Arg5>());
}

template<typename Ret, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6>
void Apply(Ret(*fun) (Arg0), Variable ret, Variable* args, int argCount)
{
	Ret r = fun(args[0].get<Arg0>(), args[1].get<Arg1>(), args[2].get<Arg2>(), args[3].get<Arg3>(), args[4].get<Arg4>(), args[5].get<Arg5>(), args[6].get<Arg6>());
	ret = Variable(&r);
}

template<typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6>
void Apply(void(*fun) (Arg0), Variable ret, Variable* args, int argCount)
{
	fun(args[0].get<Arg0>(), args[1].get<Arg1>(), args[2].get<Arg2>(), args[3].get<Arg3>(), args[4].get<Arg4>(), args[5].get<Arg5>(), args[6].get<Arg6>());
}

template<typename Ret, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7>
void Apply(Ret(*fun) (Arg0), Variable ret, Variable* args, int argCount)
{
	Ret r = fun(args[0].get<Arg0>(), args[1].get<Arg1>(), args[2].get<Arg2>(), args[3].get<Arg3>(), args[4].get<Arg4>(), args[5].get<Arg5>(), args[6].get<Arg6>(), args[7].get<Arg7>());
	ret = Variable(&r);
}

template<typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7>
void Apply(void(*fun) (Arg0), Variable ret, Variable* args, int argCount)
{
	fun(args[0].get<Arg0>(), args[1].get<Arg1>(), args[2].get<Arg2>(), args[3].get<Arg3>(), args[4].get<Arg4>(), args[5].get<Arg5>(), args[6].get<Arg6>(), args[7].get<Arg7>());
}

#pragma endregion

template<typename Fun>
void ApplyWrapper(void(*fun)(), Variable ret, Variable* args, int argCount)
{
	Apply((Fun)fun, ret, args, argCount);
}

class FunctionSignature
{
public:
	template<typename Ret>
	FunctionSignature(Ret(*)())
	{
		m_ret = META_TYPE(Ret);
		m_args = 0;
		m_argCount = 0;
	}

	template<typename Ret, typename Arg0>
	FunctionSignature(Ret(*)(Arg0))
	{
		m_ret = META_TYPE(Ret);
		static const MetaType* args[] = { META_TYPE(Arg0) };
		m_args = args;
		m_argCount = 1;
	}

	template<typename Ret, typename Arg0, typename Arg1>
	FunctionSignature(Ret(*)(Arg0, Arg1))
	{
		m_ret = META_TYPE(Ret);
		static const MetaType* args[] = { META_TYPE(Arg0), META_TYPE(Arg1) };
		m_args = args;
		m_argCount = 2;
	}

	template<typename Ret, typename Arg0, typename Arg1, typename Arg2>
	FunctionSignature(Ret(*)(Arg0, Arg1, Arg2))
	{
		m_ret = META_TYPE(Ret);
		static const MetaType* args[] = { META_TYPE(Arg0), META_TYPE(Arg1), META_TYPE(Arg2) };
		m_args = args;
		m_argCount = 3;
	}

	template<typename Ret, typename Arg0, typename Arg1, typename Arg2, typename Arg3>
	FunctionSignature(Ret(*)(Arg0, Arg1, Arg2, Arg3))
	{
		m_ret = META_TYPE(Ret);
		static const MetaType* args[] = { META_TYPE(Arg0), META_TYPE(Arg1), META_TYPE(Arg2), META_TYPE(Arg3) };
		m_args = args;
		m_argCount = 4;
	}

	template<typename Ret, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
	FunctionSignature(Ret(*)(Arg0, Arg1, Arg2, Arg3, Arg4))
	{
		m_ret = META_TYPE(Ret);
		static const MetaType* args[] = { META_TYPE(Arg0), META_TYPE(Arg1), META_TYPE(Arg2), META_TYPE(Arg3), META_TYPE(Arg4) };
		m_args = args;
		m_argCount = 5;
	}

	template<typename Ret, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
	FunctionSignature(Ret(*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5))
	{
		m_ret = META_TYPE(Ret);
		static const MetaType* args[] = { META_TYPE(Arg0), META_TYPE(Arg1), META_TYPE(Arg2), META_TYPE(Arg3), META_TYPE(Arg4), META_TYPE(Arg5) };
		m_args = args;
		m_argCount = 6;
	}

	template<typename Ret, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6>
	FunctionSignature(Ret(*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5))
	{
		m_ret = META_TYPE(Ret);
		static const MetaType* args[] = { META_TYPE(Arg0), META_TYPE(Arg1), META_TYPE(Arg2), META_TYPE(Arg3), META_TYPE(Arg4), META_TYPE(Arg5), META_TYPE(Arg6) };
		m_args = args;
		m_argCount = 7;
	}

	const MetaType* RetType() const { return m_ret; };
	const MetaType* ArgType(int index) const { return m_args[index]; };
	int ArgCount() const { return m_argCount; };
private:
	const MetaType* m_ret;
	const MetaType** m_args;
	int m_argCount;
};

class MetaFunction : public AutoLister<MetaFunction>
{
public:
	template<typename Fun>
	MetaFunction(const char* name, Fun fun)
		:	m_name(name)
		,	m_sig(fun)
		,	m_fun((void(*)())fun)
		,	m_applyWrapper(ApplyWrapper<Fun>)
	{}
	const char* Name() const { return m_name; }
	const MetaType* RetType() const { return m_sig.RetType(); }
	const MetaType* ArgType(int index) const { return m_sig.ArgType(index); };
	int ArgCount() const { return m_sig.ArgCount(); };
	void Apply(Variable ret, Variable* args, int argCount) const
	{
		m_applyWrapper(m_fun, ret, args, argCount);
	}
private:
	const char* m_name;
	FunctionSignature m_sig;
	void(*m_fun) ();
	void(*m_applyWrapper) (void (* fun) (), Variable, Variable*, int);
};

#define META_REGISTER_FUNCTION(f) \
	MetaFunction UNIQUE_NAME_GENERATOR()(#f, f)

int MetaLuaCFunction(lua_State* L)
{
	void* upval = lua_touserdata(L, lua_upvalueindex(1));
	assert(upval);

	const MetaFunction* mf = (const MetaFunction*)upval;

	//Allocate the stack memory for the return vars and arguments
	Variable ret;
	ret.type = mf->RetType();
	ret.address = ret.type->New();

	int argCount = mf->ArgCount();
	Variable* args = (Variable*)alloca(argCount * sizeof(Variable));
	for (int i = 0; i < argCount; i++)
	{
		args[i].type = mf->ArgType(i);
		args[i].address = ret.type->New();
	}

	//Load all the arguments from the Lua Stack
	for (int i = 0; i < argCount; i++)
	{
		args[i].type->LuaGet(L, 1 + i, args[i].address);
	}

	mf->Apply(ret, args, argCount);

	//push the return value onto the Lua stack
	if (ret.type->Size() > 0)
	{
		ret.type->LuaSet(L, ret.address);
	}

	//cleanup allocated memory
	ret.type->Delete(ret.address);
	for (int i = 0; i < argCount; i++)
	{
		args[i].type->Delete(args[i].address);
	}

	return (ret.type->Size() > 0) ? 1 : 0;
}

void MetaBind(lua_State* L)
{
	auto list = AutoList::get<MetaFunction>();

	for (auto func : list)
	{
		const char * name = func->Name();
		lua_pushlightuserdata(L, func);
		lua_pushcclosure(L, MetaLuaCFunction, 1);
		lua_setglobal(L, name);

	}
}



int Foo(int i) { return 2 * i; };

#include <chrono>
#include <thread>
int main()
{
	//auto lua = LuaEngine();
	/*META_REGISTER_FUNCTION(Foo);
	MetaBind(luabridge::);*/

	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		//lua.ExecuteString(R"(print(_VERSION))");
	}

	system("PAUSE");
    return 0;
}

