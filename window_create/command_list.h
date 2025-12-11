#pragma once
#include "device.h"
#include "command_allocator.h"

//コマンドリスト制御クラス
class CommandList final{
public:
	//コンストラクタ
	CommandList() = default;

	//デストラクタ
	~CommandList();

	//コマンドリスト作成
	[[nodiscard]] bool create(const Device& device, const CommandAllocator& commandAllocator) noexcept;

	//コマンドリストのリセット
	void reset(const CommandAllocator& commandAllocator) noexcept;

	//コマンドリストを取得する
	[[nodiscard]] ID3D12GraphicsCommandList* get() const noexcept;

private:
	ID3D12GraphicsCommandList* commandList_{}; //コマンドリスト
	
};

