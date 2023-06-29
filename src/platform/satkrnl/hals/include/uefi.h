#pragma once
#include "../../include/system.h"

typedef uint8_t boolean_t;
typedef uint64_t efi_status_t;
typedef void* efi_handle_t;

typedef struct {
    uint32_t Data1;
    uint16_t Data2;
    uint16_t Data3;
    uint8_t Data4[8];
} efi_guid_t;

typedef struct {
    uint64_t Signature;
    uint32_t Revision;
    uint32_t HeaderSize;
    uint32_t CRC32;
    uint32_t Reserved;
} efi_table_header_t;

typedef struct {
    efi_guid_t VendorGuid;
    void* VendorTable;
} efi_configuration_table_t;

typedef efi_status_t (*efi_text_reset_t)(void* This, boolean_t ExtendedVerification);
typedef efi_status_t (*efi_text_output_string_t)(void* This, wchar_t* String);
typedef efi_status_t (*efi_text_test_string_t)(void* This, wchar_t* String);
typedef efi_status_t (*efi_text_query_mode_t)(void* This, uint32_t ModeNumber, uint32_t* Column, uint32_t* Row);
typedef efi_status_t (*efi_text_set_mode_t)(void* This, uint32_t ModeNumber);
typedef efi_status_t (*efi_text_set_attribute_t)(void* This, uint32_t Attribute);
typedef efi_status_t (*efi_text_clear_screen_t)(void* This);
typedef efi_status_t (*efi_text_set_cursor_t)(void* This, uint32_t Column, uint32_t Row);
typedef efi_status_t (*efi_text_enable_cursor_t)(void* This, boolean_t Enable);

typedef struct {
    efi_text_reset_t Reset;
    efi_text_output_string_t OutputString;
    efi_text_test_string_t TestString;
    efi_text_query_mode_t QueryMode;
    efi_text_set_mode_t SetMode;
    efi_text_set_attribute_t SetAttribute;
    efi_text_clear_screen_t ClearScreen;
    efi_text_set_cursor_t SetCursorPosition;
    efi_text_enable_cursor_t EnableCursor;
} simple_text_output_interface_t;

typedef struct {
    efi_table_header_t Hdr;
    wchar_t* FirmwareVendor;
    uint32_t FirmwareRevision;
    efi_handle_t ConsoleInHandle;
    void* ConIn;
    efi_handle_t ConsoleOutHandle;
    simple_text_output_interface_t* ConOut;
} efi_system_table_t;