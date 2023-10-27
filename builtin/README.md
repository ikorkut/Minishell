## builtin.c

**func is_builtin -->** Bu fonksiyon "command" değişkeninde verilen komutun, shell tarafından yerleşik olarak desteklenen bir komut olup olmadığını kontrol eder. Her bir yerleşik komut için bir dönen değer vardır. Örneğin, "cd" komutu için CD değeri, "exit" komutu için EXIT değeri vb. Eğer verilen komut yerleşik bir komut değilse, fonksiyon 0 döner.


**func run_builtin -->** Bu fonksiyon, çalıştırılmak istenen komutun bir iç yapı komutu olup olmadığını belirler ve eğer iç yapı komutu ise, o komutun çalışmasını sağlar. Örneğin, çalıştırılmak istenen komut "cd" ise, "builtin_cd" fonksiyonu çağrılır ve klasör değiştirme işlemi yapılır.

<br />

## cd.c

**func builtin_cd -->** Bu fonksiyon, minishell adlı bir programda CD (Change Directory) komutunun işlemini yapar. İlk olarak, eğer input[1] boş değilse, input[1] deki dizin adına geçmeyi deniyor. Eğer başarısız olursa, perror fonksiyonuyla hatayı ekrana yazdırıyor. Eğer input[1] boş ise, HOME değişkeni içindeki ev dizinine geçmeyi deniyor. Eğer ev dizini bulunamazsa, perror fonksiyonuyla hatayı ekrana yazdırıyor. Son olarak, eğer programın çalıştığı dizin ana dizin değilse (is_parent() fonksiyonu ile kontrol ediliyor), program exit(errno) fonksiyonuyla sonlandırılıyor.

<br />

## echo.c

**func put_char -->** Bu fonksiyon girdi olarak aldığı karakter dizisini çıktı olarak yazdırır. İşlevi, her bir karakteri tek tek yazdırarak, girdi olarak verilen diziyi çıktıya yazmaktır.


**func skip_flag -->** `skip_flag` fonksiyonu, bir argüman dizisinin "-n" içerip içermediğini kontrol eder ve "-n" var ise kaç tane "-n" olduğunu sayar. Eğer "-n" var ise, fonksiyon dizinin "-n"'den sonraki elemanına gösterilen indeksi döndürür.


**func builtin_echo -->** Bu fonksiyon `echo` komutunun işlemesini yapar. `input` parametresi `echo` komutu ile birlikte verilen argümanları içerir. Fonksiyon, argümanları yazdırır ve `-n` flag'inin bulunup bulunmadığına göre yazdırılan metnin sonunda bir satır başı karakteri ekler veya eklemez. `is_parent()` fonksiyonunun çıktısına göre çalışma durumu değerlendirilir ve uygun olduğu durumlarda program `exit` fonksiyonu ile sonlanır.

<br />

## env.c

**func builtin_env -->** Bu fonksiyon sistem ortam değişkenlerini yazdırır. "g_ms.env" global bir dizi olarak tanımlanmış ortam değişkenlerini içerir ve "env" pointerı bu diziyi gösterir. Her bir ortam değişkeni ekrana yazdırılır ve sonra bir sonraki ortam değişkenine geçilir. Fonksiyon sonunda, "is_parent()" fonksiyonu çağrılır ve çıktı eğer parent prosesse aitse "EXIT_SUCCESS" ile çıkılır.

<br />

## export.c

**func env_len -->** `env_len` fonksiyonu `g_ms.env` adlı global bir dizide bulunan ortam değişkenlerinin sayısını hesaplamak için kullanılır. İşlevi, `g_ms.env` dizisindeki eleman sayısını bulmak için bir döngü oluşturmak ve sonunda döngü başı ve sonu arasındaki farkın hesaplanmasıdır. Bu hesaplanan fark, dizinin eleman sayısını verir ve bu, fonksiyonun döndürmek istediği değerdir.


**func check_env -->** `check_env` fonksiyonu, verilen bir string'in ortam değişkeni olarak kullanılabilir olup olmadığını kontrol eder. Ortam değişkeni stringi, bir '=' işareti ile başlamalı ve başında ve sonunda boşluk karakteri bulunmamalıdır. Bu fonksiyon, bir stringin ortam değişkeni olarak geçerli olup olmadığını, `TRUE` veya `FALSE` değerleri ile belirler.


**func add_env -->** Bu fonksiyon, belirtilen dizgi (str) parametresini, çalışma zamanı ortamına ekler. G_ms global değişkeni, programın çalışma zamanı ortamını tutan bir yapıdır ve add_env fonksiyonu bu yapıya belirtilen dizgiyi ekler. Bu fonksiyon, eklenecek dizginin geçerli olup olmadığını kontrol eder ve geçerli ise, g_ms yapısındaki ortam dizisini günceller ve yeni dizgi ekler.


**func is_include -->** `is_include` fonksiyonu, verilen bir stringin (`str`) g_ms.env değişkenindeki bir ortam değişkeni listesinde var olup olmadığını kontrol eder. Eğer değişken listesinde varsa, bu değişkenin listedeki sırasını (index) döndürür. Yoksa -1 döndürür.


**func builtin_export -->** "builtin_export" fonksiyonu, komut satırından "export" komutu verildiğinde çalışan bir iç komuttur. Bu fonksiyon, belirtilen ortam değişkenini kontrol eder ve eğer geçerli bir değişken ise, mevcut değişken listesinde var mı yok mu kontrol eder. Eğer mevcut ise, o değişkenin değeri güncellenir. Değilse, yeni bir değişken olarak eklenir. "set_paths" fonksiyonu sonrasında çalışır ve çalışma dizininde değişiklik yapmak için kullanılabilir.

<br />

## pwd.c

**func builtin_pwd -->** Bu fonksiyon "print working directory (pwd)" adlı minik bir shell uygulamasının parçası olabilir. Bu fonksiyon, kullanıcının mevcut çalışma dizinini (current working directory) ekrana yazdırır ve sonrasında uygulamanın çalışmasını sonlandırır. Eğer fonksiyon çalışması sırasında hata oluşursa, "minishell" hatası ekrana yazdırılır ve errno değişkeni kullanılarak uygulamanın çalışması sonlandırılır.

<br />

## unset.c

**func remove_env -->** `remove_env` fonksiyonu, belirtilen bir değişkenin ortam değişkeni dizisinden kaldırılmasını sağlar. Fonksiyon, belirtilen değişkenin ismini alır ve ortam değişkeni dizisinde bulunan tüm girişleri kontrol eder. Eğer bulunan giriş belirtilen değişkene eşitse, o giriş ortam değişkeni dizisinden silinir ve kalan girişler yeni bir ortam değişkeni dizisi oluşturulur.


**func builtin_unset -->** Bu C dilinde bir fonksiyondur ve "unset" komutunun işlevini yerine getirir. Bu fonksiyon, girdi olarak verilen değişkenleri ortam değişkenlerinden kaldırır ve set_paths() fonksiyonunu çağırarak yolun güncellenmesini sağlar. Eğer fonksiyon çalışan bir ebeveyn işlem değilse, başarıyla çıkış yapar (EXIT_SUCCESS).
