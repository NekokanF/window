#pragma once

#include<d3d12.h>   //DirectX 12（Direct3D 12）の機能を利用するために必要なヘッダーファイルを読み込むための命令
#include<dxgi1_4.h> // DXGI のバージョン 1.4 で導入された機能を使用するためのC/C++ ヘッダーファイル

class DXGI final //DXGIを制御するためのクラス
{
public:

	DXGI() = default; //コンストラクタ

	~DXGI(); //デストラクタ

	//
	[[nodiscard]] bool setDisplayAdapter() noexcept;


	//IDXGIFactory4 = 
	[[nodiscard]] IDXGIFactory4* factory() const noexcept;

	//IDXGIAdapter1 = 
	[[nodiscard]] IDXGIAdapter1* displayAdapter() const noexcept;

private:
	IDXGIFactory4* dxgiFactory_{};
	IDXGIAdapter1* dxgiAdapter_{};

};