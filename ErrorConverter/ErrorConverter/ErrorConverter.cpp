// ErrorConverter.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

#include <exception>
#include <system_error>
#include <ios> // iostream_category
#include <future> // future_category
#include <typeinfo> // bad_cast
#include <windows.h>

HRESULT HResultFromErrno(std::errc value)
{
	using std::errc;
	switch (value)
	{
	case errc::address_family_not_supported: return HRESULT_FROM_WIN32(WSAEAFNOSUPPORT); // default_condition
	case errc::address_in_use: return HRESULT_FROM_WIN32(WSAEADDRINUSE); // default_condition
	case errc::address_not_available: return HRESULT_FROM_WIN32(WSAEADDRNOTAVAIL); // default_condition
	case errc::already_connected: return HRESULT_FROM_WIN32(WSAEISCONN);
	case errc::argument_list_too_long: return HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER);
	case errc::argument_out_of_domain: return E_INVALIDARG;
	case errc::bad_address: return HRESULT_FROM_WIN32(WSAEFAULT); // default_condition
	case errc::bad_file_descriptor: return HRESULT_FROM_WIN32(WSAEBADF); // default_condition
	case errc::bad_message: return HRESULT_FROM_WIN32(ERROR_CANTREAD);
	case errc::broken_pipe: return HRESULT_FROM_WIN32(ERROR_BROKEN_PIPE);
	case errc::connection_aborted: return HRESULT_FROM_WIN32(WSAECONNABORTED); // default_condition
	case errc::connection_already_in_progress: return HRESULT_FROM_WIN32(WSAEALREADY); // default_condition
	case errc::connection_refused: return HRESULT_FROM_WIN32(WSAECONNREFUSED); // default_condition
	case errc::connection_reset: return HRESULT_FROM_WIN32(WSAECONNRESET); // default_condition
	case errc::cross_device_link: return HRESULT_FROM_WIN32(ERROR_NOT_SAME_DEVICE); // default_condition
	case errc::destination_address_required: return HRESULT_FROM_WIN32(WSAEDESTADDRREQ); // default_condition
	case errc::device_or_resource_busy: return HRESULT_FROM_WIN32(ERROR_BUSY); // default_condition
	case errc::directory_not_empty: return HRESULT_FROM_WIN32(ERROR_DIR_NOT_EMPTY); // default_condition
	case errc::executable_format_error: return HRESULT_FROM_WIN32(ERROR_BAD_FORMAT);
	case errc::file_exists: return HRESULT_FROM_WIN32(ERROR_FILE_EXISTS); // default_condition
	case errc::file_too_large: return HRESULT_FROM_WIN32(ERROR_FILE_TOO_LARGE);
	case errc::filename_too_long: return HRESULT_FROM_WIN32(ERROR_BUFFER_OVERFLOW); // default_condition
	case errc::function_not_supported: return HRESULT_FROM_WIN32(ERROR_INVALID_FUNCTION); // default_condition
	case errc::host_unreachable: return HRESULT_FROM_WIN32(WSAEHOSTUNREACH); // default_condition
	case errc::identifier_removed: return HRESULT_FROM_WIN32(ERROR_INVALID_HANDLE); // 意訳
	case errc::illegal_byte_sequence: return HRESULT_FROM_WIN32(ERROR_ILLEGAL_CHARACTER);
	case errc::inappropriate_io_control_operation: return HRESULT_FROM_WIN32(ERROR_INVALID_HANDLE);
	case errc::interrupted: return HRESULT_FROM_WIN32(WSAEINTR); // default_condition
	case errc::invalid_argument: return E_INVALIDARG;
	case errc::invalid_seek: return HRESULT_FROM_WIN32(ERROR_SEEK_ON_DEVICE);
	case errc::io_error: return HRESULT_FROM_WIN32(ERROR_OPEN_FAILED); // default_condition
	case errc::is_a_directory: return E_FAIL;
	case errc::message_size: return HRESULT_FROM_WIN32(WSAEMSGSIZE); // default_condition
	case errc::network_down: return HRESULT_FROM_WIN32(WSAENETDOWN); // default_condition
	case errc::network_reset: return HRESULT_FROM_WIN32(WSAENETRESET); // default_condition
	case errc::network_unreachable: return HRESULT_FROM_WIN32(WSAENETUNREACH); // default_condition
	case errc::no_buffer_space: return HRESULT_FROM_WIN32(WSAENOBUFS); // default_condition
	case errc::no_child_process: return HRESULT_FROM_WIN32(ERROR_WAIT_NO_CHILDREN);
	case errc::no_link: return E_FAIL;
	case errc::no_lock_available: return HRESULT_FROM_WIN32(ERROR_LOCK_VIOLATION); // default_condition
	case errc::no_message_available: return HRESULT_FROM_WIN32(ERROR_NO_DATA);
	case errc::no_message: return E_FAIL;
	case errc::no_protocol_option: return HRESULT_FROM_WIN32(WSAENOPROTOOPT); // default_condition
	case errc::no_space_on_device: return HRESULT_FROM_WIN32(ERROR_HANDLE_DISK_FULL); // default_condition
	case errc::no_stream_resources: return E_FAIL;
	case errc::no_such_device_or_address: return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
	case errc::no_such_device: return HRESULT_FROM_WIN32(ERROR_DEV_NOT_EXIST); // default_condition
	case errc::no_such_file_or_directory: return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND); // default_condition
	case errc::no_such_process: return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
	case errc::not_a_directory: return E_INVALIDARG;
	case errc::not_a_socket: return HRESULT_FROM_WIN32(WSAENOTSOCK); // default_condition
	case errc::not_a_stream: return E_INVALIDARG;
	case errc::not_connected: return HRESULT_FROM_WIN32(WSAENOTCONN); // default_condition
	case errc::not_enough_memory: return E_OUTOFMEMORY;
	case errc::not_supported: return CO_E_NOT_SUPPORTED;
	case errc::operation_canceled: return HRESULT_FROM_WIN32(ERROR_OPERATION_ABORTED); // default_condition
	case errc::operation_in_progress: return HRESULT_FROM_WIN32(WSAEINPROGRESS); // default_condition
	case errc::operation_not_permitted: return HRESULT_FROM_WIN32(ERROR_ACCESS_DENIED);
	case errc::operation_not_supported: return HRESULT_FROM_WIN32(WSAEOPNOTSUPP); // default_condition
	case errc::operation_would_block: return HRESULT_FROM_WIN32(WSAEWOULDBLOCK); // default_condition
	case errc::owner_dead: return HRESULT_FROM_WIN32(ERROR_ABANDONED_WAIT_0);
	case errc::permission_denied: return HRESULT_FROM_WIN32(ERROR_ACCESS_DENIED); // default_condition
	case errc::protocol_error: return HRESULT_FROM_WIN32(ERROR_READ_FAULT);
	case errc::protocol_not_supported: return HRESULT_FROM_WIN32(WSAEPROTONOSUPPORT); // default_condition
	case errc::read_only_file_system: return HRESULT_FROM_WIN32(ERROR_FILE_READ_ONLY);
	case errc::resource_deadlock_would_occur: return HRESULT_FROM_WIN32(ERROR_POSSIBLE_DEADLOCK);
	case errc::resource_unavailable_try_again: return HRESULT_FROM_WIN32(ERROR_RETRY); // default_condition
	case errc::result_out_of_range: return HRESULT_FROM_WIN32(ERROR_ARITHMETIC_OVERFLOW);
	case errc::state_not_recoverable: return E_FAIL;
	case errc::stream_timeout: return HRESULT_FROM_WIN32(WAIT_TIMEOUT);
	case errc::text_file_busy: return HRESULT_FROM_WIN32(ERROR_BUSY);
	case errc::timed_out: return HRESULT_FROM_WIN32(WSAETIMEDOUT); // default_condition
	case errc::too_many_files_open_in_system: return E_FAIL;
	case errc::too_many_files_open: return HRESULT_FROM_WIN32(ERROR_TOO_MANY_OPEN_FILES); // default_condition
	case errc::too_many_links: return HRESULT_FROM_WIN32(ERROR_TOO_MANY_LINKS);
	case errc::too_many_symbolic_link_levels: return E_FAIL;
	case errc::value_too_large: return DISP_E_OVERFLOW;
	case errc::wrong_protocol_type: return HRESULT_FROM_WIN32(WSAEPROTOTYPE); // default_condition
	default: return E_FAIL;
	}
}

