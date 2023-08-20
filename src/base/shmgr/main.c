#include "shmgr.h"

uuid_t sysreg_id = SYSTEM_REGISTRATION_UUID;

int _start() {
	bool running = true;
	SystemRegistration* ptr;

	SkWriteConsole("shmgr: initialization requested\n", -1);

	if (DID_FAIL(SkLockMutex(-1001))) {
		SkWriteConsole("shmgr: system is already initialized. exit\n", -1);
		return -1;
	}

	if (DID_FAIL(SkCreateObject(&sysreg_id, (void**)&ptr))) {
		// system is not registered
		SystemRegistration reg;
		SystemRegistration* regptr = &reg;

		SkWriteConsole("shmgr: looks like this system just was deployed, setting up...\n", -1);
		
		reg.system_state = SYSTEM_STATE_POST_SETUP;
		reg.user0.is_admin = true;
		reg.user0.user_name[0] = 'r';
		reg.user0.user_name[1] = 'o';
		reg.user0.user_name[2] = 'o';
		reg.user0.user_name[3] = 't';
		reg.user0.user_name[4] = 0;
		reg.user0.user_passwd[0] = 0;
		reg.user0.is_user = true;
		reg.user1.is_user = false;
		reg.user2.is_user = false;
		reg.user3.is_user = false;

		if (DID_FAIL(SkDefineObject(&sysreg_id, (void**)&regptr, sizeof(SystemRegistration)))) {
			SkWriteConsole("shmgr: automatic setup had failed! system might be corrupted. consider reinstalling system\n", -1);
			for (;;);
		}
	}

	// todo: some services thing shit

	SkExecuteProcess("/", "", "");

	while (running) {
		int rem = SkCheckRemainingMessages();

		if (rem > 0) {
			for (int i = 0; i < rem; i++) {
				int msg = 0;
				int arg0 = 0;
				int arg1 = 0;

				SkPopMessage(&msg, &arg0, &arg1);

				switch (msg)
				{
				case 1001:
					SkWriteConsole("shmgr: received a shutdown request\n", -1);
					running = false;
					break;
				case 1002:
					SkWriteConsole("shmgr: received a shutdown abort request\n", -1);
					running = true;
					break;
				default:
					SkWriteConsole("shmgr: received a weird message, ignoring..\n", -1);
					break;
				}
			}
		}
	}

	return 0; // here system shuts down, or at least should
}