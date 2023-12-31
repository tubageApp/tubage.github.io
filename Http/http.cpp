#include<iostream>
#include<string>
using namespace std;

#pragma warning(disable:4996)

//网络通信需要包含的头文件、需要加载的库文件
#include<winsock.h>
#pragma comment(lib,"WS2_32.lib")

#define PRINTF(str) cout << " [ " << __func__ << " - " << __LINE__ << " ] " << #str << " = " << str << endl;

void error_die(const char* str)
{
	perror(str);
	exit(1);
}

//实现网络的初始化
//返回值：套接字（服务器端的套接字）
//端口
//参数：port 表示端口
//		如果*port的值是0，那么就自动分配一个可用的端口
//		为了向 tinyhttpd服务器致敬
int startup(unsigned short* port)
{
	//1、网络通信的初始化
	WSADATA data;
	int ret = WSAStartup(
		MAKEWORD(1,1),    //1.1版本的协议
		&data   
	);
	if (ret != 0)
	{
		error_die("WSAStartup");
	}
	
	int server_socket = socket(
		PF_INET,        //套接字的类型
		SOCK_STREAM,    //数据流 
		IPPROTO_TCP
	);
	if (server_socket == -1)
	{
		//打印错误提示，并结束程序
		error_die("套接字");
	}

	//设置端口可复用
	int opt = 1;
	ret = setsockopt(server_socket,SOL_SOCKET,SO_REUSEADDR,(const char*)&opt,sizeof(opt));
	if (ret == -1)
	{
		error_die("setsockopt");
	}

	//配置服务器的网络地址
	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(*port);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);


	//绑定套接字
	if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
	{
		error_die("bind");
	}

	//动态分配端口
	int nameLen = sizeof(server_addr);
	if (*port == 0)
	{
		if (getsockname(server_socket, (struct sockaddr*)&server_addr, &nameLen) < 0)
		{
			error_die("getsockname");
		}

		*port = server_addr.sin_port;
	}

	//创建监听队列
	if (listen(server_socket, 5) < 0)
	{
		error_die("listen");
	}

	return server_socket;
}

//从指定的客户端套接字，读取一行数据，保存到buff中，返回实际读取到的字节数
int get_line(int sock, char* buff, int size)
{
	char c = 0;
	int i = 0;

	// \r\n
	while (i < size-1 && c != '\n')
	{
		int n = recv(sock, &c, 1, 0);
		if (n > 0)
		{
			if (c == '\r')
			{
				n = recv(sock, &c, 1, MSG_PEEK);
				if (n > 0 && c == '\n')
				{
					recv(sock, &c, 1, 0);
				}
				else
				{
					c = '\n';
				}
			}
			buff[i++] = c;
		}
		else
		{
			c = '\n';
		}
	}

	buff[i] = 0;
	return i;
}

void unimplement(int client)
{
	//向指定的套接字，发送一个提示还没有实现的错误页面

}

void not_found(int client)
{
	//发送404响应
	char buff[1024];

	strcpy(buff, "HTTP/1.0 200 OK\r\n");
	send(client, buff, strlen(buff), 0);

	strcpy(buff, "Server: TubageHttpd/0.1\r\n");
	send(client, buff, strlen(buff), 0);

	strcpy(buff, "Content-type:text/html\n");
	send(client, buff, strlen(buff), 0);

	strcpy(buff, "\r\n");
	send(client, buff, strlen(buff), 0);

	//发送404网页内容
	sprintf(buff,                                          
		"<HTML>                                                   \
			<TITLE > NOT Found</TITLE>                            \
			<BODY>                                                \
			<H2> The resource is unavailable.</H2>                \
			<img src = \"404.png\" />                             \
			</BODY >                                              \
		</HTML>");
	send(client, buff, strlen(buff), 0);
}

void headers(int client,const char* type)
{
	//发送响应包的头信息
	char buff[1024];

	strcpy(buff, "HTTP/1.0 200 OK\r\n");
	send(client, buff, strlen(buff), 0);

	strcpy(buff, "Server: TubageHttpd/0.1\r\n");
	send(client, buff, strlen(buff), 0);

	//strcpy(buff, "Content-type:text/html\n");
	//send(client, buff, strlen(buff), 0);

	char buf[1024];
	sprintf(buf, "Content-Type: %s\r\n", type);
	/*send(client, buf, strlen(buf), 0);*/

	strcpy(buff, "\r\n");
	send(client, buff, strlen(buff), 0);
}