HRESULT HResultFromException(const std::exception& e)
{
	if (auto se = dynamic_cast<const std::system_error*>(&e))
	{
		if (se->code().category() == std::system_category())
		{
			return HRESULT_FROM_WIN32(se->code().value());
		}
		auto ec = se->code().default_error_condition();
		if (ec.category() == std::system_category())
		{
			return HRESULT_FROM_WIN32(ec.value());
		}
		else if (ec.category() == std::generic_category())
		{
			return HResultFromErrno(static_cast<std::errc>(ec.value()));
		}
		else if (ec.category() == std::iostream_category())
		{
			return HResultFromErrno(std::errc::io_error);
		}
		else if (ec.category() == std::future_category())
		{
			return E_NOT_VALID_STATE;
		}
	}
	else if (dynamic_cast<const std::bad_alloc*>(&e))
	{
		return E_OUTOFMEMORY;
	}
	else if (dynamic_cast<const std::bad_cast*>(&e))
	{
		return HRESULT_FROM_WIN32(ERROR_DATATYPE_MISMATCH);
	}
	else if (dynamic_cast<const std::domain_error*>(&e))
	{
		return HResultFromErrno(std::errc::argument_out_of_domain);
	}
	else if (dynamic_cast<const std::invalid_argument*>(&e))
	{
		return HResultFromErrno(std::errc::invalid_argument);
	}
	else if (dynamic_cast<const std::length_error*>(&e))
	{
		return HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER);
	}
	else if (dynamic_cast<const std::out_of_range*>(&e))
	{
		return E_BOUNDS;
	}
	else if (dynamic_cast<const std::overflow_error*>(&e))
	{
		return HResultFromErrno(std::errc::value_too_large); // EOVERFLOW
	}
	// logic_error, runtime_error, underflow_error,
	return E_FAIL;
}

int main()
{
    return 0;
}

