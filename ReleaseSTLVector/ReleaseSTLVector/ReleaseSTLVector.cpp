// ReleaseSTLVector.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"
#include <vector>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	std::vector<std::vector<std::string>> strArray;
	strArray = {
		{ "1-1", "1-2" },
		{ "2-1", "2-2" }
	};

    return 0;
}
