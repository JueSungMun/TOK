#undef UNICODE
#undef _UNICODE
#include <iostream>
#include <string>
#include <memory>

using namespace std;

class Parent
{
public:
	char buf[100];
	Parent()
	{
		cout<<"Parent 생성자"<<endl;
	}
	Parent(Parent& p)
	{
		//buf = p.buf;
		cout<<"Parent 생성자 호출"<<endl;
		strcpy(this->buf, p.buf);
	}
	virtual ~Parent()
	{
		cout<<"Parent 소멸자"<<endl;
	}
	void Show()
	{
		cout<<buf<<endl;
	}
	void SetNickName(char* nickName)
	{
		strcpy(buf,nickName);
	}
	//virtual void Draw() = 0;
};

class Child_A : public Parent
{
public : 
	Child_A()
	{
		cout<<"Child_A 생성자"<<endl;
	}
	~Child_A()
	{
		cout<<"Child_A 소멸자"<<endl;
	}
	void Draw()
	{

	}
};

class Child_B : public Parent
{
public:
	Child_B(Parent* p) : Parent(*p)
	{
		delete p;
		cout<<"Child_B 생성자"<<endl;
	}

	Child_B(shared_ptr<Parent> p) : Parent(*p)
	{
		cout<<"Child_B 생성자"<<endl;
	}
	~Child_B()
	{
		cout<<"Child_B 소멸자"<<endl;
	}
};

int main()
{
	enum {Test = 200};

	char buf[150] = "바보야";
	std::string temp = buf;
	cout<<temp<<endl;
	cout<<(Test==100)<<endl;
	cout<<(Test==200)<<endl;
	//std::cout<<sizeof(buf)<<endl;
	/*
	shared_ptr<Parent> first(new Child_A());
	first->SetNickName("바보야");
	first->Show();
	first = shared_ptr<Parent>(new Child_B(first));
	first->Show();
	*/

	//shared_ptr<Parent> second(new Child_B(first));
	//second->Show();


	/*
	Parent* p;
	p = new Child_A;
	p->SetNickName("바보야");
	p->Show();
	p = new Child_B(p);
	p->Show();
	*/

	/*
	Parent* p[2];
	p[0] = new Child_A;
	p[0]->SetNickName("바보야");
	p[0]->Show();
	p[1] = new Child_B(p[0]);
	p[1]->Show();
	delete p[0];
	delete p[1];
	return 0;
	*/
}

/*
enum PROTOCOL {SEND_NICKNAME=200, SEND_READYSTATE};
enum PROTOCOL_TYPE {BROADCAST=100, NOTIFICATION};
typedef struct Message
{
	PROTOCOL_TYPE type;
	PROTOCOL protocol;
	char message[100];
};

const string TOKEN = "&$";

string MakeTheMessage(PROTOCOL_TYPE, PROTOCOL, char* msg);
bool TranslateMessage(const string& str);


int main()
{
	std::string buf;
	buf.append(std::to_string(BROADCAST));
	buf.append(TOKEN);
	buf.append(std::to_string(SEND_NICKNAME));
	buf.append(TOKEN);
	buf.append("나무꾼무니");

	TranslateMessage(buf);
	return 0;
}

string MakeTheMessage(PROTOCOL_TYPE type, PROTOCOL protocol, char* msg)
{
	std::string temp;
	temp.append(std::to_string(type));
	temp.append(TOKEN);
	temp.append(std::to_string(protocol));
	temp.append(TOKEN);
	temp.append(msg);
	return temp;
}

bool TranslateMessage(const string& str)
{
	Message result;
	int tokenIdx[2] = {0};
	tokenIdx[0] = str.find(TOKEN);
	tokenIdx[1] = str.find(TOKEN, tokenIdx[0]+1);
	int	tempIdx = tokenIdx[0]+TOKEN.length();
	int typeSize = tokenIdx[0];
	int protocolSize = tokenIdx[1] - tempIdx;
	
	result.type = static_cast<PROTOCOL_TYPE>(atoi(str.substr(0,typeSize).c_str()));
	result.protocol = static_cast<PROTOCOL>(atoi(str.substr(tempIdx, protocolSize).c_str()));
	tempIdx = tokenIdx[1]+TOKEN.length();
	strcpy(result.message, str.substr(tempIdx, str.length()).c_str());
	
	cout<<result.type<<endl;
	cout<<result.protocol<<endl;
	cout<<result.message<<endl;
	return true;
	/*
	Message result;
	int firstTokenIdx = str.find(TOKEN);
	int lastTokenIdx = str.find(TOKEN, firstTokenIdx+1);
	int typeSize = firstTokenIdx-0;
	int protocolSize = lastTokenIdx-firstTokenIdx-TOKEN.length();

	result.type = static_cast<PROTOCOL_TYPE>(atoi(str.substr(0,typeSize).c_str()));
	result.protocol = static_cast<PROTOCOL>(atoi(str.substr(firstTokenIdx+TOKEN.length(), protocolSize).c_str()));
	strcpy(result.message, str.substr(lastTokenIdx+2, str.length()).c_str());
	//cout<<temp.substr(firstTokenIdx+3, lastTokenIdx).c_str()<<endl;
	//
	cout<<result.type<<endl;
	cout<<result.protocol<<endl;
	cout<<result.message<<endl;
	cout<<TOKEN.length()<<endl;
	//return result;
	*/
//}