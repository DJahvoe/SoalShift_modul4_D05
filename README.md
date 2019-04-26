# SoalShift_modul4_D05

#SOAL1 <br>
Semua nama file dan folder harus terenkripsi
Enkripsi yang Atta inginkan sangat sederhana, yaitu Caesar cipher . Namun, Kusuma
mengatakan enkripsi tersebut sangat mudah dipecahkan. Dia menyarankan untuk
character list diekspansi,tidak hanya alfabet, dan diacak. Berikut character list yang
dipakai:
qE1~ YMUR2"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\8s;g<{3.u*W-0`

- Problem : Enkripsi nama file dan folder

- Tools : <br/>
  - Fungsi C
  - Caesar Cipher : 'qE1~ YMUR2"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\8s;g<{3.u*W-0'
- Approach : <br/>
Untuk melakukan enkripsi pada file atau folder, perlu dibuat suatu fungsi (dalam hal ini fungsi 'caesar()'). Konsep dalam fungsi tersebut adalah fungsi akan menerima parameter dalam bentuk string dan juga key (yang menjadi patokan ke arah mana character pada string tersebut akan di-shift). saat nilai key diterima, maka apabila character pada string input ditemukan pada 'Caesar Cipher', index nya akan digeser sebanyak 'key', dan character yang sekarang akan diganti dengan character yang baru sesuai dengan index pada 'Caesar Cipher'.

#SOAL2 <br>
rgabung ( joined ) dan diletakkan dalam folder “Videos”
Urutan operasi dari kebutuhan ini adalah:
a. Tepat saat sebelum file system di- mount
i.
Secara otomatis folder “Videos” terbuat di root directory file system
ii.
Misal ada sekumpulan file pecahan video bernama “computer.mkv.000”,
“computer.mkv.001”, “computer.mkv.002”, dst. Maka secara otomatis file
pecahan tersebut akan di- join menjadi file video “computer.mkv”
Untuk mempermudah kalian, dipastikan hanya video file saja yang
terpecah menjadi beberapa file. File pecahan tersebut dijamin terletak di
root folder fuse
iii.
Karena mungkin file video sangat banyak sehingga mungkin saja saat
menggabungkan file video, file system akan membutuhkan waktu yang
lama untuk sukses ter- mount . Maka pastikan saat akan menggabungkan
file pecahan video, file system akan membuat 1 thread/proses(fork)
baru yang dikhususkan untuk menggabungkan file video tersebut
iv.
Pindahkan seluruh file video yang sudah ter- join ke dalam folder “Videos”
v.
Jangan tampilkan file pecahan di direktori manapun
b. Tepat saat file system akan di- unmount
i.
Hapus semua file video yang berada di folder “Videos”, tapi jangan hapus
file pecahan yang terdapat di root directory file system
ii.
Hapus folder “Videos”

#SOAL3 <br>
Sebelum diterapkannya file system ini, Atta pernah diserang oleh hacker
LAPTOP_RUSAK yang menanamkan user bernama “chipset” dan “ic_controller” serta
group “rusak” yang tidak bisa dihapus. Karena paranoid, Atta menerapkan aturan pada
file system ini untuk menghapus “file bahaya” yang memiliki spesifikasi:
- Owner Name : ‘chipset’ atau ‘ic_controller’
- Group Name : ‘rusak’
- Tidak dapat dibaca
Jika ditemukan file dengan spesifikasi tersebut ketika membuka direktori, Atta akan
menyimpan nama file, group ID, owner ID, dan waktu terakhir diakses dalam file
“filemiris.txt” (format waktu bebas, namun harus memiliki jam menit detik dan tanggal)
lalu menghapus “file bahaya” tersebut untuk mencegah serangan lanjutan dari
LAPTOP_RUSAK.

#SOAL4 <br>
Pada folder YOUTUBER, setiap membuat folder permission foldernya akan otomatis
menjadi 750. Juga ketika membuat file permissionnya akan otomatis menjadi 640 dan
ekstensi filenya akan bertambah “ .iz1 ”. File berekstensi “ .iz1 ” tidak bisa diubah
permissionnya dan memunculkan error bertuliskan “ File ekstensi iz1 tidak boleh diubah
permissionnya. ”
5. Ketika mengedit

- Problem : Set otomatis permission di dalam directory "YOUTUBER" sesuai dengan syarat soal
- Tools : <br/>
  - mkdir
  - xmp_getattr
  - xmp_mkdir
  - xmp_create
- Approach : <br/>
Untuk melakukan set otomatis permission, perlu dicek di masing - masing fungsi xmp_mkdir dan xmp_create apakah benar file atau folder dibuat di dalam directory "'YOUTUBER'" atau bukan, dan untuk di dalam xmp_mkdir dibuat menjadi 0750, untuk di dalam xmp_create dibuat menjadi 0640 dengan penambahan ekstensi '.iz1'.

#SOAL5 <br>
Ketika mengedit suatu file dan melakukan save, maka akan terbuat folder baru bernama
Backup kemudian hasil dari save tersebut akan disimpan pada backup dengan nama
namafile_[timestamp].ekstensi. Dan ketika file asli dihapus, maka akan dibuat folder
bernama RecycleBin , kemudian file yang dihapus beserta semua backup dari file yang
dihapus tersebut (jika ada) di zip dengan nama namafile_deleted_[timestamp].zip dan
ditaruh kedalam folder RecycleBin (file asli dan backup terhapus). Dengan format
[timestamp] adalah yyyy-MM-dd_HH:mm:ss
