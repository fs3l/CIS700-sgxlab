Module 1: Understanding SGX Memory Protection 
---

#### Preparation

1. C/C++ programming
2. Linux shell and text editing (e.g. vim or emacs)
3. SGX SDK sample code (under dir. `intro_sample`)

#### Tutorial (1)

The tutorial in `intro_lec` presents the SGX programming specification related to ECall and OCall. It is based on sample code in dir. `intro_sample`.

#### In-class Lab (2): Performance Benchmarking 

This lab requires you to write a simple program to compute the sum of an array, execute it inside/outside enclave, and observe the performance difference, as a way to understand the performance overhead caused by SGX memory protection engine.

File `./lab1/App/sum.h` has implemented function `call_sum(int * list, long size)` which calculates sum of an array with cache misses increased deliberately. 

To compile and execute the provided repository, follow the instructions below. Note when running `./app`, it may take a while to set up the enclave memory; be patient.

```bash
make
./app
```

Write a program to compute the sum outside enclave

1. Task 1.1  is about running your `call_sum(int * list, long size)` outside enclave and measuring the execution time with a large array (e.g. 2 million integers). 
    * Add your implementation in function `task_121(int *list, long size)` in `./lab1/App/App.cpp`: invoke `call_sum()` and add time measurement.
    * Hint: measuring time can consult `gettimenow()` in `App.cpp`.
2. Task 1.2 is about running the sum computation purely inside enclave
    * Add your implementation in function `task_122(int *list, long size)` in `./lab1/App/App.cpp`: 
        1. write `ecall_sum()` to call into enclave; make sure the array `list` is copied into the enclave upon ecall.
        2. [Bonus] design where to add time measurement.
3. Run the program of the two tasks, and measure the execution time of two settings. Explain the performance difference.

#### Homework Lab (3): Performance Benchmarking with Data-Out Code-In Execution        
        
4. Task 1.3 is about computing the sum inside enclave, but *with array outside enclave*.

