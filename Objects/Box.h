#pragma once
#include "ObjectBace.h"
class Box :
    public ObjectBace
{
public:
	/*Main System*/
	Box(SceneBace* pScene, const DirectX::SimpleMath::Vector3& position = DirectX::SimpleMath::Vector3()) noexcept;
	~Box() noexcept;

	void Initialize() override final;
	void Process(float elapsedTime) override final;
};

