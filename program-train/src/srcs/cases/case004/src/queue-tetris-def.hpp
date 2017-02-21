/*
 * Progarm Name: queue-tetris-def.hpp
 * Created Time: 2017-02-17 10:26:04
 * Last modified: 2017-02-21 17:58:31
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _QUEUE_TETRIS_DEF_HPP_
#define _QUEUE_TETRIS_DEF_HPP_

#include <list>
#include <tuple>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <functional>
#include <cstdio>
#include <cstdlib>
#include <typeinfo>

using std::list;
using std::tuple;
using std::map;
using std::vector;
using std::pair;
using std::cout;
using std::endl;

template <typename T>
class QueueTetris{
public:
    QueueTetris();
    ~QueueTetris();
    int  push(T x);
    int  pop(T &x, bool flag = true);
    int  pop(T &expec, T &x, bool flag = true);
    int  is_empty(void) const;
    int  size(void) const;
private:
    list<T>     m_data;
};

template <typename T>
class Tetris{
public:
    Tetris();
    Tetris(map<int, vector<int> > &data); /* map<tid - <devs>> */
    ~Tetris();
    int  add_tid(pair<int, vector<int> > &data); /* pair<tid - <devs>> */
    int  update_tid(pair<int, vector<int> > &data); /* pair<tid - <devs>> */
    int  del_tid(int tid);
    int  is_empty(void) const;
    int  is_empty(int tid) const;
    int  push_left(int dev, T &left);
    int  push_right(int tid, T &right);
    int  push_left(pair<int, int> &indicate, T &left); /* <tid, dev> */
    int  error_check(void);
    int  error_check(int tid);
    int  register_trigger_cb(std::function<int (int, T)> trigger);
    void print_info(int tid, unsigned line = 0);
private:
    int  decrease(int tid); /* clear buttom layer */
    int  check_tid_left_status(int tid, int status); /* same return 0 */
    int  check_tid_right_status(int tid, int &status);
private:
    map<int, int>                                       m_devs_tid;
    map<int, vector<int> >                              m_tid_devs;
    map<int, tuple<vector<int>, T> >                    m_tid_devs_decoupling; /* vector<devs> -> right value */
    map<int, tuple<QueueTetris<T>, QueueTetris<T> > >   m_queue_tetris;
    std::function<int (int, T)>                         m_trigger_cb = nullptr;
};

#define ERROR_MAX_REMAIN    5

//-----------------------------------------------------------------------------

template <typename T>
QueueTetris<T>::QueueTetris()
{
}

template <typename T>
QueueTetris<T>::~QueueTetris()
{
}

template <typename T>
int  QueueTetris<T>::push(T x)
{
    this->m_data.push_back(x);
    return 0;
}

template <typename T>
int  QueueTetris<T>::pop(T &x, bool flag)
{
    int ret = 0;

    if(false == this->m_data.empty()){
        x = this->m_data.front();
        if(true == flag){
            this->m_data.pop_front();
        }
    }else
        ret = -1;

    return ret;
}

template <typename T>
int  QueueTetris<T>::pop(T &expec, T &x, bool flag)
{
    int ret = 0;

    if(false == this->m_data.empty()){
        auto iter = find(this->m_data.begin(), this->m_data.end(), expec);
        if(iter != this->m_data.end()){
            x = *iter;
            if(true == flag)
                this->m_data.erase(iter);
        }else
            ret = -1;
    }else
        ret = -1;

    return ret;
}

template <typename T>
int  QueueTetris<T>::is_empty(void) const
{
    return this->m_data.empty() ? 0 : -1;
}

template <typename T>
int  QueueTetris<T>::size(void) const
{
    return this->m_data.size();
}

template <typename T>
Tetris<T>::Tetris()
{
}

template <typename T>
Tetris<T>::Tetris(map<int, vector<int> > &data) /* map<tid - <devs>> */
    :m_tid_devs(data)
{
    for(auto iter = this->m_tid_devs.begin();
             iter!= this->m_tid_devs.end(); iter++){
        for(auto ui : iter->second){
            this->m_devs_tid[ui] = iter->first;
        }
    }
}

template <typename T>
Tetris<T>::~Tetris()
{
}

