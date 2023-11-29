#ifndef REDIS_CONNECT_H
#define REDIS_CONNECT_H
///////////////////////////////////////////////////////////////
#include "ResPool.h"

#ifdef XG_LINUX

#include <errno.h>
#include <netdb.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <sys/statfs.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/syscall.h>

#define ioctlsocket ioctl
#define INVALID_SOCKET (SOCKET)(-1)

typedef int SOCKET;

#endif

using namespace std;

class RedisConnect
{
	typedef std::mutex Mutex;
	typedef std::lock_guard<mutex> Locker;

	friend class Command;

public:
	static const int OK = 1;
	static const int FAIL = -1;
	static const int IOERR = -2;
	static const int SYSERR = -3;
	static const int NETERR = -4;
	static const int TIMEOUT = -5;
	static const int DATAERR = -6;
	static const int SYSBUSY = -7;
	static const int PARAMERR = -8;
	static const int NOTFOUND = -9;
	static const int NETCLOSE = -10;
	static const int NETDELAY = -11;
	static const int AUTHFAIL = -12;

public:
	static int POOL_MAXLEN;
	static int SOCKET_TIMEOUT;

public:
	class Socket
	{
	protected:
		SOCKET sock = INVALID_SOCKET;

	public:
		static bool IsSocketTimeout()
		{
#ifdef XG_LINUX
			return errno == 0 || errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR;
#else
			return WSAGetLastError() == WSAETIMEDOUT;
#endif
		}
		static void SocketClose(SOCKET sock)
		{
			if (IsSocketClosed(sock)) return;

#ifdef XG_LINUX
			::close(sock);
#else
			::closesocket(sock);
#endif
		}
		static bool IsSocketClosed(SOCKET sock)
		{
			return sock == INVALID_SOCKET || sock < 0;
		}
		static bool SocketSetSendTimeout(SOCKET sock, int timeout)
		{
#ifdef XG_LINUX
			struct timeval tv;

			tv.tv_sec = timeout / 1000;
			tv.tv_usec = timeout % 1000 * 1000;

			return setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char*)(&tv), sizeof(tv)) == 0;
#else
			return setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char*)(&timeout), sizeof(timeout)) == 0;
#endif
		}
		static bool SocketSetRecvTimeout(SOCKET sock, int timeout)
		{
#ifdef XG_LINUX
			struct timeval tv;

			tv.tv_sec = timeout / 1000;
			tv.tv_usec = timeout % 1000 * 1000;

			return setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)(&tv), sizeof(tv)) == 0;
#else
			return setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)(&timeout), sizeof(timeout)) == 0;
