# MINISHELL

## PDF Mandatory Part

1.  Display a prompt: Bu, kullanıcının komut girdiğinde görünecek olan bir satır olmalıdır. <br>
Örnek olarak "$" kullanabilirsiniz. Bu satırı her komut girişinde ekrana yazdırmak için while döngüsü kullanabilirsiniz.

        while (1) {
	        printf("$ ");
	        fgets(input, 100, stdin);
	        // process input
	    }


<br>


2.  Working history: Kullanıcının girdiği komutların geçmişini tutmak için bir dizi veya liste kullanabilirsiniz. Her komut girişinde, kullanıcının girdiği komutu bu diziye veya listenin sonuna ekleyebilirsiniz.

        char history[100][100];
    	int history_count = 0;
    
    	// add current input to history
    	strcpy(history[history_count++], input);
    
    	// display history
    	for (int i = 0; i < history_count; i++) {
    		printf("%d %s", i+1, history[i]);
    	}


<br>


3.  Search and launch the right executable: Kullanıcının girdiği komutun PATH değişkeninde aranması gerekir veya komutun mutlak veya göreli bir yolu kullanılabilir. Bu komutu çalıştırmak için "system" fonksiyonu kullanabilirsiniz.

        if (input[0] == '/' || input[0] == '.') {
            // input is a relative or absolute path
            system(input);
        } else {
            // input is a command, search in PATH
            char path[100];
            strcpy(path, getenv("PATH"));
            char *token = strtok(path, ":");
            while (token != NULL) {
                char command[100];
                sprintf(command, "%s/%s", token, input);
                if (system(command) == 0) {
                    break;
                }
                token = strtok(NULL, ":");
            }
        }

    
<br>


4.  Global variable: Projede sadece bir global değişken kullanmalısınız ve bu değişkenin amacını açıklamalısınız. Örneğin, komutların geçmişini tutmak için kullanılan bir değişken.

        char history[100][100];
        int history_count = 0;


<br>


5.  Unclosed quotes and special characters: Projede kapatılmamış tırnak ve özel karakterlerin yorumlanmaması gerekir. Bu karakterleri algılamak ve kullanıcının girdiği komutu uygun şekilde işlemek için string fonksiyonlarını kullanabilirsiniz.

        int len = strlen(input);
        if (input[len-1] == '\n') {
            input[len-1] = '\0';
        }

    
<br>


6.  Handle ' and ": Projede ' (tek tırnak) ve " (çift tırnak) karakterlerinin işlenmesi gerekir. Bu karakterleri algılamak ve kullanıcının girdiği komutu uygun şekilde işlemek için string fonksiyonlarını kullanabilirsiniz.


        int len = strlen(input);
        if(input[0] == '"' || input[0] == '\'' ){
            input[len-1] = '\0';
            input++;
        }


<br>


- Komutları beklerken bir prompt görüntülemelidir.
- Çalışan bir geçmişi olmalıdır.
- PATH değişkeni veya göreli veya mutlak bir yol kullanarak doğru çalıştırılabilir dosyayı aramalı ve başlatmalıdır.
- Tek bir global değişken kullanmamalıdır.
- Kapatılmamış tırnak işaretleri veya konuya gerek olmayan özel karakterleri yorumlamamalıdır, örneğin \ (ters eğik) veya ; (noktalı virgül).
- ' (tek tırnak) işaretini işaretli dizide metakarakterleri yorumlamamasını sağlamalıdır.
- " (çift tırnak) işaretini işaretli dizide metakarakterleri yorumlamamasını sağlamalıdır, ancak $ (dolar işareti) hariç olmalıdır.


<br>


**A. Implement Redirections:** <br>

Komutların çıktısını veya girdisini başka dosyalara veya kaynaklara yönlendirmek için kullanılan operatörleri içermektedir.

***Örnek olarak:*** <br>
> 1. "<" operatorü (input redirection) kullanılarak komutun girdisi başka bir dosyadan okunabilir.
<br />
Örnek: "cat < input.txt" komutu input.txt dosyasındaki içeriği ekrana yazdırır.***

