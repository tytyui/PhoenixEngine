#ifndef PHOENIX_ENGINE_H_
#define PHOENIX_ENGINE_H_

#include <functional>

namespace phoenix
{
	class PEngine
	{
	public:
		using UpdateCallback = std::function<void(float)>;

		PEngine() = default;
		PEngine(const PEngine& RHS) = delete;
		PEngine& operator = (const PEngine& RHS) = delete;
		PEngine(PEngine&& RHS) = default;
		PEngine& operator = (PEngine&& RHS) = default;
		~PEngine() = default;
		
		void Initialize(const UpdateCallback& OnUpdateCallback);
		void Run();

	private:
		UpdateCallback OnUpdateCallback;
		
		void Update(float DT);
	};
}

#endif // PHOENIX_ENGINE_H_

