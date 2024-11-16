# ACIT 4630 – Lab 6 – Public Key Infrastructure (PKI)

NOTE: This lab will be done on Kali Linux
The instructions are adapted from [seedsecuritylabs.org](https://seedsecuritylabs.org/Labs_20.04/Files/Crypto_PKI/Crypto_PKI.pdf)

## Instructions: 
Public key cryptography is the foundation of today's secure communication, but it is subject to man-in-the-middle attacks when one side of communication sends its public key to the other side. The fundamental problem is that there is no easy way to verify the ownership of a public key, i.e., given a public key and its claimed owner information, how do we ensure that the public key is indeed owned by the claimed owner? The Public Key Infrastructure (PKI) is a practical solution to this problem. 

The learning objective of this lab is for you to gain first-hand experience on PKI. We will set up an HTTPS web server for our chosen domain (you do not need to own the domain). The domain name should contain your first name/last name and 2024. For example, if I was in your group this could be my domain name: www.iman.info

### Task 1: Becoming a Certificate Authority (CA) 
A Certificate Authority (CA) is a trusted entity that issues digital certificates. The digital certificate certifies the ownership of a public key by the named subject of the certificate. Several commercial CAs are treated as root CAs; DigiCert is the largest CA at the time of writing. Users who want to get digital certificates issued by the commercial CAs need to pay those CAs.

In this lab, we need to create digital certificates, but we are not going to pay any commercial CA. We will become a root CA ourselves, and then use this CA to issue certificates for others (e.g. servers). In this task, we will make ourselves a root CA, and generate a certificate for this CA. Unlike other certificates, which are usually signed by another CA, the root CA’s certificates are self-signed. Root CA’s certificates are usually pre-loaded into most operating systems, web browsers, and other software that rely on PKI. Root CA’s certificates are unconditionally trusted.

The Configuration File `openssl.cnf`. To use OpenSSL to create certificates, you must have a configuration file. The configuration file usually has an extension `.cnf`. It is used by three OpenSSL commands: ca, req and x509. The manual page of `openssl.cnf` can be found from online resources.

By default, OpenSSL uses the configuration file from `/usr/lib/ssl/openssl.cnf`. Since we need to make changes to this file, we will copy it into our current directory, and instruct OpenSSL to use this copy instead. 

1.	**Prepare the Environment:** 
Copy the OpenSSL configuration file (`openssl.cnf`) from its default location (`/usr/lib/ssl/`) to your current working directory. This allows you to modify the file without affecting the system-wide OpenSSL configuration. 
2.	**Edit the Configuration File:** 
In the openssl.cnf file, find the `[ CA_default ]` section and uncomment the `unique_subject` line and set it to no, allowing multiple certificates with the same subject. 
3.	**Create Necessary Directories and Files:** 
    - Create a directory structure as specified by the dir variable in your openssl.cnf file. We need to first create the `demoCA` directory. Navigate to that folder. Then, create the following folders: `certs`, `crl`, `newcerts`
    - Create an empty file named `index.txt`
    - Create a file named serial and put a single number (e.g., `1000`) in it. This number is used as the starting serial number for issued certificates. 
4.	Generate the CA Certificate: 
    - Go back to the working directory (where the `openssl.cnf`) is.
    - Run the following command to generate a new RSA private key and a self-signed certificate for your CA: 
        ```sh
        openssl req -x509 -newkey rsa:4096 -sha256 -days 3650 -keyout ca.key -out ca.crt -subj "/CN=www.modelCA.com/O=Model CA LTD./C=CA" -passout pass:dees
        ```
This command creates `ca.key` (**private key**) and `ca.crt` (**self-signed certificate**). The `-subj` option provides subject information for the certificate directly in the command line, avoiding interactive prompts.

Note: `www.modelCA.com` is the CA’s domain, don't confuse this with your webserver domain. 

5.	Verify the CA Certificate:
    - Use `openssl x509 -in ca.crt -text -noout` to display the X509 certificate's content.
    - Use `openssl rsa -in ca.key -text -noout` to display the private key's content.

(Q1) What part of the certificate indicates this is a CA’s certificate?
(Q2) What part of the certificate indicates this is a self-signed certificate? 


### Task 2: Generating a Certificate Request for Your Web Server 
A company called iman.com (replace this with the name of your own web server) wants to get a public key certificate from our CA. First it needs to generate a Certificate Signing Request (CSR), which basically includes the company’s public key and identity information. The CSR will be sent to the CA, who will verify the identity information in the request, and then generate a certificate. The command to generate a CSR is quite like the one we used in creating the self- signed certificate for the CA. The only difference is the -x509 option. Without it, the command generates a request; with it, the command generates a self-signed certificate. 

To allow a certificate to have multiple names, the X.509 specification defines extensions to be attached to a certificate. This extension is called Subject Alternative Name (SAN). Using the SAN extension, it’s possible to specify several hostnames in the `subjectAltName` field of a certificate. We will use this option to add two alternative names to our certificate signing request. They will be needed in the tasks later. 

1.	**Generate the Server Key and CSR:**
Run the following command to generate a new RSA private key and a CSR for your server: 
```sh
openssl req -newkey rsa:2048 -sha256 -keyout server.key -out server.csr -subj "/CN=www.iman.info/O=Your Organization/C=CA" -passout pass:dees -addext "subjectAltName = DNS:www.iman.info, DNS: www.iman.ca, DNS:www.iman.io" 
```
Note: Replace the domain (iman.info) and Your Organization with your actual server’s name and organization. Also, replace the alternative domains (iman.ca and iman.io) with your alternative domains. 

2.	Verify the CSR:
    - Use `openssl req -in server.csr -text -noout` to review the details of the CSR.
    - Use `openssl rsa -in server.key -text -noout` to verify the private key. 

(Q3) What is your web server name? What other alternative names did you add to your certificate signing request?

(Q4) List the steps for a web server to get a public-key certificate from a CA? 

(Q5) If this were a real-world scenario, how would you submit the CSR to a Certificate Authority (CA)?


### Task 3: Generating a Certificate for your server 
The CSR file needs to have the CA’s signature to form a certificate. In the real world, the CSR files are usually sent to a trusted CA for their signature. In this task, we will use our own trusted CA to generate certificates. 

1.	Adjust Configuration to Copy Extensions: 
For security, OpenSSL's default configuration does not copy extensions (e.g. SANs) from the CSR to the certificate. To enable that, we can go to our copy of the configuration file, uncomment the following line: 
Find and uncomment the `copy_extensions` line in your CA's OpenSSL configuration file (`openssl.cnf`), setting it to copy. 
2.	Sign the CSR to Generate the Server Certificate:
The following command turns the certificate signing request (`server.csr`) from task 2 into an X509 certificate (`server.crt`), using the CA’s `ca.crt` and `ca.key`: 
```sh
openssl ca -config openssl.cnf -policy policy_anything -md sha256 -days 3650 -in server.csr -out server.crt -batch -cert ca.crt -keyfile ca.key
```
3.	Verify the Server Certificate:
Use the following command to print out the X509 certificate issued for our webserver: `openssl x509 -in server.crt -text -noout` 

(Q6) Who is the issuer of this certificate? What part of the certificate indicates this? 
(Q7) Can the certificate generated in this step be used to sign other certificates. What part of the certificate indicates this? 
(Q8) How long is this certificate valid for? Where in the OpenSSL command did we indicate this? 

### Task 4: Deploying Certificate in an Apache-Based HTTPS Website 
In this task, we will explore how public-key certificates are utilized by websites to secure web browsing. We will set up an HTTPS website using Nginx, which is installed directly on Kali Linux. To create an HTTPS website, we need to configure Nginx to specify the locations of the private key and certificate.
Nginx Setup and Commands:
- Copy your web server's key and certificate (generated in Task 3 and 4) to the appropriate folder:
    - Place server.crt and `server.key` in `/etc/nginx/ssl/`
- Edit the default configuration file in `/etc/nginx/sites-available/default` to include your web server domains and alternate names (as `server_name`):
```nginx
server {
    # SSL configuration
    listen 443 ssl default_server;
    listen [::]:443 ssl default_server;
    ssl_certificate /etc/nginx/ssl/server.crt;
    ssl_certificate_key /etc/nginx/ssl/server.key;
    root /var/www/html;
    index index.html index.htm index.nginx-debian.html;
    server_name iman.info www.iman.info;
    location / {
        try_files $uri $uri/ =404;
    }
}
server {
    listen 80;
    listen [::]:80;
    server_name iman.info www.iman.info;
    return 301 https://$host$request_uri;
}
```
NOTE: When configuring an HTTPS server, such as Nginx, it is common to encounter a situation where the private key (e.g., `server.key`) is protected with a password. While this enhances security, it can also complicate the server's ability to start automatically, as it will require manual entry of the password each time the server is restarted. For ease of management, especially in a production environment, it may be desirable to remove the password from the private key.

#### Reasons for Removing the Password
1.	Automated Server Restarts: Removing the password allows the server to start automatically without requiring manual intervention to enter the password.
2.	Simplicity: It simplifies the deployment process and management of the server, especially in environments where uptime is critical.
3.	Less Overhead: For automated deployments or in a containerized environment, not having to deal with password prompts reduces complexity.

#### How to Remove the Password from the Private Key
To remove the password from the private key, you can use the OpenSSL command-line tool. Follow these steps:
1.	Make a Backup: Before modifying the private key, it’s essential to create a backup copy for safety:
    ```sh
    sudo cp /etc/nginx/ssl/server.key /etc/nginx/ssl/server.key.bak
    ```
2.	Remove the Password: Use the following OpenSSL command to create a new private key without a password (this will overwrite the previous key):
    ```sh
    sudo openssl rsa -in /etc/nginx/ssl/server.key -out /etc/nginx/ssl/server.key
    ```
-   Now, modify your `/etc/hosts` file on Kali Linux to redirect any visits to your chosen domains to the local Nginx web server:
    ```txt
    127.0.0.1 iman.info
    127.0.0.1 www.iman.info
    ```
- Test the Nginx configuration for syntax errors:
    ```sh
    sudo nginx -t
    ```
- If the configuration test passes, start or restart Nginx to apply changes:
    ```sh
    sudo systemctl restart nginx
    ```

#### Testing the Setup:
After setting up Nginx and updating the `/etc/hosts` file, try navigating to both the HTTP and HTTPS versions of your website in a web browser on the Kali Linux VM.
- (Q9) You should see a warning if you navigate to your HTTPS website. Click on Advanced and explain what you see and why.
- (Q10) Explain how you can fix this error and provide a screenshot showing that you can successfully browse the HTTPS website without warnings (for both the main domain and the alternative domains).
    - Hint: You need to load a certificate into your browser. To manually add a certificate to the Firefox browser, type `about:preferences#privacy` in the address bar, click the View Certificates button (scroll to the bottom), and import your own certificates. Select the option: **“Trust this CA to identify websites.”**
- (Q11) On the server, confirm that all incoming traffic is redirected to the HTTPS version. You can use the curl command to verify the redirection.

### Task 5: Launching a Man-In-The-Middle Attack

???? Need some refining


In this task, we will demonstrate how PKI can prevent Man-In-The-Middle (MITM) attacks. Assume Alice wants to visit iman.com via HTTPS. She needs to get the public key from the iman.com server. If an attacker intercepts the communication and replaces the server’s public key with its own, Alice’s secret becomes compromised.

![MIMT Attack](images/lab6-fig1.png)

In this task, we will emulate an MITM attack and observe how PKI can counteract it. We will select a target website first. In this document, we will use www.iman.info as the target.
In Task 4, we have already set up an HTTPS website. To impersonate www.iman.info, follow these steps:

- (Q12) Explain what warning you will see when navigating to https://www.iman.com/ on the VM.


### Submission For Lab 6:
- Create a report answering any questions in the lab above including required screenshots.
- Submit your report to the Learning Hub in PDF format. 
