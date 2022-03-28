// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<thread>
#include<stdio.h>
#include<winsock2.h>
#include<string.h>
#include<io.h>

#pragma comment(lib,"ws2_32.lib")
using namespace std;
void error_die(const char* str) {
	cout << str << "failed:" << WSAGetLastError() << endl;
	exit(-1);
}

//发送网页
void sendHtml(SOCKET clifd,const char* filePath);
void notFound(SOCKET clifd);
void initSocket() {
	WORD version = MAKEWORD(2, 2);
	WSADATA wsadata;
	if (0 != WSAStartup(version, &wsadata)) {
		error_die("WSAStartup");
	}
}
SOCKET listenClient() {
	SOCKET serfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serfd == INVALID_SOCKET) {
		error_die("socket");
	}
	//3.绑定ip地址和端口
	//参数一指定的socket
	//参数二 IP地址和端口号
	//参数三长度
	//
	struct sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	//大端存储和小端存储 htons 把本地字节序转为网络字节序
	serAddr.sin_port = htons(80);
	serAddr.sin_addr.S_un.S_addr = INADDR_ANY;//绑定本机任意ip地址
	if (SOCKET_ERROR == bind(serfd, (struct sockaddr*)&serAddr, sizeof(serAddr))) {
		error_die("bind");
	}
	//4.监听
	listen(serfd, 10);
	return serfd;
}

void accept_request(SOCKET clifd) {
	//从clifd接受数据
	char recvBuf[1024] = "";
	if (recv(clifd, recvBuf, sizeof(recvBuf), 0) <= 0) {
		error_die("recv");
	}
	cout << "recvBuf:" << recvBuf << endl;
	//给客户端发送网页
	char filePath[128] = "";
	//随记选择一个网页
	strcpy(filePath, rand() % 2 ? "htmlFiles/4399网页游戏 - 网页游戏开服表,游戏大厅,专注精品页游的一线游戏平台.html" : "htmlFiles/百度一下，你就知道.html");
	//判断文件是否存在
	if(access(filePath,0) == 0){//如果存在返回0，否则-1
		//发送网页
		sendHtml(clifd,filePath);
	}
	else
	{
		cout << "404错误出现" << endl;
		//发送404错误
		notFound(clifd);
	}
	closesocket(clifd);
}
void sendHtml(SOCKET clifd,const char* filePath) {
	FILE* pr = fopen(filePath, "r");
	if (pr == NULL) {
		error_die("fopen");
	}

	char data[1024] = "";
	do {
		fgets(data, 1024, pr);
		send(clifd, data, strlen(data), 0);
	} while (!feof(pr));
	fclose(pr);

		
	
	}
void notFound(SOCKET clifd) {
	//(1)发送404错误；
	char sendBuf[1024];
	
	/*sprintf(sendBuf, "<html><body><h1>大家好，我是DYY</h1></body></html>\r\n");
	send(clifd, sendBuf, strlen(sendBuf), 0);*/
	
	sprintf(sendBuf, "HTTP/1.1 404 NOT FOUND\r\n");
	send(clifd, sendBuf, strlen(sendBuf), 0);
	
	sprintf(sendBuf, "Content-Type:text/htmldyyhaoshuai\r\n\r\n");
	send(clifd, sendBuf, strlen(sendBuf), 0);
	
	cout << sendBuf << endl;
}
int main() {
	//1.初始化网络库
	initSocket();

	//2.创建socket,第一个为ip协议  第二个为传输格式，两种流试传输为TCP，数据包传输UDP
	SOCKET serfd = listenClient();
	cout << "欢迎使用http服务器" << endl;
	//5.接受链接
	struct sockaddr_in cliAddr;
	int len = sizeof(cliAddr);
	while (1) {
		SOCKET clifd = accept(serfd, (struct sockaddr*)&cliAddr, &len);
		if (clifd == INVALID_SOCKET) {
			error_die("accept");
		}
		cout << "have a new connect" << endl;
		//6.处理链接请求
		/*char sendData[1024] = "<html><body><h1>大家好，我是DYY</h1></body></html>";
	
		send(clifd, sendData, strlen(sendData), 0);*/

		accept_request(clifd);
		//closesocket(clifd);
		
	}
	
	//7.关闭链接，清理网络库
	
	closesocket(serfd);
	WSACleanup();
	return 0;

}



//void myprint() {
//    cout << "我的线程开始了" << endl;
//    for (int i = 0; i < 100; i++) {
//        cout << i << endl;
//    }
//    cout << "我的线程结束了" << endl;
//}
//
//int main()
//{
//    
//
//
//    thread mytobj(myprint);
//    mytobj.join();
//    cout << "I love china" << endl;
//    system("pause");
//    return 0;
//}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单