template <typename T>
int  Tetris<T>::add_tid(pair<int, vector<int> > &data) /* pair<tid - <devs>> */
{
    int ret = 0;
    auto iter = this->m_tid_devs.find(data.first);

    if(iter != this->m_tid_devs.end()){
        vector<int> old_members = this->m_tid_devs[data.first];

        this->m_tid_devs[data.first] = data.second;

        for(auto u : old_members){
            auto iter_u = this->m_devs_tid.find(u);
            if(iter_u != this->m_devs_tid.end()){
                this->m_devs_tid.erase(iter_u);
            }else{
                cout << "[Error] Line = " << __LINE__ << endl;
            }
        }

        for(auto u : this->m_tid_devs[data.first]){
            this->m_devs_tid[u] = data.first;
        }
    }else
        ret = -1;

    return ret;
}

template <typename T>
int  Tetris<T>::update_tid(pair<int, vector<int> > &data) /* pair<tid - <devs>> */
{
    int ret = 0;
    auto iter = this->m_tid_devs.find(data.first);

    if(iter != this->m_tid_devs.end()){
        vector<int> old_members = this->m_tid_devs[data.first];

        this->m_tid_devs[data.first] = data.second;

        for(auto u : old_members){
            auto iter_u = this->m_devs_tid.find(u);
            if(iter_u != this->m_devs_tid.end()){
                this->m_devs_tid.erase(iter_u);
            }else{
                cout << "[Error] Line = " << __LINE__ << endl;
            }
        }

        for(auto u : this->m_tid_devs[data.first]){
            this->m_devs_tid[u] = data.first;
        }
        // todo
    }else
        ret = -1;

    return ret;
}

template <typename T>
int  Tetris<T>::del_tid(int tid)
{
    int ret = 0;
    auto iter = this->m_tid_devs.find(tid);

    if(iter != this->m_tid_devs.end()){
        vector<int> del_members = this->m_tid_devs[tid];

        for(auto u : del_members){
            auto iter_u = this->m_devs_tid.find(u);
            if(iter_u != this->m_devs_tid.end()){
                this->m_devs_tid.erase(iter_u);
            }else{
                cout << "[Error] Line = " << __LINE__ << endl;
            }
        }

        this->m_tid_devs.erase(iter);
    }else
        ret = -1;

    return ret;
}

template <typename T>
int  Tetris<T>::is_empty(void) const
{
    if(true != this->m_queue_tetris.empty()){
        return -1;
    }
    return 0;
}

template <typename T>
int  Tetris<T>::is_empty(int tid) const
{
    int ret = 0;

    vector<int> members = this->m_tid_devs[tid];

    for(auto u : members){
        if(0 != std::get<0>(this->m_queue_tetris[u]).is_empty()){
            ret = -1;
            break;
        }
        if(0 != std::get<1>(this->m_queue_tetris[u]).is_empty()){
            ret = -1;
            break;
        }
    }

    return ret;
}

