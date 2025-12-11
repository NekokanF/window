//コマンドキュー制御クラス

#include "command_queue.h"
#include <cassert>

//---------------------------------------------------------
//デストラクタ
CommandQueue::~CommandQueue() {
	//コマンドキューの解放
	if (commandQueue_) {
		commandQueue_->Release();
		commandQueue_ = nullptr;
	}
}

//---------------------------------------------------------
//コマンドキューの生成
[[nodiscard]] bool CommandQueue::create(const Device& device) noexcept {
	//コマンドキューの設定
	D3D12_COMMAND_QUEUE_DESC desc{};
	desc.Type           = D3D12_COMMAND_LIST_TYPE_DIRECT;       // ダイレクトコマンドキュー   
	desc.Priority       = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;  // 通常優先度
	desc.Flags          = D3D12_COMMAND_QUEUE_FLAG_NONE;        // 特別フラグなし
	desc.NodeMask       = 0;                                    // GPU はひとつのみ使用する

	// コマンドキューの作成
	const auto hr = device.get()->CreateCommandQueue(&desc, IID_PPV_ARGS(&commandQueue_));
	if (FAILED(hr)) {
		assert(false && "コマンドキューの作成に失敗");
		return false;
	}
	return true;
}

[[nodiscard]] ID3D12CommandQueue* CommandQueue::get() const noexcept {
	if (!commandQueue_) {
		assert(false && "コマンドキューが未作成です");
	}
	return commandQueue_;
}