> 2. ">" operatorü (output redirection) kullanılarak komutun çıktısı başka bir dosyaya yazılabilir. 
<br>
Örnek: "ls > output.txt" komutu listedeki dosyaları output.txt dosyasına yazar.

> 3. "<<" operatorü (heredoc) kullanılarak komutun girdisi, belirlenen bir ayraç satırına kadar okunur ve ekrandaki çıktı güncellenmez. 
<br>
Örnek: "cat output.txt" komutu output.txt dosyasına "hello" yazısını ekler. 

> 4. ">>" operatorü (append output redirection) kullanılarak komutun çıktısı başka bir dosyaya eklenir. 
Örnek: "echo "hello" >> output.txt" komutu output.txt dosyasına "hello" yazısını ekler.


<br />
<br />


**B. Pipes** <br>

"|" karakteri olarak bilinen pipe işareti, komut satırında kullanılır ve komutların çıktılarını bir sonraki komutun girdisi olarak kullanmasını sağlar. <br>
***Örneğin,*** `"command1 | command2"` komutu, command1'in çıktısını command2'nin girdisi olarak kullanır. Bu, birden fazla komutun bir arada kullanılmasını ve çıktıların birbirleriyle işlenmesini sağlar.


<br />
<br />


**C. Environment Variables**

Sistemde tanımlı olan ortam değişkenlerini ($ işareti ile başlayan bir dizi karakter) kullanmanızı istemektedir. <br> 
***Örneğin,*** `$HOME` değişkeni kullanıcının ev dizinini ifade eder ve komut satırında $HOME olarak kullanıldığında, gerçek değeri olan kullanıcının ev dizininin yolu olarak değiştirilmelidir. Bu işlem, komut satırında kullanılan ortam değişkenlerinin gerçek değerlerine çevrilmesini içerir.


<br />
<br />


**D. $?**

"$?" değişkeni, son çalıştırılan arka plandaki veya ön plandaki pipeline'ın çıkış durumunu temsil eder. <br>
***Örneğin,*** bir komut çalıştırıldıktan sonra "$?" değişkeni, o komutun çıkış durumunu içerecektir. 0 çıkış durumu başarılı bir çıkış anlamına gelirken, 1 veya daha yüksek bir değer başarısız bir çıkış anlamına gelir. Bu talimatta, $? değişkeni en son çalıştırılan ön plandaki pipeline'ın çıkış durumunu temsil etmeli ve kullanıcının kullanabileceği bir değişken olarak ele alınmalıdır.


<br />
<br />


**E. CTRL-C, CTRL-D**

`"ctrl-C, ctrl-D ve ctrl-\"` gibi klavye kısayollarının nasıl çalıştığını bash gibi yapmanız gerekmektedir. <br> 
***Örneğin,*** ctrl-C genellikle bir işlemi iptal etmek için kullanılır. ctrl-D genellikle komut satırından çıkmak için kullanılır. ctrl-\ genellikle programın çalışmasını durdurmak için kullanılır.


<br />
<br />


**F. BUILTIN**

Kullanıcının shell'de kullanabileceği bazı komutlar: 
- echo with option -n: Echo komutu, kullanıcı tarafından verilen argümanları ekrana yazdırır. -n seçeneği ile kullanıldığında, argümanlar ekrana yazdırılırken sonunda bir satır atlaması yapılmaz.
- cd with only a relative or absolute path: cd komutu, kullanıcının çalışma dizinini değiştirir. Sadece yol olarak relative veya absolute path kullanılması istenmektedir.
- pwd with no options: pwd komutu, kullanıcının çalışma dizininin yolunu ekrana yazdırır.
- export with no options: export komutu, kullanıcının sistemde tanımladığı bir değişkeni dış ortama aktarmasını sağlar.
- unset with no options: unset komutu, kullanıcının sistemde tanımlı bir değişkeni siler.
- env with no options or arguments: env komutu, sistemde tanımlı tüm ortam değişkenlerini ekrana yazdırır.
- exit with no options: exit komutu, kabuk programını sonlandırır.


<br>
<br>


## KÜTÜPHANELER

1.  "stdio.h": Standart Girdi/Çıktı kütüphanesi, fprintf(), scanf(), printf() gibi fonksiyonları içerir.
   