#endif
		}
		SOCKET SocketConnectTimeout(const char* ip, int port, int timeout)
		{
			u_long mode = 1;
			struct sockaddr_in addr;
			SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

			if (IsSocketClosed(sock)) return INVALID_SOCKET;

			addr.sin_family = AF_INET;
			addr.sin_port = htons(port);
			addr.sin_addr.s_addr = inet_addr(ip);

			ioctlsocket(sock, FIONBIO, &mode); mode = 0;

			if (::connect(sock, (struct sockaddr*)(&addr), sizeof(addr)) == 0)
			{
				ioctlsocket(sock, FIONBIO, &mode);

				return sock;
			}

#ifdef XG_LINUX
			struct epoll_event ev;
			struct epoll_event evs;
			int handle = epoll_create(1);

			if (handle < 0)
			{
				SocketClose(sock);
			
				return INVALID_SOCKET;
			}
			
			memset(&ev, 0, sizeof(ev));
			
			ev.events = EPOLLOUT | EPOLLERR | EPOLLHUP;
			
			epoll_ctl(handle, EPOLL_CTL_ADD, sock, &ev);
			
			if (epoll_wait(handle, &evs, 1, timeout) > 0)
			{
				if (evs.events & EPOLLOUT)
				{
					int res = FAIL;
					socklen_t len = sizeof(res);
			
					getsockopt(sock, SOL_SOCKET, SO_ERROR, (char*)(&res), &len);
					ioctlsocket(sock, FIONBIO, &mode);
			
					if (res == 0)
					{
						::close(handle);
			
						return sock;
					}
				}
			}
			
			::close(handle);
#else
			struct timeval tv;

			fd_set ws;
			FD_ZERO(&ws);
			FD_SET(sock, &ws);

			tv.tv_sec = timeout / 1000;
			tv.tv_usec = timeout % 1000 * 1000;

			if (select(sock + 1, NULL, &ws, NULL, &tv) > 0)
			{
				int res = ERROR;
				int len = sizeof(res);
			
				getsockopt(sock, SOL_SOCKET, SO_ERROR, (char*)(&res), &len);
				ioctlsocket(sock, FIONBIO, &mode);
			
				if (res == 0) return sock;
			}
#endif

			SocketClose(sock);
			
			return INVALID_SOCKET;
		}

	public:
		void close()
		{
			SocketClose(sock);
			sock = INVALID_SOCKET;
		}
		bool isClosed() const
		{
			return IsSocketClosed(sock);
		}
		bool setSendTimeout(int timeout)
		{
			return SocketSetSendTimeout(sock, timeout);
		}
		bool setRecvTimeout(int timeout)
		{
			return SocketSetRecvTimeout(sock, timeout);
		}
		bool connect(const string& ip, int port, int timeout)
		{
			close();

			sock = SocketConnectTimeout(ip.c_str(), port, timeout);

			return IsSocketClosed(sock) ? false : true;
		}

	public:
		int write(const void* data, int count)
		{
			const char* str = (const char*)(data);

			int num = 0;
			int times = 0;
			int writed = 0;

			while (writed < count)
			{
				if ((num = send(sock, str + writed, count - writed, 0)) > 0)
				{
					if (num > 8)
					{
						times = 0;
					}
					else
					{
						if (++times > 100) return TIMEOUT;
					}

					writed += num;
				}
				else
				{
					if (IsSocketTimeout())
					{
						if (++times > 100) return TIMEOUT;

						continue;
					}

					return NETERR;
				}
			}

			return writed;
		}
		int read(void* data, int count, bool completed)
		{
			char* str = (char*)(data);

			if (completed)
			{
				int num = 0;
				int times = 0;
				int readed = 0;

				while (readed < count)
				{
					if ((num = recv(sock, str + readed, count - readed, 0)) > 0)
					{
						if (num > 8)
						{
							times = 0;
						}
						else
						{
							if (++times > 100) return TIMEOUT;
						}

						readed += num;
					}
					else if (num == 0)
					{
						return NETCLOSE;
					}
					else
					{
						if (IsSocketTimeout())
						{
							if (++times > 100) return TIMEOUT;

							continue;
						}

						return NETERR;
					}
				}

				return readed;
			}
			else
			{
				int val = recv(sock, str, count, 0);

				if (val > 0) return val;

				if (val == 0) return NETCLOSE;

				if (IsSocketTimeout()) return 0;

				return NETERR;
			}
		}
	};

	class Command
	{
		friend RedisConnect;

	protected:
		int status;
		string msg;
		vector<string> res;
		vector<string> vec;

	protected:
		int parse(const char* msg, int len)
		{
			if (*msg == '$')
			{
				const char* end = parseNode(msg, len);

				if (end == NULL) return DATAERR;

				switch (end - msg)
				{
				case 0: return TIMEOUT;
				case -1: return NOTFOUND;
				}

				return OK;
			}

			const char* str = msg + 1;
			const char* end = strstr(str, "\r\n");

			if (end == NULL) return TIMEOUT;

			if (*msg == '+' || *msg == '-' || *msg == ':')
			{
				this->status = OK;
				this->msg = string(str, end);

				if (*msg == '+') return OK;
				if (*msg == '-') return FAIL;

				this->status = atoi(str);

				return OK;
			}

			if (*msg == '*')
			{
				int cnt = atoi(str);
				const char* tail = msg + len;

				vec.clear();
				str = end + 2;

				while (cnt > 0)
				{
					if (*str == '*') return parse(str, tail - str);

					end = parseNode(str, tail - str);

					if (end == NULL) return DATAERR;
					if (end == str) return TIMEOUT;

					str = end;
					cnt--;
				}

				return res.size();
			}

			return DATAERR;
		}
		const char* parseNode(const char* msg, int len)
		{
			const char* str = msg + 1;
			const char* end = strstr(str, "\r\n");

			if (end == NULL) return msg;

			int sz = atoi(str);

			if (sz < 0) return msg + sz;

			str = end + 2;
			end = str + sz + 2;

			if (msg + len < end) return msg;

			res.push_back(string(str, str + sz));

			return end;
		}

	public:
		Command()
		{
			this->status = 0;
		}
		Command(const string& cmd)
		{
			vec.push_back(cmd);
			this->status = 0;
		}
		void add(const char* val)
		{
			vec.push_back(val);
		}
		void add(const string& val)
		{
			vec.push_back(val);
		}
		template<class DATA_TYPE> void add(DATA_TYPE val)
		{
			add(to_string(val));
		}
		template<class DATA_TYPE, class ...ARGS> void add(DATA_TYPE val, ARGS ...args)
		{
			add(val);
			add(args...);
		}

	public:
		string toString() const
		{
			ostringstream out;

			out << "*" << vec.size() << "\r\n";

			for (const string& item : vec)
			{
				out << "$" << item.length() << "\r\n" << item << "\r\n";
			}

			return out.str();
		}
		string get(int idx) const
		{
			return res.at(idx);
		}
		const vector<string>& getDataList() const
		{
			return res;
		}
		int getResult(RedisConnect* redis, int timeout)
		{
			auto doWork = [&]() {
				string msg = toString();
				Socket& sock = redis->sock;

				if (sock.write(msg.c_str(), msg.length()) < 0) return NETERR;

				int len = 0;
				int delay = 0;
				int readed = 0;
				char* dest = redis->buffer;
				const int maxsz = redis->memsz;

				while (readed < maxsz)
				{
					if ((len = sock.read(dest + readed, maxsz - readed, false)) < 0) return len;

					if (len == 0)
					{
						delay += SOCKET_TIMEOUT;

						if (delay > timeout) return TIMEOUT;
					}
					else
					{
						dest[readed += len] = 0;

						if ((len = parse(dest, readed)) == TIMEOUT)
						{
							delay = 0;
						}
						else
						{
							return len;
						}
					}
				}

				return PARAMERR;
			};

			status = 0;
			msg.clear();

			redis->code = doWork();

			if (redis->code < 0 && msg.empty())
			{
				switch (redis->code)
				{
				case SYSERR:
					msg = "system error";
					break;
				case NETERR:
					msg = "network error";
					break;
				case DATAERR:
					msg = "protocol error";
					break;
				case TIMEOUT:
					msg = "response timeout";
					break;
				case NOTFOUND:
					msg = "element not found";
					break;
				default:
					msg = "unknown error";
					break;
				}
			}

			redis->status = status;
			redis->msg = msg;

			return redis->code;
		}
	};

