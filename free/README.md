## free_token.c

**func free_token -->** "free_token" adlı fonksiyon, bellekte tutulan "g_ms.token" nesnesinde saklanan metin dizilerini (char *str) ve token nesnelerini (t_token) serbest bırakmaya yarar. Bu fonksiyon, bellekte ayrılan alanların boşa harcanmamasını ve sistem kaynaklarının verimli kullanılmasını sağlar.

<br />

## free.c

**func free_array -->** Bu fonksiyon "arr" adlı bir diziyi bellekte serbest bırakır. Her bir dizi elemanını tek tek serbest bırakır ve sonra diziyi kendisini serbest bırakır. Bu, bellekte boşluk açmak ve bellek sıkıntısı oluşmadan programın çalışmasını sağlamaya yardımcı olur.


**func free_process -->** Bu fonksiyon, `g_ms.process` adlı bir veri yapısındaki tüm işlemleri serbest bırakır. İşlemler, `t_process` tipindeki bir veri yapısında saklanır ve tek tek serbest bırakılır. Her bir işlemin `execute` ve `redirects` alanlarındaki diziler de serbest bırakılır.
