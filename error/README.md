## error.c

**func command_err -->** Bu fonksiyon, belirtilen komutun bulunamadığı durumlar için bir hata mesajı oluşturmak için kullanılır. Eğer belirtilen komut bulunamazsa, `"minishell: [komut]: command not found"` şeklinde bir hata mesajı yazdırılır ve hata kodu 127 olarak atanır.


**func token_err -->** Bu fonksiyon, belirtilen işlem tipine (redirection, pipe, here document gibi) göre syntax hatası olduğunu belirten bir hata mesajı yazdırır. Hata mesajı, standard hata çıkışına (STDERR, file descriptor #2) yazılır ve sonunda programın sonlandırılmasına neden olabilir.


**func directory_err -->** `directory_err` fonksiyonu, belirtilen dizinin bir dizin olduğunu ve bu nedenle çalıştırılamayacağı durumunda bir hata mesajı yazdırır. Eğer çalışan işlem bir child işlem değilse (parent process), `errno` değişkenini 126 olarak ayarlar ve çıkış yapar.


**func no_file_err -->** Bu fonksiyon, verilen dosya adı için "No such file or directory" hatasını raporlar. Eğer verilen dosya adı '/' içeriyorsa, 'errno' değişkenine 127 değeri atanır, değilse 1 değeri atanır. Daha sonra, hatayı "minishell:" ve dosya adıyla birlikte standard hata akışına (stderr) yazdırır. Eğer fonksiyonun çalıştığı işlem annesi değilse, program errno değerine göre çıkar.
