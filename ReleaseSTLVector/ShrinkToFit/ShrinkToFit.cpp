// ShrinkToFit.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <cassert>

int main()
{
	std::vector<int> v = { 1, 2, 3 };

	std::cout << v.capacity() << std::endl;

	// 要素削除 : capacityは減らない
	v.erase(v.begin());
	std::cout << v.capacity() << std::endl;

	// 領域を切り詰める
	v.shrink_to_fit();
	std::cout << v.capacity() << std::endl;
	assert(v.capacity() == v.size());

	v.clear();
	std::cout << v.capacity() << std::endl;
	v.shrink_to_fit();
	std::cout << v.capacity() << std::endl;

	return 0;
}