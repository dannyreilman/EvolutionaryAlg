#ifndef FUNCTIONWITHID_H
#define FUNCTIONWITHID_H	 

#include <vector>
#include <memory>

#include "Function.h"

using std::unique_ptr;

namespace MutableFuncs
{
	class Function;
	
	class FunctionWithIdentity : public Function
	{
	public:
		FunctionWithIdentity() : Function() {}
		virtual ~FunctionWithIdentity() {}
	};
}

#endif
