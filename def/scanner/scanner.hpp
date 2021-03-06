#pragma once

// https://github.com/diegcrane/external-memory-scanner

#include <windows.h>
#include <vector>
#include <iostream>
#include <winternl.h>
#pragma comment(lib, "ntdll.lib")

#include "../console.hpp"

#define NT_SUCCESS(x) ((NTSTATUS)(x) >= NULL)

extern "C" NTSTATUS NtReadVirtualMemory( HANDLE, PVOID, PVOID, ULONG, PULONG );
extern "C" NTSTATUS NtWriteVirtualMemory( HANDLE, PVOID, PVOID, ULONG, PULONG );

struct scanner
{
private:
	HANDLE p_handle = NULL;
	size_t _address = NULL;

	MEMORY_BASIC_INFORMATION _mbi = {
		nullptr,
		nullptr,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL

	};

public:
	scanner( HANDLE p_handle );
	~scanner( );

	bool query_memory( );
	bool is_valid_page( );
	bool read_virtual_mem( PVOID x );

	std::vector<size_t> scan_unicode( std::string string );
	void rewrite_unicode( size_t addrss, std::string str );

	std::vector<size_t> scan_multibyte( std::string string );
	void rewrite_multibyte( size_t addrss, std::string str );
};
