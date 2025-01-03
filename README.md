# Embedded-in-Automotive
# Interrupt - Timer
Ngắt là một sự kiện khẩn cấp xảy ra bên trong hoặc bên ngoài vi điều khiển, yêu cầu dừng chương trình chính để thực thi chương trình xử lý ngắt.
Các loại ngắt thông dụng:
Bao gồm ngắt Reset, ngắt ngoài, ngắt Timer1, và ngắt truyền thông. 
### Hàm phục vụ ngắt :
Mỗi ngắt có địa chỉ trình phục vụ ngắt riêng trong bộ nhớ, được gọi là vector ngắt.
Ngắt ngoài:
Xảy ra khi có thay đổi điện áp trên các chân GPIO được cấu hình làm ngõ vào ngắt. Các kiểu kích hoạt ngắt gồm LOW, HIGH, Rising, và Falling.
### Ngắt Timer:
Xảy ra khi giá trị trong thanh ghi đếm của timer bị tràn. Sau mỗi lần tràn, cần phải reset giá trị thanh ghi để có thể tạo ngắt tiếp theo.
Ngắt truyền thông:
Xảy ra khi có sự kiện truyền/nhận dữ liệu giữa MCU và các thiết bị khác, thường sử dụng cho các giao thức như UART, SPI, I2C.
Độ ưu tiên ngắt:
Các ngắt có độ ưu tiên khác nhau, quyết định ngắt nào được thực thi khi nhiều ngắt xảy ra đồng thời. Trên STM32, ngắt có số ưu tiên càng thấp thì có quyền càng cao.
Giải thích về cơ chế hoạt động của chương trình (Thanh Ghi PC) khi xảy ra ngắt lồng nhau.
### Timer:
Timer là mạch digital logic dùng để đếm các chu kỳ clock, có thể hoạt động ở chế độ nhận xung clock từ tín hiệu ngoài. 
Timer trong Stm32F1: 
### Cấu hình Timer:
Các thông số như Prescaler, Period, và Clock Division được cấu hình để điều chỉnh cách thức đếm của Timer.
Ví dụ cấu hình timer với thư viện STD.
Ví dụ: Hàm delay_ms:
Được thiết kế để tạo ra khoảng trễ chính xác bằng cách sử dụng Timer. Với cài đặt cụ thể, Timer sẽ đếm lên mỗi 0.1ms và lặp lại số lần cần thiết để tạo độ trễ.
Cung cấp kiến thức cơ bản và hướng dẫn cấu hình ngắt và Timer trên vi điều khiển.
# Lý thuyết các chuẩn giao tiếp cơ bản
## SPI
### SPI – Serial Peripheral Interface – hay còn gọi là giao diện ngoại vi nối tiếp, được phát triển bởi hãng Motorola. 
Chuẩn đồng bộ nối truyền dữ liệu ở chế độ full - duplex (hay gọi là "song công toàn phần". Nghĩa là tại 1 thời điểm có thể xảy ra đồng thời quá trình truyền và nhận. Là giao tiếp đồng bộ, bất cứ quá trình nào cũng đều được đồng bộ với xung clock sinh ra bởi thiết bị Master  
Tốc độ truyền thông cao: SPI cho phép truyền dữ liệu với tốc độ rất nhanh, thường đạt được tốc độ Mbps hoặc thậm chí hàng chục Mbps. Điều này rất hữu ích khi cần truyền dữ liệu nhanh và đáng tin cậy trong các ứng dụng như truyền thông không dây, điều khiển từ xa và truyền dữ liệu đa phương tiện.

### SPI sử dụng 4 đường giao tiếp nên đôi khi được gọi là chuẩn truyền thông “ 4 dây”:
- SCK (Serial Clock): Thiết bị Master tạo xung tín hiệu SCK và cung cấp cho Slave. Xung này có chức năng giữ nhịp cho giao tiếp SPI. Mỗi nhịp trên chân SCK báo 1 bit dữ liệu đến hoặc đi → Quá trình ít bị lỗi và tốc độ truyền cao.
- MISO (Master Input Slave Output): Tín hiệu tạo bởi thiết bị Slave và nhận bởi thiết bị Master. Đường MISO phải được kết nối giữa thiết bị Master và Slave.
- MOSI (Master Output Slave Input): Tín hiệu tạo bởi thiết bị Master và nhận bởi thiết bị Slave. Đường MOSI phải được kết nối giữa thiết bị Master và Slave.
- SS (Slave Select): Chọn thiết bị Slave cụ thể để giao tiếp. Để chọn Slave giao tiếp thiết bị Master chủ động kéo đường SS tương ứng xuống mức 0 (Low). Chân này đôi khi còn được gọi là CS (Chip Select). Chân SS của vi điều khiển (Master) có thể được người dùng tạo bằng cách cấu hình 1 chân GPIO bất kỳ chế độ Output.
  
    SPI cho phép 1 MCU chủ giao tiếp với nhiều thiết bị tớ thông qua tín hiệu chọn thiết bị SS. Các thiết bị tớ chỉ có thể có 1 chân CS để nhận tín hiệu chọn này, tuy nhiên thiết bị chủ có thể có nhiều hơn 1 chân SS để chọn từng thiết bị muốn giao tiếp.


### Khung truyền SPI:
- Mỗi chip Master hay Slave đều có một thanh ghi dữ liệu 8 bits. Quá trình truyền nhận giữa Master và Slave xảy ra đồng thời theo chu kỳ clock ở chân CLK, một byte dữ liệu được truyền theo cả 2 hướng 
- Quá trình trao đổi dữ liệu bắt đầu khi Master tạo 1 xung clock từ bộ tạo xung nhịp (Clock Generator) và kéo đường SS của Slave mà nó truyền dữ liệu xuống mức Low. Mỗi xung clock, Master sẽ gửi đi 1 bit từ thanh ghi dịch (Shift Register) của nó đến thanh ghi dịch của Slave thông qua đường MOSI. Đồng thời Slave cũng gửi lại 1 bit đến cho Master qua đường MISO.Như vậy sau 8 chu kỳ clock thì hoàn tất việc truyền và nhận 1 byte dữ liệu.
- Trong giao tiếp SPI, chỉ có thể có 1 Master nhưng có thể 1 hoặc nhiều Slave cùng lúc. Ở trạng thái nghỉ, chân SS của các Slave ở mức 1, muốn giao tiếp với Slave nào thì ta chỉ việc kéo chân SS của Slave đó xuống mức 0.

### Chế độ hoạt động: 
    SPI có 4 chế độ hoạt động phụ thuộc vào cực của xung giữ (Clock Polarity – CPOL) và pha (Phase - CPHA). CPOL dùng để chỉ trạng thái của chân SCK ở trạng thái nghỉ. Chân SCK giữ ở mức cao khi CPOL=1 hoặc mức thấp khi CPOL=0. CPHA dùng để chỉ các mà dữ liệu được lấy mẫu theo xung. Dữ liệu sẽ được lấy ở cạnh lên của SCK khi CPHA=0 hoặc cạnh xuống khi CPHA=1.

- Mode 0 (mặc định) – xung nhịp của đồng hồ ở mức thấp (CPOL = 0) và dữ liệu được lấy mẫu khi chuyển từ thấp sang cao (cạnh lên) (CPHA = 0). 
- Mode 1 - xung nhịp của đồng hồ ở mức thấp (CPOL = 0) và dữ liệu được lấy mẫu khi chuyển từ cao sang thấp (cạnh xuống) (CPHA = 1).
- Mode 2 - xung nhịp của đồng hồ ở mức cao (CPOL = 1) và dữ liệu được lấy mẫu khi chuyển từ cao sang thấp (cạnh lên) (CPHA = 0).
- Mode 3 - xung nhịp của đồng hồ ở mức cao (CPOL = 1) và dữ liệu được lấy mẫu khi chuyển từ thấp sang cao (cạnh xuông) (CPHA = 1).

## UART

    UART (Universal Asynchronous Receiver-Transmitter – Bộ truyền nhận dữ liệu không đồng bộ) là một giao thức truyền thông phần cứng dùng giao tiếp nối tiếp không đồng bộ và có thể cấu hình được tốc độ
    Giao thức UART là một giao thức đơn giản và phổ biến, bao gồm hai đường truyền dữ liệu độc lập là TX (truyền) và RX (nhận). Dữ liệu được truyền và nhận qua các đường truyền này dưới dạng các khung dữ liệu (data frame) có cấu trúc chuẩn, với một bit bắt đầu (start bit), một số bit dữ liệu (data bits), một bit kiểm tra chẵn lẻ (parity bit) và một hoặc nhiều bit dừng (stop bit).

    Thông thường, tốc độ truyền của UART được đặt ở một số chuẩn, chẳng hạn như 9600, 19200, 38400, 57600, 115200 baud và các tốc độ khác. Tốc độ truyền này định nghĩa số lượng bit được truyền qua mỗi giây. Các tốc độ truyền khác nhau thường được sử dụng tùy thuộc vào ứng dụng và hệ thống sử dụng.
Uart truyền dữ liệu nối tiếp, theo 1 trong 3 chế độ:
- Simplex: Chỉ tiến hành giao tiếp một chiều
- Half duplex: Dữ liệu sẽ đi theo một hướng tại 1 thời điểm
- Full duplex: Thực hiện giao tiếp đồng thời đến và đi từ mỗi master và slave
    Chân Tx (truyền) của một chip sẽ kết nối trực tiếp với chân Rx (nhận) của chip khác và ngược lại. Quá trình truyền dữ liệu thường sẽ diễn ra ở 3.3V hoặc 5V. Uart là một giao thức giao tiếp giữa một master và một slave. Trong đó 1 thiết bị được thiết lập để tiến hành giao tiếp với chỉ duy nhất 1 thiết bị khác.
    Dữ liệu truyền đến và đi từ Uart song song với thiết bị điều khiển. Khi tín hiệu gửi trên chân Tx (truyền), bộ giao tiếp Uart đầu tiên sẽ dịch thông tin song song này thành dạng nối tiếp và sau đó truyền tới thiết bị nhận. Chân Rx (nhận) của Uart thứ 2 sẽ biến đổi nó trở lại thành dạng song song để giao tiếp với các thiết bị điều khiển.
Dữ liệu truyền qua Uart sẽ đóng thành các gói (packet). Mỗi gói dữ liệu chứa 1 bit bắt đầu, 5 – 9 bit dữ liệu (tùy thuộc vào bộ Uart), 1 bit chẵn lẻ tùy chọn và 1 bit hoặc 2 bit dừng.

    Quá trình truyền dữ liệu Uart sẽ diễn ra dưới dạng các gói dữ liệu này, bắt đầu bằng 1 bit bắt đầu, đường mức cao được kéo dần xuống thấp. Sau bit bắt đầu là 5 – 9 bit dữ liệu truyền trong khung dữ liệu của gói, theo sau là bit chẵn lẻ tùy chọn để nhằm xác minh việc truyền dữ liệu thích hợp. Sau cùng, 1 hoặc nhiều bit dừng sẽ được truyền ở nơi đường đặt tại mức cao. Vậy là sẽ kết thúc việc truyền đi một gói dữ liệu
  
##  I2C.

I2C kết hợp các tính năng tốt nhất của SPI và UART. Giống như giao tiếp UART, I2C chỉ sử dụng hai dây để truyền dữ liệu giữa các thiết bị:
- SDA (Serial Data) - đường truyền cho master và slave để gửi và nhận dữ liệu.
- SCL (Serial Clock) - đường mang tín hiệu xung nhịp.
- I2C là một giao thức truyền thông nối tiếp, vì vậy dữ liệu được truyền từng bit dọc theo một đường duy nhất (đường SDA).
 Giống như SPI, I2C là đồng bộ, do đó đầu ra của các bit được đồng bộ hóa với việc lấy mẫu các bit bởi một tín hiệu xung nhịp được chia sẻ giữa master và slave. Tín hiệu xung nhịp luôn được điều khiển bởi master.
Với I2C, dữ liệu được truyền trong các tin nhắn. Tin nhắn được chia thành các khung dữ liệu. Mỗi tin nhắn có một khung địa chỉ chứa địa chỉ nhị phân của địa chỉ slave và một hoặc nhiều khung dữ liệu chứa dữ liệu đang được truyền. Thông điệp cũng bao gồm điều kiện khởi động và điều kiện dừng, các bit đọc / ghi và các bit ACK / NACK giữa mỗi khung dữ liệu:

- Điều kiện khởi động: Đường SDA chuyển từ mức điện áp cao xuống mức điện áp thấp trước khi đường SCL chuyển từ mức cao xuống mức thấp.
- Điều kiện dừng: Đường SDA chuyển từ mức điện áp thấp sang mức điện áp cao sau khi đường SCL chuyển từ mức thấp lên mức cao.
- Khung địa chỉ: Một chuỗi 7 hoặc 10 bit duy nhất cho mỗi slave để xác định slave khi master muốn giao tiếp với nó.
- Bit Đọc / Ghi: Một bit duy nhất chỉ định master đang gửi dữ liệu đến slave (mức điện áp thấp) hay yêu cầu dữ liệu từ nó (mức điện áp cao).
- Bit ACK / NACK: Mỗi khung trong một tin nhắn được theo sau bởi một bit xác nhận / không xác nhận. Nếu một khung địa chỉ hoặc khung dữ liệu được nhận thành công, một bit ACK sẽ được trả lại cho thiết bị gửi từ thiết bị nhận.
### Địa chỉ
    I2C không có các đường Slave Select như SPI, vì vậy cần một cách khác để cho slave biết rằng dữ liệu đang được gửi đến slave này chứ không phải slave khác. Nó thực hiện điều này bằng cách định địa chỉ. Khung địa chỉ luôn là khung đầu tiên sau bit khởi động.
    Master gửi địa chỉ của slave mà nó muốn giao tiếp với mọi slave được kết nối với nó. Sau đó, mỗi slave sẽ so sánh địa chỉ được gửi từ master với địa chỉ của chính nó. Nếu địa chỉ phù hợp, nó sẽ gửi lại một bit ACK điện áp thấp cho master. Nếu địa chỉ không khớp, slave không làm gì cả và đường SDA vẫn ở mức cao.
### Bit đọc / ghi
    Khung địa chỉ bao gồm một bit duy nhất ở cuối tin nhắn cho slave biết master muốn ghi dữ liệu vào nó hay nhận dữ liệu từ nó. Nếu master muốn gửi dữ liệu đến slave, bit đọc / ghi ở mức điện áp thấp. Nếu master đang yêu cầu dữ liệu từ slave, thì bit ở mức điện áp cao.
### Khung dữ liệu
    Sau khi master phát hiện bit ACK từ slave, khung dữ liệu đầu tiên đã sẵn sàng được gửi.
    Khung dữ liệu luôn có độ dài 8 bit và được gửi với bit quan trọng nhất trước. Mỗi khung dữ liệu ngay sau đó là một bit ACK / NACK để xác minh rằng khung đã được nhận thành công. Bit ACK phải được nhận bởi master hoặc slave (tùy thuộc vào cái nào đang gửi dữ liệu) trước khi khung dữ liệu tiếp theo có thể được gửi.
 
Sau khi tất cả các khung dữ liệu đã được gửi, master có thể gửi một điều kiện dừng cho slave để tạm dừng quá trình truyền. Điều kiện dừng là sự chuyển đổi điện áp từ thấp lên cao trên đường SDA sau khi chuyển tiếp từ thấp lên cao trên đường SCL , với đường SCL vẫn ở mức cao.
 
## Các bước truyền dữ liệu I2C
1. Master gửi điều kiện khởi động đến mọi slave được kết nối bằng cách chuyển đường SDA từ mức điện áp cao sang mức điện áp thấp trước khi chuyển đường SCL từ mức cao xuống mức thấp.
2. Master gửi cho mỗi slave địa chỉ 7 hoặc 10 bit của slave mà nó muốn giao tiếp, cùng với bit đọc / ghi.
3. Mỗi slave sẽ so sánh địa chỉ được gửi từ master với địa chỉ của chính nó. Nếu địa chỉ trùng khớp, slave sẽ trả về một bit ACK bằng cách kéo dòng SDA xuống thấp cho một bit. Nếu địa chỉ từ master không khớp với địa chỉ của slave, slave rời khỏi đường SDA cao.
4. Master gửi hoặc nhận khung dữ liệu.
5. Sau khi mỗi khung dữ liệu được chuyển, thiết bị nhận trả về một bit ACK khác cho thiết bị gửi để xác nhận đã nhận thành công khung.
6. Để dừng truyền dữ liệu, master gửi điều kiện dừng đến slave bằng cách chuyển đổi mức cao SCL trước khi chuyển mức cao SDA.

### Một master với nhiều slave
    Vì I2C sử dụng định địa chỉ nên nhiều slave có thể được điều khiển từ một master duy nhất. Với địa chỉ 7 bit sẽ có 128 (2 mũ 7) địa chỉ duy nhất. Việc sử dụng địa chỉ 10 bit không phổ biến, nhưng nó cung cấp 1.024 (2 mũ 10) địa chỉ duy nhất.

### Nhiều master với nhiều slave
    Nhiều master có thể được kết nối với một slave hoặc nhiều slave. Sự cố với nhiều master trong cùng một hệ thống xảy ra khi hai master cố gắng gửi hoặc nhận dữ liệu cùng một lúc qua đường SDA. Để giải quyết vấn đề này, mỗi master cần phải phát hiện xem đường SDA thấp hay cao trước khi truyền tin nhắn. Nếu đường SDA thấp, điều này có nghĩa là một master khác có quyền điều khiển bus và master đó phải đợi để gửi tin nhắn. Nếu đường SDA cao thì có thể truyền tin nhắn an toàn. Để kết nối nhiều master với nhiều slave.
# SPI Software & SPI Hardware 
## SPI Software
  Trên mỗi dòng vi điều khiển khác nhau module SPI sẽ được tích hợp, điều khiển bởi các thanh ghi,phần cứng, IO khác nhau, đấy gọi là SPI cứng (hardware SPI). Như vậy bản chất chuẩn truyền thông SPI giống nhau trên mỗi chip nhưng lại được cài đặt và sử dụng không giống nhau. Điều này gây thêm khó khăn cho người sử dụng khi bạn bắt đầu tìm hiểu một dòng vi điều khiển mới, bạn sẽ phải nhớ các chân MISO, SS, MOSI, SCK mỗi chip khác nhau, nhớ các thanh ghi, các chế độ hoạt động và cách cài đặt trên các dòng vi điều khiển khác nhau. 
  Để khắc phục nhược điểm trên, có 1 cách lập trình giả lập SPI cứng đó là “SPI mềm”. Thực chất SPI mềm là cách “mô phỏng” bằng cách tạo ra một giao thức truyền thông giống SPI nhưng chỉ sử dụng các cổng vào ra của vi điều khiển. Như vậy chỉ với việc điều khiển GPIO của chip hoàn toàn có thể thực hiện giao thức SPI. 
Điều này cũng có nghĩa là có thể sử dụng giao thức này trên bất kì vi điều khiển nào mà không cần phải nhớ thanh ghi hay các chân phần cứng.
### 1.1 Cấu hình GPIO cho SPI mềm.
  SPI dùng 4 chân để truyền nhận, gồm MISO, MOSI, CS và SCK.
  ![image alt](https://github.com/nguyenquyhoang20/Embedded-in-Automotive/blob/2edd27a9e8f7b2fbd5b950e6f4574dce14730bcb/%E1%BA%A2nh%20ch%E1%BB%A5p%20m%C3%A0n%20h%C3%ACnh%202024-12-20%20225316.png) 
- MISO: (Master In Slave Out) Chân nhận tín hiệu của Master nối với chân truyền của Slave, vì vậy được cấu hình Input ở Master và Output ở Slave.
- MOSI: (Master Out SLave In) Ngược lại với MISO, cấu hình Input cho Slave và Output cho Master.
- SCK: (Clock) Chân truyền tín hiệu xung đồng bộ từ Master cho Slave, được cấu hình Output cho Master và Input cho Slave.
- CS: (Chip Select) Chân gửi tín hiệu chọn Slave của Master tới các Slave. Cấu hình Output cho Master và Input cho Slave. Có thể có nhiều CS để Master điều khiển nhiều Slave.
  Bước đầu, ta định nghĩa cho 4 chân sử dụng cho SPI:
```
#define SPI_MISO_Pin GPIO_Pin_1
#define SPI_MOSI_Pin GPIO_Pin_2
#define SPI_CS_Pin GPIO_Pin_3
#define SPI_GPIO GPIOA
#define SPI_RCC RCC_APB2Periph_GPIOA
```
Tạo hàm khởi tạo cho SPI:
``` 
void SPI_Init(){
GPIO_WriteBit(SPI_PORT, SPI_SCK, 0);
GPIO_WriteBit(SPI_PORT, SPI_CS, 1);
GPIO_WriteBit(SPI_PORT, SPI_MISO, 0);
GPIO_WriteBit(SPI_PORT, SPI_MOSI, 0);
}
```
Hàm SPI_Init khởi tạo các giá trị cho các chân khi chưa có sự kiện truyền nhận.
- SCK = 0: Clock sẽ ở mức thấp, tùy vào cấu hình CPHA, CPOL mà giá trị này có thể sẽ khác. Ở đây ta mô phỏng đơn giản, khi clock ở mức 1 sẽ lấu mẫu dữ liệu, mức 0 sẽ là chế độ nghỉ.
- CS = 1: Khi Master chưa truyền nhận, CS ở mức 1 cho tất cả các Slave.
- Các chân MISO, MOSI được kéo về 0 ở chế độ nghỉ.
 ### 1.2 SPI software code cho master
   Clock sẽ được tạo bằng hàm delay kết hợp với set/reset tín hiệu trên đường SCK:
```
void Clock()
{
	GPIO_WriteBit(SPI_PORT, SPI_SCK, 1);
	delay(1000);
	GPIO_WriteBit(SPI_PORT, SPI_SCK, 0);
	delay(1000);
}
```
Mỗi khi hàm Clock được gọi, sẽ tạo 1 xung vuông, tín hiệu sẽ được truyền nhận theo clock này.
![image alt](https://github.com/nguyenquyhoang20/Embedded-in-Automotive/blob/d83668584b8565b0d134455056439ac9fc6fb178/%E1%BA%A2nh%20ch%E1%BB%A5p%20m%C3%A0n%20h%C3%ACnh%202024-12-20%20230611.png) 
	Hàm truyền ở master:
```
void SPI_Master_Transmit(uint8_t u8Data){
	uint8_t u8Mask = 0x80;
	uint8_t tempData;
	GPIO_WriteBit(SPI_GPIO, SPI_CS_Pin, Bit_RESET);
	delay(10);
	for(int i=0; i<8; i++){
		tempData = u8Data & u8Mask;
		if(tempData){
			GPIO_WriteBit(SPI_GPIO, SPI_MOSI_Pin, Bit_SET);
			delay(10);
		} else{
			GPIO_WriteBit(SPI_GPIO, SPI_MOSI_Pin, Bit_RESET);
			delay(10);
		}
		u8Data<<=1;
		Clock();
	}
	GPIO_WriteBit(SPI_GPIO, SPI_CS_Pin, Bit_SET);
	delay(10);
}
```
Mô phỏng quá trình truyền nhận:
```
	while(1)
		{	
			for(int i=0; i<7; i++){
			SPI_Master_Transmit(DataTrans[i]);
			delay(5000000);
			}
		}
```
Các byte trong 1 chuỗi DataTrans sẽ được truyền lần lượt bằng hàm SPI_Master_Transmit.
```
uint8_t SPI_SlaveReceive()
{
  uint8_t i = 0;  uint8_t dataReceive=0x00;bool st=0;
  while (digitalRead(SS));
  while (!digitalRead(SCK));
    for(i=0; i<8;i++)
    { if(digitalRead(SCK)){
      while (digitalRead(SCK)) st = digitalRead(MISO);
      dataReceive=dataReceive<<1;
      dataReceive=dataReceive|st;
    }
    while (!digitalRead(SCK));
    }
  return dataReceive;
}
///in main loop
void loop(){
  if(!(digitalRead(SS))){
    dat=SPI_SlaveReceive();
    Serial.println(dat,DEC);
  }
}
```
Ở slave sẽ dựa vào tín hiệu CS và SCK để xác định lệnh truyền nhận từ Master cũng như thời diểm đọc dữ liệu.
## SPI Hardware
STM32F1 có 2 khối SPI, SPI1 ở APB2 và SPI2 ở PAB1. Các khối này được xây dựng các kết nối, driver và các hàm riêng trong bộ thư viện chuẩn.
### 2.1 Cấu hình GPIO cho SPI.
	STM32 cấu hình sẵn các chân dành cho chức năng SPI. 
![image alt](https://github.com/nguyenquyhoang20/Embedded-in-Automotive/blob/8a61614a6cb86cc69eaee3300d1bcc582f27b48c/%E1%BA%A2nh%20ch%E1%BB%A5p%20m%C3%A0n%20h%C3%ACnh%202024-12-20%20223315.png) 
	Ở đây, ví dụ sử dụng SPI1, các chân đã được thiết lập sẵn. Ta sẽ cấu hình cho các chân này. Đầu tiên define các chân với các tên riêng biệt:
```
#define SPI1_NSS 	GPIO_Pin_4
#define SPI1_SCK	GPIO_Pin_5
#define SPI1_MISO 	GPIO_Pin_6
#define SPI1_MOSI 	GPIO_Pin_7
#define SPI1_GPIO 	GPIOA
```
Hàm GPIO config cấu hình các chân của SPI theo từng mode khác nhau:
```
void GPIO_Cofig(){
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = SPI1_NSS| SPI1_SCK| SPI1_MISO| SPI1_MOSI;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(SPI1_GPIO, &GPIO_InitStructure);
}
```
### 2.2 Cấu hình SPI.
Tương tự các ngoại vi khác, các tham số SPI được cấu hình trong Struct SPI_InitTypeDef:
- SPI_Mode: Quy định chế độ hoạt động của thiết bị SPI. 
- SPI_Direction: Quy định kiểu truyền của thiết bị.
- SPI_BaudRatePrescaler: Hệ số chia clock cấp cho Module SPI.
- SPI_CPOL: Cấu hình cực tính của SCK . Có 2 chế độ:
    - SPI_CPOL_Low: Cực tính mức 0 khi SCK không truyền xung.
    - SPI_CPOL_High: Cực tính mức 1 khi SCK không truyền xung.
- SPI_CPHA: Cấu hình chế độ hoạt động của SCK. Có 2 chế độ:
    - SPI_CPHA_1Edge: Tín hiệu truyền đi ở cạnh xung đầu tiên.
    - SPI_CPHA_2Edge: Tín hiệu truyền đi ở cạnh xung thứ hai.
- SPI_DataSize: Cấu hình số bit truyền. 8 hoặc 16 bit.
- SPI_FirstBit: Cấu hình chiều truyền của các bit là MSB hay LSB.
- SPI_CRCPolynomial: Cấu hình số bit CheckSum cho SPI.
- SPI_NSS: Cấu hình chân SS là điều khiển bằng thiết bị hay phần mềm.
Hàm SPI_Config() cấu hình tham số có SPI:
```
void SPI_Config(){
	SPI_InitTypeDef SPI_InitStructure;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	
	SPI_Init(SPI1, &SPI_InitStructure);
	SPI_Cmd(SPI1, ENABLE);
}
```
- Hàm SPI_I2S_SendData(SPI_TypeDef* SPIx, uint16_t Data), tùy vào cấu hình datasize là 8 hay 16 bit sẽ truyền đi 8 hoặc 16 bit dữ liệu. Hàm nhận 2 tham số là bộ SPI sử dụng và data cần truyền.
- Hàm SPI_I2S_ReceiveData(SPI_TypeDef* SPIx) trả về giá trị đọc được trên SPIx. Hàm trả về 8 hoặc 16 bit data.
- Hàm SPI_I2S_GetFlagStatus(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG) trả về giá trị 1 cờ trong thanh ghi của SPI. Các cờ thường được dùng:
    - SPI_I2S_FLAG_TXE: Cờ báo truyền, cờ này sẽ set lên 1 khi truyền xong data trong buffer.
    - SPI_I2S_FLAG_RXNE: Cờ báo nhận, cờ này set lên 1 khi nhận xong data.
    - SPI_I2S_FLAG_BSY: Cờ báo bận,set lên 1 khi SPI đang bận truyền nhận
      
Các hàm truyền nhận có thể viết nhứ sau:
*Vì cấu hình NSS soft nên khi truyền, ta phải chủ động kéo SS xuống Low bằng phần mềm:
```
void SPI_Send1Byte(uint8_t data){
    GPIO_WriteBit(SPI1_GPIO, SPI1_NSS, Bit_RESET);
   
    SPI_I2S_SendData(SPI1, data);
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE)==0);
   
    GPIO_WriteBit(SPI1_GPIO, SPI1_NSS, Bit_SET);
}

uint8_t SPI_Receive1Byte(void){
    uint8_t temp;
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY)==1);
    temp = (uint8_t)SPI_I2S_ReceiveData(SPI1);
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE)==0);
    return temp;
}
``` 
# I2C Sofware & I2C Hardware
## I2C Software
Cấu hình GPIO 
 I2C chỉ sử dụng hai dây để truyền dữ liệu giữa các thiết bị:
- SDA (Serial Data) - đường truyền cho master và slave để gửi và nhận dữ liệu.
- SCL (Serial Clock) - đường mang tín hiệu xung nhịp.
![alt](https://github.com/nguyenquyhoang20/Embedded-in-Automotive/blob/2f6b72e42d3fb5938db705d5178b5945b4582d20/%E1%BA%A2nh%20ch%E1%BB%A5p%20m%C3%A0n%20h%C3%ACnh%202024-12-26%20155145.png) 

Các chân có thể vừa là ngõ vào, vừa là ngõ ra tùy thuộc vào Master và slave khi truyền.
```
#define I2C_SCL GPIO_Pin_6
#define I2C_SDA	GPIO_Pin_7
#define I2C_GPIO GPIOB

void RCC_Config(){
    // Bật đồng hồ cho GPIOB (dùng cho các chân I2C SCL và SDA)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    
    // Bật đồng hồ cho TIM2 (dùng cho bộ đếm thời gian, có thể dùng cho I2C hoặc các tác vụ khác)
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
}

void GPIO_Config(){
    GPIO_InitTypeDef GPIO_InitStructure;
    
    // Bật đồng hồ cho GPIOB (cổng này sẽ dùng cho SDA và SCL)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    // Cấu hình các chân GPIO (SDA và SCL) cho giao thức I2C
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; // Chế độ đầu ra Open-Drain
    GPIO_InitStructure.GPIO_Pin = I2C_SDA | I2C_SCL; // Cấu hình chân SDA và SCL
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // Cấu hình tốc độ của chân GPIO là 50 MHz
    
    // Khởi tạo các chân GPIOB theo cấu hình đã chỉ định
    GPIO_Init(I2C_GPIO, &GPIO_InitStructure);
}
```
## I2C Software code
![alt](https://github.com/nguyenquyhoang20/Embedded-in-Automotive/blob/2f6b72e42d3fb5938db705d5178b5945b4582d20/%E1%BA%A2nh%20ch%E1%BB%A5p%20m%C3%A0n%20h%C3%ACnh%202024-12-26%20155336.png) 

Ở trạng thái không truyền, các đừng SDA, SCL đều ở mức cao:
```
void I2C_Start(){
    WRITE_SDA_1; // Đảm bảo SDA ở mức cao
    WRITE_SCL_1; // Đảm bảo SCL ở mức cao
    delay_us(1); // Đợi một khoảng ngắn
    
    WRITE_SDA_0; // SDA chuyển xuống mức thấp
    delay_us(1);
    WRITE_SCL_0; // Sau đó kéo SCL xuống mức thấp để bắt đầu truyền
    delay_us(1);
}
```
Massage bắt đầu với 1 tín hiệu start: SDA được kéo xuống 0 trong khi SCL vẫn mức cao
	Các macro dưới đây nhằm mục đích đơn giản hóa việc gọi hàm.
 ```
 // Đặt SDA xuống mức thấp (0) để tạo tín hiệu dữ liệu 0
#define WRITE_SDA_0 	GPIO_ResetBits(I2C_GPIO, I2C_SDA)

// Đặt SDA lên mức cao (1) để tạo tín hiệu dữ liệu 1 hoặc giữ SDA ở trạng thái chờ
#define WRITE_SDA_1 	GPIO_SetBits(I2C_GPIO, I2C_SDA)

// Đặt SCL xuống mức thấp (0) để tạo cạnh xuống cho xung nhịp
#define WRITE_SCL_0 	GPIO_ResetBits(I2C_GPIO, I2C_SCL)

// Đặt SCL lên mức cao (1) để tạo cạnh lên cho xung nhịp hoặc giữ SCL ở trạng thái chờ
#define WRITE_SCL_1 	GPIO_SetBits(I2C_GPIO, I2C_SCL)

// Đọc trạng thái mức logic (0 hoặc 1) từ chân SDA để nhận dữ liệu từ thiết bị khác
#define READ_SDA_VAL 	GPIO_ReadInputDataBit(I2C_GPIO, I2C_SDA)
```
Frame truyền bắt đầu bằng tín hiệu Start, Start: SDA kéo xuống 0 trước SCL 1 khoảng delay nhỏ. Kết thúc bằng tín hiệu stop: SCL kéo lên 1 trước SDA 1 khoảng delay nhỏ.
```
// Hàm tạo tín hiệu START cho giao thức I2C
void I2C_Start(){

	WRITE_SCL_1;  	// Đảm bảo SCL (Clock) ở mức cao để chuẩn bị gửi tín hiệu START.
	delay_us(3);	// Trễ nhỏ để tín hiệu ổn định.

	WRITE_SDA_1;    // Đảm bảo SDA (Data) ở mức cao trước khi tạo cạnh xuống để bắt đầu.
	delay_us(3);	// Trễ nhỏ để tín hiệu ổn định.

	WRITE_SDA_0;	// Kéo SDA xuống mức thấp (0) trong khi SCL vẫn ở mức cao -> tạo tín hiệu START.
	delay_us(3);	// Trễ để đảm bảo Slave nhận biết tín hiệu START.

	WRITE_SCL_0;	// Kéo SCL xuống mức thấp để tiếp tục truyền dữ liệu sau tín hiệu START.
	delay_us(3);	// Trễ nhỏ để tín hiệu ổn định.
}

// Hàm tạo tín hiệu STOP cho giao thức I2C
void I2C_Stop(){

	WRITE_SDA_0;	// Đảm bảo SDA ở mức thấp (0) trước khi tạo tín hiệu dừng.
	delay_us(3);	// Trễ nhỏ để tín hiệu ổn định.

	WRITE_SCL_1; 	// Đặt SCL lên mức cao trước khi đưa SDA lên mức cao -> tạo tín hiệu STOP.
	delay_us(3);	// Trễ nhỏ để tín hiệu ổn định.

	WRITE_SDA_1;	// Kéo SDA lên mức cao (1) khi SCL đang ở mức cao -> tạo tín hiệu STOP.
	delay_us(3);	// Trễ để đảm bảo Slave nhận biết tín hiệu STOP.
}
```
### Hàm truyền: 
Hàm truyền sẽ truyền lần lượt 8 bit trong byte dữ liệu.
	- Truyền 1 bit.
	- Tạo clock;
	- Dịch 1 bit.
- Chờ nhận lại ACK ở xung thứ 9.
![alt](https://github.com/nguyenquyhoang20/Embedded-in-Automotive/blob/2f6b72e42d3fb5938db705d5178b5945b4582d20/%E1%BA%A2nh%20ch%E1%BB%A5p%20m%C3%A0n%20h%C3%ACnh%202024-12-26%20161459.png)
```
// Hàm ghi dữ liệu 8-bit vào bus I2C
status I2C_Write(uint8_t u8Data) {	
	uint8_t i;          // Biến đếm vòng lặp.
	status stRet;       // Biến trạng thái trả về (OK hoặc NOT_OK).

	// Vòng lặp để ghi từng bit của byte dữ liệu (8 bit).
	for(int i = 0; i < 8; i++) {		
		// Kiểm tra bit cao nhất (MSB) của dữ liệu.
		if (u8Data & 0x80) {	// Nếu bit này là 1
			WRITE_SDA_1;      // Đặt SDA ở mức cao.
		} else {              // Nếu bit này là 0
			WRITE_SDA_0;      // Đặt SDA ở mức thấp.
		}

		delay_us(3);		// Trễ nhỏ để đảm bảo tín hiệu ổn định.

		WRITE_SCL_1;		// Đưa SCL lên mức cao -> Chốt dữ liệu vào Slave.
		delay_us(5);		// Giữ mức cao để Slave nhận dữ liệu.

		WRITE_SCL_0;		// Đưa SCL xuống mức thấp để chuẩn bị bit tiếp theo.
		delay_us(2);		// Trễ nhỏ để tín hiệu ổn định.

		u8Data <<= 1;		// Dịch trái dữ liệu 1 bit để chuẩn bị gửi bit tiếp theo.
	}

	// Tạo tín hiệu nhận ACK từ Slave.
	WRITE_SDA_1;			// Nhả SDA để chuyển sang chế độ đọc (Input Mode).
	delay_us(3);			// Trễ nhỏ để tín hiệu ổn định.

	WRITE_SCL_1;			// Đưa SCL lên mức cao để Slave gửi ACK.
	delay_us(3);			// Giữ mức cao để chốt trạng thái ACK.

	// Đọc ACK từ Slave.
	if (READ_SDA_VAL) {	    // Nếu SDA vẫn ở mức cao -> không có ACK (NACK).
		stRet = NOT_OK;		// Trả về trạng thái thất bại.
	} else {                // Nếu SDA được kéo xuống thấp -> có ACK.
		stRet = OK;			// Trả về trạng thái thành công.
	}

	delay_us(2);			// Trễ nhỏ để tín hiệu ổn định.
	WRITE_SCL_0;			// Đưa SCL xuống mức thấp để kết thúc quá trình ACK.
	delay_us(5);			// Trễ nhỏ để ổn định tín hiệu trước khi kết thúc.

	return stRet;			// Trả về kết quả quá trình ghi dữ liệu.
}
```
Giải thích chi tiết về hoạt động:
1.Ghi dữ liệu (Write Byte):
- Vòng lặp chạy 8 lần, mỗi lần xử lý 1 bit từ dữ liệu đầu vào u8Data.
- Bit cao nhất (MSB) được kiểm tra và ghi vào SDA.
- SCL được đưa lên cao để chốt dữ liệu vào Slave.
2.Nhận ACK (Acknowledgment):
  
- Sau khi ghi dữ liệu, Master nhả SDA (đặt SDA lên mức cao) để Slave gửi tín hiệu ACK.
- Slave sẽ kéo SDA xuống mức thấp để xác nhận đã nhận dữ liệu.
- Nếu SDA vẫn ở mức cao, tức là không có ACK (NACK), trả về NOT_OK.
  
3.Tín hiệu thời gian (Timing):
- Các lệnh delay_us() được sử dụng để tạo trễ theo yêu cầu của giao thức I2C, đảm bảo tín hiệu ổn định và tuân thủ tốc độ truyền dữ liệu.
### Hàm nhận:
Hàm nhận sẽ nhận lần lượt 8 bit trong byte dữ liệu.
- Kéo SDA lên 1
	- Đọc data trên SDA, ghi vào biến.
	- Dịch 1 bit.
- Gửi lại 1 tín hiệu ACK ở xung thứ 9
![alt](https://github.com/nguyenquyhoang20/Embedded-in-Automotive/blob/2f6b72e42d3fb5938db705d5178b5945b4582d20/%E1%BA%A2nh%20ch%E1%BB%A5p%20m%C3%A0n%20h%C3%ACnh%202024-12-26%20161509.png)

```
// Hàm đọc dữ liệu 8-bit từ bus I2C.
uint8_t I2C_Read(ACK_Bit _ACK) {	
	uint8_t i;						// Biến đếm vòng lặp.
	uint8_t u8Ret = 0x00;			// Biến để lưu dữ liệu nhận được, ban đầu là 0.

	WRITE_SDA_1;					// Nhả SDA để chuyển sang chế độ đọc (Input Mode).
	delay_us(3);					// Trễ nhỏ để tín hiệu ổn định.

	// Vòng lặp đọc từng bit của dữ liệu từ SDA.
	for (i = 0; i < 8; ++i) {		
		u8Ret <<= 1;				// Dịch trái 1 bit để chuẩn bị nhận bit tiếp theo.

		WRITE_SCL_1;				// Đưa SCL lên mức cao -> đọc dữ liệu từ SDA.
		delay_us(3);				// Giữ mức cao để dữ liệu ổn định.

		if (READ_SDA_VAL) {			// Đọc trạng thái SDA.
			u8Ret |= 0x01;			// Nếu SDA ở mức cao -> ghi 1 vào bit thấp nhất.
		}

		delay_us(2);				// Trễ nhỏ để tín hiệu ổn định.
		WRITE_SCL_0;				// Đưa SCL xuống mức thấp để kết thúc việc đọc bit.
		delay_us(5);				// Trễ nhỏ trước khi đọc bit tiếp theo.
	}

	// Gửi tín hiệu ACK hoặc NACK.
	if (_ACK) {						// Nếu _ACK là 1 -> gửi ACK (Master chấp nhận dữ liệu).
		WRITE_SDA_0;				// Đặt SDA ở mức thấp để gửi ACK.
	} else {						// Nếu _ACK là 0 -> gửi NACK (Master không chấp nhận thêm dữ liệu).
		WRITE_SDA_1;				// Đặt SDA ở mức cao để gửi NACK.
	}
	delay_us(3);					// Trễ nhỏ để tín hiệu ổn định.

	WRITE_SCL_1;					// Đưa SCL lên mức cao để chốt trạng thái ACK/NACK.
	delay_us(5);					// Giữ mức cao để Slave nhận tín hiệu.
	WRITE_SCL_0;					// Đưa SCL xuống mức thấp để kết thúc chu kỳ ACK/NACK.
	delay_us(5);					// Trễ nhỏ trước khi kết thúc quá trình đọc.

	return u8Ret;					// Trả về dữ liệu đã đọc được từ bus I2C.
}
```
Giải thích chi tiết về hoạt động:
1.Chế độ đọc dữ liệu:
- Đặt SDA ở mức cao để chuyển sang chế độ đọc dữ liệu từ Slave.
- Chạy vòng lặp 8 lần, mỗi lần đọc 1 bit từ SDA.
- SCL được đưa lên mức cao để chốt dữ liệu từ Slave và xuống thấp để chuẩn bị đọc bit tiếp theo.
2.Xử lý dữ liệu đọc được:
- Dịch trái dữ liệu hiện tại để mở chỗ cho bit mới nhận được.
- Nếu SDA ở mức cao, ghi 1 vào bit thấp nhất của dữ liệu.
3.Gửi tín hiệu ACK/NACK:
- Nếu _ACK = 1, Master gửi ACK để báo hiệu đã nhận dữ liệu thành công và yêu cầu dữ liệu tiếp theo.
- Nếu _ACK = 0, Master gửi NACK để báo hiệu không yêu cầu thêm dữ liệu.
4.Tín hiệu thời gian (Timing):
Các lệnh delay_us() được sử dụng để tạo trễ phù hợp với chuẩn I2C, đảm bảo tín hiệu ổn định.
## I2C Hardware 
### Cấu hình GPIO 
Các chân của từng bộ I2C được cài đặt sẵn trong datasheet.
```
#define I2C_SCL GPIO_Pin_6
#define I2C_SDA	GPIO_Pin_7
#define I2C1_GPIO GPIOB
```
![alt](https://github.com/nguyenquyhoang20/Embedded-in-Automotive/blob/2f6b72e42d3fb5938db705d5178b5945b4582d20/%E1%BA%A2nh%20ch%E1%BB%A5p%20m%C3%A0n%20h%C3%ACnh%202024-12-26%20163339.png)

- SCL: Output
- SDA: Input/Output
- Vì có trở kéo lên nên sẽ hoạt động ở chế độ OD.
![alt](https://github.com/nguyenquyhoang20/Embedded-in-Automotive/blob/2f6b72e42d3fb5938db705d5178b5945b4582d20/%E1%BA%A2nh%20ch%E1%BB%A5p%20m%C3%A0n%20h%C3%ACnh%202024-12-26%20163745.png)


```
void GPIO_Config(void) {
    // Tạo một biến cấu trúc để lưu cấu hình cho GPIO
    GPIO_InitTypeDef GPIO_InitStructure;

    // Bật xung clock cho GPIO Port B để có thể sử dụng các chân của nó
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    // Chọn các chân cần cấu hình: PB6 và PB7
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; 
    
    // Đặt chế độ chân là Alternate Function Open-Drain (AF_OD)
    // - AF (Alternate Function): Chân hoạt động với chức năng thay thế, ở đây là I2C
    // - OD (Open-Drain): Chân chỉ có thể kéo xuống mức thấp (0) và cần điện trở kéo lên để tạo mức cao (1)
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;

    // Đặt tốc độ chuyển trạng thái tối đa của chân là 50MHz
    // Tốc độ này đảm bảo giao tiếp ổn định cho I2C
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    // Áp dụng cấu hình đã thiết lập cho các chân PB6 và PB7 thuộc Port B
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}
``` 
### Cấu hình I2C
Tương tự các ngoại vi khác, các tham số I2C được cấu hình trong Struct I2C_InitTypeDef:

- **I2C_Mode:** Cấu hình chế độ hoạt động cho I2C:
	- **I2C_Mode_I2C:** Chế độ I2C FM(Fast Mode);
	- **I2C_Mode_SMBusDevice&I2C_Mode_SMBusHost:** Chế độ SM(Slow Mode).
- **I2C_ClockSpeed:** Cấu hình clock cho I2C, tối đa 100khz với SM và 400khz ở FM.
- **I2C_DutyCycle:** Cấu hình chu kì nhiệm vụ của xung:
	- **I2C_DutyCycle_2:** Thời gian xung thấp/ xung cao =2;
	- **I2C_DutyCycle_16_9:** Thời gian xung thấp/ xung cao =16/9;
- **I2C_OwnAddress1:** Cấu hình địa chỉ slave.
- **I2C_Ack:** Cấu hình ACK, có sử dụng ACK hay không.
- **I2C_AcknowledgedAddress:** Cấu hình số bit địa chỉ. 7 hoặc 10 bit
- Hàm**I2C_Send7bitAddress(I2C_TypeDef* I2Cx, uint8_t Address, uint8_t I2C_Direction)**, gửi đi 7 bit address để xác định slave cần giao tiếp. Hướng truyền được xác định bởi I2C_Direction để thêm bit RW.
- Hàm**I2C_SendData(I2C_TypeDef* I2Cx, uint8_t Data)** gửi đi 8 bit data.
- Hàm**I2C_ReceiveData(I2C_TypeDef* I2Cx)** trả về 8 bit data.
- Hàm**I2C_CheckEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT)** trả về kết quả kiểm tra I2C_EVENT tương ứng:
- Hàm**I2C_CheckEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT)** trả về kết quả kiểm tra I2C_EVENT tương ứng:
	- **I2C_EVENT_MASTER_MODE_SELECT:** Đợi Bus I2C về chế độ rảnh.
	- **I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED:** Đợi xác nhận của Slave với yêu cầu ghi của Master.
	- **I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED:** Đợi xác nhận của Slave với yêu cầu đọc của Master.
	- **I2C_EVENT_MASTER_BYTE_TRANSMITTED:** Đợi truyền xong 1 byte data từ Master.
	- **I2C_EVENT_MASTER_BYTE_RECEIVED:** Đợi Master nhận đủ 1 byte data.

Bắt đầu truyền nhận, bộ I2C sẽ tạo 1 tín hiệu start. Đợi tín hiệu báo Bus sẵn sàng.
![alt](https://github.com/nguyenquyhoang20/Embedded-in-Automotive/blob/92ca4bd119a9909b7cd7f297f17ff1aba8ae9a0e/%E1%BA%A2nh%20ch%E1%BB%A5p%20m%C3%A0n%20h%C3%ACnh%202024-12-26%20173449.png)

- Gửi 7 bit địa chỉ để xác định slave. Đợi Slave xác nhận.
```
I2C_GenerateSTART(I2C1, ENABLE);
// Gửi tín hiệu Start để bắt đầu giao tiếp I2C. 
// I2C1 là I2C interface bạn đang sử dụng và ENABLE cho phép tạo tín hiệu Start.

while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
// Chờ cho đến khi I2C chuyển sang chế độ master, tức là thiết bị đang làm chủ giao tiếp.
// I2C_EVENT_MASTER_MODE_SELECT là một sự kiện flag cho biết master đã sẵn sàng.

I2C_Send7bitAddress(I2C1, 0x44, I2C_Direction_Transmitter);
// Gửi địa chỉ của thiết bị I2C (0x44) và hướng truyền là **Transmitter** (gửi dữ liệu).
// Địa chỉ 0x44 được gửi theo chuẩn 7-bit (không phải 8-bit) và chỉ định rằng thiết bị này sẽ truyền dữ liệu.

while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
// Chờ cho đến khi chế độ truyền (transmitter mode) của master được chọn. 
// Đây là sự kiện cho biết rằng master đã sẵn sàng để truyền dữ liệu.
```
- Gửi/đọc các byte data, Đợi truyền xong.
```
void Send_I2C_Data(uint8_t data)
{
    I2C_SendData(I2C1, data);
    // Gửi dữ liệu (byte) qua I2C1. 
    // Dữ liệu cần truyền được chứa trong biến `data` và được gửi tới slave thông qua I2C1.
    
    // wait for the data transmitted flag
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    // Kiểm tra xem byte đã được truyền xong chưa bằng cách kiểm tra sự kiện `I2C_EVENT_MASTER_BYTE_TRANSMITTED`.
    // Nếu dữ liệu chưa được truyền xong, chương trình sẽ đợi cho đến khi sự kiện này xảy ra.
}

uint8_t Read_I2C_Data(){
    
    uint8_t data = I2C_ReceiveData(I2C1);
    // Nhận dữ liệu (byte) từ I2C1. Dữ liệu nhận được sẽ được lưu vào biến `data`.
    
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
    // Chờ cho đến khi byte dữ liệu được nhận hoàn toàn.
    // Kiểm tra sự kiện `I2C_EVENT_MASTER_BYTE_RECEIVED` để xác nhận rằng dữ liệu đã được nhận thành công.
    
    return data;
    // Trả về byte dữ liệu đã nhận từ I2C1.
}
```
- Sau đó kết thúc bằng tín hiệu stop.








	





















