## parse_string.c

**func find_end_pos -->** Bu fonksiyon, verilen `str` değişkeninin içinde belirtilen `type` karakterini arar. Eğer `type` karakteri bulunursa, karakterin bulunduğu pozisyondan sonraki karakterin boşluk veya operator karakter olup olmadığı kontrol edilir. Eğer boşluk veya operator karakter değilse, o karakterden sonraki boşluk veya operator karakter bulunana kadar `str` değişkeni içindeki karakterler gezilir. Bu fonksiyon, bulunan `type` karakterine kadarki kısmın son pozisyonunu belirler ve geriye döndürür.


**func without_quote_parse -->** Bu fonksiyon, verilen karakter dizisi içinde (`*str`) bir operatör veya boşluk bulana kadar karakterleri okuyup ilerletir. Eğer bir operatör veya boşluk bulunursa döngüden çıkar ve fonksiyon sonlanır.


**func skip_whitespace -->** `skip_whitespace` fonksiyonu, verilen bir karakter dizisi içinde, gösterici (`str`) pozisyonunu oluşan boşluk karakterlerine kadar hareket ettirir. Sonra, `head` göstericisi o pozisyonu gösterir. Yani, `str` ve `head` göstericileri, verilen karakter dizisindeki ilk boşluk karakteri dışındaki ilk karakteri gösterir.


**func parse_token_string -->** Bu fonksiyon, bir metin dizesinde belirtilen bir token'ı parse etmeye yarar. İlk olarak, belirtilen dizinin başındaki boşluklar atlanır ve token'ın başlangıç noktası belirlenir. Daha sonra, eğer token, çift veya tek tırnak içinde ise, token'ın son noktası belirlenir ve belirtilen tırnak tipi arasındaki metin alınır. Aksi takdirde, boşluk veya operatör bulunana kadar metin taranır. Elde edilen metin, son olarak token olarak eklenir.

<br />

## tokenize.c

**func init_token -->** "init_token" fonksiyonu belirli bir string ve token tipi ile bir token nesnesi oluşturmak için kullanılır. Fonksiyon, token nesnesi için bellek alanı ayırarak oluşturulan nesnenin değerlerini ayarlar ve döndürür. "str" parametresi token nesnesinin string değerini belirler, "type" parametresi ise token nesnesinin tipini belirler.


**func token_addback -->** Bu fonksiyon, belirtilen token dizisinin sonuna, belirtilen yeni token nesnesini ekler. Fonksiyon, eklenen token'ın sayısını (önceki token sayısı + 1) geri döndürür.s


**func tokenize -->** Bu fonksiyon "tokenize" verilen bir metin dizesini belirli işaretler ve operatörler bazında ayrıştırır. İşaret ve operatörler belirlenerek "t_token" tipinde bir yapı içinde saklanır. Bu yapıdaki veriler sonrasında işlem yapmak için kullanılabilir.
