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
    [format]
        signoff = true

    [core]
        editor = vim

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
    echo 'GRUB_CMDLINE_LINUX="earlyprink=vga"' | sudo tee -a /etc/default/grub && sudo grub-mkconfig -o /boot/grub/grub.cfg
    ```  
    - In case you're using the broadcom-wl driver or it's dkms equivalent you need to follow the instructions at the bottom of this document in order to get your WiFi adapter up and working after the reboot  
    - reboot  
    - check with the command above if dmesg shows additional errors  

8. Writing a Kernel Patch  
   - check out the [patch submission guide on the kernel docs](https://www.kernel.org/doc/html/latest/process/submitting-patches.html)  
   - Kernel Configuration: Drivers and other features may be either disabled, compiled as module or into the vmlinuz image to be loaded at boot time. The more features are added, the larger the kernel image, the longer the boot time. Modules are loaded when the kernel detects hardware that matches the driver or by using modprobe.  
   - `make listconfig`, `make menuconfig` and others may be used for configuration of the kernel (the former uses an old config while the latter starts a complete new configuration). Use `make help` or [the kernel docs on configuration](https://www.kernel.org/doc/html/latest/kbuild/index.html) for more information.  
   - create a new branch `git checkout -b somenewpatch`  
  - Add a remote `git remote add linux git://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git` and fetch from it `git fetch linux`  



### Broadcom-wl patch for kernel version 5.6.0
```
cd /usr/src/broadcom-wl-6.30.223.271 
echo "
diff -Naur src/shared/linux_osl.c src_patch/shared/linux_osl.c
--- a/src/shared/linux_osl.c	2020-03-31 22:28:46.355112835 +0200
+++ b/src/shared/linux_osl.c	2020-03-31 23:10:09.887370484 +0200
@@ -942,7 +942,7 @@
 void *
 osl_reg_map(uint32 pa, uint size)
 {
-	return (ioremap_nocache((unsigned long)pa, (unsigned long)size));
+	return (ioremap((unsigned long)pa, (unsigned long)size));
 }
 
 void
diff -Naur src/wl/sys/wl_linux.c src_patch/wl/sys/wl_linux.c
--- a/src/wl/sys/wl_linux.c	2019-05-08 12:04:33.000000000 +0200
+++ b/src_patch/wl/sys/wl_linux.c	2020-03-31 23:15:32.420900390 +0200
@@ -582,7 +582,7 @@
 	}
 	wl->bcm_bustype = bustype;
 
-	if ((wl->regsva = ioremap_nocache(dev->base_addr, PCI_BAR0_WINSZ)) == NULL) {
+	if ((wl->regsva = ioremap(dev->base_addr, PCI_BAR0_WINSZ)) == NULL) {
 		WL_ERROR(("wl%d: ioremap() failed\n", unit));
 		goto fail;
 	}
@@ -772,7 +772,7 @@
 	if ((val & 0x0000ff00) != 0)
 		pci_write_config_dword(pdev, 0x40, val & 0xffff00ff);
 		bar1_size = pci_resource_len(pdev, 2);
-		bar1_addr = (uchar *)ioremap_nocache(pci_resource_start(pdev, 2),
+		bar1_addr = (uchar *)ioremap(pci_resource_start(pdev, 2),
 			bar1_size);
 	wl = wl_attach(pdev->vendor, pdev->device, pci_resource_start(pdev, 0), PCI_BUS, pdev,
 		pdev->irq, bar1_addr, bar1_size);
@@ -3335,10 +3335,9 @@
 }
 
 #if LINUX_VERSION_CODE >= KERNEL_VERSION(3, 10, 0)
-static const struct file_operations wl_fops = {
-	.owner	= THIS_MODULE,
-	.read	= wl_proc_read,
-	.write	= wl_proc_write,
+static const struct proc_ops wl_proc_ops = {
+	.proc_read	= wl_proc_read,
+	.proc_write	= wl_proc_write,
 };
 #endif
 
@@ -3351,7 +3350,7 @@
 	if ((wl->proc_entry = create_proc_entry(tmp, 0644, NULL)) == NULL) {
 		WL_ERROR(("%s: create_proc_entry %s failed\n", __FUNCTION__, tmp));
 #else
-	if ((wl->proc_entry = proc_create_data(tmp, 0644, NULL, &wl_fops, wl)) == NULL) {
+	if ((wl->proc_entry = proc_create_data(tmp, 0644, NULL, &wl_proc_ops, wl)) == NULL) {
 		WL_ERROR(("%s: proc_create_data %s failed\n", __FUNCTION__, tmp));
 #endif
 		ASSERT(0);
        " | sudo tee patches/010-linux560.patch  
        echo '
PACKAGE_NAME="broadcom-wl"
PACKAGE_VERSION="6.30.223.271"
BUILT_MODULE_NAME[0]="wl"
DEST_MODULE_LOCATION[0]="/kernel/drivers/net/wireless"
PATCH[0]="001-null-pointer-fix.patch"
PATCH[1]="002-rdtscl.patch"
PATCH[2]="003-linux47.patch"
PATCH[3]="004-linux48.patch"
PATCH[4]="005-debian-fix-kernel-warnings.patch"
PATCH[5]="006-linux411.patch"
PATCH[6]="007-linux412.patch"
PATCH[7]="008-linux415.patch"
PATCH[8]="010-linux560.patch"
AUTOINSTALL="yes"' | sudo tee dkms.conf
    sudo dkms install broadcom-wl-6.30.223.271 -k 5.6.0
    ```
