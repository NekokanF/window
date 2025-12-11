#pragma once
#include "device.h"

class CommandAllocator final{
public:
	//コンストラクタ
	CommandAllocator() = default;

	//デストラクタ
	~CommandAllocator();

	//コマンドアロケーター作成
	[[nodiscard]] bool create(const Device& device, const D3D12_COMMAND_LIST_TYPE type) noexcept;

	//コマンドアロケーターをリセットする
	void reset() noexcept;

	//コマンドアロケーターを取得する
	[[nodiscard]] ID3D12CommandAllocator* get() const noexcept;

	//コマンドリストのタイプを取得する
	[[nodiscard]] D3D12_COMMAND_LIST_TYPE getType() const noexcept;

private:
	ID3D12CommandAllocator* commandAllocator_{}; //コマンドアロケーター
	D3D12_COMMAND_LIST_TYPE type_{};             //コマンドリストのタイプ
};

