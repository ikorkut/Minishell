## array.c

**func push_array -->** Bu fonksiyon, verilen bir dizi ("arg_arr") ve bir metin dizesi ("str") alır ve bu metin dizesini dizinin sonuna ekleyerek yeni bir dizi oluşturur. Eski dizi önce serbest bırakılır ve yeni dizi döndürür.

<br />

## cleaner.c

**func push_new_str -->** belirtilen bir dizgiyi (str) bir diğer dizgine (new_str) ekleme işlevini yerine getirir. İlk olarak, new_str boşsa, str'nin kopyası olarak ayarlanır. Eğer new_str daha önce tanımlanmışsa, str new_str ile birleştirilir ve sonuç yeniden new_str'nin değerine atanır. Böylece, belirtilen dizgi, bir kez daha kullanılabilir olarak korunur.


**func clean_quote_with_type -->** Bu fonksiyon, belirtilen karakter (type) ile çevrili olan metin dizisindeki metin parçalarını temizler ve temizlenen parçaları yeni bir metin dizisi olarak döndürür. Fonksiyonun girdisi olarak verilen "str" değişkenindeki metin içinde, belirtilen tip karakteri ile çevrili olan metin parçaları bulunur ve bu parçalar "new_str" adında yeni bir metin dizisi olarak oluşturulur. Aynı zamanda, işlenen metnin pozisyonu "pos" değişkeni ile güncellenir.


**func get_str -->** "get_str" isimli fonksiyon, belirtilen pozisyondan başlayarak metindeki en fazla tek tırnaklı veya çift tırnaklı metin bloğunu bulmaya çalışır. Bulduğu bu metin bloğunu döndürür ve "pos" parametresi ile verilen pozisyon değişkenini de günceller.


**func clean_quote -->** Bu fonksiyon, verilen bir dize içindeki çift veya tek tırnak karakterlerini temizlemek için kullanılır. Fonksiyon, metin içindeki tırnak karakterlerini algılar ve tırnakların içindeki metnin dışındaki herhangi bir şeyi temizler. Sonuç olarak, fonksiyon, tırnak karakterleri içindeki metin dışındaki her şeyin atılmasıyla oluşan temiz bir metin dizesi oluşturur.

<br />

## dollar.c

**func valid_op -->** Bu fonksiyon "c" değişkeninin geçerli bir operatör olarak kullanılıp kullanılamayacağını kontrol etmek için kullanılır. Fonksiyon, "c" değişkeninin a-z, A-Z, 0-9, _ veya ? içermesi durumunda 1, aksi durumda 0 döndürür.


**func check_dollar -->** Bu fonksiyon bir verilen string (`str`) içindeki `$` işaretinin doğru kullanılıp kullanılmadığını kontrol eder. Fonksiyon, string içinde gezinerek tek tırnak ve çift tırnak kullanımını takip eder. Eğer `$` işareti ile takip eden karakter geçerli bir operatör değilse veya `$` işareti tek tırnak içindeyse fonksiyon `FALSE` döndürür. Aksi durumda fonksiyon `TRUE` döndürür.


**func get_str -->** Bu fonksiyon, verilen string (`str`) içindeki bir karakter dizisini (`type`) bulur ve bu diziyi sınırlandıran ilk pozisyon (`first`) ile son pozisyon (`*pos`) arasındaki kısmı, `ft_substr` fonksiyonu ile ayıklar. Döndürülen kısım, `data` değişkenine atanır ve `*pos` değişkeni, karakter dizisinin son pozisyonunu belirtir.


