# Embedded-in-Automotive
# Interrupt - Timer
## Định nghĩa ngắt
gắt là 1 sự kiện khẩn cấp xảy ra trong hay ngoài vi điều khiển. Nó yêu cầu MCU phải dừng chương trình chính và thực thi chương trình ngắt (trình phục vụ ngắt).
## Các ngắt thông dụng
Mỗi ngắt sẽ có 1 trình phục vụ ngắt riêng
Trình phục vụ ngắt (Interrupt Service Routine - ISR) là một đoạn chương trình được thực hiện khi ngắt xảy ra.
Địa chỉ trong bộ nhớ của ISR được gọi là vector ngắt
## Các ngắt thông dụng 
### Ngắt ngoài
#### LOW (Mức thấp)
Mô tả: Ngắt xảy ra liên tục khi nút bấm được giữ (chân GPIO ở mức logic thấp).
Tình huống: Khi nhấn nút, LED sẽ sáng liên tục cho đến khi nhả nút.
Ví dụ thực tế:
Nút bấm nối chân GPIO với mức thấp (GND) khi nhấn.
```// ISR cho ngắt LOW
void GPIO_ISR() {
    turnOnLED(); // Bật LED khi nút bấm giữ.
}
Hiệu quả: LED bật liên tục khi nhấn giữ nút.
#### HIGH (Mức cao)
Mô tả: Ngắt xảy ra liên tục khi chân GPIO ở mức logic cao.
Tình huống: LED chỉ sáng khi nút được giữ ở trạng thái logic cao.
Ví dụ thực tế:
Nút bấm nối chân GPIO với mức cao (VCC) khi nhấn.

```// ISR cho ngắt HIGH
void GPIO_ISR() {
    turnOnLED(); // Bật LED khi nút giữ ở mức cao.
}
Hiệu quả: LED bật liên tục khi nút được nhấn giữ.
#### RISING (Chuyển từ thấp lên cao)
Mô tả: Ngắt xảy ra một lần khi trạng thái trên chân GPIO chuyển từ thấp lên cao.
Tình huống: LED sáng một lần ngay khi nút được nhấn xuống.
Ví dụ thực tế:
Khi nhấn nút, trạng thái chân GPIO chuyển từ thấp (0V) lên cao (3.3V hoặc 5V).
```// ISR cho ngắt RISING
void GPIO_ISR() {
    toggleLED(); // Đổi trạng thái LED (bật/tắt mỗi lần nhấn nút).
}
Hiệu quả: LED đổi trạng thái mỗi khi nhấn nút.
#### RISING (Chuyển từ thấp lên cao)
Mô tả: Ngắt xảy ra một lần khi trạng thái trên chân GPIO chuyển từ thấp lên cao.
Tình huống: LED sáng một lần ngay khi nút được nhấn xuống.
Ví dụ thực tế:
Khi nhấn nút, trạng thái chân GPIO chuyển từ thấp (0V) lên cao (3.3V hoặc 5V).

```// ISR cho ngắt RISING
void GPIO_ISR() {
    toggleLED(); // Đổi trạng thái LED (bật/tắt mỗi lần nhấn nút).
}
Hiệu quả: LED đổi trạng thái mỗi khi nhấn nút.
### Ngắt timer
Ngắt Timer là một loại ngắt trong vi điều khiển xảy ra khi bộ đếm thời gian (Timer) đạt đến một giá trị xác định trước (thường là giá trị tràn hoặc so sánh). Ngắt Timer được sử dụng để thực hiện các tác vụ theo chu kỳ mà không cần CPU liên tục theo dõi trạng thái Timer.
ví dụ đơn giản: Điều khiển LED nhấp nháy bằng ngắt Timer
Giả sử:

LED được nối vào chân GPIO.
Bạn muốn LED nhấp nháy (bật/tắt) mỗi giây bằng ngắt Timer.
1. Cấu hình ngắt Timer:
Sử dụng Timer 0 của vi điều khiển.
Thiết lập Timer đếm từ 0 và tạo ngắt khi đạt đến giá trị tràn.

