#pragma once
#include <skapi.h>

#define SYSTEM_REGISTRATION_UUID { 0xDEE8A893, 0x5A16, 0x4AE6, 0xBF9B, 0xB85757C6, 0x00D6 }
#define SYSTEM_STATE_POST_INSTALL 0
#define SYSTEM_STATE_POST_SETUP 1
#define SYSTEM_STATE_UPDATE 2

typedef struct tagDateTime {
	uint16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	uint16_t millisecond;
} DateTime;

typedef struct tagUserRegistration {
	uuid_t uid;
	char user_name[64];
	char user_passwd[64];
	bool is_admin;
	bool is_user; // if only one user exists, other ones' is_user field would be false
	DateTime last_login_time;
	DateTime creation_time;
} UserRegistration;

typedef struct tagSystemRegistration {
	uuid_t sid;
	uint32_t system_state;
	DateTime system_reg_date;
	UserRegistration user0;
	UserRegistration user1;
	UserRegistration user2;
	UserRegistration user3;
} SystemRegistration;