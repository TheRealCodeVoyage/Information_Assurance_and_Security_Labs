# ACIT 4630 – Lab 1 – Setup Kali Linux and Metasplotable 2

### Note: 
You may optionally work with a partner for the labs in this course. Make sure you submit your own-written report of your lab, since the lab submission is individual.


Note For Apple Machines with M series:
- Instead of Virtual Machine you must use of of below options:
    - Download the UTM App
        - [UTM, Virtual machines for Mac](https://getutm.app/)
    - Download VMware Fusion Pro
        - [Link](https://blogs.vmware.com/teamfusion/2024/05/fusion-pro-now-available-free-for-personal-use.html)

### Instructions
**Kali Linux** is an advanced penetration testing Linux distribution that comes with lots of security tools preinstalled. Download a VM image for Kali Linux and set up a VM machine for it https://www.kali.org/get-kali/#kali-virtual-machines
- Make sure the VM's network is a NAT network
- Login to the VM. username: kali password: kali
- Explore different tools on Kali Linux.
- (Q1) How can you find this machine's IP?
- Change your Kali machine's hostname to a name unique to you:

```sh
hostnamectl hostname for-example-iman-a
```
Also you should replace the exact same name which you just chose as your hostname in `/etc/hosts/ file with `kali`

```sh
sudo nano /etc/hosts
```

```plaintext
127.0.0.1       localhost
127.0.1.1       for-example-iman-a
```

- Find Metasploit (https://www.offensive- security.com/metasploitunleashed/introduction/) and run it from the Applications menu. You should see msfconsole open. Almost all of your interaction with Metasploit will be through its many modules, which we explore more next week.

**Metasploitable 2**, is an intentionally vulnerable Ubuntu (64-bit) Linux virtual machine that is designed for testing common vulnerabilities.
- Download a VM image for metasploitable 2 and set up a VM machine for it
- https://sourceforge.net/projects/metasploitable/

Note for MacOS with M series Chip:
1. Download and Install the HomeBrew
2. InstallQEMU

    ```sh
    brew install qemu
    ```
3.	Convert the .vdmk file to .QCOW2 (QEMU Image)

    ```sh
    qemu-img convert -f vmdk -O qcow2 vmName.vmdk vmName.qcow2
    ```
4.	Load the .QCOW2 file to UTM App

Note for Windows 11 Users using VirtualBox:
-	You might face a Kernel Panic with Metasploitable 2; here are steps for workaround:
    -	Turn of the MetaSploitable 2 VM machine
    -	Run below commands in the PowerShell:

        ```powershell
        vboxmanage modifyvm <uuid|vmname> --acpi off
        vboxmanage modifyvm <uuid|vmname> --ioapic off
        ```
-	Make sure the VM's network is the same NAT network as Kali VM's
-	Login to the VM. username: msfadmin, password: msfadmin
-	(Q2) How can you find this machine's IP?
    - Note: If you're getting the same IP as the Kali Linux machine you need to change the network to a NAT network
-	(Q3) Get yourself familiar with nmap command and its different options. How can you find this machine's OS as well as the services and their software versions running on open ports on this machine from your Kali VM?
-	![nmap-cheatsheet.jpg](images/nmap-cheatsheet.jpg)
-	https://nmap.org/book/man.html
-	[Nmap Tutorial to find Network Vulnerabilities (YouTube)](https://youtu.be/4t4kBkMsDbQ?si=EtiqpWknYs2GBDH_)
-	[Introduction to NMAP for Beginners! (YouTube)](https://youtu.be/NYgDzO8iQJ0?si=NcbmoceDVjTYUAM8)
    - Hint: If you cannot see any port open on this machine from the Kali machine double-check the NAT network
- (Q4) What's the use case when we need to use -Pn probing option with nmap?
    - Hint: try nmap google.com
        - The server is live on the internet, and ready for you to probe even though running above command might tell you differently.

### Prep for Lab 2:
Please install the OpenVAS software on you Kali VM before the week 2 class.

```sh
sudo apt update
sudo apt upgrade -y
sudo apt dist-upgrade -y
sudo apt install openvas -y
sudo gvm-setup
```
It will take a while to gather and download all the information.

**Note**: Make sure to take a note of the password generated in the terminal.

If there installation was successfull, run:

```sh
gvm-check-setup
```
#### Unsuccessful Installation? Troubleshooting
If you have encounter such error:

```sh
[>] Starting PostgreSQL service
[-] ERROR: The default PostgreSQL version (16) is not 17 that is required by libgvmd
[-] ERROR: libgvmd needs PostgreSQL 17 to use the port 5432
[-] ERROR: Use pg_upgradecluster to update your PostgreSQL cluster
```

It means you have 2 version of postgreSQL and the older version is using port 5432.

1. To make sure of our assumption you can run the command below and confirm

```sh
pg_lsclusters
```

2. we can simple delete the older version and change the latest version's port to `5432`:

```sh
sudo apt remove --purge postgresql-16
sudo apt autoremove
sudo service postgresql stop
```

3. We just stoped the PostgreSQL service. now we can edit its config:

```sh
sudo nano /etc/postgresql/17/main/postgresql.conf
```

4. In `nano` you can search a word with `CTRL + W`. let's search for the word `port` and change it to `5432`.

5. After we Saved (`CTRL + S`) and Exited (`CTRL + X`), we need to restart the PostgreSQL service:

```sh
sudo systemctl start postgresql
```

6. Now, it's time to re-run the openvas installation command:

```sh
sudo gvm-setup
```

### Submission For Lab 1:
- Demonstrate your running VMs above to your instructor.
- Take screenshots of your running VMs and answers to the questions in the lab. 
- Craft a report including the screenshot and your observations and the answers to the questions. 
- Submit your report to the learning hub.