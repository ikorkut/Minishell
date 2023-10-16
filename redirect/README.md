## heredoc.c

**func close_heredoc -->** "close_heredoc" fonksiyonu bir signal handler fonksiyonu olarak görünüyor ve SIGINT sinyalini yakaladığında çalışır. İşlevi, g_ms değişkeninin "ignore" özelliğini TRUE yapmak ve bir satır sonu eklemek için STDIN_FILENO için ioctl çağrısı yapmaktır.


**func heredoc -->** "heredoc" adında bir fonksiyon tanımlanmış. Bu fonksiyon, verilen bir son satır metni (endline) kadar kullanıcıdan girdi alır ve bu girdileri bir pipe üzerinden bir dosyaya yazdırır. Kullanıcı, herhangi bir zaman bu girdi işlemini sonlandırmak için son satır metnini girene kadar girdi almaya devam eder. Bu girdiler "heredoc>> " yazısıyla kullanıcıya gösterilir ve SIGINT sinyalini yakalandığında fonksiyon sonlanır.

<br />

## input.c

**func input -->** Bu fonksiyon, bir dosya adı verilen dosyayı okunabilir olarak açar ve standart giriş (STDIN) ile dosya arasında bir çiftleme yapar. Bu, komutların dosyadan okunmasını ve standart giriş yerine dosya girdisi olarak kullanmasını sağlar. Eğer dosya açılamazsa, "no_file_err" fonksiyonu çağrılır ve dosya adı ile birlikte bir hata mesajı görüntülenir.

<br />

## output.c

**func output -->** "input" ve "output" fonksiyonları, belirtilen dosya isimli dosyalardan veya bu dosyalara veri okumak/yazmak için kullanılan dosya tanımlayıcılarını yönetmek için kullanılır. Bu fonksiyonlar, verilerin standart giriş veya standart çıkış akışından okunması veya yazılması yerine belirtilen dosyalardan okunması veya belirtilen dosyalara yazılmasını sağlar.

<br />

## redirect.c

**func get_all_inputs -->** Bu fonksiyon, belirtilen işlemde yönlendirilmiş girdi kaynaklarını almak için kullanılır. İşlemdeki tüm yönlendirme işaretçleri taranır ve eğer RED_INPUT veya HERE_DOC gibi yönlendirme operatörleri bulunursa, ilgili fonksiyonlar çağrılır ve girdi kaynağı belirlenir.


**func set_all_outputs -->** `get_all_inputs` ve `set_all_outputs` fonksiyonları, `process` verilerini yönlendirme işlemlerini yapmak için kullanılan fonksiyonlardır. `get_all_inputs` fonksiyonu verilen `process` verilerine göre girdi dosyalarını okumak için gerekli olan fonksiyonları çağırır. `set_all_outputs` fonksiyonu verilen `process` verilerine göre çıktı dosyalarını yazmak için gerekli olan fonksiyonları çağırır.


**func fill_all_heredoc -->** Bu fonksiyon, bir shell uygulamasında "here document" (heredoc) yönlendirmesini desteklemek için tasarlandı. Her process için, process'in "redirects" dizisindeki her bir "here document" yönlendirmesini işler ve o yönlendirmenin bitiş satırına kadar okunan kullanıcı girdilerini bir pipe üzerinden saklar. "heredoc_fd" dizisi, pipe'ın okuma ve yazma uçlarını tutar. "heredoc()" fonksiyonu, kullanıcı girdilerini okur ve yazdığı pipe üzerinde saklar. "fill_all_heredoc()" fonksiyonu ise tüm processler için "heredoc()" fonksiyonunu çağırır ve tüm "here document" yönlendirmelerinin doldurulmasını sağlar.
