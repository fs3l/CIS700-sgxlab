1.SGX Labs
===
<!--

Setup 
---

### Lab Machine

Make sure you can get access to an SGX machine: `ssh 128.230.209.67`.  You can contact Dr. Tang (through his email: ytang100@syr.edu) for the username and password to access the machine.

If you are off campus, you need to use VPN to first get access to the campus LAN before trying to access the machine.

Once you access the SGX machine, `git clone` this repository to get started on the lab.



### Emulator

1. Install VirtualBox on your local OS.
2. Download the prebuilt VirtualBox image: [[Google Drive](https://goo.gl/3wLLic)]. The login username and password are both `sgx`.
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
-->


* Module 1: Understanding SGX Memory Protection [[lab 1](https://github.com/syracuse-fullstacksecurity/CIS700-sgxlab/tree/master/lab1/README.md)]

* Module 2: Side-channel Vulnerability and Protection [[lab 2](https://github.com/syracuse-fullstacksecurity/CIS700-sgxlab/tree/master/lab2/README.md)]

* Module 3: Software Attestation with Intel SGX [[lab 3](https://github.com/syracuse-fullstacksecurity/CIS700-sgxlab/tree/master/lab3/README.md)]

