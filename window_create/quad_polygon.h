#pragma once
#include "device.h"
#include "command_list.h"

class Quad_polygon final {
public:
	//コンストラクタ
	Quad_polygon() = default;

	//デストラクタ
	~Quad_polygon();

	//ポリゴンの生成
	[[nodiscard]] bool create(const Device& device) noexcept;

	//ポリゴンの描画
	[[nodiscard]] void draw(const CommandList& commandList) noexcept;

private:
	//頂点バッファ
	[[nodiscard]] bool createVertexBuffer(const Device& device) noexcept;

	//インデックスバッファの生成
	[[nodiscard]] bool createIndexBuffer(const Device& device) noexcept;

private:
	ID3D12Resource* vertexBuffer_{}; //頂点バッファ
	ID3D12Resource* indexBuffer_{};  //インデックスバッファ

	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_ = {};  //頂点バッファビュー
	D3D12_INDEX_BUFFER_VIEW indexBufferView_ = {};    //インデックスバッファビュー
};
