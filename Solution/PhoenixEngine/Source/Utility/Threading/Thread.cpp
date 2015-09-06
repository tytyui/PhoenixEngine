#include "Utility/Threading/Thread.h"

#include "Utility/Debug/Assert.h"

using namespace Phoenix;

FThreadRAII::FThreadRAII(FThread&& Thread)
	: Thread(std::move(Thread))
{
}

FThreadRAII::~FThreadRAII()
{
	F_Assert(!Thread.joinable(), "Thread should have been joined before destruction");
	if (Thread.joinable())
	{
		Join();
	}
}

FThread& FThreadRAII::Get()
{
	return Thread;
}

void Phoenix::FThreadRAII::Join()
{
	F_Assert(Thread.joinable(), "Thread is not joinable");
	Thread.join();
}
