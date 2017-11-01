Module 2: Side-channel Vulnerability and Protection
---

#### Preparation

1. C/C++ programming
2. Linux shell and text editing (e.g. vim or emacs)
3. SGX SDK
4. Sorting Algorithms 
 
#### SGX Emulator (1)

1. Install VirtualBox on your local OS.
2. Download the prebuilt VirtualBox image: [Google Drive](https://goo.gl/8sFN2y). The login username and password are both `sgx`.
    - Note our emulator currently only supports the setting of *64-bit `Ubuntu 14.04.3 LTS` guest OS in VirtualBox*.
    - Make sure the right Linux version by `uname -r`: `3.19.0-25-generic`
3. Load the emulator
```bash
sudo insmod ~/sgx-emulator/sgx.ko
lsmod | grep sgx #help you check whether module insert successfully
```
4. Run sample code
```bash
make #compile user code
make r #run user code
```
5. Unload the emulator
```bash
sudo rmmod sgx
```

#### Download Lab2

After you downloaded the lab2 folder, you need to load the emulator first. The emulator module is in `~/sgx-emulator/`. Under this directory, run _3. Load the emulator_


When loaded successfully, run your code.
```bash
make #compile client code
make r #run client code
dmesg | tail #see kernel output
```

#### In-class Lab (2): Leakage of Sorting Algorithms

This lab requires you to complete three sorting algorithms for an array, execute it inside/outside enclave, and observe the data accessing and index referencing differences. The objective of this lab is to help you understand Side-Channel Vulnerability exposed while sorting.

For your convinience, index print out has been overrided into a Class called `List`. You can use the class as usage of array. For example,

```C++
List list;
list[0] = 3;
list[1] = list[2];


List * lptr;
(*lptr)[0] = 0;
(*lptr)[2] = (*lptr)[1];
```

##### Bubble sort/merge sort with access history of indices

1. Task 1 is about running your bubble sort outside enclave with an array. Be sure there is no bug in your algorithm.     
   * Sample output:
        - If you insert 4 numbers, {10,30,20,50}, and your algorithm should print out the history: 
            `(0) (1) (1) (2) (1) (1) (2) (2) (2) (3) (0) (1) (1) (2) (0) (1)`
        - Operation types for each index are below, you do not need to print out them. They are just here to help you understand this example:[C: comparison, R: read, W: write]
            ` C   C   C   C   R   W   R   W   C   C   C   C   C   C   C   C `

2. Task 2 is about running your merge sort 
    * Finish your merge sort algorithm by completing `merge()` and `divide()`
    * Sample output:
        - If you insert 4 numbers, {10,30,20,50}, and your algorithm should print the history: [C: comparison, R: read, W: write]
           `(0) (1) (2) (3) (0) (2) (1) (2) (2) (1) (1) (2) (1) (3)`
        - Operation types for each index are below, you do not need to print out them. They are just here to help you understand this example:[C: comparison, R: read, W: write]
           ` C   C   C   C   C   C   C   C   R   W   R   W   C   C `

#### Homework Lab (3): Other Sorting algorithms
        
3. Task 3 is about implementing your sorting algorithm other than algorithms in in-class lab, and run it inside and outside enclave. You can choose whatever sorting algorithm you like. Such as quick sort, sorting network and heap sort. Please print out the indices compared each time.

4. Try to run at least two different arrays as input. Try to define the output difference between different inputs.
    - For instance, [18,17,16,15,14,13,12,11] and [18,11,12,17,16,14,13,15]

5. Discuss the Side-channel leakage you found. Explain your found, and think about methods to protect the vulnerability.
