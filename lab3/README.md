Module 3: Blockchain Mining on Local Network
===

In this lab, you are given the initial state that a custom Blockchain network of several miners is hosted on an on-campus machine which has been running for several days before the class. The Blockchain machine also runs a daemon that perdically instructs some miner to conduct transactions with other miners.

Pre-requiresite
---

1. Linux shell commands
2. Understand [Ethereum](http://www.ethdocs.org/en/latest/introduction/index.html)

Lab Environment Setup
---

### 1. Download Ethereum clients

There are serveral `Ethereum` [clients](http://ethdocs.org/en/latest/ethereum-clients/choosing-a-client.html) implementations, we will use the `Go` implementaion, that is, `Geth`, for this lab. You can choose to either install the `Geth` on you own machine or the Linux machine running on VirtualBox which you've already had in previous lab. See [here](https://github.com/ethereum/go-ethereum/wiki/Building-Ethereum) for more information.

***Ubuntu Users***
Here is the instructions to install the `Geth` for Ubuntu.

```
$ sudo apt-get install software-properties-common
$ sudo add-apt-repository -y ppa:ethereum/ethereum
$ sudo apt-get update
$ sudo apt-get install ethereum
```
***Mac Users***

```
brew tap ethereum/ethereum
brew install ethereum
```

***Windows Users***

https://github.com/ethereum/go-ethereum/wiki/Installation-instructions-for-Windows


### 2. Join the Blockchain network

**2.1 Connect to the Blockchain Gateway (Bootnode)**: Every blockchain starts with the genesis block. When you run geth with default settings for the first time, the main net genesis block is committed to the database. For our local network, you usually want a different genesis block. We have a pre-defined custom `genesis.json` file. The `config` section ensures that certain protocol upgrades are immediately available. The `alloc` section pre-funds accounts, which is currently empty. Following the instructions below to run geth.

```
$ mkdir <data-dir>
$ geth --datadir <data-dir> init genesis.json  # create a database that uses this genesis bloc
$ geth --datadir <datadir> --networkid 7002017 --bootnodes enode://00a9f01578deb7088ae17d36c081051033e779cb42734db6c5edb683a56e81eb1540af856f40bffdde6e81457d77c9b37951f18a350a80a77ac30e386d2c44dc@128.230.208.73:30301 console 2>console.log
```

In the last command above, `--networkid` specify the local network ID. Connections between nodes are valid only if peers have identical protocol version and network ID, you can effectively isolate your network by setting either of these to a non default value. `--bootnode` option specify the bootnode address, following the format `[nodeID]:IP:port`. Every subsequent Geth node pointed to the bootnode for peer discovery. [This page](https://github.com/ethereum/go-ethereum/wiki/Command-Line-Options) describes the options for ```geth``` commands.

**2.2 Add a Peer Miner**: Add a peer node running on the remote machine by specify the node URL.
	
```
>admin.addPeer("enode://bcc93b5a33ac287611d1a68bfa2967771ccb6a500b3a7235f02cb19fb7826c5e6562a1fa5b8e9063ea38772e6b0b3f35424baed36662791c0fb315b6f4fd9b41@128.230.208.73:30304")
```	

Check the connectivity by running:
	
```
> admin.peers
```

### 3. Start Mining
	
Before mining, the coinbase has to be specified to one personal account, where your earnings will be settled. Run following commands to create a new account, and set it as coinbase.

```
> personal.newAccount() # create an Account
> eth.accounts # check accounts
> miner.setEtherbase(eth.accounts[0]) # that address that will receive your earnings	
```
	
You can now start/stop the miner. 
	
```
> miner.start(1)	# one thread
> miner.stop()
```

To know currently you are mining or not, you can run 
	
```
> miner.getHashrate()  # if you are mining, the hash rate should be a non-zero positive constant, and will change at different time 
```
	
The following command is used to check the balance you achieve.
	
```
> web3.fromWei(web3.eth.getBalance(web3.eth.accounts[0]), "ether")
```
	
The list of `Geth` commands can be found on [[this page](https://github.com/ethereum/go-ethereum/wiki/Management-APIs)].
	

Lab Tasks
---

The tasks in this lab will require you to inspect and modify the content of Blockchain. In addition to the Ethereum commands you used  above, there are some other relevant commands as below.

```
> eth.blockNumber # check the toppest block number on the chain
> eth.getBlock(eth.blockNumber)   # display the certain block 
> eth.getBlock('latest', true)	# display the latest block
> eth.getBlock('pending', true)	# display the pending block
> eth.sendTransaction({from:"0x0c54f3f7d820bf52344772fa8ed097d1189cd93f", to:"0xda1b60c80502fea9977bab42dcebad05c289dcd2", value:web3.toWei(1,"ether")})
#eth.sendTransaction({from:senderAccount, to:receiverAccount, value: amount})
> eth.getTransaction("0x57dfe8f7f4760f09cd76a8b09000fd43275d798503ed88ed6d8b39c1d5ce3157")
```

**Task 1:** After you started mining, show the coins that you have mined. Then wait 1 minute, check the balance again.

**Task 2:** Show the content (all the blocks and transactions) on the blockchain. Then wait 1 minute, show the blockchain again to see how it is extended over time.

**Task 3:** 

1. Submit a transaction, say `tx5`, to the blockchain. You create another account as the recipent (sellor) of the transaciton.

2. Show whether transaction `tx5` is included in the Blockchain; if not wait for a while, check again.

Note 1: The above command will return a hash tag which served as the ID of the transaction, you could use that ID to query the transaction in the future.

Note 2: [Ether](http://www.ethdocs.org/en/latest/ether.html) is the name of the currency used within Ethereuem. Wei is the smallest unit in Ethereum. 1 Ether = 10^18 Wei. The account balance and transfer amount are shown in Wei. You can use the converter utility web3.fromWei and web3.toWei to convert between Ether and Wei. 

Note 3: Before sending transactions, you may need to unlock your personnal wallet/account and input passphrase. Example:

```
personal.unlockAccount(eth.accounts[0])
```




