#include <iostream> 
#include <csignal> 
#include <windows.h>
using namespace std; 
void signalHandler( int signum ) 
{ 
	cout << "Interrupt signal (" << signum << ") received.\n"; // 清理并关闭 
	// 终止程序 
	exit(signum); 
} 

int main () 
{ 
	// 注册信号 SIGINT 和信号处理程序 
	signal(SIGINT, signalHandler); 
	signal(SIGTERM, signalHandler);
	while(1){ 
		cout << "Going to sleep...." << endl; 
		Sleep(1); 
	} 
	
	return 0; 
}