protected:
	int code = 0;
	int port = 0;
	int memsz = 0;
	int status = 0;
	int timeout = 0;
	char* buffer = NULL;

	string msg;
	string host;
	Socket sock;
	string passwd;

public:
	~RedisConnect()
	{
		close();
	}

public:
	int getStatus() const
	{
		return status;
	}
	int getErrorCode() const
	{
		if (sock.isClosed()) return FAIL;

		return code < 0 ? code : 0;
	}
	string getErrorString() const
	{
		return msg;
	}

public:
	void close()
	{
		if (buffer)
		{
			delete[] buffer;
			buffer = NULL;
		}

		sock.close();
	}
	bool reconnect()
	{
		if (host.empty()) return false;

		return connect(host, port, timeout, memsz) && auth(passwd) > 0;
	}
	int execute(Command& cmd)
	{
		return cmd.getResult(this, timeout);
	}
	template<class DATA_TYPE, class ...ARGS>
	int execute(DATA_TYPE val, ARGS ...args)
	{
		Command cmd;

		cmd.add(val, args...);

		return cmd.getResult(this, timeout);
	}
	template<class DATA_TYPE, class ...ARGS>
	int execute(vector<string>& vec, DATA_TYPE val, ARGS ...args)
	{
		Command cmd;

		cmd.add(val, args...);

		cmd.getResult(this, timeout);

		if (code > 0) std::swap(vec, cmd.res);

		return code;
	}
	bool connect(const string& host, int port, int timeout = 3000, int memsz = 2 * 1024 * 1024)
	{
		close();

		if (sock.connect(host, port, timeout))
		{
			sock.setSendTimeout(SOCKET_TIMEOUT);
			sock.setRecvTimeout(SOCKET_TIMEOUT);

			this->host = host;
			this->port = port;
			this->memsz = memsz;
			this->timeout = timeout;
			this->buffer = new char[memsz + 1];
		}

		return buffer ? true : false;
	}

