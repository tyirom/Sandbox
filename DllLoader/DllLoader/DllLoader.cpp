// DllLoader.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

#include <windows.h>

class Dll
{
protected:
	template <typename T> friend class DllProc;
	Dll(const char *name) {
		h_ = ::LoadLibraryA(name);
	}
	~Dll() {
		::FreeLibrary(h_);
	}
	Dll(Dll &&) = delete;
	Dll(const Dll &) = delete;
	Dll& operator=(Dll &&) = delete;
	Dll& operator=(const Dll &) = delete;
private:
	HMODULE h_;
};

template <typename T> class DllProc;
template <typename R, typename ...A>
class DllProc<R(A...)>
{
	typedef R(*func_t)(A...);
public:
	DllProc(const Dll *dll, const char *name) {
		func_ = (func_t)::GetProcAddress(dll->h_, name);
	}
	R operator()(A... args) {
		return (*func_)(args...);
	}
private:
	func_t func_;
};

class User32 : private Dll
{
public:
	User32()
		: Dll("User32.dll")
		, MessageBoxA(this, "MessageBoxA")
	{}
	DllProc<int(HWND, LPCSTR, LPCSTR, UINT)> MessageBoxA;
};

int main()
{
	User32 user32;
	user32.MessageBoxA(NULL, "Text", "Caption", MB_YESNO | MB_ICONERROR);

    return 0;
}

