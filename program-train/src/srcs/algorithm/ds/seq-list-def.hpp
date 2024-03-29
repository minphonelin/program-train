/*
 * Progarm Name: seq-list-def.hpp
 * Created Time: 2016-08-27 08:44:20
 * Last modified: 2017-01-06 11:25:31
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _SEQ_LIST_DEF_HPP_
#define _SEQ_LIST_DEF_HPP_

#include "linear-list-def.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include <cstdlib>
#include <cstdio>
#include <cstring>

using std::cout;
using std::endl;
using std::string;
using std::vector;

/*
 * Note : 
 *  用顺序存储方式实现的线性表称为顺序表(sequential list)，是用数组作为表的存储结构的
 *
 *  顺序表所有操作的实现中，最复杂、最耗时的就是搜索、插入和删除运算的实现代码，分析顺序表的性能，主要
 *  就是分析这3个操作的实现代码的时间复杂性
 * */

template <typename T>
class SeqList: public LinearList<T>{
public:
    SeqList(int sz = 100);
    SeqList(SeqList<T> &L);
    ~SeqList(){ delete [] this->data; }
    int  size(void) const { return this->max_size; }
    int  length(void) const { return this->last + 1; }
    int  search(T &x) const;
    T   *get_data(int i) const;
    void set_data(int i, T &x){ if(i > 0 && i <= this->last + 1) this->data[i-1] = x; }
    int  insert(int i, T &x);
    int  remove(int i, T &x);
    int  isempty(void) const { return (this->last == -1) ? 0 : -1 ; }
    int  isfull(void) const { return (this->last == this->max_size - 1) ? 0 : -1 ; }
    int  sort(void);
    int  input(T x);
    void output(void);
    SeqList<T> &operator=(const SeqList<T> &L);
protected:
    int  resize(int size);
protected:
    T  *data;
    int max_size;
    int last;
};

//-----------------------------------------------------------------------------

template <typename T>
SeqList<T>::SeqList(int sz)
{
    if(sz > 0){
        this->last      = -1;
        this->max_size  = sz;

        this->data      = new T[this->max_size];
        if(NULL == this->data){
            cout << "new T[max_size] err!" << endl;
            exit(1);
        }else{

            int nid = 0;

            string un[] = {
                string(typeid(char).name()),
                string(typeid(unsigned char).name()),
                string(typeid(int).name()),
                string(typeid(unsigned int).name()),
                string(typeid(short).name()),
                string(typeid(unsigned short).name()),
                string(typeid(long).name()),
                string(typeid(unsigned long).name()),
                string(typeid(float).name()),
                string(typeid(double).name())
            };

            string tname = typeid(T).name();
            for(size_t i=0; i<sizeof(un)/sizeof(un[0]); i++){
                if(tname == un[i]){
                    nid = 1;
                    cout << "SeqList<T> :: nid = 1" << endl;
                    break;
                }
            }

            switch(nid){
                case 1:
                    break;
                default : break;
            }
        }
    }
}

template <typename T>
SeqList<T>::SeqList(SeqList<T> &L)
{
    this->max_size  = L.size();
    this->last      = L.length() - 1;

    this->data      = new T[this->max_size];
    if(NULL == this->data){
        cout << "new T[max_size] err !" << endl;
        exit(1);
    }else{
            int nid = 0;

            string un[] = {
                string(typeid(char).name()),
                string(typeid(unsigned char).name()),
                string(typeid(int).name()),
                string(typeid(unsigned int).name()),
                string(typeid(short).name()),
                string(typeid(unsigned short).name()),
                string(typeid(long).name()),
                string(typeid(unsigned long).name()),
                string(typeid(float).name()),
                string(typeid(double).name())
            };

            string tname = typeid(T).name();
            for(size_t i=0; i<sizeof(un)/sizeof(un[0]); i++){
                if(tname == un[i]){
                    nid = 1;
                    cout << "SeqList<T> :: nid = 1" << endl;
                    break;
                }
            }

            switch(nid){
                case 1:
                    break;
                default : break;
            }
    }

    for(int i=0; i<L.length(); i++){
        this->data[i] = L.get_data(i);
    }
}

template <typename T>
T   *SeqList<T>::get_data(int i) const 
{
    return (i >= 0 && i <= this->last ) ? &this->data[i] : NULL;
}

template <typename T>
int  SeqList<T>::search(T &x) const 
{
    int ret = -1;

    for(int i=0; i<this->max_size; i++){
        if(x == this->data[i]){
            ret = i;
            break;
        }
    }

    return ret;
}

template <typename T>
int  SeqList<T>::insert(int i, T &x)
{
    int ret = 0;

    if(this->last == this->max_size - 1)    ret = -1;
    else if((i < 0) || (i > this->last+1))  ret = -1;
    else{
        for(int j=this->last; j>=i; j--) this->data[j+1] = this->data[j];
        this->data[i] = x;
        this->last++;
    }

    return ret;
}

template <typename T>
int  SeqList<T>::remove(int i, T &x)
{
    int ret = 0;

    if(0 > this->last)                   ret = -1;
    else if((0 > i) || (i > this->last)) ret = -1;
    else{
        x = this->data[i];
        for(int j=i; j<(this->last+1); j++) this->data[j] = this->data[j+1];
        this->last--;
    }

    return ret;
}

template <typename T>
int  SeqList<T>::sort(void)
{
    cout << "sort" << endl;
    return 0;
}

template <typename T>
int  SeqList<T>::input(T x)
{
    int ret = 0;

    if(this->last == this->max_size - 1)    ret = -1;
    else{
        this->data[++this->last] = x;
    }

    return ret;
}

template <typename T>
void SeqList<T>::output(void)
{
    cout << "this->last : " << this->last << endl;
    cout << "SeqList<T> : " << typeid(this->data[0]).name() << " ";
    for(int i=0; i<=this->last; i++){
        cout << this->data[i] << "-";
    }
    cout << endl;
}

template <typename T>
SeqList<T> &SeqList<T>::operator=(const SeqList<T> &L)
{
    return L;
}

template <typename T>
int  SeqList<T>::resize(int size)
{
    int ret = 0;

    if(size > this->max_size){

        T *newbuf = new T[size];

        if(NULL != newbuf){
            int n = this->last + 1;
            T *sptr = this->data;
            T *dptr = newbuf;

            while(n--) *dptr++ = *sptr++;
            delete [] this->data;

            this->data = newbuf;
            this->max_size = size;

        }else{
            ret = -1;
        }

    }else{
        ret = -1;
    }

    return ret;
}

#endif //_SEQ_LIST_DEF_HPP_

