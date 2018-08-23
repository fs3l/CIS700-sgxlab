Tutorial: Chameleon Cloud with SGX SDK 
===

Start a Chameleon instance
---

- Step 1: Register an account on Chameleon website [[link](https://www.chameleoncloud.org/user/register/)]
- Step 2: Ask your instructor and join a Chameleon project
  * Your instructor has already created a project on Chameleon for this lab. Ask your instructor to include you in the project by telling her/him your account name. 
  * Once your instructor has added you to the project, you should be able to find the project in your Dashboard, which is located in the top right corner of the web page. 
- Step 3: Choose the resource site 
  * Now you can start using Chameleon. You can choose from two available resources sites, one at the University of Chicago and one at the Texas Advanced Computing Center. You can find them by clicking the `Hardware` button in the top navigation bar. Once you logged in one of them, you should find a summary of your project's current resource usage.
- Step 4: Reserve a node
  * Click `Reservations` in the sidebar, then click `Leases`
  * Click `+Create Lease` button.
  * Type in Lease Name, Start Date, Start Time, End Date and End Time. Note that Chameleon allows resevation one week long.
  * Find the `Resource Properties` section, in the dropdown menu, select **compute_skylake**.
  * Click the create button.
- Step 5: Launch an instance
  * In the sidebar, click `Compute`, then click `Instances`.
  * Click on the Launch Instance button in the toolbar, and the wizard will load.
  * Type in instance name. For the `Reservation` section, select the reservation name you created in the previous step
  * Click `Source` in the sidebar. Then select `dtn_ubuntu1604` in the image list by clicking the `Up` arrow.
  * Click the `Flavor` in the sidebar, select the `baremetal` flavor.
  * Click `Keypair` in the sidebar. Click the `+Create Key Pair` button and enter `mychameleonkey` for the key name. This will automatically start a download for a file named `mychameleonkey.pem`. This is your private key that you will use to access your instance. 
  * Click the `Launch Instance` button.
- Step 6: Associating an IP address
  * Click on `Compute and Instances` in the sidebar to locate your instance. It is probably in the `Spawning State`.
  * Click the `Associate Floating IP` button. Click the `+` button next to the dropdown that says select an IP address. A new dialog will open for allocating floating IP.
  * Click the `Allocate IP` button. You will return to the previous dialog, and an IP address will be selected for you.
  * Click the `Associate` button and make a note of the public IP addresses that have been associated with your instance.
- Step 7: Access your instance.
  * Open a terminal window and navigate to where you downloaded the mychameleonkey.pem file. 
    ``` 
    chmod 600 mychameleonkey.pem
    ```
  * Add the key to your current SSH identity
    ```
    ssh-add mychameleonkey.pem
    ```
  * Log in to your Chameleon instance using the user account, say "cc" and your floating IP address. 
    ```
    ssh cc@your_floating_ip
    ```

- You can find more details in [[here](https://chameleoncloud.readthedocs.io/en/latest/getting-started/)].


Install the Intel SGX Driver
---

- To build the SGX driver, run the following commands in a bash terminal

  ```
  $ git clone https://github.com/intel/linux-sgx-driver.git
  $ cd linux-sgx-driver
  $ sudo apt-get install linux-headers-$(uname -r)
  $ make
  ```
  You can find the driver *isgx.ko* generated in the same directory.

- To install, run the below commands one by one

  ```
  $ sudo mkdir -p "/lib/modules/"`uname -r`"/kernel/drivers/intel/sgx"    
  $ sudo cp isgx.ko "/lib/modules/"`uname -r`"/kernel/drivers/intel/sgx"
  $ sudo sh -c "cat /etc/modules | grep -Fxq isgx || echo isgx >> /etc/modules"    
  $ sudo /sbin/depmod
  $ sudo /sbin/modprobe isgx
  ```

Install the Intel SGX SDK and PSW 
----

- To build the SGX SDK/PSW, run the following commands in a bash terminal

  ```
  $ git clone https://github.com/intel/linux-sgx.git
  $ cd linux-sgx
  $ sudo apt-get install build-essential ocaml automake autoconf libtool wget python
  $ sudo apt-get install libssl-dev libcurl4-openssl-dev protobuf-compiler libprotobuf-dev
  $ ./download_prebuilt.sh
  $ make  
  $ make sdk_install_pkg
  ```
  **Important:** Type `no` when it asks `Do you want to install in current directory?`, and then type `~` in the next question. Your Intel SDK will be installed in your home directory which is at `~/sgxsdk`. This directory becomes your SGX SDK installation path and will be used repeatedly.
  ```
  $ make psw_install_pkg
  ```
  You can find the generated Intel SGX SDK and PSW installers ``sgx_linux_x64_sdk_${version}.bin`` ``sgx_linux_x64_sdk_${version}.bin`` located under `linux/installer/bin/`, where `${version}` refers to the version number.

- To install SDK, run the following commands

  ```  
  $ sudo apt-get install build-essential python
  $ sudo apt-get install libssl-dev libcurl4-openssl-dev libprotobuf-dev
  $ cd linux/installer/bin
  $ ./sgx_linux_x64_sdk_${version}.bin 
  $ sudo ./sgx_linux_x64_psw_${version}.bin
  ```  

- To test the installation, run the following commands
  ```
  $ source ${sgx-sdk-install-path}/environment  
  ```
  **Important:** Before compiling your code, make sure to run the above command.
  ```
  $ cd SampleCode/LocalAttestation
  $ make SGX_MODE=SIM
  $ ./app
  ```

![success](https://github.com/syracuse-fullstacksecurity/security-education/blob/master/lab4/sucess.png)