public:
	int ping()
	{
		return execute("ping");
	}
	int del(const string& key)
	{
		return execute("del", key);
	}
	int ttl(const string& key)
	{
		return execute("ttl", key) == OK ? status : code;
	}
	int hlen(const string& key)
	{
		return execute("hlen", key) == OK ? status : code;
	}
	int auth(const string& passwd)
	{
		this->passwd = passwd;

		if (passwd.empty()) return OK;

		return execute("auth", passwd);
	}
	int get(const string& key, string& val)
	{
		vector<string> vec;

		if (execute(vec, "get", key) <= 0) return code;

		val = vec[0];

		return code;
	}
	int decr(const string& key, int val = 1)
	{
		return execute("decrby", key, val);
	}
	int incr(const string& key, int val = 1)
	{
		return execute("incrby", key, val);
	}
	int expire(const string& key, int timeout)
	{
		return execute("expire", key, timeout);
	}
	int keys(vector<string>& vec, const string& key)
	{
		return execute(vec, "keys", key);
	}
	int hdel(const string& key, const string& filed)
	{
		return execute("hdel", key, filed);
	}
	int hget(const string& key, const string& filed, string& val)
	{
		vector<string> vec;

		if (execute(vec, "hget", key, filed) <= 0) return code;

		val = vec[0];

		return code;
	}
	int set(const string& key, const string& val, int timeout = 0)
	{
		return timeout > 0 ? execute("setex", key, timeout, val) : execute("set", key, val);
	}
	int hset(const string& key, const string& filed, const string& val)
	{
		return execute("hset", key, filed, val);
	}

public:
	int pop(const string& key, string& val)
	{
		return lpop(key, val);
	}
	int lpop(const string& key, string& val)
	{
		vector<string> vec;

		if (execute(vec, "lpop", key) <= 0) return code;

		val = vec[0];

		return code;
	}
	int rpop(const string& key, string& val)
	{
		vector<string> vec;

		if (execute(vec, "rpop", key) <= 0) return code;

		val = vec[0];

		return code;
	}
	int push(const string& key, const string& val)
	{
		return rpush(key, val);
	}
	int lpush(const string& key, const string& val)
	{
		return execute("lpush", key, val);
	}
	int rpush(const string& key, const string& val)
	{
		return execute("rpush", key, val);
	}
	int range(vector<string>& vec, const string& key, int start, int end)
	{
		return execute(vec, "lrange", key, start, end);
	}
	int lrange(vector<string>& vec, const string& key, int start, int end)
	{
		return execute(vec, "lrange", key, start, end);
	}

public:
	int zrem(const string& key, const string& filed)
	{
		return execute("zrem", key, filed);
	}
	int zadd(const string& key, const string& filed, int score)
	{
		return execute("zadd", key, score, filed);
	}
	int zrange(vector<string>& vec, const string& key, int start, int end, bool withscore = false)
	{
		return withscore ? execute(vec, "zrange", key, start, end, "withscores") : execute(vec, "zrange", key, start, end);
	}