```#include <avr/io.h>        // Thư viện cho vi điều khiển AVR
#include <avr/interrupt.h> // Thư viện hỗ trợ ngắt

#define LED_PIN PB0        // LED nối với chân PB0

void setup_timer() {
    // Cấu hình Timer 0
    TCCR0A = 0;                    // Chế độ Normal (đếm thông thường)
    TCCR0B |= (1 << CS02) | (1 << CS00); // Prescaler = 1024
    TIMSK0 |= (1 << TOIE0);        // Cho phép ngắt tràn Timer 0
    TCNT0 = 0;                     // Đặt giá trị đếm ban đầu là 0
}

void setup_gpio() {
    DDRB |= (1 << LED_PIN);        // Cấu hình PB0 là ngõ ra
}

ISR(TIMER0_OVF_vect) {
    // ISR cho ngắt tràn Timer 0
    PORTB ^= (1 << LED_PIN);       // Đổi trạng thái LED (Bật/Tắt)
    TCNT0 = 0;                     // Đặt lại giá trị Timer
}

int main() {
    setup_gpio();                  // Cấu hình chân GPIO
    setup_timer();                 // Cấu hình Timer
    sei();                         // Cho phép ngắt toàn cục

    while (1) {
        // Chương trình chính (không cần làm gì)
    }
}

Kết quả:
LED sẽ nhấp nháy liên tục mà không cần CPU kiểm tra thủ công, giúp tiết kiệm tài nguyên hệ thống.
### Ngắt truyền thông
Ngắt truyền thông là một loại ngắt xảy ra khi thiết bị giao tiếp (như UART, SPI, I2C) hoàn thành việc gửi hoặc nhận dữ liệu. Khi có dữ liệu cần xử lý (ví dụ: một byte vừa được nhận qua cổng truyền thông), một ngắt sẽ được kích hoạt, và CPU sẽ tạm dừng chương trình chính để xử lý sự kiện này.
Ngắt truyền thông giúp tránh việc CPU phải liên tục kiểm tra trạng thái của cổng truyền thông (polling), giúp hệ thống hoạt động hiệu quả hơn.

Ví dụ đơn giản: Nhận dữ liệu qua UART bằng ngắt
Mô tả:
Một vi điều khiển nhận dữ liệu từ máy tính qua giao tiếp UART (RS-232).
Mỗi khi một byte dữ liệu được nhận, ngắt UART sẽ được kích hoạt để lưu dữ liệu vào bộ đệm (buffer).

```#include <avr/io.h>
#include <avr/interrupt.h>

#define BUFFER_SIZE 64
volatile char rx_buffer[BUFFER_SIZE]; // Bộ đệm nhận dữ liệu
volatile uint8_t rx_index = 0;        // Chỉ số lưu vị trí trong bộ đệm

void uart_init(unsigned int baudrate) {
    // Cấu hình UART với tốc độ baudrate
    unsigned int ubrr = F_CPU / 16 / baudrate - 1; // Tính giá trị UBRR
    UBRR0H = (unsigned char)(ubrr >> 8);          // Cấu hình phần cao
    UBRR0L = (unsigned char)ubrr;                 // Cấu hình phần thấp
    UCSR0B = (1 << RXEN0) | (1 << RXCIE0);        // Kích hoạt nhận và ngắt RX
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);       // Giao thức 8N1 (8-bit, không parity, 1 stop bit)
}

ISR(USART_RX_vect) {
    // Ngắt nhận dữ liệu UART
    char received_char = UDR0;                 // Đọc byte vừa nhận từ thanh ghi dữ liệu UART
    if (rx_index < BUFFER_SIZE - 1) {          // Kiểm tra bộ đệm còn chỗ
        rx_buffer[rx_index++] = received_char; // Lưu dữ liệu vào bộ đệm
    }
}

int main() {
    uart_init(9600); // Khởi tạo UART với tốc độ 9600 baud
    sei();           // Cho phép ngắt toàn cục

    while (1) {
        // Xử lý khác hoặc chờ đợi dữ liệu (bộ đệm tự nhận dữ liệu qua ngắt)
    }
}
Giải thích chi tiết:
Cấu hình UART:

UBRR0H và UBRR0L: Thiết lập tốc độ baud (ví dụ: 9600 baud).
UCSR0B: Kích hoạt chế độ nhận dữ liệu (RX) và ngắt nhận dữ liệu (RXCIE0).
UCSR0C: Đặt giao thức truyền thông 8-bit dữ liệu, không parity, 1 stop bit.
Ngắt nhận dữ liệu (USART_RX_vect):

Ngắt này xảy ra khi một byte dữ liệu mới được nhận vào qua UART.
UDR0: Thanh ghi chứa byte dữ liệu vừa nhận. Giá trị này được lưu vào bộ đệm rx_buffer.
Vòng lặp chính:

CPU tiếp tục thực thi các tác vụ khác trong vòng lặp chính mà không phải bận tâm đến việc nhận dữ liệu.
Khi có dữ liệu mới, ngắt tự động xử lý và lưu dữ liệu vào bộ đệm.
