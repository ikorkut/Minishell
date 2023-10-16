## get_env.c

**func split_env -->** "split_env" fonksiyonu, bir string içinde "=" simgesinin sağındaki değerini kopyalamak için kullanılır. Fonksiyon, bir "=" simgesini bulana kadar string içinde ilerler ve bu simge bulunduğunda sağındaki değeri kopyalar ve yeni bir string olarak döndürür.


**func get_env -->** Bu fonksiyon, verilen "str" değişkeni ile eşleşen bir ortam değişkeninin değerini bulmak için kullanılır. Eğer bir eşleşme bulunursa, bu değer döndürülür. Aksi takdirde, boş bir karakter dizisi döndürülür.

<br />

## get_path.c

**func check_dir -->** Bu fonksiyon `check_dir`, verilen `cmd` argümanının bir dizin olup olmadığını kontrol eder. Eğer bir dizin ise, `directory_err` fonksiyonu çağırılır.


**func mimi_ret_free -->** Bu fonksiyon, iki string verilen "mim" ve "path" parametrelerini birleştirir ve "mim" parametresinin bellekte ayrılmış alanını serbest bırakır. Sonuç olarak, "path" parametresi döndürülür.


**func get_path -->** Bu fonksiyon "cmd" adındaki bir komutun yolunu almaya çalışır. İlk olarak "cmd" yolunun geçerli olup olmadığını kontrol eder. Eğer geçerli ise, "cmd" yolunun kopyasını döndürür. Eğer "cmd" yolu geçerli değilse, g_ms.paths değişkenindeki yolları kullanarak komutun yolunu bulmaya çalışır. Eğer yol bulunamazsa, "cmd" içinde "/" karakteri varsa, no_file_err fonksiyonunu çağırarak "cmd" adındaki dosya veya dizin bulunamadı hatası verir. Eğer g_ms.paths değişkeni de tanımlı değilse, command_err fonksiyonunu çağırarak komut bulunamadı hatası verir.

<br />

## is_heredoc.c

**func contain_heredoc -->** "contain_heredoc" adlı fonksiyon, verilen "t_process" tipindeki bir nesnenin "redirects" alanında HEREDOC operatörünün bulunup bulunmadığını kontrol eder. Eğer bulunuyorsa, "TRUE" değerini döndürür; bulunmuyorsa, "FALSE" döndürür.

<br />

## is_operator.c

**func is_operator -->** "is_operator" fonksiyonu, belirtilen bir dizginin bir işleç olup olmadığını kontrol eder ve işleç türünü (giriş yönlendirmesi, çıkış yönlendirmesi, burada belge veya boru) geri döndürür.

<br />

## is_parent.c

**func is_parent -->** "is_parent" fonksiyonu, g_ms global değişkeninin parent_pid değerinin geçerli işlemin (process) PID değerine eşit olup olmadığını kontrol eder. Eğer eşitse, fonksiyon 1 döndürür, eşit değilse 0 döndürür.

<br />

## is_whitespace.c

**func is_whitespace -->** Bu fonksiyon, verilen bir karakterin boşluk veya sekme olup olmadığını kontrol eder ve eğer boşluk veya sekme ise 1, değilse 0 değerini döndürür.

<br />

## set_env.c

**func set_env -->** "set_env" fonksiyonu, bir ortam değişkeni dizisi olan "env" verilen bir programın ortam değişkenlerini "g_ms.env" isimli global bir değişkene atar. Bu değişken, programın çalışma sırasında kullanılabilecek ortam değişkenlerinin tutulmasını sağlar.

<br />

## set_paths.c

**func set_paths -->** "set_paths" fonksiyonu PATH ortam değişkeninin değerini alır ve bu değerin parçalarını ": " karakteri kullanarak dizi olarak ayırır. Elde edilen dizi "g_ms.paths" değişkenine atanır. Eğer PATH değişkeni boş ise "g_ms.paths" değişkeni NULL olarak atanır.
