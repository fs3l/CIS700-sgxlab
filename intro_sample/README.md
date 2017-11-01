real run
---

```
make 
#default opt: SGX_MODE=HW SGX_PRERELEASE=1
# /opt/intel/sgxsdk/bin/x64/sgx_sign sign -key Enclave/Enclave_private.pem -enclave enclave.so -out enclave.signed.so -config Enclave/Enclave.config.xml 

./app
```

misc
---

Purpose of SampleEnclave

The project demonstrates several fundamental usages:

    1. Initializing and destroying an enclave
    2. Creating ECALLs or OCALLs
    3. Calling trusted libraries inside the enclave

