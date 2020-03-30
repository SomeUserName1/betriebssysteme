# Course Infos
The course is hosted by the Linux Foundation, addressing beginner's in kernel development.  
It's free and shall provide an introduction to the kernel development procedure including.  

Covered Topics:  
1. Setup your development system  
2. Overview of Linux Kernel repos and releases  
3. Git basics  
4. Building and installing the Kernel  
5. Writing patches  
6. Do's and Don'ts of contribution  
7. Building, loading and dependencies for drivers

Requirements:  
- C  
- Shell scripting  

[Course Page on linuxfoundation.org](https://training.linuxfoundation.org/training/a-beginners-guide-to-linux-kernel-development-lfd103/)  


## Summary by Keywords, Resources and Commands  
1. Section: Course introduction  
    Can be skipped entirely, no neccessary information here.  
2. Section: Linux Kernel Development Process (Organisatorial Stuff)  
    Release cycle, merge window, release candidates, quiet period, kernel trees, mainline, stable, linux-next, mailing lists, maintainer, developer, god of the Kernel aka Linus Torvalds  
    [Kernel Documentation on the Kernel dev process](https://www.kernel.org/doc/html/latest/process/development-process.html)  
3. Patches  
    Patch, git, tags, E-Mail subject conventions, patch version history, diff  
    [Git Book](https://git-scm.com/book/en/v2) (also available in the literature folder of this repo)   
    ```
    git format-patch -1 --pretty=fuller <commit_hash>
    ```  
4. Working with the Kernel Community  
    [code of conduct](https://www.kernel.org/doc/html/latest/process/code-of-conduct.html), [enforcement statement](https://www.kernel.org/doc/html/latest/process/kernel-enforcement-statement.html)  
5. Development System Configuration  
    1. Install a Linux Distro  
    2. Install dependencies (see command below)  
    Pacman:  
    ```
    sudo pacman -Sy base-devel vim git cscope ncurses openssl bison flex binutils gcc make util-linux kmod e2fsprogs jfsutils reiserfsprogs xfsprogs squashfs-tools btrfs-progs quota-tools ppp nfs-utils oprofile grub iptables bc python-sphinx git perl-authen-sasl perl-net-smtp-ssl perl-mime-tools
      ```  
    apt:  
    ```
    sudo apt-get install build-essential vim git cscope libncurses-dev libssl-dev bison flex git-email
    ```

    3. Setup git send-email  
    Git send-email setup:
    ```
    git config --global user.email "<your e-mail address>"
    git config --global user.name "<Your Name>"
    git config --global --edit
    ```  
    Insert your e-mail providers SMTP configuration in the following:  
    ```
    [sendemail]
	smtpserver = <smtp.example.com>
	smtpuser = <username>
    smtppassword=<password>
	smtpencryption = tls
	smtpserverport = 587
    ```
    Setup ssh keys (optional):  
    ```
    ssh-keygen -t rsa -b 4096 -C "<email'adress>"
    eval "$(ssh-agent -s)"
    ssh-add ~/.ssh/id_rsa
    ```  

    4. Configure your e-mail client (e.g. thunderbird)  
    Rules:
        - Post your answer __below__ the quoted previous emails  
        - Strip quoted emails to the parts you want to adress
        - No HTML, no signatures, no attachments (only in exceptional cases)   

6. Intro to exploring the Linux Kernel sources  
    - Clone the mainline sources from [here](git://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git) using 
    ```
    git clone git://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git
    ```    
    - Visually inspect the source structure [here](https://cregit.linuxsources.org/)  
    - Check the top level Makefile, the ;MAINTAINERS file, script/get_maintainer.pl and scripts/checkpatch.pl  
    - play with cregit and git log, generate patches using `git format-patch -1 <commit_hash>`  
    - clone the linux-kselftest repository using `git clone git://git.kernel.org/pub/scm/linux/kernel/git/shuah/linux-kselftest.git" and checkout the branch next "cd linux-kselftest && git checkout next`

7. Building and Installing the Kernel  
    - clone the stable kernel repository `git clone git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux-stable.git`
    - checkout the latest stable version (5.6 as of 30th March 2020) `git checkout linux-5.6.y`  
    - copy and gunzip the config of the current kernel for the sake of simplicity `cp /proc/config.gz . && gunzip config.gz && mv config .config`  
    - configure the new features using `make oldconfig` (or `make localmodconfig`)  
    - compile using `make -j4 all`  
    - install the kernel `su -c "make modules_install install"`
    - Safe the current dmesg logs to files to check if new errors occur when booting the new kernel    
    ```
    dmesg -t > dmesg_current
    dmesg -t -k > dmesg_kernel
    dmesg -t -l emerg > dmesg_current_emerg
    dmesg -t -l alert > dmesg_current_alert
    dmesg -t -l crit > dmesg_current_alert
    dmesg -t -l err > dmesg_current_err
    dmesg -t -l warn > dmesg_current_warn
    ```  
    - edit /etc/default/grub to print early boot messages to vga  
    ```
    echo 'GRUB_CMDLINE_LINUX="earlyprink=vga"' | sudo tee -a /etc/default/grub && sudo update-grub
    ```  

