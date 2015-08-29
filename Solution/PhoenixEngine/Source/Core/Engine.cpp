#include "Core/Engine.h"

#include "Utility/Debug.h"
#include "Utility/Endian.h"
#include "Utility/Primitives.h"

using namespace Phoenix;

void FEngine::Init(const UpdateCallback& OnUpdateCallback)
{
	F_LogOpen("Log.txt");
	F_LogTrace("Engine::Init()\n");
	FEndian::Init();

	this->OnUpdateCallback = OnUpdateCallback;
}

void FEngine::DeInit()
{
	F_LogClose();
}

void FEngine::Run()
{
	F_LogTrace("Engine::Run()\n");

	// Main Thread
	/* 
	while running
		
		poll events
		dispatch events to game thread

		if game thread sent events to main thread
			retrieve events
			process events

	end while loop
	*/

	// Game Thread
	/*
		while running
			
			update game timer
			get delta time
			add to accumulated time

			while accumulated time >= max delta time
				reduce accumulated time
				get current time

				if main thread sent events to game thread
					retrieve events
					process events
				
				dispatch events to main thread

				update audio
				update physics
				update c++ scripts

				if multiple updates occured this frame
					display a warning
					potentially reduce target frame rate
			
			draw graphics

		end while loop
	*/

	{
		Update(0.016f);
		Update(0.016f);
		Update(0.016f);
	}
}

void FEngine::Update(float DT)
{
	F_LogTrace("Engine::Update()");

	//Goes to PGame::InternalUpdate
	OnUpdateCallback(DT);
}
