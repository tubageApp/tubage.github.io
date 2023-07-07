#include<iostream>
#include<string>
using namespace std;

#pragma warning(disable:4996)

//����ͨ����Ҫ������ͷ�ļ�����Ҫ���صĿ��ļ�
#include<winsock.h>
#pragma comment(lib,"WS2_32.lib")

#define PRINTF(str) cout << " [ " << __func__ << " - " << __LINE__ << " ] " << #str << " = " << str << endl;

void error_die(const char* str)
{
	perror(str);
	exit(1);
}

//ʵ������ĳ�ʼ��
//����ֵ���׽��֣��������˵��׽��֣�
//�˿�
//������port ��ʾ�˿�
//		���*port��ֵ��0����ô���Զ�����һ�����õĶ˿�
//		Ϊ���� tinyhttpd�������¾�
int startup(unsigned short* port)
{
	//1������ͨ�ŵĳ�ʼ��
	WSADATA data;
	int ret = WSAStartup(
		MAKEWORD(1,1),    //1.1�汾��Э��
		&data   
	);
	if (ret != 0)
	{
		error_die("WSAStartup");
	}
	
	int server_socket = socket(
		PF_INET,        //�׽��ֵ�����
		SOCK_STREAM,    //������ 
		IPPROTO_TCP
	);
	if (server_socket == -1)
	{
		//��ӡ������ʾ������������
		error_die("�׽���");
	}

	//���ö˿ڿɸ���
	int opt = 1;
	ret = setsockopt(server_socket,SOL_SOCKET,SO_REUSEADDR,(const char*)&opt,sizeof(opt));
	if (ret == -1)
	{
		error_die("setsockopt");
	}

	//���÷������������ַ
	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(*port);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);


	//���׽���
	if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
	{
		error_die("bind");
	}

	//��̬����˿�
	int nameLen = sizeof(server_addr);
	if (*port == 0)
	{
		if (getsockname(server_socket, (struct sockaddr*)&server_addr, &nameLen) < 0)
		{
			error_die("getsockname");
		}

		*port = server_addr.sin_port;
	}

	//������������
	if (listen(server_socket, 5) < 0)
	{
		error_die("listen");
	}

	return server_socket;
}

//��ָ���Ŀͻ����׽��֣���ȡһ�����ݣ����浽buff�У�����ʵ�ʶ�ȡ�����ֽ���
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
	//��ָ�����׽��֣�����һ����ʾ��û��ʵ�ֵĴ���ҳ��

}

void not_found(int client)
{
	//����404��Ӧ
	char buff[1024];

	strcpy(buff, "HTTP/1.0 200 OK\r\n");
	send(client, buff, strlen(buff), 0);

	strcpy(buff, "Server: TubageHttpd/0.1\r\n");
	send(client, buff, strlen(buff), 0);

	strcpy(buff, "Content-type:text/html\n");
	send(client, buff, strlen(buff), 0);

	strcpy(buff, "\r\n");
	send(client, buff, strlen(buff), 0);

	//����404��ҳ����
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
	//������Ӧ����ͷ��Ϣ
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
	cout << "һ�����͡�" << count << "���ֽڸ������" << endl;
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

	//���������ݰ���ʣ�������У�����
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

		//��ʽ������Դ�������
		headers(client, getHeadType(fileName));

		//�����������Դ��Ϣ
		cat(client,resource);

		cout << "��Ϣ��Դ������ϣ�" << endl;
	}
	fclose(resource);
}

//�����û�������̺߳���
DWORD WINAPI accept_request(LPVOID arg)
{
	char buff[1024];  //1K

	int client = (SOCKET)arg;   //�ͻ����׽���

	//��ȡһ������
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

	// �������ķ��������������Ƿ�֧��
	if (_stricmp(method, "GET") && _stricmp(method, "POST"))
	{
		//�����������һ��������ʾҳ��
		unimplement(client);
		return 0;
	}

	//������Դ�ļ���·��
	//www.tubage.com/xlf/first.html
	//GET /xlf/first.html HTTP/1.1\n
	char url[255];  //����������Դ������·��
	i = 0;
	//������Դ·��ǰ��Ŀո�
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
	//·����Xpath/first.html

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
		//�������ʣ�����ݶ�ȡ���
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
	cout << "http�����Ѿ����������ڼ���" << port << "�˿ڣ�" << endl;

	struct sockaddr_in client_addr;
	int client_addr_len = sizeof(client_addr);

	// to do.
	while (1)
	{
		//����ʱ�ȴ��û�ͨ��������������
		int client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_addr_len);
		if (client_sock == -1)
		{
			error_die("accept");
		}

		//ʹ��client_sock���û����з���

		//�����µ��߳�
		//���̣���������̣߳�
		DWORD threadId = 0;  //�߳�Id
		CreateThread(0, 0, accept_request, (void*)client_sock, 0, &threadId);  //�����߳�

	}

	// "/" ��վ��������ԴĿ¼�µ� index.html


	closesocket(server_sock);

	return 0;
}