Join Blockchain on Campus
---

#### Preparation

1. Linux shell commands
2. Understand [Ethereum](http://www.ethdocs.org/en/latest/introduction/index.html)

#### Lab Environment Setup

There are serveral `Ethereum` [clients](http://ethdocs.org/en/latest/ethereum-clients/choosing-a-client.html) implementations, we will use the `Go` implementaion - `Geth`- for this lab. You can choose to either install the `Geth` on you own machine or the Linux machine running on VirtualBox which you've already had in previous lab. See [here](https://github.com/ethereum/go-ethereum/wiki/Building-Ethereum) for more information.

Here is the instructions to install the `Geth` for Ubuntu.

```
$ sudo apt-get install software-properties-common
$ sudo add-apt-repository -y ppa:ethereum/ethereum
$ sudo apt-get update
$ sudo apt-get install ethereum
```

#### Join the On-Campus Blockchain Network

1. **Run Geth**
 
	Every blockchain starts with the genesis block. When you run geth with default settings for the first time, the main net genesis block is committed to the database. For a private network, you usually want a different genesis block. We have a pre-defined custom `genesis.json` file. The `config` section ensures that certain protocol upgrades are immediately available. The `alloc` section pre-funds accounts, which is currently empty.
	
	Following the instructions below to run geth.
		
	```
	$ mkdir <data-dir>
	$ geth --datadir <data-dir> init genesis.json  # create a database that uses this genesis bloc
	$ geth --datadir <datadir> --networkid 15 --bootnodes enode://274bee3ca81e8f659196259d3138f83b90708422cdc356ce853a67e64be856bc63809516667f7cdf676365a0ed4fc2599ceb3d068a82058f586b02ca969f76fc@128.230.208.73:30301 console
	```
	See the last command above: `--networkid` specify the private network ID.

	> Connections between nodes are valid only if peers have identical protocol version and network ID, you can effectively isolate your network by setting either of these to a non default value.
	
	`--bootnode` option specify the bootnode address, following the format `[nodeID]:IP:port`
	
	> Every subsequent Geth node pointed to the bootnode for peer discovery
	
	[This page](https://github.com/ethereum/go-ethereum/wiki/Command-Line-Options) describes the options for ```geth``` command.
	

2. **Add Peer(run in Geth console)**
	
	Add a peer node running on the remote machine by specify the node URL.
	
	```
	> admin.addPeer("enode://175fd73f7035504783b477e6d2747f73dbc81e652849ddaae832e924ef612fb61dce2de1c21b008c25c849d82470ea6c93b6be1293a8334cd6835ce1a1969da4@128.230.208.73:30304")
	```	
	Check the connectivity by running:
	
	```
	> admin.peers
	```
	
3. **Start Mining**
	
	Before mining, the coinbase has to be specified to one personal account, where your earnings will be settled. Run following commands to create a new account, and set it as coinbase.
	
	```
	> personal.newAccount("1QfERYC4Lu3edt") # create an Account
	> web3.eth.accounts			# check accounts
	> miner.setEtherbase(eth.accounts[0])  # that address that will receive your earnings	
	```
	
	You can now start/stop the miner. 
	
	```
	> miner.start(1)	# one thread
	> miner.stop()
	```
	To know currently you are mining or not, you can run 
	
	```
	> miner.getHashrate()  # if you are mining, the hash rate should be a non-zero positive constant, and will change at different time period.
	```
	
	The following command is used to check the balance you achieve.
	
	```
    > web3.fromWei(web3.eth.getBalance(web3.eth.accounts[0]), "ether")
	```
	
	[This page](https://github.com/ethereum/go-ethereum/wiki/Management-APIs) describes the Ethereum management APIs, check it for more information.
	


