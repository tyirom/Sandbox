// ShrinkToFit.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <cassert>

int main()
{
	std::vector<int> v = { 1, 2, 3 };

	std::cout << v.capacity() << std::endl;

	// �v�f�폜 : capacity�͌���Ȃ�
	v.erase(v.begin());
	std::cout << v.capacity() << std::endl;

	// �̈��؂�l�߂�
	v.shrink_to_fit();
	std::cout << v.capacity() << std::endl;
	assert(v.capacity() == v.size());

	v.clear();
	std::cout << v.capacity() << std::endl;
	v.shrink_to_fit();
	std::cout << v.capacity() << std::endl;

	return 0;
}