2.  "readline/readline.h": Kullanıcıdan girdi okuma fonksiyonlarını içerir.
   
3.  "readline/history.h": Kullanıcı tarafından girilen komutların geçmişini saklamaya yarar.

4.  "unistd.h": Unix tabanlı sistemler için genel işlevleri tanımlar, örneğin exec(), fork() gibi.

5.  "stdlib.h": Standart Kütüphane, malloc(), free(), exit() gibi fonksiyonları tanımlar.

6.  "errno.h": Sistem çağrıları sırasında oluşan hata kodlarını tanımlar.

7.  "string.h": String işlemleri için fonksiyonları tanımlar, örneğin strcmp(), strlen() gibi.

8.  "sys/types.h": Sistem çağrıları için tip tanımlarını içerir.

9.  "sys/wait.h": Çocuk süreçlerin beklenmesine yarar.

10.  "fcntl.h": Dosya kontrol işlevlerini tanımlar.

11.  "dirent.h": Dosya ve dizin işlemleri için fonksiyonları tanımlar.

12.  "signal.h": Sinyal işlemlerini tanımlar, örneğin sigaction().

13.  "sys/ioctl.h": Terminal boyutunu kontrol etmek için fonksiyonları tanımlar.


<br>
<br>


## DEFINE 

1.  TRUE ve FALSE: Mantıksal değerler için tanımlanmış sabit değerlerdir, bu değerler programda True ve False mantıksal değerleri ifade etmek için kullanılabilir.

2.  DOLLAR_OP: '$' sembolünü tanımlar.

3.  DOUBLE_QUOTE ve SINGLE_QUOTE: Çift ve tek tırnak sembollerini tanımlar.

4.  CHILD_PROCESS ve MAIN_PROCESS: Çocuk ve ana süreçler için tanımlanmış sabit değerlerdir.

5.  REPLACE ve APPEND: Dosya yazma modlarını tanımlar, REPLACE dosyanın içeriğini yazacak, APPEND dosyanın sonuna ekleme yapacak.


<br>
<br>


## ENUMLAR

Built-in komutlarını ve işlemlerin türlerini tanımlar.

1.  e_builtin_types: Built-in komutlar için bir enumerasyon tanımlar. Her bir built-in komut için bir sabit değer belirlenmiştir. Örneğin, CD = 1 anlamına gelir ki CD komutu 1 numaralı tanımlanmış bir built-in komuttur.

2.  e_ttype: Shell programındaki işlemlerin türleri için bir enumerasyon tanımlar. Her bir işlem türü için bir sabit değer belirlenmiştir. Örneğin, PIPE = 1 anlamına gelir ki PIPE işlemi 1 numaralı tanımlanmış bir işlem türüdür.


<br>
<br>


## STRUCTLAR

1.  t_token: Shell programındaki her bir girdiyi (input) tutmak için kullanılan bir yapı tanımıdır. Bu yapı, girdinin metnini (str), girdinin türünü (type), girdinin önceki ve sonraki girdilerini (prev ve next) içerir.

2.  t_process: Shell programındaki her bir işlemi tutmak için kullanılan bir yapı tanımıdır. Bu yapı, işlemin PID numarasını (pid), işlemin giriş/çıkış akışını yönetmek için kullanılan dosya tanımlayıcılarını (fd), heredoc yapısının dosya tanımlayıcılarını (heredoc_fd), işlemi yapacak komutların listesini (execute), yönlendirme komutlarının listesini (redirects), işlemin önceki ve sonraki işlemlerini (prev ve next) içerir.

3.  t_minishell: Minishell programının genel verilerini tutmak için kullanılan bir yapı tanımıdır. Bu yapı, programın anne işleminin PID numarasını (parent_pid), işlem sayısını (process_count), komutların yoksayılıp yoksayılmayacağını (ignore), ortam değişkenlerini (env), yolları (paths), token verilerini (token), işlem verilerini (process) içerir.


<br>
<br>


## EXTERN KEYWORDÜ

