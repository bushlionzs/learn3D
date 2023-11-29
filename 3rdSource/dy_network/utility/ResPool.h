#ifndef XG_RESPOOL_H
#define XG_RESPOOL_H
//////////////////////////////////////////////////////////////////////////////
#include "RedisTypeDef.h"

#include <ctime>
#include <mutex>
#include <vector>
#include <string>
#include <memory>
#include <thread>
#include <sstream>
#include <iostream>
#include <iterator>
#include <typeinfo>
#include <algorithm>
#include <functional>

using namespace std;

template<typename T> class ResPool
{
	class Data
	{
	public:
		int num;
		time_t utime;
		shared_ptr<T> data;

		shared_ptr<T> get()
		{
			utime = time(NULL);
			num++;

			return data;
		}
		Data(shared_ptr<T> data)
		{
			update(data);
		}
		void update(shared_ptr<T> data)
		{
			this->num = 0;
			this->data = data;
			this->utime = time(NULL);
		}
	};

protected:
	mutex mtx;
	int maxlen;
	int timeout;
	vector<Data> vec;
	function<shared_ptr<T>()> func;

public:
	shared_ptr<T> get()
	{
		if (timeout <= 0) return func();

		auto grasp = [&](){
			int len = 0;
			int idx = -1;
			shared_ptr<T> tmp;
			time_t now = time(NULL);

			mtx.lock();

			len = vec.size();

			for (int i = 0; i < len; i++)
			{
				Data& item = vec[i];

				if (item.data.get() == NULL || item.data.use_count() == 1)
				{
					if (tmp = item.data)
					{
						if (item.num < 100 && item.utime + timeout > now)
						{
							shared_ptr<T> data = item.get();

							mtx.unlock();

							return data;
						}

						item.data = NULL;
					}

					idx = i;
				}
			}

			mtx.unlock();

			if (idx < 0)
			{
				if (len >= maxlen) return shared_ptr<T>();

				shared_ptr<T> data = func();

				if (data.get() == NULL) return data;

				mtx.lock();

				if (vec.size() < maxlen) vec.push_back(data);

				mtx.unlock();

				return data;
			}

			shared_ptr<T> data = func();

			if (data.get() == NULL) return data;

			mtx.lock();

			vec[idx].update(data);

			mtx.unlock();

			return data;
		};

		shared_ptr<T> data = grasp();

		if (data) return data;

		time_t endtime = time(NULL) + 3;

		while (true)
		{
			Sleep(10);

			if (data = grasp()) return data;

			if (endtime < time(NULL)) break;
		}

		return data;
	}
	void clear()
	{
		lock_guard<mutex> lk(mtx);

		vec.clear();
	}
	int getLength() const
	{
		return maxlen;
	}
	int getTimeout() const
	{
		return timeout;
	}
	void disable(shared_ptr<T> data)
	{
		lock_guard<mutex> lk(mtx);

		for (Data& item : vec)
		{
			if (data == item.data)
			{
				item.data = NULL;

				break;
			}
		}
	}
	void setLength(int maxlen)
	{
		lock_guard<mutex> lk(mtx);

		this->maxlen = maxlen;

		if (vec.size() > maxlen) vec.clear();
	}
	void setTimeout(int timeout)
	{
		lock_guard<mutex> lk(mtx);

		this->timeout = timeout;

		if (timeout <= 0) vec.clear();
	}
	void setCreator(function<shared_ptr<T>()> func)
	{
		lock_guard<mutex> lk(mtx);

		this->func = func;
		this->vec.clear();
	}
	ResPool(int maxlen = 8, int timeout = 60)
	{
		this->timeout = timeout;
		this->maxlen = maxlen;
	}
	ResPool(function<shared_ptr<T>()> func, int maxlen = 8, int timeout = 60)
	{
		this->timeout = timeout;
		this->maxlen = maxlen;
		this->func = func;
	}
};
//////////////////////////////////////////////////////////////////////////////
#endif