## close.c

**func close_heredoc_fd -->** Bu C dilinde bir fonksiyondur ve "Heredoc" denilen bir özelliğin işlem dosyasını kapatır. Bu fonksiyon, verilen t_process tipindeki işlem nesnesinde "Heredoc" içeriğinin bulunup bulunmadığını kontrol eder ve eğer bulunuyorsa ve işlem dosyası 2'den büyükse, dosyayı kapatır (close(process->heredoc_fd[0])).


**func close_all_fd -->** Bu C dilinde bir fonksiyondur ve tüm açık işlem dosyalarını kapatır. Bu fonksiyon, g_ms.process değişkeni tarafından tanımlanan tüm t_process tipindeki işlem nesnelerinin bulunduğu bağlı listede dolaşır ve her bir işlem nesnesi için close_heredoc_fd(process) fonksiyonunu çağırarak dosyaları kapatır. Eğer işlem dosyası 2'den büyükse, dosyayı kapatır (close(process->fd[0/1])).

<br />

## cmd.c

**func get_builtin -->** Fonksiyon, çalıştırılacak dahili bir komutun girdi ve çıktı dosyalarını geçici olarak değiştirerek, dahili komutun çalışmasını ve sonrasında orijinal girdi ve çıktı dosyalarının geri yüklenmesini sağlar. Bu işlemler şunları içerir:

1.  Girdi ve çıktı dosyalarını yedekler (in ve out değişkenlerinde).
2.  İşlem için girdi ve çıktı dosyalarını ayarlar (get_all_inputs ve set_all_outputs fonksiyonları).
3.  İçin belirlenen dahili komutu çalıştırır (run_builtin fonksiyonu).
4.  Girdi ve çıktı dosyalarını eski haline geri yükler (dup2 ile).
5.  Yedek dosyaları kapatır (close).

Bu fonksiyon, dahili bir komutun çalışması sırasında girdi ve çıktı dosyalarının geçici olarak değiştirilmesini ve dahili komutun tamamlanmasından sonra orijinal durumlarına geri döndürülmesini sağlar.


**func wait_cmd -->** 1.  Tüm dosya tanımlayıcılarını kapatır (close_all_fd fonksiyonu).
2.  Bağlantı noktalarının listesi taranır (g_ms.process).
3.  Her işlem için (process), eğer pid -1 değilse, işlem tamamlanana kadar beklenir (waitpid).
4.  İşlem durumunun değerinin alınması ve errno değişkenine atanması (WEXITSTATUS).
5.  Sonraki işlem (process->next) taranır.

Bu fonksiyon, shell programı tarafından başlatılan tüm işlemlerin tamamlanmasını bekler ve errno değişkeninde her işlem için çıkış durumunu tutar.


**func start_cmd -->** 1.  Bağlantı noktalarının listesi taranır (g_ms.process).
2.  Eğer liste boşsa, fonksiyon dönüş yapar.
3.  Tüm heredoc (g_ms.process) doldurulur (fill_all_heredoc fonksiyonu).
4.  Eğer g_ms.ignore true ise, tüm dosya tanımlayıcıları kapatılır ve fonksiyon dönüş yapar (close_all_fd).
5.  Eğer tek işlem varsa ve bu işlem bir built-in komut ise (is_builtin fonksiyonu), get_builtin fonksiyonu çalıştırılır.
6.  Bağlantı noktalarının listesi taranır ve her işlem için run_cmd fonksiyonu çalıştırılır.
7.  Tüm işlemlerin beklenmesi için wait_cmd fonksiyonu çalıştırılır.

Bu fonksiyon, shell programı tarafından verilen komutları çalıştırır ve sonuçları bekler. İşlem durumlarını wait_cmd fonksiyonu tarafından tutulur.

<br />

## run_cmd.c

**func pipe_route -->** bir pipe (boru) mekanizması için gerekli dosya tanımlayıcılarını (file descriptors) yapılandırır. Aşağıdaki adımları gerçekleştirir:

1.  Eğer işlem bir listenin başındaysa, verilerin yazılacağı dosya tanımlayıcısı process->fd[1] olarak yapılandırılır.
2.  Eğer işlem bir listenin sonundaysa, verilerin okunacağı dosya tanımlayıcısı process->prev->fd[0] olarak yapılandırılır.
3.  Eğer işlem listenin başında veya sonunda değilse, verilerin okunacağı dosya tanımlayıcısı process->prev->fd[0], verilerin yazılacağı dosya tanımlayıcısı ise process->fd[1] olarak yapılandırılır.

Bu fonksiyon, pipe mekanizmasının farklı bölümlerinde verilerin nasıl yazılacağı ve okunacağı hakkında bilgi sağlar.


**func heredoc_route -->** 
1.  Verilerin okunacağı dosya tanımlayıcısı process->heredoc_fd[0] olarak yapılandırılır.
2.  Eğer işlem bir listenin sonundaysa, verilerin yazılacağı dosya tanımlayıcısı process->fd[1] olarak yapılandırılır.

Bu fonksiyon, "heredoc" mekanizmasının nasıl çalışacağı hakkında bilgi sağlar ve işlemin verilerin nasıl okunacağı ve yazılacağı hakkında bilgi verir.


**func cmd_route -->** 
1.  Eğer işlem tek bir işlem değilse ve içerisinde "heredoc" mekanizması bulunuyorsa, heredoc_route fonksiyonu çağrılır ve işlemin verilerin okunması ve yazılması için gerekli dosya tanımlayıcıları yapılandırılır.
2.  Eğer "heredoc" mekanizması bulunmuyorsa, pipe_route fonksiyonu çağrılır ve işlemin verilerin okunması ve yazılması için gerekli dosya tanımlayıcıları yapılandırılır.
3.  get_all_inputs ve set_all_outputs fonksiyonları çağrılır ve işlemin girdileri ve çıktıları yapılandırılır.
4.  Tüm dosya tanımlayıcıları kapatılır.

Bu fonksiyon, işlemin nasıl yapılandırılacağını belirler ve işlemin girdilerinin ve çıktılarının nasıl yapılandırılacağı hakkında bilgi verir.


**func run_cmd -->** "run_cmd" fonksiyonu, belirtilen süreç için bir çocuk süreci oluşturur ve çocuk sürecinde belirtilen komutun yürütülmesini sağlar. İşlem yapılacak komut, belirtilen girdi ve çıktılar aracılığıyla yapılır ve çocuk süreci beklenir. Eğer komut bir "built-in" komut ise çocuk süreci tarafından direk çalıştırılır, değilse PATH değişkeni aracılığıyla komutun yolu bulunur ve execve fonksiyonu ile çalıştırılır. Eğer komut bulunamaz veya başka bir hata oluşursa, hata mesajı görüntülenir ve çocuk süreci sonlandırılır.

