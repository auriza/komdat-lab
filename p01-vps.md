# Instalasi Web Server Virtual

**Tujuan**: mahasiswa dapat menginstal aplikasi web pada *virtual private
server* (VPS) berbasis Linux.

VPS menyediakan fleksibilitas untuk menginstal aplikasi server apa saja, tidak
terbatas hanya pada aplikasi web berbasis PHP/MySQL. Layanan VPS banyak tersedia
(misal: [Alibaba](https://www.rumahweb.com/vps-alibaba-cloud/), [DigitalOcean](https://www.digitalocean.com/), dan
[AWS](https://aws.amazon.com/ec2)) dengan harga bervariasi sesuai spek server.

Layanan VPS hanya menyediakan server virtual dengan satu alamat IP publik.
Untuk mempermudah pengguna mengakses server kita, perlu tambahan nama domain yang mudah diingat.
Misalnya, untuk berlangganan nama domain `*.my.id`, harganya sekitar [Rp 12.000](https://order2.rumahweb.com/?domain=komdat) per tahun.

## Membuat VM Ubuntu Server

Telah tersedia *virtual disk image* (VDI) instalasi Ubuntu Server 18.04 di
direktori `/opt/vm`.
Salin *file* `ubuntu-server.vdi` tersebut ke direktori *home* anda.
Kemudian, buat VM baru pada VirtualBox dengan tipe "Ubuntu 64-bit".
Gunakan *virtual disk* yang sudah disalin tadi.

*File* VDI di atas dapat diunduh di <http://repo.apps.cs.ipb.ac.id/lab/ubuntu-server.vdi.gz>.

## Setting *port-forwarding* VM

Tujuannya adalah agar VM bisa diakses dari luar melalui alamat IP *host* (*localhost*).
Masuk ke '*Settings -> Network -> Advanced -> Port Forwarding*' dan
tambahkan dua aturan berikut. Dengan demikian, jika kita mengakses *port* 8000 di *host*, maka
akan diteruskan ke *port* 80 di *guest* (VM). Begitu juga dengan SSH,
jika kita mengakses *port* 2200 di *host*, maka akan diteruskan ke *port* 22 di
*guest*.

Setelah semuanya beres, jalankan VM dengan mode *headless* (tanpa tampilan).

: Aturan *port forwarding*

Name   | Protocol   | Host IP    | Host Port  | Guest IP   | Guest Port
----   | --------   | -------    | ---------  | --------   | ----------
http   | TCP        |            | 8000       |            | 80
ssh    | TCP        |            | 2200       |            | 22

![*Port forwarding* pada NAT VirtualBox](etc/1/vbox-nat.png)


## Instalasi LAMP (Linux Apache MySQL PHP)

Buka terminal di komputer *host*, dan akses VM dengan *username* dan *password* `student`.

```bash
# akses vm dari host
ssh student@localhost -p 2200

# set repo
sudo tee /etc/apt/sources.list << !
deb http://repo.apps.cs.ipb.ac.id/ubuntu bionic          main restricted universe multiverse
deb http://repo.apps.cs.ipb.ac.id/ubuntu bionic-updates  main restricted universe multiverse
deb http://repo.apps.cs.ipb.ac.id/ubuntu bionic-security main restricted universe multiverse
!

# instal apache, mysql, php
sudo apt update
sudo apt install apache2 php mysql-server
sudo apt install php-mysql php-gd php-mbstring php-xml php-curl
sudo service apache2 restart
```

Cek instalasi Apache dengan membuka laman <http://localhost:8000>.

## Instalasi aplikasi web Wordpress

```bash
# buat database untuk wordpress
sudo mysql -u root -ve "
  CREATE DATABASE wordpress;
  CREATE USER wordpress IDENTIFIED BY 'secret';
  GRANT ALL PRIVILEGES ON wordpress.* TO wordpress;"

# unduh wordpress terbaru
wget "https://wordpress.org/latest.tar.gz"

# ekstrak ke direktori webroot
sudo tar -xvzf latest.tar.gz -C /var/www/html

# ubah kepemilikan ke user www-data
sudo chown -R www-data:www-data /var/www/html/wordpress
```

Buka laman <http://localhost:8000/wordpress> untuk meneruskan instalasi.
Untuk mematikan server, ketikkan perintah `sudo poweroff`.

![Halaman utama Wordpress](etc/1/wordpress.png)



<!--

## Tugas: Instalasi aplikasi web OwnCloud

Dokumentasikan langkah-langkahnya dengan singkat dan jelas.
Sertakan *screenshot* sebagai pelengkap.
Kumpulkan pada saat akhir praktikum.

Anda boleh mencoba instalasi aplikasi web berbasis PHP lainnya seperti VanillaForums, GNUSocial, SilverStripe, GetSimple, atau Ghost (berbasis Node.js).
Semua berkas instalasi dapat diunduh di <http://cs.ipb.ac.id/~auriza/komdat/webapp/>.

```bash
wget "https://download.owncloud.org/community/owncloud-7.0.4.tar.bz2"
sudo tar -xjf owncloud-7.0.4.tar.bz2 -C /var/www/html/
sudo chown -R www-data:www-data /var/www/html/owncloud
mysql -u root -p -vv -e "
  CREATE DATABASE owncloud;
  CREATE USER owncloud IDENTIFIED BY 'password';
  GRANT ALL PRIVILEGES ON owncloud.* TO owncloud;"
sudo aptitude install php5-gd
sudo service apache2 reload
```

Buka halaman <http://localhost:8888/owncloud> untuk meneruskan instalasi.

### Setting PHP untuk OwnCloud

```bash
sudo editor /etc/php5/apache2/php.ini
  post_max_size = 2G
  upload_max_filesize = 2G
  output_buffering = 0
  date.timezone = Asia/Jakarta
```

![Halaman utama OwnCloud](etc/1/owncloud.png)

- Vanilla Forums
    ```bash
    wget "http://cdn.vanillaforums.com/www.vanillaforums.org/addons/YJLWYW9YJXT7.zip"
    sudo unzip vanilla-core-2-1-3.zip -d /var/www/html/
    sudo chown -R www-data:www-data /var/www/html/vanilla
    mysql -u root -p -vv -e "\
      CREATE USER vanilla IDENTIFIED BY 'passw0rd'; \
      CREATE DATABASE vanilla; \
      GRANT ALL PRIVILEGES ON vanilla.* TO vanilla;"
    w3m "http://localhost/vanilla"
    ```

## Instalasi aplikasi web Node.js (ghost)

    ```bash
    $ sudo apt install nodejs nodejs-legacy npm
    $ wget "https://ghost.org/zip/ghost-0.5.2.zip"
    $ unzip ghost-0.5.2.zip -d ghost
    $ cd ghost
    $ npm install --production
    $ npm start
    ```

## Instalasi Moodle

wget "https://download.moodle.org/download.php/direct/stable34/moodle-latest-34.zip"

mysql -u root -p -v -e "
CREATE DATABASE moodle;
CREATE USER moodle IDENTIFIED BY 'first';
GRANT ALL PRIVILEGES ON moodle.* TO moodle;"

sudo apt install unzip
sudo unzip moodle-latest-34.zip -d /var/www/html

sudo chown -R www-data:www-data /var/www/html/moodle

sudo mkdir /var/www/moodledata
sudo chown -R www-data:www-data /var/www/moodledata

sudo apt install php-curl php-zip php-intl php-xmlrpc php-soap
sudo service apache2 restart

-->
