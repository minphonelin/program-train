/*
 * Progarm Name: process.hpp
 * Created Time: 2016-12-02 17:31:56
 * Last modified: 2016-12-06 22:44:30
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _PROCESS_HPP_
#define _PROCESS_HPP_

/* 
 * 向exit()函数传递的参数值和main()函数的return语句返回的值都会传递给操作系统
 *
 * 而操作系统不会销毁子进程，直到把这些值传递给产生该子进程的父进程，处于这种
 * 状态下的进程就是僵尸进程
 * */

class Process{
public:
    Process();
    ~Process();
    int process_main(int argc, char **argv);
private:
    int fork_child_porc(void);
    int zombie(void);
    int destroy_zombie(void);
    int destroy_zombie(int);
private:
    int m_global;
};

#endif //_PROCESS_HPP_
