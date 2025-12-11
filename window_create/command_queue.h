#pragma once
#include "device.h"

class CommandQueue final{
public:
	//-------------------------------------------------------
	//コンストラクタ
	CommandQueue() = default;

	//-------------------------------------------------------
	//デストラクタ
	~CommandQueue();

	//-------------------------------------------------------
	//コマンドキューの作成
	[[nodiscard]] bool create(const Device& device) noexcept;

	//-------------------------------------------------------
	[[nodiscard]] ID3D12CommandQueue* get() const noexcept;

private:
	ID3D12CommandQueue* commandQueue_{}; //コマンドキュー
};