public:
	template<class ...ARGS>
	int eval(const string& lua)
	{
		vector<string> vec;

		return eval(lua, vec);
	}
	template<class ...ARGS>
	int eval(const string& lua, const string& key, ARGS ...args)
	{
		vector<string> vec;
	
		vec.push_back(key);
	
		return eval(lua, vec, args...);
	}
	template<class ...ARGS>
	int eval(const string& lua, const vector<string>& keys, ARGS ...args)
	{
		vector<string> vec;

		return eval(vec, lua, keys, args...);
	}
	template<class ...ARGS>
	int eval(vector<string>& vec, const string& lua, const vector<string>& keys, ARGS ...args)
	{
		int len = 0;
		Command cmd("eval");

		cmd.add(lua);
		cmd.add(len = keys.size());

		if (len-- > 0)
		{
			for (int i = 0; i < len; i++) cmd.add(keys[i]);

			cmd.add(keys.back(), args...);
		}

		cmd.getResult(this, timeout);
	
		if (code > 0) std::swap(vec, cmd.res);

		return code;
	}

	string get(const string& key)
	{
		string res;

		get(key, res);

		return res;
	}
	string hget(const string& key, const string& filed)
	{
		string res;

		hget(key, filed, res);

		return res;
	}

	const char* getLockId()
	{
		thread_local char id[0xFF] = {0};

		auto GetHost = [](){
			char hostname[0xFF];

			if (gethostname(hostname, sizeof(hostname)) < 0) return "unknow host";

			struct hostent* data = gethostbyname(hostname);

			return (const char*)inet_ntoa(*(struct in_addr*)(data->h_addr_list[0]));
		};

		if (*id == 0)
		{
#ifdef XG_LINUX
			snprintf(id, sizeof(id) - 1, "%s:%ld:%ld", GetHost(), (long)getpid(), (long)syscall(SYS_gettid));
#else
			snprintf(id, sizeof(id) - 1, "%s:%ld:%ld", GetHost(), (long)GetCurrentProcessId(), (long)GetCurrentThreadId());
#endif
		}

		return id;
	}
	bool unlock(const string& key)
	{
		const char* lua = "if redis.call('get',KEYS[1])==ARGV[1] then return redis.call('del',KEYS[1]) else return 0 end";

		return eval(lua, key, getLockId()) > 0 && status == OK;
	}
	bool lock(const string& key, int timeout = 30)
	{
		int delay = timeout * 1000;

		for (int i = 0; i < delay; i += 10)
		{
			if (execute("set", key, getLockId(), "nx", "ex", timeout) >= 0) return true;

			Sleep(10);
		}

		return false;
	}

protected:
	virtual shared_ptr<RedisConnect> grasp() const
	{
		static ResPool<RedisConnect> pool([&]() {
			shared_ptr<RedisConnect> redis = make_shared<RedisConnect>();

			if (redis && redis->connect(host, port, timeout, memsz))
			{
				if (redis->auth(passwd)) return redis;
			}

			return redis = NULL;
		}, POOL_MAXLEN);

		shared_ptr<RedisConnect> redis = pool.get();

		if (redis && redis->getErrorCode())
		{
			pool.disable(redis);

			return grasp();
		}

		return redis;
	}

public:
	static bool CanUse()
	{
		return GetTemplate()->port > 0;
	}
	static RedisConnect* GetTemplate()
	{
		static RedisConnect redis;
		return &redis;
	}
	static void SetMaxConnCount(int maxlen)
	{
		if (maxlen > 0) POOL_MAXLEN = maxlen;
	}
	static shared_ptr<RedisConnect> Instance()
	{
		return GetTemplate()->grasp();
	}
	static void Setup(const string& host, int port, const string& passwd = "", int timeout = 3000, int memsz = 2 * 1024 * 1024)
	{
#ifdef XG_LINUX
		signal(SIGPIPE, SIG_IGN);
#else
		WSADATA data; WSAStartup(MAKEWORD(2, 2), &data);
#endif
		RedisConnect* redis = GetTemplate();

		redis->host = host;
		redis->port = port;
		redis->memsz = memsz;
		redis->passwd = passwd;
		redis->timeout = timeout;
	}
};

int RedisConnect::POOL_MAXLEN = 8;
int RedisConnect::SOCKET_TIMEOUT = 10;
	
///////////////////////////////////////////////////////////////
#endif