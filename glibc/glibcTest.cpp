#include<gnu/libc-version.h>
#include<sys/syscall.h>
#include<sys/types.h>
#include<pwd.h>
#include<cstdlib>
#include<sys/stat.h>
#include<iostream>
#include<signal.h>
#include<unistd.h>

int main(){
	std::cout << "the GNU libc version is: " << gnu_get_libc_version() << "\n";
	
	struct passwd *pass = getpwuid(getuid());
	std::cout << "The current user's login is: " << pass->pw_name << "\n";
	std::cout << "-->their full name is: " << pass->pw_gecos << "\n";
	std::cout << "-->their user ID is: " << pass->pw_uid << "\n";
	
	std::cout << "The user's shell is: " << getenv("SHELL") << "\n";
	std::cout << "The user's path is: " << getenv("PATH") << "\n";
	
	int uid = syscall(0xc7);
	std::cout << "Syscall gives their user ID as: " << uid << "\n";
	
	int ret = chmod("test.txt", 0666);
	ret = syscall(SYS_chmod, "test.txt", 0666);
	return 0;
}