template <typename T>
int  Tetris<T>::push_left(int dev, T &left)
{
    if(0 == this->error_check(this->m_devs_tid[dev])){

        /*
         * clear buttom layer
         * */
        while(-1 != this->decrease(this->m_devs_tid[dev]));
    }


    /*
     * recover coupling check
     * */
    auto iter = find(
                    std::get<0>(this->m_tid_devs_decoupling[this->m_devs_tid[dev]]).begin(),
                    std::get<0>(this->m_tid_devs_decoupling[this->m_devs_tid[dev]]).end(),
                    dev);
    if(iter != std::get<0>(this->m_tid_devs_decoupling[this->m_devs_tid[dev]]).end()){

        /*
         * Trigger
         * */
        if(left != std::get<1>(this->m_tid_devs_decoupling[this->m_devs_tid[dev]])){

            /* 
             * recover right
             * */
            {
                int dev_bro = this->m_tid_devs[this->m_devs_tid[dev]][0];

                QueueTetris<T> right_que = std::get<1>(this->m_queue_tetris[dev_bro]);

                while(0 != right_que.is_empty()){
                    T right_u;
                    right_que.pop(right_u);

                    std::get<0>(this->m_queue_tetris[dev]).push(right_u);
                    std::get<1>(this->m_queue_tetris[dev]).push(right_u);
                }

                std::get<0>(this->m_queue_tetris[dev]).push(left);
                std::get<1>(this->m_queue_tetris[dev]).push(left);
            }

            /* trigger to dev-brothers */
            for(auto u : this->m_tid_devs[this->m_devs_tid[dev]]){
                std::get<1>(this->m_queue_tetris[u]).push(left);
            }

            this->m_tid_devs[this->m_devs_tid[dev]].push_back(dev);

            std::get<0>(this->m_tid_devs_decoupling[this->m_devs_tid[dev]]).erase(iter);

            this->m_trigger_cb(this->m_devs_tid[dev], left);

        /*
         * Recover
         * */
        }else{

            std::get<0>(this->m_queue_tetris[dev]).push(left);
            std::get<1>(this->m_queue_tetris[dev]).push(left);

            this->m_tid_devs[this->m_devs_tid[dev]].push_back(dev);

            std::get<0>(this->m_tid_devs_decoupling[this->m_devs_tid[dev]]).erase(iter);

            #if 0
            /*
             * clear buttom layer
             * */
            this->decrease(this->m_devs_tid[dev]);
            #endif
        }
    }else{

        std::get<0>(this->m_queue_tetris[dev]).push(left);

        /*
         * clear buttom layer
         * */
        this->decrease(this->m_devs_tid[dev]);

        if(0 == std::get<1>(this->m_queue_tetris[dev]).is_empty()){

            QueueTetris<T> left_que = std::get<0>(this->m_queue_tetris[dev]);
            cout << "Line : " << __LINE__ << " - left_que.size() : " << left_que.size() << endl; 
            while(0 != left_que.is_empty()){
                T left_u;
                left_que.pop(left_u);

                /* trigger to dev-brothers */
                for(auto u : this->m_tid_devs[this->m_devs_tid[dev]]){
                    std::get<1>(this->m_queue_tetris[u]).push(left_u);
                }

                if(0 != this->decrease(this->m_devs_tid[dev])){
                    this->m_trigger_cb(this->m_devs_tid[dev], left_u);
                }else{
                    cout << "Line : " << __LINE__ << " - push_left() - decrease() " << endl;
                }
            }
        }else{
            cout << "Line : " << __LINE__ << " - push_left() " << endl;
        }
    }

    return 0;
}

template <typename T>
int  Tetris<T>::push_right(int tid, T &right)
{
    vector<int> members = this->m_tid_devs[tid];

    for(auto u : members){
        auto iter = this->m_queue_tetris.find(u);
        if(iter != this->m_queue_tetris.end()){
            std::get<1>(*iter).push(right);
        }else{
            QueueTetris<T> qleft;
            QueueTetris<T> qright;

            qright.push(right);

            this->m_queue_tetris.insert(make_pair(u, make_tuple(qleft, qright)));
        }
    }

    auto iter = this->m_tid_devs_decoupling.find(tid);
    if(iter != this->m_tid_devs_decoupling.end()){
        std::get<1>(this->m_tid_devs_decoupling[tid]) = right;
    }

    return 0;
}

template <typename T>
int  Tetris<T>::push_left(pair<int, int> &indicate, T &left) /* <tid, dev> */
{
    return this->push_left(indicate.second, left);
}

template <typename T>
int  Tetris<T>::error_check(void)
{
    int ret = -1;

    for(auto &u : this->m_tid_devs){
        ret = this->error_check(u.first);
    }

    return ret;
}

template <typename T>
int  Tetris<T>::error_check(int tid)
{
    int status;
    vector<int> members = this->m_tid_devs[tid];

    if(0 < members.size()){
        if(0 != std::get<1>(this->m_queue_tetris[members[0]]).pop(status, false)){
            cout << "[Warning] Line = " << __LINE__ << " status = -1 ! - members[0] = " << members[0] << endl;
            status = -1;
            return -1;
        }
    }else{
        cout << "[Error] Line = " << __LINE__ << " - tid-devs size() = 0 " << endl;
        return 0;
    }

    for(auto u : members){
        int status_right = 0;

        if(-1 != std::get<1>(this->m_queue_tetris[u]).pop(status_right, false)){
            if(status_right != status){
                cout << "[Error] Line = " << __LINE__ << "status_right != status !"<< endl;
                status = -1;
                return 0;
            }
        }
    }

    int  left_remain  = 0;
    int  right_remain = 0;
    vector<int> decoupling_devs;

    for(auto u : members){
        int left_size  = std::get<0>(this->m_queue_tetris[u]).size();
        int right_size = std::get<1>(this->m_queue_tetris[u]).size();

        if(left_size > right_size){
            if(ERROR_MAX_REMAIN > left_remain)
                left_remain = left_size - right_size;
        }else if(0 == left_size){
            right_remain= right_size;
            decoupling_devs.push_back(u);
        }

        #if 0
        if((left_remain >= ERROR_MAX_REMAIN) && (right_remain >= ERROR_MAX_REMAIN)){
            break;
        }
        #endif
    }

    if((left_remain >= ERROR_MAX_REMAIN) && (right_remain >= ERROR_MAX_REMAIN)){
        /* 
         * decoupling
         * */
        for(auto u : decoupling_devs){
            auto iter = find(this->m_tid_devs[tid].begin(), this->m_tid_devs[tid].end(), u);
            if(iter != this->m_tid_devs[tid].end()){
                this->m_tid_devs[tid].erase(iter);
            }
        }

        this->m_tid_devs_decoupling.insert(make_pair(tid, make_tuple(decoupling_devs, -1)));

        return 0;
    }

    return -1;
}

