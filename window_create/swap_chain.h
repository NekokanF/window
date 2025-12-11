//スワップチェイン制御クラス
#pragma once

#include "DXGI.h"
#include "command_queue.h"
#include "window.h"

class SwapChain final{
public:
	//-------------------------------------------------------------
	//コンストラクタ
	SwapChain() = default;

	//-------------------------------------------------------------
	//デストラクタ
	~SwapChain();

	//-------------------------------------------------------------
	//スワップチェインの生成
	[[nodiscard]] bool create(const DXGI& dxgi, const Window& window, const CommandQueue& commandQueue) noexcept;

	//スワップチェインを取得する
	[[nodiscard]] IDXGISwapChain3* get() const noexcept;

	//スワップチェインの設定を取得する
	[[nodiscard]] const DXGI_SWAP_CHAIN_DESC1& getDesc() const noexcept;

private:
	IDXGISwapChain3*      swapChain_{};     //スワップチェイン
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc_{}; //スワップチェインの設定
};



