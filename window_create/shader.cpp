#include "shader.h"
#include <cassert>
#include <string>

#include<d3dcompiler.h>
#pragma comment (lib,"d3dcompiler.lib")

//デストラクタ
Shader::~Shader() {
	//頂点シェーダーの解放
	if (vertexShader_) {
		vertexShader_->Release();
		vertexShader_ = nullptr;
	}
	//ピクセルシェーダーの解放
	if (pixelShader_) {
		pixelShader_->Release();
		pixelShader_ = nullptr;
	}
}

//シェーダーを作成する
[[nodiscard]] bool Shader::create(const Device& device) noexcept {
	//シェーダーを読み込み、コンパイルして生成する

	//シェーダーファイルのパス
	const std::string filePath = "shader.hlsl";
	const std::wstring temp = std::wstring(filePath.begin(), filePath.end());

	//シェーダーのコンパイルエラーなどが分かるようにする
	ID3DBlob* error{};

	auto res = D3DCompileFromFile(temp.data(), nullptr, nullptr, "vs", "vs_5_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &vertexShader_, &error);
	if (FAILED(res)) {
		char* p = static_cast<char*>(error->GetBufferPointer());
		assert(false && "頂点シェーダーのコンパイルに失敗");
	}
	res = D3DCompileFromFile(temp.data(), nullptr, nullptr, "ps", "ps_5_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &pixelShader_, &error);
	if (FAILED(res)) {
		char* p = static_cast<char*>(error->GetBufferPointer());
		assert(false && "ピクセルシェーダーのコンパイルに失敗しました");
	}

	if (error) {
		error->Release();
	}

	return true;

}

//頂点シェーダーを取得する
[[nodiscard]] ID3DBlob* Shader::vertexShader() const noexcept {
	if (!vertexShader_) {
		assert(false && "頂点シェーダーが未作成です");
	}

	return vertexShader_;
}

//ピクセルシェーダーを取得する
[[nodiscard]] ID3DBlob* Shader::pixelShader() const noexcept {
	if (!pixelShader_) {
		assert(false && "ピクセルシェーダーが未作成です");
	}

	return pixelShader_;
}