extern --> bir değişkenin ya da fonksiyonun diğer dosyalarda da tanımlanabileceğini belirtir. Bu anahtar kelime ile tanımlanan değişkenler veya fonksiyonlar programın diğer bölümlerinde erişilebilir ve kullanılabilir. "extern" anahtar kelimesi, tanımladığı değişkenin ya da fonksiyonun yalnızca başka bir dosyada tanımlı olduğunu belirtir, fakat bu dosya içinde tanımlanmaz.

`extern t_minishell g_ms;` şu anlama gelir: `g_ms` adında bir global `t_minishell` tipinde bir değişken var ve bu dosya dışında tanımlanmış. Bu tanım, bu dosya içinde `g_ms` değişkenine erişebilmek için kullanılır ve bu değişkenin başka bir dosyada tanımlandığı anlaşılır.


<br>
<br>


## MAKEFILE'DA KULLANILAN KOMUTLAR

`$@` --> `$@` kullanımı Makefile dosyalarında, hedef dosyanın adını ifade eder. Örneğin, bir make komutuyla derlenmesi istenen objekt dosyasının adı "$@" ile belirtilebilir. Bu kısaltma, hedef dosyanın adının değiştiği durumlarda kodun otomatik olarak güncellenebilmesini sağlar.


`$<` --> makefile içindeki bir hedef için ilk bağımlılık olarak tanımlanmış olan dosyanın adıdır.
Makefile'daki bağımlılıklar, bir hedefin (örneğin, bir derleme komutu) hangi dosyalardan etkilendiğini belirtir. Eğer bağımlı dosyalardaki değişiklikler, o hedefe ait komutların tekrar çalışmasını gerektirirse, bu bağımlılıklar tanımlanır. Makefile içindeki bağımlılıklar, bir hedefin adının sol tarafındaki dosyalarla belirtilir ve sağ tarafındaki komutlar tarafından gerçekleştirilir.


<br>
<br>


## main.c

**func main -->** Ana fonksiyon, yürütme başlamadan önce uygulamayı başlatmak için `init_app` fonksiyonunu çağırır ve daha sonra sonsuz bir döngü içinde `readline` fonksiyonunu kullanarak kullanıcıdan girdi okur. Okunan girdi, `init_shell` fonksiyonu aracılığıyla işlenir ve işlenen girdi `add_history` fonksiyonu aracılığıyla geçmişe eklenir. Döngü sonunda, girdi bellekten boşaltılır ve döngü tekrar başlar.


**func init_app -->** "init_app" adlı fonksiyon, uygulamanın başlatılması sırasında gerekli olan ilk adımların yapılmasını sağlar. Bu fonksiyon, bellekte errno değişkeni için bir boşluk açar, "g_ms.paths" global değişkenini NULL'a ayarlar, "g_ms.parent_pid" global değişkenini çalışan programın PID'sini alır, "set_env" fonksiyonunu çağırarak ortam değişkenlerini ayarlar ve "set_paths" fonksiyonunu çağırarak yolları ayarlar.


**func init_shell -->** "init_shell" fonksiyonu, bir kullanıcı tarafından girilen komut satırının tokenize edilmesi, lexer tarafından analiz edilmesi ve sonuçta çalıştırılmasını sağlar. Bu fonksiyon, token dizilerini ve işlem dizilerini g_ms yapısı içerisinde tanımlar ve başlatır, ardından da çalıştırılması tamamlanan komut satırından boşalmasını sağlar.


**func ctrl_c -->** Bu fonksiyon, işletim sistemi tarafından SIGINT sinyali olarak adlandırılan bir sinyali ele alır ve bu sinyal, kullanıcının Ctrl + C tuşlarına basması durumunda tetiklenir. Fonksiyon, ekranda bir satır altına inmek için TIOCSTI ioctl çağrısı yapar ve sonra g_ms.ignore değişkenini TRUE olarak ayarlar. Bu, giriş ekranının "minishell_>" olarak tanımlanmış olan başlığını tekrar yazdırmasını ve kullanıcının tekrar komut girmesine izin vermesini sağlar.


**func ctrl_d -->** Bu fonksiyon, kullanıcı tarafından girilen verinin boş olup olmadığını kontrol eder. Eğer veri boşsa, ekrana "exit" yazdırır ve programı sonlandırır.


