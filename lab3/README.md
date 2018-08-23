Lab 1.2 Software Attestation with Intel SGX
===

Introduction
---

Software attestation is a two-party scheme to convince a client that the server runs a container loaded with the software image provided by the client and hosted in a trusted processor. Software attestation is a fundamental service in establishing a trusted execution environment (TEE) in a distributed system. In essence, the software attestation produces a verifiable proof about the binding between software image I and trusted processor C. Internally, the proof is produced by the trusted processor signing the measurement of the software image. Externally, the software attestation can be combined with authenticated key exchange to set up shared secrets and establish a secure channel.

The learning objective of this lab is the *use* of SGX software attestation for remote applications. Students doing the lab will be able to write programs that call proper functions for enclave attestation in SGX machines. The lab focuses on the interfaces and functions for calling software attestation services in Intel SGX SDK. The lab treats the internal of software attestation as a black box and hides from students the various internal mechanisms (e.g., quoting enclaves for signing and measurement).

Lab Description
---

The lab focuses on the local-attestation setting where the client and server are co-located on the same machine. 

In the given program (the setup is described next), two enclaves, Enclave 1 and Enclave 2, are running respectively as caller and callee. The two enclaves fist establishes a secure channel through software attestation and then Enclave 1 invokes an application-level function defined in Enclave 2. To be a little bit specific, Enclave 2 defines a function table `func_table` that stores the pointers to various application functions and the Enclave 1 calls a fixed procedure in Enclave 2 that dispatches the call though the function table to the target application function.

This lab includes two main tasks: 1) to implement an argument-encoding scheme when establishing shared secrets and secure channel, 2) to implement new applications functions in the attested enclave.

Environment Setup
---

This lab requires Intel SGX SDK and we provide two options of running SGX; student can choose one of the two for their convenience. The first option is (O1) running SGX SDK in a simulation mode in a virtual-machine (VM). The second option (O2) is running the SGX SDK on a real SGX machine in the Chameleon cloud [[link](https://www.chameleoncloud.org/)].

#### Option 1: VM with SGX SDK simulation

- Install virtualbox on your computer.
- Download the VM image that has SGX SDK pre-installed; [[link](https://drive.google.com/file/d/1f34XLRPsToIHg6Fd6fKqbENQfMY3EkDm/view?usp=sharing)]
    - The username of VM is `sgx`, and password is `sgx`

#### Option 2: Chameleon cloud instance with SGX CPU and SDK

- Follow the tutorial page [[link](chameleon-tutorial.md)] to 1) allocate an SGX instance in Chameleon cloud, and to 2) install SGX SDK there.

#### Set up the lab

After a SGX SDK is installed and running, you should set up the lab and run the given program on the machine.

```
git clone https://github.com/syracuse-fullstacksecurity/CIS700-sgxlab.git
cd CIS700-sgxlab/lab3
make SGX_MODE=SIM
./app #this command may take a while to set up the enclave memory; be patient.
```

Task 1: Secure Channel Setup
---

**Exercise 1**: When establishing a secure channel, sharing the secrets is an important primitive (recall DH is a key-distribution protocol in TLS for setting up a secure channel). This exercise requires implementing a new secret-encoding scheme when the two Enclaves establish a secure channel after the software attestation.

To do the exercise, you may want to modify the function `get_message_exchange_response()` in  `./Enclave2/Enclave2.cpp`. The task requires computing the XOR of the input secret with a fixed "key",`0x10010011`.

The exercise will be evaluated by running the program and checking the correctness of the result.

Task 2: Remote Function Calls
---

In the setting of TEE, the purpose of software attestation is for one enclave to call functions defined in the other enclave. In this task you will explore the  post-attestation function calls between enclaves.

**Exercise 2**: Write a sum-of-two-integer function that is called between enclaves. Given two integers provided by enclave 1, the function defined in enclave 2 will calculate the sum of the integers and return the result.

Hint 1: In this exercise, you can complete the function `e2_task()` in `Enclave2.cpp`. You could consult the implementation of function `e2_sample(uint32_t var1, uint32_t var2)` which compares two integers.

Hint 2: Modify the function table to register the new `sum` function; see the top of file `Enclave2.cpp`.

**Exercise 3**: Write a program to integrate the argument marshaling/unmarshaling (in exercise 1) in the setting of post-attestation remote function calls. 

Hint 1: Complete the function `e2_task_wrapper()` in `./Enclave2/Enclave2.cpp` by consulting the implemented function
`e2_sample_wrapper()`.

