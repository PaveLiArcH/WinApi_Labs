#pragma once

template <typename T> class CyclicBuf
{
	unsigned int cf_size;
	unsigned int cf_head;
	unsigned int cf_fill;
	T *cf_buf;

public:
	CyclicBuf(unsigned int a_size)
	{
		cf_size=a_size;
		cf_buf=new T[a_size];
		cf_head=0;
		cf_fill=0;
	}

	T operator[](unsigned int a_index)
	{
		if (a_index<cf_fill)
		{
			if (cf_fill==cf_size-1)
			{
				a_index=(a_index+cf_head+1)%cf_size;
			}
			return cf_buf[a_index];
		} else
		{
			throw 1;
		}
	}

	void cm_Add(T a_element)
	{
		if (cf_fill)
		{
			cf_head++;
			cf_head%=cf_size;
		}
		if (cf_fill<cf_size-1)
		{
			cf_fill++;
		}
		cf_buf[cf_head]=a_element;
	}

	unsigned int cm_GetFill()
	{
		return cf_fill;
	}
};