template <typename T>
int  Tetris<T>::decrease(int tid) /* clear buttom layer */
{
    int status_right;
    int status_left;

    if(-1 != this->check_tid_right_status(tid, status_right)){
        if(-1 != this->check_tid_left_status(tid, status_right)){
            vector<int> members = this->m_tid_devs[tid];
            for(auto u : members){
                if(0 != std::get<1>(this->m_queue_tetris[u]).pop(status_right)){
                    cout << "[Error] Line = " << __LINE__ << " - decrease()" << endl;
                    return -1;
                }
                if(0 != std::get<0>(this->m_queue_tetris[u]).pop(status_right, status_left)){
                    cout << "[Error] Line = " << __LINE__  << " - decrease()" << endl;
                    return -1;
                }
            }
        }else
            return -1;
    }else
        return -1;

    return 0;
}

template <typename T>
int  Tetris<T>::check_tid_left_status(int tid, int status) /* same return 0 */
{
    vector<int> members = this->m_tid_devs[tid];

    if(0 > members.size()){
        cout << "[Error] Line = " << __LINE__ << " - tid-devs size() = 0 " << endl;
        return -1;
    }

    int ret = 0;

    for(auto u : members){
        int status_left = 0;
        if(0 != std::get<0>(this->m_queue_tetris[u]).pop(status, status_left, false)){
            ret = -1;
            break;
        }
    }

    return ret;
}

template <typename T>
int  Tetris<T>::check_tid_right_status(int tid, int &status) /* same return 0 */
{
    vector<int> members = this->m_tid_devs[tid];

    if(0 < members.size()){
        if(0 != std::get<1>(this->m_queue_tetris[members[0]]).pop(status, false)){
            cout << "[Warning] Line = " << __LINE__ << endl;
            status = -1;
            return -1;
        }
    }else{
        cout << "[Error] Line = " << __LINE__ << " - tid-devs size() = 0 " << endl;
        return -1;
    }

    for(auto u : members){
        int status_right = 0;
        if(-1 != std::get<1>(this->m_queue_tetris[u]).pop(status_right, false)){
            if(status_right != status){
                cout << "[Error] Line = " << __LINE__ << endl;
                status = -1;
                return -1;
            }
        }else
            return -1;
    }

    return 0;
}

template <typename T>
int  Tetris<T>::register_trigger_cb(std::function<int (int, T)> trigger)
{
    this->m_trigger_cb = trigger; return 0;
}

template <typename T>
void Tetris<T>::print_info(int tid, unsigned line)
{
    cout << "-----------------------------------------------------------------------------" << endl;
    cout << "Tetris<T> Info : "; printf("tid = %.2d -", tid);
    for(auto i : this->m_tid_devs[tid]) printf(" %2.d", i);
    cout << " | Line = " << line << endl;

    vector<int> members = this->m_tid_devs[tid];
    for(auto i : members){
        QueueTetris<T> left_que = std::get<0>(this->m_queue_tetris[i]);
        QueueTetris<T> right_que= std::get<1>(this->m_queue_tetris[i]);

        printf("    left :<%3.3d> ", i);
        while(0 != left_que.is_empty()){
            T left_u;

            if(0 == left_que.pop(left_u)){
                if(typeid(int).name() == typeid(T).name()){
                    printf(" %.2d", left_u);
                }
            }

        }
        cout << endl;

        printf("    right:<%3.3d> ", i);
        while(0 != right_que.is_empty()){
            T right_u;

            if(0 == right_que.pop(right_u)){
                if(typeid(int).name() == typeid(T).name()){
                    printf(" %.2d", right_u);
                }
            }

        }
        cout << endl;
    }
}

#endif //_QUEUE_TETRIS_DEF_HPP_