void cat(int client, FILE* resource)
{
	char buff[4096];
	int count = 0;

	while (1)
	{
		int ret = fread(buff, sizeof(char), sizeof(buff), resource);
		if (ret <= 0)
		{
			break;
		}
		send(client, buff, ret, 0);
		count += ret;
	}
	cout << "一共发送【" << count << "】字节给浏览器" << endl;
}

const char* getHeadType(const char* fileName)
{
	const char* ret = "text/html";
	const char* p = strrchr(fileName, '.');
	if (!p) return ret;

	p++;
	if (!strcmp(p, "css")) ret = "text/css";
	else if (!strcmp(p, "jpg")) ret = "image/jpg";
	else if (!strcmp(p, "png")) ret = "image/png";
	else if (!strcmp(p, "js")) ret = "application/x-javascript";

	return ret;
}

void server_file(int client,const char *fileName)
{
	int numchars = 1;
	char buff[1024];

	//把请求数据包的剩余数据行，读完
	while (numchars > 0 && strcmp(buff, "\n"))
	{
		numchars = get_line(client, buff, sizeof(buff));
		buff[numchars] = '\0';
		PRINTF(buff);
	}

	FILE* resource = NULL;

	if (strcmp(fileName, "Xpath/first.html") == 0)
	{
		resource = fopen(fileName, "r");
	}
	else
	{
		resource = fopen(fileName, "rb");
	}

	if (resource == NULL)
	{
		not_found(client);
	}
	else
	{

		//正式发送资源给浏览器
		headers(client, getHeadType(fileName));

		//发送请求的资源信息
		cat(client,resource);

		cout << "信息资源发送完毕！" << endl;
	}
	fclose(resource);
}

//处理用户请求的线程函数
DWORD WINAPI accept_request(LPVOID arg)
{
	char buff[1024];  //1K

	int client = (SOCKET)arg;   //客户端套接字

	//读取一行数据
	//0x015ffad8 "GET / HTTP/1.1\n"
	int numchars = get_line(client, buff, sizeof(buff));
	PRINTF(buff);  //[accept_request-53]buff="EGT..."

	char method[255];
	int j = 0, i = 0;
	while (!isspace(buff[j]) && i < sizeof(method) - 1)
	{
		method[i++] = buff[j++];
	}

	method[i] = 0;   //'0'
	PRINTF(method);

	// 检查请求的方法，本服务器是否支持
	if (_stricmp(method, "GET") && _stricmp(method, "POST"))
	{
		//向浏览器返回一个错误提示页面
		unimplement(client);
		return 0;
	}

	//解析资源文件的路径
	//www.tubage.com/xlf/first.html
	//GET /xlf/first.html HTTP/1.1\n
	char url[255];  //存放请求的资源的完整路径
	i = 0;
	//跳过资源路径前面的空格
	while (isspace(buff[j]) && j < sizeof(buff))
	{
		j++;
	}

	while (!isspace(buff[j]) && i < sizeof(url) - 1 && j < sizeof(buff))
	{
		url[i++] = buff[j++];
	}
	url[i] = 0;
	PRINTF(url);

	//www.tubage.com
	//127.0.0.1:8080/first.html
	//url /irst.html
	//路径：Xpath/first.html

	char path[512];
	sprintf(path, "Xpath%s", url);
	if (path[strlen(path) - 1] == '/')
	{
		strcat(path, "first.html");
	}
	PRINTF(path);

	struct stat status;
	if (stat(path, &status) == -1)
	{
		//请求包的剩余数据读取完毕
		while (numchars > 0 && strcmp(buff, "\n"))
		{
			numchars = get_line(client, buff, sizeof(buff));
		}
		not_found(client);
	}
	else 
	{
		if ((status.st_mode & S_IFMT) == S_IFDIR)
		{
			strcat(path, "/first.html");
		}

		server_file(client, path);
	}
	closesocket(client);

	return 0;
}

int main(void)
{
	unsigned short port = 8080;
	int server_sock = startup(&port);
	cout << "http服务已经启动，正在监听" << port << "端口！" << endl;

	struct sockaddr_in client_addr;
	int client_addr_len = sizeof(client_addr);

	// to do.
	while (1)
	{
		//阻塞时等待用户通过浏览器发起访问
		int client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_addr_len);
		if (client_sock == -1)
		{
			error_die("accept");
		}

		//使用client_sock对用户进行访问

		//创建新的线程
		//进程（包含多个线程）
		DWORD threadId = 0;  //线程Id
		CreateThread(0, 0, accept_request, (void*)client_sock, 0, &threadId);  //创建线程

	}

	// "/" 网站服务器资源目录下的 index.html


	closesocket(server_sock);

	return 0;
}