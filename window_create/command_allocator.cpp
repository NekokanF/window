#include "command_allocator.h"
#include<cassert>

//デストラクタ
CommandAllocator::~CommandAllocator() {
	if (commandAllocator_) {
		commandAllocator_->Release();
		commandAllocator_ = nullptr;
	}
}

//コマンドキューの生成
[[nodiscard]] bool CommandAllocator::create(const Device& device, const D3D12_COMMAND_LIST_TYPE type) noexcept {

	//コマンドリストのタイプを設定
	type_ = type;

	//コマンドアロケーターの生成
	const auto hr = device.get()->CreateCommandAllocator(type_, IID_PPV_ARGS(&commandAllocator_));
	if (FAILED(hr)) {
		assert(false && "コマンドアロケーターの作成に失敗しました");
		return false;
	}

	return true;
}

//コマンドアロケーターをリセットする
void CommandAllocator::reset() noexcept {
	if (!commandAllocator_) {
		assert(false && "コマンドアロケーターが未作成です");
	}

	commandAllocator_->Reset();
}

//コマンドアロケーターを取得する
[[nodsicard]] ID3D12CommandAllocator* CommandAllocator::get() const noexcept {
	if (!commandAllocator_) {
		assert(false && "コマンドアロケーターが未作成です");
	}
	return commandAllocator_;
}

//コマンドリストのタイプを取得する
[[nodiscard]] D3D12_COMMAND_LIST_TYPE CommandAllocator::getType() const noexcept {
	if (!commandAllocator_) {
		assert(false && "コマンドリストのタイプが未設定です");
	}
	return type_;
}