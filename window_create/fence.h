#pragma once
#include "device.h"

class Fence final {
public:
	//コンストラクタ
	Fence() = default;

	//デストラクタ
	~Fence();

	//フェンスを作成する
	[[nodiscard]] bool create(const Device& device) noexcept;

	//同期待ちを行う
	void wait(UINT64 denceValue) const noexcept;

	//フェンスを取得する
	[[nodsicard]] ID3D12Fence* get() const noexcept;

private:
	ID3D12Fence* fence_{};  //フェンス
	HANDLE waitGpuEvent_{}; //GPU と CPU 同期用のイベントハンドル
};

