typedef unsigned int u32;
typedef unsigned short int u16;
typedef signed int s32;
typedef unsigned char u8;
typedef signed char s8;

#define SIZE 2

typedef struct emp_attand{
  u8 flag;
  s8 name[15];
  s8 rollno[12];
  s8 in_time[10];
  s8 out_time[10];
}EMP;
extern s8 RO_NO[12];
extern s8 time[4];
extern EMP SD[SIZE];

/*UART0 DRIVER DEF*/
extern void uart0_init(int baud);
extern void uart0_tx(u8 data);
extern u8 uart0_rx(void);
extern void uart0_tx_string(s8 *ptr);
extern void uart0_rx_string(s8* ptr,u8 max_bytes);
extern void uart0_tx_integer(s32 num);
extern void uart0_tx_float(float num);
extern void uart0_tx_hex(u8 data);

/*LCD DRIVER DEF*/
extern void lcd_init(void);
extern void lcd_data(u8 data);
extern void lcd_cmd(u8 data);
extern void delay_ms(u32 ms);
extern void lcd_string(s8 *ptr);

/*I2C DRIVER DEF*/
extern void i2c_init(void);
extern void i2c_byte_write_frame(u8 sa,u8 mr,u8 data);
extern u8 i2c_byte_read_frame(u8 sa,u8 mr);
extern void i2c_slave_detect(void);
extern void i2c_page_write_frame(u8 sa,u8 mr,u8 *data);
extern void i2c_page_read_frame(u8 sa,u8 mr);
extern void i2c_eeprom_write_frame(u8 sa,u16 mr,u8 data);
extern u8 i2c_eeprom_read_frame(u8 sa,u16 mr);
extern void i2c_eeprompage_write_frame(u8 sa,u16 mr,u8 * ptr);
extern void i2c_eeprompage_read_frame(u8 sa,u16 mr);

/*RFID PRO FUN DEF*/
extern u32 menu_display(void);
extern void add_details(u32);
extern void run_RFID(void);
extern void show_details(void);
extern void RFID_rx_string(EMP * ptr);
extern void hours_worked(void);
extern void set_time(void);