**func parse_dollar_op -->** Bu fonksiyon, verilen string (`str`) içindeki `$` işareti ve bu işareti takip eden operatörü (örneğin, `$PATH`) kullanılarak bir ortam değişkenini (environment variable) çözmeyi amaçlar. İlk olarak `get_str` fonksiyonu ile `str` içindeki `$` işareti bulunur ve `result` değişkenine atanır. Eğer `$` işareti takip eden karakter `?` ise, `errno` değişkeninin değeri `ft_itoa` fonksiyonu ile string olarak alınır ve `result` değişkenine eklenir. Aksi durumda, `valid_op` fonksiyonu ile belirlenen geçerli bir operatör bulunur ve bu operatör ile ilişkili ortam değişkeni `get_env` fonksiyonu ile alınır. Son olarak, `get_str` fonksiyonu ile stringin geri kalan kısmı `result` değişkenine eklenir ve `result` değişkeni döndürülür.


**func dollar -->** Bu fonksiyon, verilen string (`str`) içindeki `$` işaretlerini ve bu işaretleri takip eden operatörleri (örneğin, `$PATH`) çözmek için `parse_dollar_op` fonksiyonunu kullanır. `check_dollar` fonksiyonu ile `$` işaretinin geçerli bir operatör ile ilişkili olup olmadığı kontrol edilir. Eğer `$` işareti geçerli bir operatör ile ilişkiliyse, `parse_dollar_op` fonksiyonu ile bu operatör çözülür ve `new_str` değişkenine atanır. Bu işlem tekrar edilir ve eğer `$` işareti yoksa veya `$` işareti geçerli bir operatör ile ilişkili değilse, `new_str` değişkeni döndürülür.

<br />

## lexer.c

**func append_arguments -->** Bu fonksiyon bir shell sözdizimi analizi sırasında, belirtilen `token` ve `process` değişkenlerine veri eklemek için kullanılır. `token` bir sözdizimi parçasıdır ve `process` ise bu parçayı işlemek için gerekli verileri saklayan bir yapıdır.

Eğer `token`in tipi `STRING` ise, fonksiyon `process->execute` dizisine bu tokenin içeriğini temizleyerek ekler.

Eğer `token`in tipi `STRING` değilse, fonksiyon `process->redirects` dizisine bu tokenin içeriğini temizleyerek ekler. Ardından, `token` pointer'ı bir sonraki `token`'a güncellenir. Eğer sonraki `token` `STRING` tipinde değilse, bir hata oluşur ve bu hatayı göstermek için `token_err` fonksiyonu çağrılır.

Fonksiyon sonunda, veri ekleme işlemi başarılı olduğu sürece `TRUE`, başarısız olduğunda `FALSE` değeri döndürür.


**func lexer -->** Bu fonksiyon, bir komut satırındaki token'ları süzerek işlemleri ve yönlendirmeleri bir t_process yapısı içinde gruplandırır. Bu fonksiyon, token'ları gezerek, PIPE türündeki token'lardan sonra başka bir işlem başlatır ve token'ları (komutları ve yönlendirmeleri) bir t_process yapısına ekler. Her t_process yapısı bir komut satırındaki tek bir işlemi temsil eder. Fonksiyon, sonunda t_process yapılarını bir liste halinde saklar ve token'ları serbest bırakır.

<br />

## process.c

**func init_process -->** `init_process()` fonksiyonu bir `t_process` yapısı oluşturur ve bu yapının tüm elemanlarını başlangıç değerlerine atar. Özellikle, `pipe` fonksiyonu ile bir pipe oluşturur ve fd değişkenine kaydeder, pid değişkenini -1 olarak atar, execute ve redirects dizilerini bellekte yer açar ve bu dizilerin içeriklerini sıfırlar. Son olarak, bu yapının prev ve next işaretçilerini NULL yapar.


**func process_addback -->** "process_addback" fonksiyonu, bir süreç verilen bir bağlı listesine eklemek için kullanılır. Eğer verilen bağlı liste boş ise, verilen yeni süreç bağlı listenin tek öğesi olarak atanır. Aksi takdirde, bağlı listedeki son süreç bulunur ve yeni süreç bu son sürecin "next" öğesine atanır. Ayrıca, yeni sürecin "prev" öğesi de bulunan son sürecin kendisi olarak ayarlanır.
