
#include "quad_polygon.h"
#include <cassert>
#include<DirectXMath.h>

namespace {
	struct vertex {
		DirectX::XMFLOAT3 position; //頂点座標（x,y,z）
		DirectX::XMFLOAT4 color;    //頂点色（r,g,b,a）
	};
}

//デストラクタ
Quad_polygon::~Quad_polygon() {
	//頂点バッファの解放
	if (vertexBuffer_) {
		vertexBuffer_->Release();
		vertexBuffer_ = nullptr;
	}

	//インデックスバッファの解放
	if (indexBuffer_) {
		indexBuffer_->Release();
		indexBuffer_ = nullptr;
	}
}

[[nodiscard]] bool Quad_polygon::create(const Device& device) noexcept {
	//頂点バッファの生成
	if (!createVertexBuffer(device)) {
		return false;
	}
	//インデックスバッファの生成
	if (!createIndexBuffer(device)) {
		return false;
	}
	return true;
}

//"nodiscard"はこの関数が例外を投げないことを示すもの
[[nodiscard]] bool Quad_polygon::createVertexBuffer(const Device& device) noexcept {
	//今回利用する四角形の頂点データ
	vertex quadVertices[] = {
		//-こっちが位置-// //-----こっちが色------//
		{{-0.5f,0.5f,0.0f},{1.0f,1.0f,1.0f,1.0f}},
		{{0.5f,0.5f,0.0f}, {1.0f,1.0f,1.0f,1.0f  }}, 
		{{-0.5f,-0.5f,0.0f},{1.0f,1.0f,1.0f,1.0f }},
		{{0.5f,-0.5f,0.0f},{1.0f,1.0f,1.0f,1.0f}}
	};

	//頂点データのサイズ
	//バッファサイズ = バッファ（データを格納するメモリ領域が何バイトの大きさを持っているかを表す値）のこと
	const auto vertexBufferSize = sizeof(quadVertices);

	//ヒープの設定を指定
	//CPU からアクセス可能なメモリを利用するための設定
	D3D12_HEAP_PROPERTIES heapProperty{};
	heapProperty.Type                 = D3D12_HEAP_TYPE_UPLOAD; //CPUが書き込めるメモリを確保する
	heapProperty.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	heapProperty.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	heapProperty.CreationNodeMask     = 1;
	heapProperty.VisibleNodeMask      = 1;

	//どんなリソースを作成するかの設定
	D3D12_RESOURCE_DESC resourceDesc{};
	resourceDesc.Dimension               = D3D12_RESOURCE_DIMENSION_BUFFER;
	resourceDesc.Alignment               = 0;
	resourceDesc.Width                   = vertexBufferSize;
	resourceDesc.Height                  = 1;
	resourceDesc.DepthOrArraySize        = 1;
	resourceDesc.MipLevels               = 1;
	resourceDesc.Format                  = DXGI_FORMAT_UNKNOWN;
	resourceDesc.SampleDesc.Count        = 1;
	resourceDesc.SampleDesc.Quality      = 0;
	resourceDesc.Layout                  = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	resourceDesc.Flags                   = D3D12_RESOURCE_FLAG_NONE;

	//頂点バッファの生成
	auto res = device.get()->CreateCommittedResource(
		&heapProperty,
		D3D12_HEAP_FLAG_NONE,
		&resourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertexBuffer_));
	if (FAILED(res)) {
		assert(false && "頂点バッファの作成失敗");
		return false;
	}

	//頂点バッファにデータを転送する
	//CPU からアクセス可能なアドレスを取得する
	vertex* data{};

	//バッファをマップ（CPUからアクセス可能にする）
	// vertexBuffer_ を直接利用するのではなく、data を介して更新するイメージ
	res = vertexBuffer_->Map(0, nullptr, reinterpret_cast<void**>(&data));
	if (FAILED(res)) {
		assert(false && "頂点バッファのマップに失敗");
		return false;
	}

	//頂点データをコピー
	memcpy_s(data, vertexBufferSize, quadVertices, vertexBufferSize);

	//コピーが終わったのでマップ解除（CPUからアクセス負荷にする）
	//ここまで来たら GPU が利用するメモリ領域（VRAM）にコピー済みなので、triangleVertices は不要になる
	vertexBuffer_->Unmap(0, nullptr);

	//頂点バッファビューの設定
	vertexBufferView_.BufferLocation = vertexBuffer_->GetGPUVirtualAddress();
	vertexBufferView_.SizeInBytes = vertexBufferSize;
	vertexBufferView_.StrideInBytes = sizeof(vertex);

	return true;
}

//インデックスバッファの生成
[[nodiscard]] bool Quad_polygon::createIndexBuffer(const Device& device)	noexcept {
	uint16_t quadIndices[] = {
		0,1,2,3//四角形を構成する頂点のインデックス
	};

	//インデックスデータのサイズ
	const auto indexBufferSize = sizeof(quadIndices);

	//ヒープの設定を指定
	D3D12_HEAP_PROPERTIES heapProperty{};
	heapProperty.Type = D3D12_HEAP_TYPE_UPLOAD;
	heapProperty.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	heapProperty.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	heapProperty.CreationNodeMask = 1;
	heapProperty.VisibleNodeMask = 1;

	//リソースの設定を行う
	D3D12_RESOURCE_DESC resourceDesc{};
	resourceDesc.Dimension           = D3D12_RESOURCE_DIMENSION_BUFFER;
	resourceDesc.Alignment           = 0;
	resourceDesc.Width               = indexBufferSize;
	resourceDesc.Height              = 1;
	resourceDesc.DepthOrArraySize    = 1;
	resourceDesc.MipLevels           = 1;
	resourceDesc.Format              = DXGI_FORMAT_UNKNOWN;
	resourceDesc.SampleDesc.Count    = 1;
	resourceDesc.SampleDesc.Quality  = 0;
	resourceDesc.Layout              = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	resourceDesc.Flags               = D3D12_RESOURCE_FLAG_NONE;

	//インデックスバッファの生成
	auto res = device.get()->CreateCommittedResource(
		&heapProperty,
		D3D12_HEAP_FLAG_NONE,
		&resourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&indexBuffer_));
	if (FAILED(res)) {
		assert(false && "インデックスバッファの作成失敗");
		return false;
	}

	//インデックスバッファにデータを転送する
	uint16_t* data{};
	res = indexBuffer_->Map(0, nullptr, reinterpret_cast<void**>(&data));
	if (FAILED(res)) {
		assert(false && "インデックスバッファのマップに失敗");
		return false;
	}

	memcpy_s(data, indexBufferSize, quadIndices, indexBufferSize);
	//ここまで来たら GPU が利用するメモリ領域（VRAM）にコピー済みなので、triangleIndices は不要になる
	indexBuffer_->Unmap(0, nullptr);

	//インデクスバッファビュー作成
	indexBufferView_.BufferLocation = indexBuffer_->GetGPUVirtualAddress();
	indexBufferView_.SizeInBytes = indexBufferSize;
	indexBufferView_.Format = DXGI_FORMAT_R16_UINT; //triangleIndices の型が 16bit 符号なし整数なので R16_UINT

	return true;

}

[[nodiscard]] void Quad_polygon::draw(const CommandList& commandList)noexcept {
	//頂点バッファの設定
	commandList.get()->IASetVertexBuffers(0, 1,&vertexBufferView_);
	//インデックスバッファの設定
	commandList.get()->IASetIndexBuffer(&indexBufferView_);
	//プリミティブ形状の設定（三角形）
	commandList.get()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//描画コマンド
	commandList.get()->DrawIndexedInstanced(3, 1, 0, 0, 0);
}


